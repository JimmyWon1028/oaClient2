#pragma once

namespace oa {
//2026.11.17 by codex, observe only the current trusted main document and reuse its existing OACS socket.
inline constexpr char kDesktopHelperInstall[] = R"JS(
(function(epoch) {
  if (window.__oaPet) window.__oaPet.stop();
  const send = window.oaPetSend;
  if (typeof send !== 'function') return;
  let stopped = false, suspended = false, seenLogout = false, socket = null, abort = null;
  let hookedGlobal = null, originalState, originalLogout, wrappedLogout;
  const emit = (body) => { if (!stopped) send(JSON.stringify({epoch, ...body})); };
  function snapshot() {
    const g = window.$g || {};
    const logged = g.isLogin === true;
    if (!logged) { seenLogout = true; if (abort) abort.abort(); }
    if (logged && seenLogout) { suspended = false; seenLogout = false; }
    return {
      logged: logged && !suspended,
      api: logged && typeof g.api_root === 'string' ? g.api_root : '',
      user: logged && g.login_user ? String(g.login_user.userid || '') : '',
      database: logged ? String(g.last_select_database || '') : ''
    };
  }
  function state() { const data = snapshot(); emit({kind: 'state', ...data}); return data; }
  const wake = (message) => {
    if (!message || message.act === 'desktop-helper') emit({kind: 'wake', ...snapshot()});
  };
  const reconnect = () => wake();
  function detach() {
    if (socket) {
      socket.removeListener('notification', wake);
      socket.removeListener('connect', reconnect);
      socket = null;
    }
  }
  function poll() {
    if (stopped) return;
    const g = window.$g;
    if (g && hookedGlobal !== g) {
      const descriptor = Object.getOwnPropertyDescriptor(g, 'isLogin');
      if (descriptor && descriptor.configurable && 'value' in descriptor) {
        hookedGlobal = g;
        originalState = descriptor;
        let value = g.isLogin;
        Object.defineProperty(g, 'isLogin', {
          configurable: true, enumerable: descriptor.enumerable,
          get: () => value,
          set: (next) => { value = next; state(); }
        });
      }
    }
    if (typeof window.logout === 'function' && window.logout !== wrappedLogout) {
      originalLogout = window.logout;
      const original = originalLogout;
      wrappedLogout = function(...args) {
        suspended = true;
        if (abort) abort.abort();
        state();
        return original.apply(this, args);
      };
      window.logout = wrappedLogout;
    }
    const active = g && g.isLogin === true ? g.chatHub : null;
    if (active !== socket) {
      detach();
      if (active && typeof active.on === 'function' && typeof active.removeListener === 'function') {
        socket = active;
        socket.on('notification', wake);
        socket.on('connect', reconnect);
      }
    }
    state();
  }
  async function connect(api, identity) {
    if (abort) abort.abort();
    const controller = new AbortController();
    abort = controller;
    try {
      const headers = {'Accept': 'application/json', 'Content-Type': 'application/json'};
      const cookie = document.cookie.split('; ').find(item => item.startsWith('XSRF-TOKEN='));
      if (cookie) headers['X-XSRF-TOKEN'] = decodeURIComponent(cookie.slice(11));
      const response = await fetch(api + 'desktop-helper/connect', {
        method: 'POST', credentials: 'include', redirect: 'error', cache: 'no-store',
        headers, body: '{}', signal: controller.signal
      });
      if (!response.ok) { emit({kind: 'connect-error', identity, status: response.status}); return; }
      const grant = await response.json();
      state();
      if (!controller.signal.aborted) emit({kind: 'grant', identity, grant});
    } catch (_) {
      if (!controller.signal.aborted) emit({kind: 'connect-error', identity, status: 0});
    }
  }
  function open(order) {
    const g = window.$g || {};
    if (!snapshot().logged) return;
    for (const key of ['ctrlBSI020010', 'ctrlMDL_BSI020010']) {
      if (g[key] && ['Insert', 'Modify'].includes(g[key].formState)) {
        emit({kind: 'editing'});
        if (typeof window.notice === 'function') notice('詢報價單尚在編輯，請先儲存或取消後再點通知。', 'warning');
        return;
      }
    }
    if (typeof window.openFormById === 'function') {
      openFormById('BSI020010', false, {qryfld: 'quano', qryval: order});
      emit({kind: 'opened'});
    }
  }
  function stop() {
    stopped = true;
    if (abort) abort.abort();
    detach();
    if (window.logout === wrappedLogout) window.logout = originalLogout;
    if (hookedGlobal && originalState) {
      const value = hookedGlobal.isLogin;
      Object.defineProperty(hookedGlobal, 'isLogin', {...originalState, value});
    }
  }
  Object.defineProperty(window, '__oaPet', {
    configurable: true, value: {poll, connect, open, stop}
  });
  poll();
})
)JS";
}

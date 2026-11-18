const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const {EventEmitter} = require('node:events');
const header = fs.readFileSync('src/app/desktop_helper_script.h', 'utf8');
const install = header.split('R"JS(')[1].split(')JS"')[0];
let checks = 0;
function check(value, label) { assert.ok(value, label); console.log('PASS ' + label); checks++; }
async function run() {
  const messages = [], calls = [], socket = new EventEmitter();
  const context = {
    $g: {isLogin: false, api_root: 'https://current.invalid/', login_user: {userid: 'synthetic'}, last_select_database: 'db-a', chatHub: socket},
    oaPetSend: data => messages.push(JSON.parse(data)),
    document: {cookie: ''}, AbortController,
    logout() { calls.push('logout'); },
    openFormById(...args) { calls.push(args); },
    notice() { calls.push('notice'); },
    fetch: async () => ({ok: true, json: async () => ({token: 'synthetic-memory-only'})})
  };
  context.window = context;
  vm.createContext(context);
  vm.runInContext(install + '(7);', context);
  check(messages.at(-1).logged === false, 'startup does not treat document readiness as login');
  context.$g.isLogin = true;
  check(messages.at(-1).logged === true && messages.at(-1).epoch === 7, 'successful login is observed synchronously');
  context.__oaPet.poll();
  check(socket.listenerCount('notification') === 1, 'reuse existing socket without duplicate notification listeners');
  socket.emit('notification', {act: 'todo'});
  check(messages.at(-1).kind === 'state', 'unrelated notifications do not trigger order reads');
  socket.emit('notification', {act: 'desktop-helper'});
  check(messages.at(-1).kind === 'wake' && !('token' in messages.at(-1)), 'OACS wake carries no order or token');
  socket.emit('connect');
  check(messages.at(-1).kind === 'wake', 'socket reconnect triggers cursor catch-up');
  const secondSocket = new EventEmitter();
  context.$g.chatHub = secondSocket;
  context.__oaPet.poll();
  check(socket.listenerCount('notification') === 0 && secondSocket.listenerCount('notification') === 1,
    'replaced socket detaches old listeners');
  context.$g.ctrlBSI020010 = {formState: 'Modify'};
  context.__oaPet.open('ORDER-A');
  check(messages.at(-1).kind === 'editing' && calls.at(-1) === 'notice', 'edited target order is never refreshed or switched');
  context.$g.ctrlBSI020010.formState = 'Query';
  context.__oaPet.open('ORDER-A');
  check(calls.at(-1)[0] === 'BSI020010' && calls.at(-1)[2].qryfld === 'quano' && calls.at(-1)[2].qryval === 'ORDER-A',
    'open the customer quotation by quano through the existing form opener');
  context.$g.ctrlMDL_BSI020010 = {formState: 'Insert'};
  context.__oaPet.open('ORDER-A');
  check(messages.at(-1).kind === 'editing', 'protect an unsaved customer quotation in a modal form');
  context.$g.ctrlMDL_BSI020010.formState = 'Query';
  let pending;
  context.fetch = () => new Promise(resolve => { pending = resolve; });
  const request = context.__oaPet.connect('https://current.invalid/', 'old-binding');
  context.logout();
  check(messages.at(-1).logged === false && calls.at(-1) === 'logout', 'logout hides immediately and calls original implementation once');
  pending({ok: true, json: async () => ({token: 'never-deliver'})});
  await request;
  check(!messages.some(message => message.kind === 'grant'), 'late grant after logout is aborted');
  context.$g.isLogin = false;
  context.$g.isLogin = true;
  check(messages.at(-1).logged === true, 'fresh successful login re-enables observation');
  const count = messages.length;
  context.__oaPet.stop();
  context.__oaPet.poll();
  check(messages.length === count && secondSocket.listenerCount('notification') === 0,
    'stop removes listeners and prevents subsequent native messages');
  check(Object.getOwnPropertyDescriptor(context.$g, 'isLogin').value === true,
    'stop restores original state property without changing website state');
  vm.runInContext(install + '(8);', context);
  check(messages.at(-1).epoch === 8, 'new document observer uses its own generation');
  let resumePending;
  context.fetch = () => new Promise(resolve => { resumePending = resolve; });
  const sleepingRequest = context.__oaPet.connect('https://current.invalid/', 'same-binding');
  vm.runInContext(install + '(9);', context);
  check(messages.at(-1).epoch === 9 && messages.at(-1).logged === true && secondSocket.listenerCount('notification') === 1,
    'resume reinstalls the observer using current login state without duplicate socket listeners');
  resumePending({ok: true, json: async () => ({token: 'synthetic-stale-before-resume'})});
  await sleepingRequest;
  check(!messages.some(message => message.kind === 'grant' && message.epoch === 8),
    'late pre-resume grant is aborted when the observer generation changes');
  context.__oaPet.stop();
  console.log(`${checks} checks, 0 failures`);
}
run().catch(error => { console.error(error); process.exitCode = 1; });

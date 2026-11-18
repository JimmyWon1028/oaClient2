const http = require('node:http');
const crypto = require('node:crypto');
const fs = require('node:fs');
const path = require('node:path');

//2026.11.17 by codex, isolate native pet verification from real ERP sessions and business records.
const clients = new Set();
let date = '20261117', sequence = 5, events = [], allowed = true, gap = false;
const history = [];
const token = 'a'.repeat(64);
function record(entry) { history.push({at: Date.now(), ...entry}); }
function wake() {
  const payload = Buffer.from(JSON.stringify({act: 'desktop-helper'}));
  const frame = Buffer.concat([Buffer.from([0x81, payload.length]), payload]);
  for (const socket of clients) socket.write(frame);
  record({type: 'wake'});
}
function reply(response, status, data) {
  response.writeHead(status, {'Content-Type': 'application/json', 'Cache-Control': 'no-store'});
  response.end(JSON.stringify(data));
}
const server = http.createServer(async (request, response) => {
  const url = new URL(request.url, 'http://127.0.0.1');
  if (url.pathname === '/api/desktop-helper/connect') {
    record({type: 'connect'});
    request.resume();
    reply(response, allowed ? 200 : 403, {token, scope: 'b'.repeat(64), date, cursor: sequence, expires_at: 9999999999});
  } else if (url.pathname === '/api/desktop-helper/changes') {
    const cursor = url.searchParams.get('date') === date ? Number(url.searchParams.get('cursor')) : 0;
    record({type: 'changes', cursor, authorized: request.headers.authorization === 'Bearer ' + token});
    reply(response, allowed ? 200 : 403, {date, cursor: sequence, gap, events: events.filter(event => event.id > cursor)});
  } else if (url.pathname === '/control') {
    const action = url.searchParams.get('action');
    if (action === 'add' || action === 'mod') {
      events.push({id: ++sequence, action, quano: 'SYNTHETIC-' + sequence});
      record({type: 'event', id: sequence});
      wake();
    } else if (action === 'yesterday') { record({type: 'excluded-old-document'}); wake(); }
    else if (action === 'replay') wake();
    else if (action === 'next-day') { date = '20261118'; sequence = 1; events = [{id: 1, action: 'add', quano: 'NEXT-DAY'}]; wake(); }
    else if (action === 'gap') { gap = true; wake(); }
    else if (action === 'revoke') { allowed = false; wake(); }
    else if (action === 'allow') { allowed = true; gap = false; }
    else if (action === 'drop') { for (const client of clients) client.destroy(); }
    reply(response, 200, {ok: true});
  } else if (url.pathname === '/history') reply(response, 200, history);
  else if (url.pathname === '/opened') { record({type: 'opened', order: url.searchParams.get('order')}); reply(response, 200, {ok: true}); }
  else if (url.pathname === '/page-state') { record({type: 'page-state', value: url.searchParams.get('value')}); reply(response, 200, {ok: true}); }
  else {
    response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8', 'Cache-Control': 'no-store'});
    response.end(fs.readFileSync(path.join(__dirname, 'pages/desktop-helper.html')));
  }
});
server.on('upgrade', (request, socket) => {
  const accept = crypto.createHash('sha1').update(request.headers['sec-websocket-key'] + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11').digest('base64');
  socket.write('HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ' + accept + '\r\n\r\n');
  clients.add(socket);
  socket.on('data', () => {});
  socket.on('close', () => clients.delete(socket));
  socket.on('error', () => clients.delete(socket));
});
server.listen(Number(process.argv[2] || 19376), '127.0.0.1', () => console.log('Synthetic pet server ready: ' + server.address().port));
process.on('SIGINT', () => { for (const client of clients) client.destroy(); server.close(); });

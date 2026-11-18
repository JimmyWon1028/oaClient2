const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const {EventEmitter} = require('node:events');
const apiRoot = path.resolve(process.argv[2] || '');
if (!process.argv[2]) throw new Error('Provide the real API root.');
let checks = 0;
function check(value, label) { assert.ok(value, label); console.log('PASS ' + label); checks++; }

//2026.11.17 by codex, execute only the existing OACS dispatcher with a fake socket and never start its server.
const server = fs.readFileSync(path.join(apiRoot, '../oacs/src/server2.js'), 'utf8');
const start = server.indexOf('function sendNotification(data) {');
const end = server.indexOf('function handleNotification(', start);
assert.ok(start >= 0 && end > start);
const socket = new EventEmitter();
const oacs = {io: socket, socks: [], _: {each: (items, fn) => items.forEach(fn)}};
vm.createContext(oacs);
vm.runInContext(server.slice(start, end), oacs);
const messages = [];
const browser = {
  $g: {isLogin: true, api_root: 'https://fixture.invalid/', login_user: {userid: 'FIXTURE'}, last_select_database: 'fixture', chatHub: socket},
  oaPetSend: message => messages.push(JSON.parse(message)), AbortController
};
browser.window = browser;
vm.createContext(browser);
const header = fs.readFileSync(path.join(__dirname, '../src/app/desktop_helper_script.h'), 'utf8');
vm.runInContext(header.split('R"JS(')[1].split(')JS"')[0] + '(41);', browser);
oacs.sendNotification({act: 'desktop-helper', userid: 'ALL', data: null});
check(messages.at(-1).kind === 'wake' && messages.at(-1).logged, 'real OACS ALL dispatcher wakes the existing client observer');
check(!('token' in messages.at(-1)) && !('quano' in messages.at(-1)) && !('ordno' in messages.at(-1)),
  'wake sends no token, quotation or order content');
const count = messages.length;
oacs.sendNotification({act: 'todo', userid: 'ALL', data: null});
check(messages.length === count, 'other OACS actions preserve existing behavior');
browser.__oaPet.stop();
oacs.sendNotification({act: 'desktop-helper', userid: 'ALL', data: null});
check(messages.length === count, 'stopped client does not receive another wake');

const routes = fs.readFileSync(path.join(apiRoot, 'routes/web.php'), 'utf8');
check((routes.match(/Route::post\('desktop-helper\/connect'/g) || []).length === 1
  && /Route::post\('desktop-helper\/connect', 'DesktopHelperController@connect'\)->middleware\('auth'\)/.test(routes),
  'connect route is registered once with the existing login middleware');
check((routes.match(/Route::get\('desktop-helper\/changes'/g) || []).length === 1
  && /Route::get\('desktop-helper\/changes', 'DesktopHelperController@changes'\)->withoutMiddleware\(\[\s*\\Illuminate\\Session\\Middleware\\StartSession::class,\s*\\Illuminate\\View\\Middleware\\ShareErrorsFromSession::class,\s*\]\)/.test(routes),
  'changes route is registered once without starting an anonymous session');
console.log(`${checks} checks, 0 failures`);

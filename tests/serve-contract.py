from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
import json
import sys
import time

#2026.10.12 modify by codex, reuse the localhost event server for targeted shutdown pages.
page = Path(sys.argv[2]) if len(sys.argv) > 2 else Path(__file__).parent / 'pages' / 'legacy-contract.html'
events = Path(sys.argv[1])


class Handler(BaseHTTPRequestHandler):
  def do_GET(self):
    if self.path.startswith('/event/'):
      with events.open('a', encoding='utf-8') as output:
        output.write(json.dumps({'time': time.time(), 'event': self.path[7:]}) + '\n')
      self.send_response(204)
      self.end_headers()
      return
    #2026.10.12 modify by codex, serve a local worker for actual website-data reset tests.
    worker = self.path == '/site-data-worker.js'
    data = b"self.addEventListener('install', () => self.skipWaiting());" if worker else page.read_bytes()
    self.send_response(200)
    self.send_header('Content-Type', 'text/javascript' if worker else 'text/html; charset=utf-8')
    self.send_header('Cache-Control', 'no-store')
    self.send_header('Content-Length', str(len(data)))
    self.end_headers()
    self.wfile.write(data)

  def log_message(self, *_):
    pass


HTTPServer(('127.0.0.1', 8765), Handler).serve_forever()

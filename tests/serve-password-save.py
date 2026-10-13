from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
import json
import sys
import time

page = Path(__file__).parent / 'pages/password-save.html'
events = Path(sys.argv[1])


class Handler(BaseHTTPRequestHandler):
  def do_GET(self):
    if self.path == '/success':
      data = b'<!doctype html><meta charset="utf-8"><title>W28 Form Submitted</title><h1>Native synthetic form submitted</h1><script>function doLogout(){console.log("loginState=0")}</script>'
    else:
      data = page.read_bytes()
    self.send_response(200)
    self.send_header('Content-Type', 'text/html; charset=utf-8')
    self.send_header('Cache-Control', 'no-store')
    self.send_header('Content-Length', str(len(data)))
    self.end_headers()
    self.wfile.write(data)

  def do_POST(self):
    length = int(self.headers.get('Content-Length', '0'))
    if length > 4096:
      self.send_error(413)
      return
    #2026.10.13 modify by codex, discard synthetic form values and record only the submission route.
    self.rfile.read(length)
    with events.open('a', encoding='utf-8') as stream:
      stream.write(json.dumps({'time': time.time(), 'event': self.path}) + '\n')
    if self.path == '/submit':
      self.send_response(303)
      self.send_header('Location', '/success')
      self.end_headers()
    elif self.path == '/ajax-submit':
      self.send_response(204)
      self.end_headers()
    else:
      self.send_error(404)

  def log_message(self, *_):
    pass


HTTPServer(('127.0.0.1', 8765), Handler).serve_forever()

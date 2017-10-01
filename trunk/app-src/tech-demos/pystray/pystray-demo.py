# with help from https://pythonexample.com/snippet/python/traypy_kamathln_python

# pystray libs
import pystray
import sys
import PIL.Image

import webview

# built-in webserver -- replace with Flask
import http.server
import socketserver
import os

PORT = 8000
Handler = http.server.SimpleHTTPRequestHandler
httpd = socketserver.TCPServer(("", PORT), Handler)

# pystray code
def configure(icon):
    # need to demonize this call and ensure only one window opens
    webview.create_window('Holoseat', 'http://localhost:8000', width=768,
        height=640, resizable=False)

def exitTrayIcon(icon):
    httpd.shutdown()
    icon.stop()

theMenu = pystray.Menu(pystray.MenuItem(text="Configure", action=configure, default=True),
                       pystray.MenuItem(text="Exit", action=exitTrayIcon))

trayIcon = pystray.Icon(name="Holoseat", icon=PIL.Image.open('./holoseat32x32.png'),
                        title="Holoseat", menu=theMenu)
trayIcon.warnings = True

def trayRunner(icon):
    web_dir = os.path.join(os.path.dirname(__file__), '../mockup')
    os.chdir(web_dir)

    print("serving at port", PORT)
    icon.visible = True
    httpd.serve_forever()



trayIcon.run(trayRunner)

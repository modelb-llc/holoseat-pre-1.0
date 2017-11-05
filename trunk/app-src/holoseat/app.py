# the main app is a pystray application, developed with help from
# https://pythonexample.com/snippet/python/traypy_kamathln_python

# Holoseat imports
from holoseat import config, ui, api

# other imports
import pystray
import sys
import os
import PIL.Image
import webview
import threading

# manage the window, only one should ever open
appWindowOpen = False
lock = threading.Lock()
currentConfig = None
iconFileName = os.path.join(os.path.dirname(__file__), './holoseat32x32.png')

def openAppWindow():
    global appWindowOpen
    if not appWindowOpen:
        with lock:
            appWindowOpen = True
            webview.create_window('Holoseat', 'http://localhost:%s' % currentConfig.UI_PORT,
                                  width=768, height=640, resizable=False)
            appWindowOpen = False

# pystray code
def configure(icon):
    # need to demonize this call and ensure only one window opens
    thread = threading.Thread(target=openAppWindow, args=())
    thread.daemon = True                            # Daemonize thread
    thread.start()                                  # Start the execution

def exitTrayIcon(icon):
    icon.stop()

theMenu = pystray.Menu(pystray.MenuItem(text="Configure", action=configure, default=True),
                       pystray.MenuItem(text="Exit", action=exitTrayIcon))

trayIcon = pystray.Icon(name="Holoseat", icon=PIL.Image.open(iconFileName),
                        title="Holoseat", menu=theMenu)
trayIcon.warnings = True

def trayRunner(icon):
    api.start(debug=currentConfig.DEBUG, apiPort=currentConfig.API_PORT)
    ui.start(debug=currentConfig.DEBUG, uiPort=currentConfig.UI_PORT, apiPort=currentConfig.API_PORT)
    icon.visible = True

def start(debug=False):
    global currentConfig
    if (debug):
        currentConfig = config.DevConfig()
    else:
        currentConfig = config.ProdConfig()

    trayIcon.run(trayRunner)

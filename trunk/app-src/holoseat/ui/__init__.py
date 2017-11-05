# Flask related imports
from flask import Flask

# other imports
import threading
from uuid import uuid4

# decalre the UI object before importing other ui modules since they need UI
UI = Flask(__name__)
UI.secret_key = uuid4().hex

uiConfig = { 'uiPort' : 8000,
             'apiPort' : 8080,
             'debug' : False}

@UI.context_processor
def inject_debug():
    return dict(debug=UI.debug)

# import required modules from the ui package so we can just run it
from holoseat.ui import views

# turned off reloader per https://stackoverflow.com/a/24618018
# set host to 0.0.0.0 per https://stackoverflow.com/a/7027113
def uiThreadFunc(debug=False, port=8000):
    UI.run(debug=debug, host= '0.0.0.0', port=port, threaded=True, use_reloader=False)

# this is the function to use for starting the UI thread
def start(debug=False, uiPort=8000, apiPort=8080):
    # capture config
    uiConfig['uiPort'] = uiPort
    uiConfig['apiPort'] = apiPort
    uiConfig['debug'] = debug

    uiThread = threading.Thread(target=uiThreadFunc, args=(debug,uiPort,), name='UI-Thread')
    uiThread.setDaemon(True)
    uiThread.start()

# Flask related imports
from flask import Flask
from flask_debugtoolbar import DebugToolbarExtension

# other imports
import threading
from uuid import uuid4

# decalre the UI object before importing other ui modules since they need UI
UI = Flask(__name__)
UI.secret_key = uuid4().hex
UI.config['SECRET_KEY'] = UI.secret_key
UI.config['DEBUG_TB_INTERCEPT_REDIRECTS'] = False
debug_toolbar = DebugToolbarExtension()

uiConfig = { 'uiPort' : 8000,
             'apiPort' : 8080,
             'debug' : False,
             'jsVersionString' : uuid4().hex}

@UI.context_processor
def inject_constants():
    return dict(debug=UI.debug, jsVersionString=uiConfig['jsVersionString'])

# import required modules from the ui package so we can just run it
from holoseat.ui import views

# turned off reloader per https://stackoverflow.com/a/24618018
# set host to 0.0.0.0 per https://stackoverflow.com/a/7027113
def uiThreadFunc(debug=False, port=8000):
    UI.run(host='0.0.0.0', port=port, threaded=True, use_reloader=False)

# this is the function to use for starting the UI thread
def start(debug=False, uiPort=8000, apiPort=8080):
    # capture config
    uiConfig['uiPort'] = uiPort
    uiConfig['apiPort'] = apiPort
    uiConfig['debug'] = debug

    UI.debug = debug
    debug_toolbar.init_app(UI)

    uiThread = threading.Thread(target=uiThreadFunc, args=(debug,uiPort,), name='UI-Thread')
    uiThread.setDaemon(True)
    uiThread.start()

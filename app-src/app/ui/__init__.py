# Flask related imports
from flask import Flask

# other imports
import threading

# decalre the UI object before importing other ui modules since they need UI
UI = Flask(__name__)

# import required modules from the ui package so we can just run it
from ui import views

# turned off reloader per https://stackoverflow.com/a/24618018
def uiThreadFunc(debug=False):
    UI.run(debug=debug, threaded=True, use_reloader=False)

# this is the function to use for starting the UI thread
def start(debug=False):
    uiThread = threading.Thread(target=uiThreadFunc, args=(debug,))
    uiThread.setDaemon(True)
    uiThread.start()

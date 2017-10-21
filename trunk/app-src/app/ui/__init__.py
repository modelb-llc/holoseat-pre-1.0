# Flask related imports
from flask import Flask

# other imports
import threading

# decalre the UI object before importing other ui modules since they need UI
UI = Flask(__name__)

# import required modules from the ui package so we can just run it
from ui import views

# turned off reloader per https://stackoverflow.com/a/24618018
def uiThreadFunc(debug=False, port=8000):
    UI.run(debug=debug, port=port, threaded=True, use_reloader=False)

# this is the function to use for starting the UI thread
def start(debug=False, port=8000):
    uiThread = threading.Thread(target=uiThreadFunc, args=(debug,port,), name='UI-Thread')
    uiThread.setDaemon(True)
    uiThread.start()

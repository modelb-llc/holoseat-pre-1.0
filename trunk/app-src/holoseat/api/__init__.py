# Tornado imports
from tornado import web, escape, ioloop, httpclient, gen

# other imports
import threading
from concurrent.futures import ThreadPoolExecutor

apiConfig = { 'apiPort' : 8080,
              'debug' : False }

apiThreadPool = ThreadPoolExecutor()

# package imports now that the package variables are declared
from api import mainHandlers, debugHandlers

def apiThreadFunc(debug=False, port=8080):
    application = web.Application([
        (r"/api/main/devicename", mainHandlers.DevicenameHandler),
        (r"/api/main/version", mainHandlers.VersionHandler),
        (r"/api/debug", debugHandlers.DebugHandler),
        (r"/api/debug/serial", debugHandlers.DebugSerialHandler)
    ], debug=debug)
    print("Listening at port {0}".format(port))
    application.listen(port)
    ioloop.IOLoop.instance().start()

def start(debug=False, apiPort=8080):
    apiConfig['apiPort'] = apiPort
    apiConfig['debug'] = debug

    apiThread = threading.Thread(target=apiThreadFunc, args=(debug,apiPort,), name='API-Thread')
    apiThread.setDaemon(True)
    apiThread.start()

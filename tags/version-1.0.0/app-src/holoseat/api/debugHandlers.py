from tornado import web, escape
from holoseat.api import status, apiConfig, apiHandler

class DebugHandler(web.RequestHandler):
    def initialize(self):
        pass

    def get(self):
        pass

    SUPPORTED_METHODS = ('GET')

    def get(self):
        self.set_status(status.HTTP_200_OK)
        response = {'debug': apiConfig['debug']}
        self.write(response)

class DebugSerialHandler(apiHandler):
    def initialize(self):
        pass

    def get(self):
        pass

    SUPPORTED_METHODS = ('PUT')

    def put(self):
        if (apiConfig['debug']):
            super().processCommand(escape.json_decode(self.request.body))
        else:
            response = {
                'Error': 'Direct Serial Access Forbidden, Launch in Debug Mode'
            }
            self.set_status(status.HTTP_401_UNAUTHORIZED)
            self.write(response)
            self.finish()
            return

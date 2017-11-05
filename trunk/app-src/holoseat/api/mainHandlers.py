from tornado import web
from holoseat.api import status, apiConfig, apiHandler

class DevicenameHandler(apiHandler):
    def initialize(self):
        pass

    def get(self):
        pass

    SUPPORTED_METHODS = ('GET')

    def get(self):
        super().processCommand({"uri":"/main/devicename","verb":"GET"})

class VersionHandler(apiHandler):
    def initialize(self):
        pass

    def get(self):
        pass

    SUPPORTED_METHODS = ('GET')

    def get(self):
        super().processCommand({"uri":"/main/version","verb":"GET"})

class ApiVersionHandler(web.RequestHandler):
    def initialize(self):
        pass

    def get(self):
        pass

    SUPPORTED_METHODS = ('GET')

    def get(self):
        self.set_status(status.HTTP_200_OK)
        response = {'apiVer': apiConfig['apiVersion']}
        self.write(response)

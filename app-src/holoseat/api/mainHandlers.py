from tornado import web
from api.apiHandler import apiHandler

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

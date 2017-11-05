from holoseat import util

class Config(object):
    pass

class ProdConfig(Config):
    def __init__(self):
        super(ProdConfig, self).__init__()
        self.DEBUG = False
        self.UI_PORT = util.findFreePort()
        self.API_PORT = util.findFreePort()

class DevConfig(Config):
    def __init__(self):
        super(DevConfig, self).__init__()
        self.DEBUG = True
        self.UI_PORT = 8000
        self.API_PORT = 8080

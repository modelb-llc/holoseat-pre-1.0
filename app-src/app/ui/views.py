from ui import UI

@UI.route('/', methods=['GET'])
def configure():
    return "Hello Holoseat!"

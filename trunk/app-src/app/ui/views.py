from ui import UI
from flask import render_template

@UI.route('/', methods=['GET'])
def controls():
    return render_template("index.html")

@UI.route('/about', methods=['GET'])
def about():
    return render_template("about.html")

@UI.route('/hw-defaults', methods=['GET'])
def hwDefaults():
    return render_template("hw-defaults.html")

@UI.route('/profiles', methods=['GET'])
def profiles():
    return render_template("profiles.html")

@UI.route('/serial-monitor', methods=['GET'])
def serialMonitor():
    return render_template("serial-monitor.html")

@UI.route('/help/', methods=['GET'])
@UI.route('/help', methods=['GET'])
def help():
    return render_template("help-index.html")

@UI.route('/help/app', methods=['GET'])
def helpApp():
    return render_template("help-app.html")

@UI.route('/help/hardware', methods=['GET'])
def helpHardware():
    return render_template("help-hardware.html")

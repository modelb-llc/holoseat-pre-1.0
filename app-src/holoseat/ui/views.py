from holoseat.ui import UI, uiConfig
from flask import render_template, flash, request, url_for, redirect
from urllib.parse import urlparse, urljoin
import socket

# helper functions
def isSafeUrl(target):
    ref_url = urlparse(request.host_url)
    test_url = urlparse(urljoin(request.host_url, target))
    return test_url.scheme in ('http', 'https') and \
           ref_url.netloc == test_url.netloc

def getRedirectBackTarget():
    if isSafeUrl(request.referrer):
        return request.referrer
    return url_for('controls')

# routes/views
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

@UI.route('/mobile-address', methods=['GET'])
def mobileAddress():
    # per https://stackoverflow.com/a/19638229
    host = socket.gethostbyname(socket.gethostname())
    #port = urlparse(request.host_url).port
    flash('You may access the Holoseat App from your mobile device at http://%s:%s.' % (host, uiConfig['uiPort']), 'info')
    return redirect(getRedirectBackTarget())

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

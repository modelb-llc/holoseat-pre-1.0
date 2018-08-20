from holoseat.ui import UI, uiConfig, forms
from holoseat.util import getHost
from flask import render_template, flash, request, url_for, redirect, jsonify
from urllib.parse import urlparse, urljoin
import json
import requests

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

@UI.route('/serial-monitor', methods=['GET', 'POST'])
def serialMonitor():
    commandForm = forms.SerialMonitorCommandForm()
    if request.method == 'POST':
        if commandForm.validate_on_submit():
            result = requests.put('http://localhost:%s/api/debug/serial'%uiConfig['apiPort'],
                                  data=commandForm.command.data)
            return jsonify(result=result.content.decode("utf-8"))
        else:
            return jsonify(formError=commandForm.errors)
    else:
        commandForm = forms.SerialMonitorCommandForm()

    return render_template("serial-monitor.html", commandForm=commandForm)

@UI.route('/mobile-address', methods=['GET'])
def mobileAddress():
    flash('You may access the Holoseat App from your mobile device at http://%s:%s.' % (getHost(), uiConfig['uiPort']), 'info')
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

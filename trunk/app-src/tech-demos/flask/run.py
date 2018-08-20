from flask import Flask, render_template
import datetime

app = Flask(__name__)

@app.template_filter()
def datetimefilter(value, format='%Y/%m/%d %H:%M'):
    """convert a datetime to a different format."""
    return value.strftime(format)

app.jinja_env.filters['datetimefilter'] = datetimefilter

@app.route("/")
def template_test():
    return render_template('template.html', my_string="Wheeeee!",
        my_list=[0,1,2,3,4,5], title="Index", current_time=datetime.datetime.now())

@app.route("/home")
def home():
    return render_template('template.html', my_string="Foo",
        my_list=[6,7,8,9,10,11], title="Home", current_time=datetime.datetime.now())

@app.route("/about")
def about():
    return render_template('template.html', my_string="Bar",
        my_list=[12,13,14,15,16,17], title="About", current_time=datetime.datetime.now())

@app.route("/contact")
def contact():
    return render_template('template.html', my_string="FooBar"
        , my_list=[18,19,20,21,22,23], title="Contact Us", current_time=datetime.datetime.now())

@app.route("/thing1")
def thing1():
    return render_template('template.html', my_string="Thing 1"
        , my_list=[24,25,26,27,28,29], title="Thing 1", current_time=datetime.datetime.now())

@app.route("/thing2")
def thing2():
    return render_template('template.html', my_string="Thing 2"
        , my_list=[30,31,32,33,34,35], title="Thing 2", current_time=datetime.datetime.now())

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, threaded=True, debug=True)
from flask_wtf import FlaskForm
from wtforms import TextField
from wtforms.validators import DataRequired
from holoseat.ui.json_validator import json_string

class SerialMonitorCommandForm(FlaskForm):
    command = TextField('Command',
                        description='Enter a command to send to Holoseat',
                        validators=[DataRequired(), json_string()])

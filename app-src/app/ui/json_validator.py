# created by Joe Sillitoe - https://gist.github.com/jsillitoe
# from https://gist.github.com/jsillitoe/5487566b0c6e7c49cc81

from wtforms import ValidationError
import json

class JsonString(object):
    def __init__(self, message=None):
        if not message:
            message = u'Field must be valid json string.'
        self.message = message

    def __call__(self, form, field):
        try:
            json.loads(field.data)
        except:
            raise ValidationError(self.message)

json_string = JsonString()

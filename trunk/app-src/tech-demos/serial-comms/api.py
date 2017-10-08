import serial
from serial.tools import list_ports
import status
from tornado import web, escape, ioloop, httpclient, gen

# set up the serial port for Holoseat comms
holoseatSerial = serial.Serial()
holoseatSerial.baudrate = 115200
holoseatSerial.bytesize = serial.EIGHTBITS
holoseatSerial.parity = serial.PARITY_NONE
holoseatSerial.stopbits = serial.STOPBITS_ONE
holoseatSerial.timeout = 5 # 5 second timeout for comms with Holoseat

def sendCommand(cmd):
    return holoseatSerial.write(cmd.encode('utf-8'))

def readResult():
    return holoseatSerial.readline().decode("utf-8").strip()

def connectToHoloseat():
    ready = False
    comPorts = list_ports.comports()
    for comPort in comPorts:
        holoseatSerial.port = comPort.device
        try:
            holoseatSerial.open()
            sendCommand('?')
            result = readResult()
            ready = ('R' == result)
            readResult() # throw away status line from Holoseat v0.3.5

            if ready:
                return True  # we found a working Holoseat controller
            else:
                holoseatSerial.close()
        except serial.serialutil.SerialException as e:
            pass # throw errors away as we may be connecting to the wrong port

    return False  # we iterated through all available ports and did not find
                  # a Holoseat controller

def disconnectFromHoloseat():
    holoseatSerial.close()
    holoseatSerial.port = None

# def getStatus():
#     if (holoseatSerial.is_open or connectToHoloseat()):
#         try:
#             sendCommand('Q')
#             return readResult()
#         except serial.serialutil.SerialException as e:
#             disconnectFromHoloseat()
#             return e.args[0]

class HoloseatHandler(web.RequestHandler):
    SUPPORTED_MEHTODS = {'GET'}

    def get(self):
        if (holoseatSerial.is_open or connectToHoloseat()):
            try:
                sendCommand('Q')
                result = readResult()
                response = {
                    'status': result
                }
                self.set_status(status.HTTP_200_OK)
                self.write(response)
            except serial.serialutil.SerialException as e:
                disconnectFromHoloseat()
                self.set_status(status.HTTP_500_INTERNAL_SERVER_ERROR)
                response = {
                    'error': 'Lost connection to Holoseat',
                    'exceptionDetails': e.args[0]
                }
                self.write(response)
        else:
            response = {
                'error': 'Cannot find Holoseat'
            }
            self.set_status(status.HTTP_500_INTERNAL_SERVER_ERROR)
            self.write(response)

application = web.Application([
    (r"/status", HoloseatHandler)
], debug=True)

if __name__ == "__main__":
    port = 8888
    print("Listening at port {0}".format(port))
    application.listen(port)
    ioloop.IOLoop.instance().start()

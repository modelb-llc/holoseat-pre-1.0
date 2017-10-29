import serial
from serial.tools import list_ports
from collections import deque
import json

# set up the serial port for Holoseat comms
holoseat = serial.Serial()
holoseat.baudrate = 115200
holoseat.bytesize = serial.EIGHTBITS
holoseat.parity = serial.PARITY_NONE
holoseat.stopbits = serial.STOPBITS_ONE
holoseat.timeout = 5 # 5 second timeout for comms with Holoseat

data = deque([])

def sendCommand(cmd):
    return holoseat.write(cmd.encode('utf-8'))

def readResultLine():
    return holoseat.readline().decode("utf-8").strip()

def connected():
    return holoseat.is_open

def readData():
    readData = False
    while (holoseat.in_waiting):
        data.append(readResultLine())
        readData = True

    # return the last read element, it is usually what we want
    if readData:
        return data[-1]

    # return None if we did not read any new data
    return None

def popData():
    if (len(data)):
        return data.popleft()
    return None

def execCommand(cmd):
    sendCommand(cmd)

    # wait for the result to come back
    result = None
    while not(result):
        result = readData()

    return result

def findHoloseatPort():
    comPorts = list_ports.comports()
    for comPort in comPorts:
        vid = format(comPort.vid, 'X')
        pid = format(comPort.pid, 'X')

        # check for Alpha Controller (aka - Adafruit Feather 324u)
        if (vid == '239A' and pid == '800C'):
            return { 'comPort': comPort.device,
                     'expectedHW_Vers' : ['v0.4'] }

        # check for v1.0+ (aka Holoseat vid/pid)
        if (vid == '1209' and pid == 'B058'):
            return { 'comPort': comPort.device,
                     'expectedHW_Vers' : ['v1.0'] }

    # we iterated over all available com ports and did not find Holoseat
    return None

def connect():
    holoseatPort = findHoloseatPort()
    if not(holoseatPort):
        return False  # no Holoseat Controllers connected to USB

    holoseat.port = holoseatPort['comPort']
    try:
        holoseat.open()
        sendCommand(json.dumps({"uri":"/main/ready","verb":"GET"}))
        readyResults = json.loads(readResultLine())

        # check for errors
        if ('Error' in readyResults):
            disconnect()
            print('Error: %s' % readyResults['Error'])
            return False

        # check result, is this Holoseat?
        if (readyResults['device'] != 'Holoseat'):
            disconnect()
            return False

        # is this the expected HW version?
        if not(readyResults['hwVer'] in holoseatPort['expectedHW_Vers']):
            disconnect()
            return False

        # TODO - is this a compatible FW version?
        # TODO - is this a compatible HSP version?

        # passed all tests, we can talk to this Holoseat
        return True
    except serial.serialutil.SerialException as e:
        return False  # Holoseat not accessible


def disconnect():
    holoseat.close()
    holoseat.port = None

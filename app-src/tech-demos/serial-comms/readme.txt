This is a demo of mapping serial communications with the Holoseat controller to
a REST API.  It uses pyserial and tornado.  You will need a Feather board with
v0.3.5 Holoseat firmware installed as the demo relies on v0.3.5, or lower, of the
Holoseat Serial Protocol
(https://opendesignengine.net/projects/holoseat/wiki/Software_Source_Code#HoloSeat-Serial-Protocol).

Steps to run this demo:

1. Start the REST server
  a. cd to tech-demos\
  b. activate virtualenv
  c. cd serial-comms\
  d. start the demo REST server with: python api.py
2. Test graceful failure when no Holoseat is connected
  a. Open a web browser
  b. Go to http://localhost:8888/status
  c. You should get a "Cannot find Holoseat" error in a JSON result
     {"error": "Cannot find Holoseat"}
3. Test working state
  a. Connect a Holoseat controller to a USB port
  b. Open a web browser
  c. Go to http://localhost:8888/status
     You should get an HSP standard state message as the status field in a JSON result
     {"status": "0.3.0,w(w),s(s),1(1),1/25(0),0(0)/10(10)"}
4. Test lost connection
  a. After running step 3, unplug Holoseat from the computer
  b. Refresh http://localhost:8888/status
     You should get a "Lost connection to Holoseat" error in a JSON result that
     also includes the exception text.
     {"error": "Lost connection to Holoseat",
      "exceptionDetails": "WriteFile failed (PermissionError(13, 'The device does not recognize the command.', None, 22))"}
5. Test recovery from lost connection
  a. After running step 4, onnect a Holoseat controller to a USB port
  b. Refresh http://localhost:8888/status
     You should get an HSP standard state message as the status field in a JSON result
     {"status": "0.3.0,w(w),s(s),1(1),1/25(0),0(0)/10(10)"}

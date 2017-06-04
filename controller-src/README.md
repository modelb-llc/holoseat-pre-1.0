Source code for the Holoseat controller.  There are three sub-projects to the controller source code.

* docker-images - contains docker and other required build files for the two CHIPtainer images used with Holoseat.
  * chiptainer-holoseat - release docker image for Holoseat main board
  * chiptainer-holoseat-dev - development image for the Holoseat main board
* main-board - source files for the Holoseat main board (runs inside a Holoseat CHIPtainer)
* hid-usb-board - source files for the daughter board used to implment HID over usb (current spec is an Adafruit Feather board); also facilitates serial communication between the main board and the host PC
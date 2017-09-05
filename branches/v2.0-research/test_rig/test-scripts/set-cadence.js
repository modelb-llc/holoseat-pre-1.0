// Copyright Model B, LLC 2016.
// Author: J. Simmons 
// https://opendesignengine.net/projects/holoseat/
// 
// This file is part of the Holoseat software suite (firmware, control software, etc).
//
// The Holoseat software suite is free software: you can redistribute it and/or modify 
// it under the terms of the GNU General Public License as published by the Free Software 
// Foundation, either version 3 of the License, or (at your option) any later version.
//
// Holoseat software suite is distributed in the hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with Holoseat 
// software suite.  If not, see <http://www.gnu.org/licenses/>.

// start the test rig running at specified cadence

// tests have two magnets so run motor at half speed
var cadence = process.argv[2];  

// initialize serial port to the arduino running the motor
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var port = new SerialPort('/dev/ttyACM0', { 
	baudrate: 57600,
	parser: serialport.parsers.readline('\n') });

port.on('data', function (data) {
	//console.log('received ready flag: ' + data); 
    writeAndDrain(' ' + (cadence/2), function(err) {
    if (err) {
      return console.log('Error: ', err.message);
    }
    // report cadence at specified speed
    console.log('set cadence to ' + cadence);
    process.exit();
  });
});

function writeAndDrain (data, callback) {
  port.write(data, function () {
    port.drain(callback);
  });
}

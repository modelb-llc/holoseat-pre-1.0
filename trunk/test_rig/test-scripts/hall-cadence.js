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

// log calculated cadence to the console, useful for verifying test rig ability to set a cadence

var raspi = require('raspi-io');
var five = require('johnny-five');
var board = new five.Board({
  io: new raspi()
});

board.on('ready', function() {
	// set up timing info
	var logData = true;
	var steps = 0;
	var loopDelay = 500;
	var lastTime = new Date();
	
	// connect to pin GPIO3 as a digital input
	var sensor = new five.Button('GPIO17');
	
	// set timeout to stop logging data and exit 
	setTimeout(function() {
		logData = false;
		process.exit();
	}, 30000);

	sensor.on("up", function() {
		var currentTime = new Date();
		var deltaT = (currentTime-lastTime)/1000;
		var cadence = 60/deltaT;  // in rpm
		lastTime = new Date();
		console.log(cadence);
	});

});

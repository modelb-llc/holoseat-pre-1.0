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

// print time and sensor values to the console, useful for testing sensor activity

var raspi = require('raspi-io');
var five = require('johnny-five');
var board = new five.Board({
  io: new raspi()
});

board.on('ready', function() {
	// set up timing info
	var startTime = new Date();
	var logData = true;
	
	// connect to pin GPIO3 as a digital input
	this.pinMode('GPIO17', five.Pin.INPUT);
	
	// set timeout to stop logging data and exit 
	setTimeout(function() {
		logData = false;
		process.exit();
	}, 30000);
	
	// start the reading data
	this.digitalRead('GPIO17', function(value) {
		if (logData) {
			var currentTime = new Date();
			console.log((currentTime-startTime)/1000 + ', ' + value);
		}
	});
});

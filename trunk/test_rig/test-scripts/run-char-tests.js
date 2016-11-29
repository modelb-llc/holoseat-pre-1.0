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

// run characterization test

var fs = require('fs');
var dateFormat = require('dateformat');
var readlineSync = require('readline-sync');
var stringify = require('csv-stringify');
var raspi = require('raspi-io');
var five = require('johnny-five');

var board = new five.Board({
  io: new raspi()
});

// read test definition and prepare output file name
var testFile = process.argv[2];
var testDefinition = JSON.parse(fs.readFileSync(testFile, 'utf8'));
var now = new Date();
var outFileName = './' + testDefinition.ID + '_' + 
                  dateFormat(now, 'yyyymmdd-HHMM') + '.csv';

// confirm test definition
console.log('This is test ID: ' + testDefinition.ID);
console.log('   ' + testDefinition.Description + '\n');
console.log('Please confirm the following configuration');
console.log('------------------------------------------');
console.log('Sensor:\t\t' + testDefinition.Sensor);
console.log('Magnet:\t\t' + testDefinition.Magnet);
console.log('Distance:\t' + testDefinition.Distance);

var runTest = readlineSync.question('Ready to run this test (y/n)? ');
if (runTest === 'n') {
	console.log('Aborting test');
	process.exit();
}

// set up the test
var testData = [];
var logData = false;
var spm = testDefinition.Cadence/2;
var portID = '';

if (testDefinition.Sensor === 'TR 10')
	portID = 'GPIO27';
else 
	portID = 'GPIO17';
	
board.on('ready', function() {
	console.log('starting actual test');
	logData = true;
	
	// set up timing info
	var startTime = new Date();
	
	this.pinMode(portID, five.Pin.INPUT);
	
	// set timeout to stop logging data and exit 
	setTimeout(function() {
		logData = false;
		stringify(testData, function(err, output){
			fs.writeFileSync(outFileName, output);
			process.exit();
		});
	}, testDefinition.Duration * 1000);
	
	// start the reading data
	this.digitalRead(portID, function(value) {
		if (logData) {
			var currentTime = new Date();
			testData.push([(currentTime-startTime)/1000, value]);
			//console.log((currentTime-startTime)/1000 + ', ' + value);
		}
	});
});

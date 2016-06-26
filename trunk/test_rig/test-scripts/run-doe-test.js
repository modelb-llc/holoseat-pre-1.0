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
console.log('Cadence:\t' + testDefinition.Cadence);

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
	var lastTime = new Date();
	
	var sensor = new five.Button('GPIO17');
	
	// set timeout to stop logging data and exit 
	setTimeout(function() {
		logData = false;
		stringify(testData, function(err, output){
			fs.writeFileSync(outFileName, output);
			console.log('RSME = ' + computeRSME());
			process.exit();
		});
	}, testDefinition.Duration * 1000);
	
	// collect cadence
	sensor.on("up", function() {
		var currentTime = new Date();
		var deltaT = (currentTime-lastTime)/1000;
		var cadence = 60/deltaT;  // in rpm
		lastTime = new Date();
		if (logData) {
			var currentTime = new Date();
			testData.push([(currentTime-startTime)/1000, cadence]);
			//console.log((currentTime-startTime)/1000 + ', ' + cadence);
		}
	});
});

function computeRSME() {
	// Note: going to skip the first value, it is noise as the time
	// delta is wrong
	var sumOfSquares = 0.0;
	var cadence = testDefinition.Cadence;
	var numValues = testData.length - 1;  
	
	for (var i = 1; i < numValues; i++) {
		sumOfSquares += Math.pow(cadence - testData[i][1], 2);
	}
	
	return Math.sqrt(sumOfSquares/numValues);
}

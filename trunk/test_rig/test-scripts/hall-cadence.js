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

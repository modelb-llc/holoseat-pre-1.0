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

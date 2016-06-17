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

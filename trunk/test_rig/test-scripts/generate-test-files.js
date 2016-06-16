var fs = require('fs');
var parse = require('csv-parse/lib/sync');

var testFile = process.argv[2];
var testDefinitions = fs.readFileSync(testFile, 'utf8');

//console.log(testDefinitions);

var tests = parse(testDefinitions, {columns: true});
//console.log(JSON.stringify(tests[0], null, 2));
//console.log(tests[0].Duration*1000);

for (var i = 0; i < tests.length; i++) {
	fs.writeFileSync('./' + tests[i].ID + '.json', 
				     JSON.stringify(tests[i], null, 2));
}

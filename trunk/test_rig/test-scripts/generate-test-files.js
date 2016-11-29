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

// convert a group test definitions stored in csv file to a series of individual test
// files stored in JSON data to be consumed by the test scripts.

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

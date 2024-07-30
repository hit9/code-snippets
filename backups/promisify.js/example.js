var fs = require('fs');
var promisify = require('./index');

var readdir = promisify(fs.readdir);

readdir('.').then(function(filenames) {
  console.log(filenames);
})

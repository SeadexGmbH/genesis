const Asciidoctor = require('asciidoctor');

const asciidoctor = Asciidoctor();


var attributes = {
    'data-uri': true,
    doctype: 'book',
    attributes: 'showtitle',
	//linkcss: true,
	'stylesheet': 'scripts/asciidoctor.css'
};

var run = function () {
    var args = process.argv.slice(2);
	var adocFilePath = args[0];
	
    var filePath = adocFilePath + '/index.adoc';
    console.log('Generate HTML for file: ' + filePath);
    asciidoctor.convertFile(filePath, { 'to_file': true, 'mkdirs': true, 'safe': 'safe', attributes });
}

run();
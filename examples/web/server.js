const http = require('http');
const url = require('url');
const fs = require('fs');

const mimes = {
	css  : 'text/css',
	html : 'text/html',
	js   : 'application/javascript'
};

const paths = {
	css  : '.',
	html : '.',
	js   : '../../sdk/web'
};

function zeroPad(num) {
	return num < 10 ? '0' + num : num;
}

function timeStamp() {
	const d = new Date();
	return `${zeroPad(d.getMonth() + 1)}-${zeroPad(d.getDate())} ` +
		`${zeroPad(d.getHours())}:${zeroPad(d.getMinutes())}:${zeroPad(d.getSeconds())}`;
}

http.createServer((req, res) => {
	const parsed = url.parse(req.url);
	let fileName = parsed.pathname === '/' ? '/index.html' : parsed.pathname;
	const fileType = fileName.split('.').slice(-1)[0];
	let fullPath = ((fileName === '/main.js') ? '.' : (paths[fileType] || '.')) + fileName;

	// Redirect requests for the Parsec SDK to /sdk/web
	if (fileName.indexOf('/sdk') != -1) {
		fileName = fileName.replace('/sdk', '');
		fullPath = '../../sdk/web' + fileName;
	}

	let code = 404;
	let color = '\x1b[31m';
	let body = '404';

	if (fs.existsSync(fullPath)) {
		code = 200;
		color = '\x1b[32m';
		body = fs.readFileSync(fullPath);
	}

	console.log(`${color}%s\x1b[0m %s`, code, `[${timeStamp()}] ${fullPath}`);
	res.writeHead(code, {'Content-Type': mimes[fileType] || 'text/plain'});
	res.end(body);

}).listen(9000);

console.log('Development server started on port 9000');

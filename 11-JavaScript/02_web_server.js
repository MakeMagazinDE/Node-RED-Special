const http = require('http');

http.createServer(function (request, response) {
  response.writeHead(200, { 'Content-Type': 'text/plain' });
  response.end('Hallo, Make-Magazin!');
}).listen(8080);

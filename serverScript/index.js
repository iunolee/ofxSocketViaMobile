'use strict'
require('colors')
const app = require('express')();
const http = require('http').Server(app);

// http protocol
app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html');
});

http.listen(9999, function() {
  console.log('listening on *:9999');
});


// const config = require('./config.json')
const datas = {
  stringData: 'foo',
  intData: 0,
  // floatData: 0.5,
  // boolData: true,
  // nested: {
  //   hello: 'world'
  // }
}

// io = require('socket.io')(config.server.port)


const io = require('socket.io')(http);

io.on('connection', function(socket) {
  console.log('connected'.bold.green)
  console.log("We have a new client: " + socket.id);
  // console.log('query:', socket.handshake.query)


  //mobile part
  socket.on('button', function(data) {
    // Data comes in as whatever was sent, including objects
    let sendData = {number : parseInt(data)};
    console.log("Received: 'button value' " + data);
    // // Send it to all of the clients
    // io.emit('chatmessage', data);
    // datas.stringData = 'button clicked';
    // datas.intData = data;
    // console.log(sendValue.intData);
    // let emitInterval = setInterval(() => {
      io.emit('server-event', sendData)
    //   // socket.emit('pingy')
    // }, 2000)
    // io.emit('pingy');
  });

  // let emitInterval = setInterval(() => {
  //   socket.emit('server-event', datas)
  //   // socket.emit('pingy')
  // }, 2000)

  socket.on('disconnect', () => {
      console.log('disconnect'.bold.red)
      // clearInterval(emitInterval)
    })
    // .on('pongy', (data) => {
    //   console.log('pongy'.blue, data)
    // })
});

// const nsp = io.of('/nsp')
// nsp.on('connection', function(socket) {
//   console.log('connection from namespace /nsp'.bold.green)
//   let emitInterval = setInterval(() => {
//     socket.emit('nsping')
//   }, 2000)
//
//   socket
//     .on('disconnect', () => {
//       console.log('disconnect from namespace /nsp'.bold.red)
//       clearInterval(emitInterval)
//     })
//     .on('nspong', (data) => {
//       console.log('nspong'.blue)
//     })
// })

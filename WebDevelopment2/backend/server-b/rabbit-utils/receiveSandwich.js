#!/usr/bin/env node

/* To receive sandwich orders from server a, require "./receiveSandwich" and call the getTask method.

Example:

let recieverB = require("./receiveSandwich")

let order = recieverB.getTask('localhost', 'sandwich').then(order => {
    order.status = "done";
    return senderB.addTask('localhost', 'task', order);
})
*/
'use strict';

var amqp = require('amqplib');
let sender = require("./sendTask")

module.exports.getTask = function (rabbitHost, queueName) {

  return new Promise((resolve, reject) => {
    amqp.connect('amqp://' + rabbitHost)
      .then(function (conn) {
        // Call .close when proccess is cancelled
        process.once('SIGINT', function () { conn.close(); });
        return conn.createChannel().then(function (ch) {
          ch.assertQueue(queueName, { durable: true });
          ch.prefetch(1); // Only consume one sandwich at a time
          ch.consume(queueName, function (msg) {
            var order = JSON.parse(msg.content.toString());
            // Recieved sandwiches are handled when a message is consumed from que
            handleSandwich(order, msg);
          }, { noAck: false });


          function handleSandwich(order, msg) {
            console.log("Server B recieved following order:")
            console.log(order)
            order.status = "ready";
            console.log("Preparing order...")
            setTimeout(function () {
              // The response message to server A is unceremoniously sent here
              sender.addTask(rabbitHost, process.env.OUTPUT_QUEUE, order);
              ch.ack(msg);
              resolve(order)
            }, 7000);
          }
          return ch;
        });
      })
      .catch(function (err) {
        console.error('Error occurred in receiving sandwich:', err);

        reject(err);
      });
  });
}



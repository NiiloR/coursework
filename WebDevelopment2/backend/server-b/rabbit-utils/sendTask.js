#!/usr/bin/env node

/* To send a readu order to server a, require "./sendTask" and call the addTask method.

Example:

let senderB = require("./sendTask")

let order = recieverB.getTask('localhost', 'sandwich').then(order => {
    order.status = "done";
    return senderB.addTask('localhost', 'task', order);
})
.catch(error => {("Error: ", error);
});

*/

'use strict';

var amqp = require('amqplib');

module.exports.addTask = function(rabbitHost, queueName, order){
  amqp.connect('amqp://' + rabbitHost)
  .then(function(c) {
    c.createConfirmChannel()
    .then(function(ch) {
      console.log("Sending ready task to server A")
      ch.sendToQueue(queueName, new Buffer.from(JSON.stringify(order)), {},
      function(err, ok) {
        if (err !== null){
          console.warn(new Date(), 'Message nacked!');
        }
        else{
          console.log(new Date(), 'Message acked');
        }
      });
    });
  });
}

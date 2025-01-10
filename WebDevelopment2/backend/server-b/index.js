#!/usr/bin/env node

/*
Server B

This server consumes messages from the rabbitMQ que 'sandwich'.
After 7 seconds, the server publishes the completed order to the que 'task'.
*/
'use strict';

var amqp = require('amqplib');
let reciever = require("./rabbit-utils/receiveSandwich")
let sender = require("./rabbit-utils/sendTask")

// RabbitMQ hostname defaulted to localhost. A different host can be provided as an argument when running server.
let hostName = 'localhost';
if (process.argv.length > 2) {

    hostName = process.argv[2];
}
console.log("Starting server B, rabbitMQ host: " + hostName)

console.log("Server B waiting for messages")
reciever.getTask(process.env.MESSAGE_QUEUE, process.env.INPUT_QUEUE)
    .catch(error => {
        console.log("Error: ", error);
    });

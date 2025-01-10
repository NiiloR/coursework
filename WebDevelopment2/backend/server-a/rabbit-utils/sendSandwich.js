'use strict';

const amqp = require('amqplib');

module.exports.addTask = async function (rabbitHost, queueName, order) {
  try {
    const connection = await amqp.connect('amqp://' + rabbitHost);
    const channel = await connection.createConfirmChannel();

    console.log("Order created:");
    console.log(order);

    await new Promise((resolve, reject) => {
      channel.sendToQueue(queueName, Buffer.from(JSON.stringify(order)), {}, (err, ok) => {
        if (err !== null) {
          console.warn(new Date(), 'Message nacked!');
          reject(err);
        } else {
          console.log(new Date(), 'Message acked');
          resolve(ok);
        }
      });
    });
    await channel.close()
    return order;
  } catch (err) {
    console.error('Error occurred in sending task:', err);
    throw err;
  }
};


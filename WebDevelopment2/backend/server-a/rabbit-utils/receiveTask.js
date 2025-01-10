'use strict';
const amqp = require('amqplib');
const orderService = require("../service/OrderService")

module.exports.getTask = async function (rabbitHost, queueName) {
  try {
    const connection = await amqp.connect('amqp://' + rabbitHost);
    process.once('SIGINT', () => { connection.close(); });
    const channel = await connection.createChannel();
    await channel.assertQueue(queueName, { durable: true });

    await new Promise((resolve, reject) => {
      channel.consume(queueName, async function (msg) {
        const order = JSON.parse(msg.content.toString());
        await handleTask(order, msg, channel);
        resolve(order);
      }, { noAck: false });
    });

  } catch (err) {
    console.error('Error occurred in receiving task:', err);
    throw err;
  }
};

async function handleTask(order, msg, channel) {
  console.log("Server A received the following order:");
  console.log(order);

  try {
    await orderService.updateOrder(order)
    console.log("Order updated!");
    await new Promise(resolve => setTimeout(resolve, 1000));
    channel.ack(msg);
  } catch (err) {
    console.error('Error occurred while handling task:', err);
    //throw err;
  }
}
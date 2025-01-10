'use strict';

const sequelize = require("../index")
const rabbitUtilsSend = require('../rabbit-utils/sendSandwich.js');

const getNewOrderId = async () => {
  const max = await sequelize.models.Order.max("id")
  if (max === null) {
    return 0
  }
  return max + 1
}

exports.updateOrder = async function (order) {
  try {
    const rowToUpdate = await sequelize.models.Order.findOne(
      {
        where: {
          id: order.id
        }
      }
    )
    console.log(rowToUpdate)
    rowToUpdate.status = order.status
    await rowToUpdate.save()
  } catch (err) {
    console.error('Error occurred while handling task:', err);
    //throw err;
  }
}

/**
 * Add an order for an sandwich
 *
 * order Order place an order for a sandwich
 * returns Order
 **/
exports.addOrder = async function (order) {
  try {
    // Create the order in the database
    const max = await getNewOrderId()
    const createdOrder = await sequelize.models.Order.create({
      id: max,
      status: "received",
      SandwichId: order.sandwichId
    })
    // Send order to message que
    await rabbitUtilsSend.addTask(process.env.MESSAGE_QUEUE, process.env.OUTPUT_QUEUE, createdOrder)
    createdOrder.status = "inQueue"
    await createdOrder.save()

    // Return the created order
    return createdOrder;
  } catch (error) {
    console.log(error)
    // Handle any errors that occur during the database operation
    throw error;
  }
}


/**
 * Find an order by its ID
 * IDs must be positive integers
 *
 * orderId Long ID of the order that needs to be fetched
 * returns Order
 **/
exports.getOrderById = async function (orderId) {
  try {
    const order = await sequelize.models.Order.findOne({
      attributes: ["id", "status", "SandwichId"],
      where: {
        id: orderId
      }
    })
    return order
  } catch (error) {
    console.log(error)
    // Handle any errors that occur during the database operation
    throw error;
  }
}


/**
 * Get a list of all orders. Empty array if no orders are found.
 *
 * returns ArrayOfOrders
 **/
exports.getOrders = async function () {
  try {
    const orders = await sequelize.models.Order.findAll({
      attributes: [
        "id",
        "sandwichId",
        "status"
      ]
    })
    return orders;
  } catch (error) {
    console.log(error)
    throw error;
  }
}


'use strict';

var utils = require('../utils/writer.js');
var Order = require('../service/OrderService');
var rabbitUtilsSend = require('../rabbit-utils/sendSandwich.js');

module.exports.addOrder = function addOrder(req, res, next) {
  const { id, sandwichId, status } = req.swagger.params['order'].value;
  
  const ord = {
    id: id,
    sandwichId: sandwichId,
    status: status
  };
  Order.addOrder(ord)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.getOrderById = function getOrderById(req, res, next) {
  var orderId = req.swagger.params['orderId'].value;
  Order.getOrderById(orderId)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.getOrders = function getOrders(req, res, next) {
  Order.getOrders()
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

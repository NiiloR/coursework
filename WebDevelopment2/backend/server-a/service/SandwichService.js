'use strict';

const sequelize = require("../index")
/**
 * Add a new sandwich to the store. Needs an API key.
 *
 * body Sandwich Sandwich object that needs to be added to the store
 * no response value expected for this operation
 **/
exports.addSandwich = function (body) {
  return new Promise(function (resolve, reject) {
    resolve();
  });
}


/**
 * Deletes a sandwich
 *
 * sandwichId Long Sandwich id to delete
 * api_key String  (optional)
 * no response value expected for this operation
 **/
exports.deleteSandwich = function (sandwichId, api_key) {
  return new Promise(function (resolve, reject) {
    resolve();
  });
}


/**
 * Find sandwich by ID
 * Returns a single sandwich
 *
 * sandwichId Long ID of sandwich to return
 * returns Sandwich
 **/
exports.getSandwichById = function (sandwichId) {
  return new Promise(function (resolve, reject) {
    var examples = {};
    examples['application/json'] = { "empty": false };
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}


/**
 * Get a list of all sandwiches. Empty array if no sandwiches are found.
 *
 * returns ArrayOfSandwiches
 **/
exports.getSandwiches = async function () {
  try {
    const sandwiches = await sequelize.models.Sandwich.findAll({
      include:
      {
        model: sequelize.models.Topping,
        as: "Toppings",
        through: {
          attributes: [

          ]
        },
        attributes: {
          exclude: ['createdAt', 'updatedAt']
        }

      },
      attributes: ["name", "id", ["breadtype", "breadType"]]
    }

    )
    console.log(JSON.stringify(sandwiches, null, 2));
    return sandwiches
  } catch (error) {
    console.log(error)
  }

}


/**
 * Updates a sandwich in the store with JSON in body
 *
 * sandwichId Long ID of sandwich to return
 * body Sandwich Sandwich object that needs to be added to the store
 * no response value expected for this operation
 **/
exports.updateSandwich = function (sandwichId, body) {
  return new Promise(function (resolve, reject) {
    resolve();
  });
}


const { Sequelize, DataTypes } = require('sequelize');
const { BREAD_TYPES } = require("../../constants");


module.exports = (sequelize, Sequelize) => {
    const Topping = sequelize.define("Topping", {
        id: {
            type: DataTypes.INTEGER,
            allowNull: true
        },
        name: {
            type: DataTypes.STRING,
            primaryKey: true
        }
    })
}
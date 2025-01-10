const { Sequelize, DataTypes } = require('sequelize');
const { STATUTES } = require("../../constants")
module.exports = (sequelize, Sequelize) => {
    const Order = sequelize.define("Order", {
        id: {
            type: DataTypes.INTEGER,
            allowNull: false,
            primaryKey: true
        },
        status: {
            type: DataTypes.ENUM(STATUTES)
        }
    })
    return Order
}
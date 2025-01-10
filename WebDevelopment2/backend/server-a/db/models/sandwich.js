const { Sequelize, DataTypes } = require('sequelize');
const { BREAD_TYPES } = require("../../constants")

module.exports = (sequelize, Sequelize) => {
    const Sandwich = sequelize.define('Sandwich', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true
        },
        name: {
            type: DataTypes.STRING,
            allowNull: false,
        },
        breadType: {
            type: DataTypes.ENUM(BREAD_TYPES),
            allowNull: false
        }
    })
    return Sandwich
}

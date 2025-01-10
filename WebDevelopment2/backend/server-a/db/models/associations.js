
module.exports = (models) => {
    models.Sandwich.belongsToMany(models.Topping, { through: 'SandwichToppings' })
    models.Topping.belongsToMany(models.Sandwich, { through: 'SandwichToppings' })
    models.Sandwich.hasOne(models.Order)
}
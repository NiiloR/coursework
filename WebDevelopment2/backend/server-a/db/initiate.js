const sandwiches = require("./data/sandwiches")
const toppings = require("./data/toppings")

module.exports = async (sequelize) => {
    // Add sandwiches and toppings.
    await sequelize.models.Topping.bulkCreate(toppings)
    await sequelize.models.Sandwich.bulkCreate(sandwiches)

    // Populate SandwichToppings table
    for (const sandwich of sandwiches) {
        const toppingsNames = sandwich.toppings.split(", "); // Split toppings string into an array

        // Find the sandwich ID
        const sandwichRecord = await sequelize.models.Sandwich.findOne({
            where: { id: sandwich.id }
        });

        // Find the IDs of toppings
        const toppingRecords = await sequelize.models.Topping.findAll({
            where: { name: toppingsNames }
        });

        // Associate toppings with the sandwich
        await sandwichRecord.addToppings(toppingRecords);
    }
}
'use strict';
const { Sequelize } = require('sequelize');
const sequelize = new Sequelize(process.env.DB_NAME, process.env.DB_USER, process.env.DB_PASSWORD, {
  dialect: process.env.DIALECT,
  host: process.env.DB_HOST,
})
sequelize.authenticate().then(x => console.log('Connection has been established successfully.'));
require("./db/models/order.js")(sequelize, Sequelize)
require("./db/models/sandwich.js")(sequelize, Sequelize)
require("./db/models/topping.js")(sequelize, Sequelize)
require("./db/models/associations.js")(sequelize.models)
// Drop all tables and re-populate them with data
sequelize.sync({ force: true }).then(x => require("./db/initiate.js")(sequelize).then(x => console.log("Sandwiches and toppings added!")))


var fs = require('fs'),
  path = require('path'),
  http = require('http');

var app = require('connect')();
var swaggerTools = require('swagger-tools');
var jsyaml = require('js-yaml');
var serverPort = 8080;

// swaggerRouter configuration
var options = {
  swaggerUi: path.join(__dirname, '/swagger.json'),
  controllers: path.join(__dirname, './controllers'),
  useStubs: process.env.NODE_ENV === 'development' // Conditionally turn on stubs (mock mode)
};

// The Swagger document (require it, build it programmatically, fetch it from a URL, ...)
var spec = fs.readFileSync(path.join(__dirname, 'api/swagger.yaml'), 'utf8');
var swaggerDoc = jsyaml.safeLoad(spec);


app.use(function (req, res, next) {

  // Website you wish to allow to connect
  res.setHeader('Access-Control-Allow-Origin', '*');

  // Request methods you wish to allow
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

  // Request headers you wish to allow
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');

  // Pass to next layer of middleware
  next();
});

// This is for preflight check.
app.use(function (req, res, next) {
  if (req.method === "OPTIONS") {
    res.writeHead(200);
    res.end();
  }
  else {
    next();
  }
})

// Initialize the Swagger middleware
swaggerTools.initializeMiddleware(swaggerDoc, function (middleware) {

  // Interpret Swagger resources and attach metadata to request - must be first in swagger-tools middleware chain
  app.use(middleware.swaggerMetadata());

  // Validate Swagger requests
  app.use(middleware.swaggerValidator());

  // Route validated requests to appropriate controller
  app.use(middleware.swaggerRouter(options));

  // Serve the Swagger documents and Swagger UI
  app.use(middleware.swaggerUi());

  // Start the server
  http.createServer(app).listen(serverPort, function () {
    console.log('Your server is listening on port %d (http://localhost:%d)', serverPort, serverPort);
    console.log('Swagger-ui is available on http://localhost:%d/docs', serverPort);
  });
});

module.exports = sequelize
const receiveTask = require("./rabbit-utils/receiveTask.js")
receiveTask.getTask(process.env.MESSAGE_QUEUE, process.env.INPUT_QUEUE).then(x => console.log("Server A waiting for messages"))
const path = require("path");
require("dotenv").config();

const express = require("express");
const bodyParser = require("body-parser");
const { graphqlExpress } = require("apollo-server-express");
const { makeExecutableSchema } = require("graphql-tools");
const expressPlayground = require("graphql-playground-middleware-express").default;
const { ApolloEngine } = require("apollo-engine");

const Pokemon = require("./models/Pokemon.js");
const Ability = require("./models/Ability.js");
const UserPreferences = require("./models/UserPreferences.js");

const PokeApiConnector = require("./PokeApiConnector.js");
const userPreferencesConnector = require("./UserPreferencesConnector.js");

const typeDefs = require("./schema.graphql");
const resolvers = require("./resolvers.js");

const __PROD__ = process.env.NODE_ENV === "production";
const __CACHE__ = !process.env.NO_CACHE;
console.log("ENV:");
console.log("PROD", __PROD__);
console.log("CACHE", __CACHE__);

const schema = makeExecutableSchema({
  typeDefs,
  resolvers
});

const pokeApiConnector = new PokeApiConnector();

const context = {
  Pokemon: new Pokemon({ connector: pokeApiConnector }),
  Ability: new Ability({ connector: pokeApiConnector }),
  UserPreferences: UserPreferences({ connector: userPreferencesConnector }),
};

const app = express();

app.use("/graphql", bodyParser.json(), graphqlExpress({
  schema,
  context,
  tracing: true,
  cacheControl: __CACHE__
}));

app.use("/playground", expressPlayground({ endpoint: "/graphql" }));

const engine = new ApolloEngine({
  apiKey: process.env.ENGINE_API
});

app.listen(3001, () => console.log("running"));
/*
engine.listen({
  port: __PROD__ ? 80 : 3001,
  expressApp: app
});
*/

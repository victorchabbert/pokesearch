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
const PokeApiConnector = require("./PokeApiConnector.js");

const typeDefs = require("./schema.graphql");
const resolvers = require("./resolvers.js");

const schema = makeExecutableSchema({
  typeDefs,
  resolvers
});

const pokeApiConnector = new PokeApiConnector();

const context = {
  Pokemon: new Pokemon({ connector: pokeApiConnector }),
  Ability: new Ability({ connector: pokeApiConnector })
}

const app = express();

app.use("/graphql", bodyParser.json(), graphqlExpress({
  schema,
  context,
  tracing: true,
  cacheControl: true
}));

app.use("/playground", expressPlayground({ endpoint: "/graphql" }));

const engine = new ApolloEngine({
  apiKey: process.env.ENGINE_API
});

// app.listen(4000, () => console.log(`Server listening on port 4000`));
engine.listen({
  port: 3000,
  expressApp: app
});

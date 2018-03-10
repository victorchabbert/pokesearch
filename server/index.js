const { GraphQLServer } = require("graphql-yoga");
const resolvers = require("./resolvers.js");

const server = new GraphQLServer({
  typeDefs: './server/schema.graphql',
  resolvers
});

const options = {
  port: 8000,
  endpoint: '/graphql',
  playground: '/playground'
};

server.start(options, ({ port }) => console.log(`Server listening on port ${port}`));

const fetch = require("node-fetch");

const resolvers = {
  Query: {
    pokemons: () => fetch(`${baseURL}/pokemon`).then(res => res.json()),
    pokemon: (parent, { name }, context) => {
      return context.Pokemon.getByName(name);
    },
  },
  Abilities: {
    ability: (parent, args, context) => {
      const ability = parent.ability;
      if (ability && ability.url) {
        return context.Ability.getByUrl(ability.url);
      }
      return null;
    }
  },
  Types: {
    type_: (parent) => parent.type
  }
};

module.exports = resolvers;

const fetch = require("node-fetch");

const resolvers = {
  Query: {
    pokemons: (parent, {search, limit, offset}, context) => {
      if (search && search !== "") {
        return context.Pokemon.searchByName(search);
      }
      return context.Pokemon.getNameList(limit, offset);
    },
    pokemon: (parent, { name }, context) => {
      return context.Pokemon.getByName(name);
    },
  },
  Pokemon: {
    types: (parent, {sort}) => {
      if (!parent.types) {
        return parent.types;
      }

      const compare = sort === "DESC" ? (a, b) => b.slot - a.slot : (a, b) => a.slot - b.slot;
      return parent.types.sort(compare);
    }
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

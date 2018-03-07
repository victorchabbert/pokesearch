const fetch = require("node-fetch");
const baseURL = `https://pokeapi.co/api/v2`;

const resolvers = {
  Query: {
    pokemons: () => fetch(`${baseURL}/pokemon`).then(res => res.json()),
    pokemon: (parent, { name }) => {
      return fetch(`${baseURL}/pokemon/${name}`).then(res => res.json());
    },
  },
  Abilities: {
    ability: (parent) => {
      console.log("Ability", parent);
      const ability = parent.ability;
      if (ability && ability.url) {
        return fetch(ability.url).then(res => res.json());
      }
      return null;
    }
  },
};

module.exports = resolvers;

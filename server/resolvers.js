const fetch = require("node-fetch");
const GraphQLDateTime = require("graphql-iso-date").GraphQLDateTime;

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
  Mutation: {
    likePokemon: async (_parent, { id, name }, context) => {
      const userId = context.user_token;
      if (!userId) {
        // TODO: send HTTP 401 error code
        return null;
      }

      const pokemon_id = parseInt(id, 10);
      const liked = await context.UserPreferences.isLikedBy(pokemon_id, userId);
      console.log("liked", liked, +liked);
      
      await context.UserPreferences.likePokemon(pokemon_id, userId, +liked);
      return context.Pokemon.getByName(name);
    }
  },
  Pokemon: {
    types: (parent, {sort}) => {
      if (!parent.types) {
        return parent.types;
      }

      const compare = sort === "DESC" ? (a, b) => b.slot - a.slot : (a, b) => a.slot - b.slot;
      return parent.types.sort(compare);
    },
    likes: (parent, _args, context) => {
      const id = parent.id;

      return context.UserPreferences.likes.load(id);
    },
    liked: async (parent, _args, context) => {
      const pokemonId = parent.id;
      const userId = context.user_token;

      const liked = await context.UserPreferences.isLikedBy(pokemonId, userId);

      return liked;
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
  },
  DateTime: GraphQLDateTime,
};

module.exports = resolvers;

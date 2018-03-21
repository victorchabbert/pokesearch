const fetch = require("node-fetch");
const GraphQLDateTime = require("graphql-iso-date").GraphQLDateTime;

const resolvers = {
  Query: {
    pokemons: (parent, { search, limit, offset }, context) => {
      if (search && search !== "") {
        return context.Pokemon.searchByName(search);
      }
      return context.Pokemon.getNameList(limit, offset);
    },
    pokemon: (parent, { name }, context) => {
      return context.Pokemon.getByName(name);
    },
    bookmarks: (parent, args, context) => {
      return context.UserPreferences.getUserBookmarks.load(context.user_token);
    }
  },
  Mutation: {
    likePokemon: async (_parent, { id, name }, context) => {
      const userId = context.user_token;
      if (!userId) {
        // TODO: send HTTP 401 error code
        return null;
      }

      const pokemon_id = typeof id === "string" ? parseInt(id, 10) : id;
      const liked = await context.UserPreferences.isLikedBy(pokemon_id, userId);

      await context.UserPreferences.likePokemon(pokemon_id, userId, +liked);
      return context.Pokemon.getByName(name);
    },
    bookmarkPokemon: async (_parent, { id, name }, context) => {
      const userId = context.user_token;
      if (!userId) {
        return null;
      }

      const pokemon_id = typeof id === "string" ? parseInt(id, 10) : id;
      const bookmarked = await context.UserPreferences.isBookmarkedBy(
        pokemon_id,
        userId
      );
      await context.UserPreferences.bookmarkPokemon(
        pokemon_id,
        name,
        userId,
        bookmarked
      );
      return context.Pokemon.getByName(name);
    }
  },
  Pokemon: {
    types: (parent, { sort }) => {
      if (!parent.types) {
        return parent.types;
      }

      const compare =
        sort === "DESC" ? (a, b) => b.slot - a.slot : (a, b) => a.slot - b.slot;
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
    },
    bookmarked: async (parent, _args, context) => {
      const pokemonId = parent.id;
      const userId = context.user_token;
      const bookmarked = await context.UserPreferences.isBookmarkedBy(
        pokemonId,
        userId
      );

      if (bookmarked && bookmarked.bookmarkedAt) {
        return {
          value: true,
          bookmarkedAt: bookmarked.bookmarkedAt
        };
      }

      return null;
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
    type_: parent => parent.type
  },
  DateTime: GraphQLDateTime,
  PokemonBookmark: {
    id: parent => parent.pokemon_id,
    name: parent => parent.pokemon_name
  }
};

module.exports = resolvers;

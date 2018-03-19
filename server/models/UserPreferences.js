const DataLoader = require("dataloader");

module.exports = ({ connector }) => {

  const likesDataloader = new DataLoader(pokemon_ids => connector.table('likes')
    .whereIn('pokemon_id', pokemon_ids).select()
    .then(rows => pokemon_ids.map(id => rows.filter(row =>  row.pokemon_id === id)))
  );

  const likesReverseDataloader = new DataLoader(pokemon_ids => connector.table('likes')
    .whereIn('pokemon_id', pokemon_ids).orderBy('id', 'desc').select()
    .then(rows => pokemon_ids.map(id => rows.filter(row =>  row.pokemon_id === id)))
  );

  const bookmarksDataloader = new DataLoader(pokemon_ids => connector.table('bookmarks')
    .whereIn('pokemon_id', pokemon_ids).select()
    .then(rows => pokemon_ids.map(id => rows.filter(row =>  row.pokemon_id === id)))
  );

  const isLikedByDataloader = (pokemonId, userId) => likesReverseDataloader.load(pokemonId)
    .then(res => res.find((like) => like.user === userId))
    .then(res => { console.log("isLikedBy", res); return res; })
    .then(res => !!res ? !res.disliked : false);

  const likePokemon = (pokemon_id, user, disliked) => connector
    .insert({pokemon_id, user, disliked , likedAt: new Date().toISOString()}).into('likes')
    .then(_id => {
      console.log("likes, pkm id", pokemon_id, typeof pokemon_id)
      likesReverseDataloader.clear(pokemon_id);
      likesDataloader.clear(pokemon_id);
      return disliked;
    });

  return {
    likes: likesDataloader,
    likesReverse: likesReverseDataloader,
    bookmarks: bookmarksDataloader,
    isLikedBy: isLikedByDataloader,
    likePokemon: likePokemon
  };
};

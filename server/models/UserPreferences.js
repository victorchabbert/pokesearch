const DataLoader = require("dataloader");

module.exports = ({ connector }) => {
  const likesDataloader = new DataLoader(pokemon_ids =>
    connector
      .table("likes")
      .whereIn("pokemon_id", pokemon_ids)
      .select()
      .then(rows =>
        pokemon_ids.map(id => rows.filter(row => row.pokemon_id === id))
      )
  );

  const likesReverseDataloader = new DataLoader(pokemon_ids =>
    connector
      .table("likes")
      .whereIn("pokemon_id", pokemon_ids)
      .orderBy("id", "desc")
      .select()
      .then(rows =>
        pokemon_ids.map(id => rows.filter(row => row.pokemon_id === id))
      )
  );

  const isLikedByDataloader = (pokemonId, userId) =>
    likesReverseDataloader
      .load(pokemonId)
      .then(res => res.find(like => like.user === userId))
      .then(res => (!!res ? !res.disliked : false));

  const likePokemon = (pokemon_id, user, disliked) =>
    connector
      .insert({ pokemon_id, user, disliked, likedAt: new Date().toISOString() })
      .into("likes")
      .then(_id => {
        likesReverseDataloader.clear(pokemon_id);
        likesDataloader.clear(pokemon_id);
        return disliked;
      });

  const bookmarksDataloader = new DataLoader(pokemon_ids =>
    connector
      .table("bookmarks")
      .whereIn("pokemon_id", pokemon_ids)
      .select()
      .then(rows =>
        pokemon_ids.map(id => rows.filter(row => row.pokemon_id === id))
      )
  );

  const bookmarksReverseDataloader = new DataLoader(pokemon_ids =>
    connector
      .table("bookmarks")
      .whereIn("pokemon_id", pokemon_ids)
      .orderBy("id", "desc")
      .select()
      .then(rows =>
        pokemon_ids.map(id => rows.filter(row => row.pokemon_id === id))
      )
  );

  const isBookmarkedByDataloader = (pokemon_id, userId) =>
    bookmarksReverseDataloader
      .load(pokemon_id)
      .then(res => res.find(bookmark => bookmark.user === userId));

  const bookmarkPokemon = (pokemon_id, name, user, bookmarked) => {
    if (bookmarked) {
      return connector
        .table("bookmarks")
        .where("pokemon_id", pokemon_id)
        .where("user", user)
        .delete()
        .then(_id => {
          bookmarksReverseDataloader.clear(pokemon_id);
          bookmarksDataloader.clear(pokemon_id);
          getUserBookmarks.clear(user);
          return false;
        });
    }
    return connector
      .insert({
        pokemon_id,
        pokemon_name: name,
        user,
        bookmarkedAt: new Date().toISOString()
      })
      .into("bookmarks")
      .then(_id => {
        bookmarksReverseDataloader.clear(pokemon_id);
        bookmarksDataloader.clear(pokemon_id);
        getUserBookmarks.clear(user);
        return true;
      });
  };

  const getUserBookmarks = new DataLoader(user_ids =>
    connector
      .table("bookmarks")
      .whereIn("user", user_ids)
      .select()
      .then(rows => user_ids.map(id => rows.filter(row => row.user === id)))
  );

  return {
    likes: likesDataloader,
    likesReverse: likesReverseDataloader,
    bookmarks: bookmarksDataloader,
    isLikedBy: isLikedByDataloader,
    likePokemon,
    isBookmarkedBy: isBookmarkedByDataloader,
    bookmarkPokemon,
    getUserBookmarks: getUserBookmarks
  };
};

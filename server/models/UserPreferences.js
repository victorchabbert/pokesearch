const DataLoader = require("dataloader");

module.exports = ({ connector }) => ({
  likes: new DataLoader(pokemon_ids => connector.table('likes')
    .whereIn('pokemon_id', pokemon_ids).select()
    .then(rows => pokemon_ids.map(id => rows.filter(row =>  row.pokemon_id === id)))
  ),
  bookmarks: new DataLoader(pokemon_ids => connector.table('bookmarks')
    .whereIn('pokemon_id', pokemon_ids).select()
    .then(rows => pokemon_ids.map(id => rows.filter(row =>  row.pokemon_id === id)))
  ),
})


exports.seed = function(knex, Promise) {
  // Deletes ALL existing entries
  return knex('likes').del()
    .then(function () {
      // Inserts seed entries
      return knex('likes').insert([
        {pokemon_id: 25, disliked: false, user: "beba11985431f837ba1308d3dc7cf702bd074fdeae77440cdc99d6fa88865f8", likedAt: new Date().toISOString()},
        {pokemon_id: 25, disliked: false, user: "beba11985431f837ba1308d3dc7cf702bd074fdeae77440cdc99d6fa88865f8", likedAt: new Date().toISOString()},
        {pokemon_id: 25, disliked: true, user: "beba11985431f837ba1308d3dc7cf702bd074fdeae77440cdc99d6fa88865f8", likedAt: new Date().toISOString()},
        {pokemon_id: 25, disliked: false, user: "beba11985431f837ba1308d3dc7cf702bd074fdeae77440cdc99d6fa88865f8", likedAt: new Date().toISOString()},
      ]);
    });
};

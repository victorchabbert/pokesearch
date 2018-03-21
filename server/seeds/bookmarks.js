exports.seed = function(knex, Promise) {
  // Deletes ALL existing entries
  return knex("bookmarks")
    .del()
    .then(function() {
      // Inserts seed entries
      return knex("bookmarks").insert([
        {
          pokemon_id: 25,
          pokemon_name: "pikachu",
          user:
            "beba11985431f837ba1308d3dc7cf702bd074fdeae77440cdc99d6fa88865f8",
          bookmarkedAt: new Date().toISOString()
        }
      ]);
    });
};

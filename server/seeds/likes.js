
exports.seed = function(knex, Promise) {
  // Deletes ALL existing entries
  return knex('likes').del()
    .then(function () {
      // Inserts seed entries
      return knex('likes').insert([
        {pokemon_id: 25, disliked: false},
        {pokemon_id: 25, disliked: true},
        {pokemon_id: 25, disliked: false},
        {pokemon_id: 25, disliked: false},
      ]);
    });
};

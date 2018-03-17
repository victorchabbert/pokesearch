exports.up = function(knex, Promise) {
  return knex.schema.createTable('bookmarks', table => {
    table.increments('id');
    table.integer('pokemon_id');
    table.dateTime('bookmarkedAt').defaultTo(knex.fn.now());
  });
};

exports.down = function(knex, Promise) {
  return knex.schema.dropTableIfExists('bookmarks');
};

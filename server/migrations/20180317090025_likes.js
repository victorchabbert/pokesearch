exports.up = function(knex, Promise) {
  return knex.schema.createTable('likes', table => {
    table.increments('id');
    table.integer('pokemon_id');
    table.boolean('disliked').notNull();
    table.string('user').notNull();
    table.timestamp('likedAt').notNull();
  });
};

exports.down = function(knex, Promise) {
  return knex.schema.dropTableIfExists('likes');
};

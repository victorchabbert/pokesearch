exports.up = function(knex, Promise) {
  return knex.schema.createTable('likes', table => {
    table.increments('id');
    table.integer('pokemon_id');
    table.boolean('disliked').notNull();
    table.timestamp('likedAt').defaultTo(new Date().toISOString());
  });
};

exports.down = function(knex, Promise) {
  return knex.schema.dropTableIfExists('likes');
};

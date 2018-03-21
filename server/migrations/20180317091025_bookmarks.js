exports.up = function(knex, Promise) {
  return knex.schema.createTable("bookmarks", table => {
    table.increments("id");
    table.integer("pokemon_id").notNull();
    table.string("user").notNull();
    table.timestamp("bookmarkedAt").notNull();
  });
};

exports.down = function(knex, Promise) {
  return knex.schema.dropTableIfExists("bookmarks");
};

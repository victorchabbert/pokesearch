const knex = require("knex");
const path = require("path");
const dbPath = path.resolve(__dirname, "./db/UserPreferencesDB.sqlite3");

const db = knex({
  client: "sqlite3",
  connection: {
    filename: dbPath
  }
});

module.exports = db;

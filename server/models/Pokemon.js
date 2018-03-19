const Fuse = require("fuse.js");
const flattenKeyName = require("../utils/flattenKeyName.js");

module.exports = class Pokemon {
  constructor({ connector }) {
    this.connector = connector;

    const options = {
      shouldSort: true,
      threshold: 0.6,
      location: 0,
      distance: 2,
      maxPatternLength: 32,
      minMatchCharLength: 1,
      keys: ["name"]
    };

    console.log("Fetching pokemon list.");
    const list = this.getNameList(2000).then(res => {
      console.log("Pokemon List fetched.");
      this.fuse = new Fuse(res.results, options);
      console.log("Search module initialized.");
    });
  }

  searchByName(search, limit = 20, offset = 0) {
    const searchResults = this.fuse.search(search);
    const results = searchResults.slice(offset, offset + limit);
    return {
      count: results.length,
      results
    };
  }

  getNameList(limit = 20, offset = 0) {
    return this.connector.get(`/pokemon?limit=${limit}&offset=${offset}`);
  }

  getByName(name) {
    return this.connector
      .get(`/pokemon/${name}`)
      .then(res => {
        let stats = res.stats;
        if (stats) {
          stats = stats.map(stat => flattenKeyName(stat, "stat"));
        }

        res.stats = stats;

        return res;
      })
      .then(res => {
        if (!res.stats || !(res.stats.length > 0)) {
          return res;
        }

        const firstElement = res.stats[0];
        const firstName = !!firstElement && firstElement.name;
        if (firstName !== "hp") {
          res.stats = res.stats.reverse();
        }

        return res;
      });
  }

  getAbilityFromUrl(url) {
    return this.connector.get(url);
  }
};

const Fuse = require("fuse.js");

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
      keys: [
        "name",
      ]
    };
    const list = this.getNameList(2000).then(res => {
      this.fuse = new Fuse(res.results, options);
    });
  }

  searchByName(search, limit = 20, offset = 0) {
    const searchResults = this.fuse.search(search);
    const results = searchResults.slice(offset, offset + limit)
    return {
      count: results.length,
      results
    }
  }

  getNameList(limit = 20, offset = 0) {
    return this.connector.get(`/pokemon?limit=${limit}&offset=${offset}`)
  }

  getByName(name) {
    return this.connector.get(`/pokemon/${name}`);
  }

  getAbilityFromUrl(url) {
    return this.connector.get(url);
  }
}

module.exports = class Pokemon {
  constructor({ connector }) {
    this.connector = connector;
  }

  getNameList(limit = 20, offset = 20) {
    return this.connector.get(`/pokemon?limit=${limit}&offset=${offset}`)
  }

  getByName(name) {
    return this.connector.get(`/pokemon/${name}`);
  }

  getAbilityFromUrl(url) {
    return this.connector.get(url);
  }
}

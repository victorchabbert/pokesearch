module.exports = class Pokemon {
  constructor({ connector }) {
    this.connector = connector;
  }

  getByName(name) {
    return this.connector.get(`/pokemon/${name}`);
  }

  getAbilityFromUrl(url) {
    return this.connector.get(url);
  }
}

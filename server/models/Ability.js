module.exports = class Ability {
  constructor({ connector }) {
    this.connector = connector;
  }

  getByName(name) {
    return this.connector.get(`/ability/${name}`);
  }

  getByUrl(url) {
    return this.connector.getAbsolute(url);
  }
};

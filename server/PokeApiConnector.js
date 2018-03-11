const fetch = require("node-fetch");
const DataLoader = require("dataloader");

const POKEAPI_API_ROOT = `https://pokeapi.co/api/v2`;

const cache = {};

module.exports = class PokeApiConnector {
  constructor() {
    this.loader = new DataLoader(this.fetch.bind(this), {
      batch: false
    });
  }

  fetch(urls) {
    return Promise.all(urls.map(url => {
      const cachedRes = cache[url];

      console.log("cache:", url, cachedRes);
      if (!!cachedRes) {
        return new Promise((resolve, reject) => {
          resolve(cachedRes);
        });
      }

      return new Promise((resolve, reject) =>
        fetch(url)
          .then(res => res.json())
          .then(res => {
            cache[url] = res;
            resolve(res);
          })
          .catch(error => {
            reject(error);
          })
      );
    }));
  }

  get(path) {
    return this.loader.load(POKEAPI_API_ROOT + path);
  }

  getAbsolute(path) {
    return this.loader.load(path);
  }
}

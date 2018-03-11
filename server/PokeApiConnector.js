const __CACHE__ = !process.env.NO_CACHE;

const fetch = require("node-fetch");
const DataLoader = require("dataloader");

const POKEAPI_API_ROOT = `https://pokeapi.co/api/v2`;

const cache = {};

module.exports = class PokeApiConnector {
  constructor() {
    this.loader = new DataLoader(this.fetch.bind(this), {
      batch: false,
      cache: __CACHE__
    });
  }

  fetch(urls) {
    return Promise.all(urls.map(url => {
      const cachedRes = cache[url];

      if (!!cachedRes) {
        return new Promise((resolve, reject) => {
          resolve(cachedRes);
        });
      }

      return new Promise((resolve, reject) =>
        fetch(url)
          .then(res => res.json())
          .then(res => {
            if (__CACHE__) {
              cache[url] = res;
            }

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

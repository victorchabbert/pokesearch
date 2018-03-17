const flattenKeyName = (object, key) => {
  if (typeof object !== "object" || !key) {
    return object;
  }

  const name = !!object[key] && object[key].name;
  if (name) {
    object.name = name;
    delete object.stat;
  }

  return object;
}

module.exports = flattenKeyName;

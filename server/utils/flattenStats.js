const flattenStatObject = (object) => {
  if (typeof object !== "object") {
    return object;
  }

  const name = !!object.stat && object.stat.name;
  if (name) {
    object.name = name;
    delete object.stat;
  }

  return object;
}

module.exports = flattenStatObject

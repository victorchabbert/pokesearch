let leftpad = (s: string, ~len: int, c: char) => {
  let length = len - String.length(s);
  length <= 0 ? s : Bytes.to_string(Bytes.make(length, c)) ++ s
};

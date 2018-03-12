let leftpad = (s: string, ~len: int, c: char) => {
  let length = len - String.length(s);
  length <= 0 ? s : Bytes.to_string(Bytes.make(length, c)) ++ s
};

let divideTen = (n) => float_of_int(n) /. 10.0;

let appendZero = (s) => s ++ "0";

let appendZeroIfNonNumeric = (s) => {
  let last = Char.code(s.[String.length(s) - 1]);
  last < 0 || last > 9 ? appendZero(s) : s
};

module Debounce = {
  type debounceOptions = {. "leading": bool, "maxWait": int, "trailing": bool};
  [@bs.module]
  external _make : ('fArgs => 'fOutput, int, debounceOptions) => [@bs] ('fArgs => 'fOutput) =
    "lodash.debounce";
  let make = (~wait=0, ~options=Js.Obj.empty(), f) => _make(f, wait, options);
  let call = (input, f) => [@bs] f(input);
};

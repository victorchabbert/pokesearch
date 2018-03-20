let leftpad = (s: string, ~len: int, c: char) => {
  let length = len - String.length(s);
  length <= 0 ? s : Bytes.to_string(Bytes.make(length, c)) ++ s;
};

let divideTen = n => float_of_int(n) /. 10.0;

let appendZero = s => s ++ "0";

let appendZeroIfNonNumeric = s => {
  let last = Char.code(s.[String.length(s) - 1]);
  last < 0 || last > 9 ? appendZero(s) : s;
};

module Debounce = {
  type debounceOptions = {
    .
    "leading": bool,
    "maxWait": int,
    "trailing": bool
  };
  [@bs.module]
  external _make :
    ('fArgs => 'fOutput, int, debounceOptions) => [@bs] ('fArgs => 'fOutput) =
    "lodash.debounce";
  let make = (~wait=0, ~options=Js.Obj.empty(), f) => _make(f, wait, options);
  let call = (input, f) => [@bs] f(input);
};

let convertDate = date =>
  [Js.Date.getMonth(date) +. 1.0, Js.Date.getDay(date)]
  |> List.map(int_of_float)
  |> List.map(string_of_int)
  |> List.map(i => leftpad(i, '0', ~len=2))
  |> String.concat("/")
  |> (++)(string_of_int(int_of_float(Js.Date.getFullYear(date))) ++ "/");

let unhyphenate: string => string = [%bs.raw
  {|
  function unhyphenate(str){
    return str.replace(/(\w)(-)(\w)/g, '$1 $3');
  }
|}
];

let titlecase = (str: string) =>
  String.lowercase(str)
  |> Js.String.split(" ")
  |> Array.map(word =>
       String.make(1, Char.uppercase(word.[0]))
       ++ String.sub(word, 1, String.length(word) - 1)
     )
  |> Array.to_list
  |> String.concat(" ");

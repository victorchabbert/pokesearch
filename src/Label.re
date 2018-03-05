[%bs.raw {|require("./label.css")|}];

let component = ReasonReact.statelessComponent("Label");

let se = ReasonReact.stringToElement;

let prepareClass = (s) =>
  switch s {
  | None => ""
  | Some(str) => str ++ " "
  };

let getColorClass = (color) =>
  switch color {
  | None => ""
  | Some(c) =>
    switch c {
    | "yellow" => " ps-label--yellow"
    | "black" => " ps-label--black"
    | _ => ""
    }
  };

let getColorFromKeyword = (w) =>
  switch w {
  | "electric" => "yellow"
  | _ => ""
  };

let make = (~label, ~className=?, ~color=?, _children) => {
  ...component,
  render: (_self) =>
    <span className=(prepareClass(className) ++ "ps-label" ++ getColorClass(color))>
      (se(label))
    </span>
};

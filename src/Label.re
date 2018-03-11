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
  | Some(c) => "ps--" ++ c
  };

let getColorFromKeyword = (w) =>
  switch w {
  | "normal" => "hillary"
  | "fire" => "light_red"
  | "fighting" => "red"
  | "water" => "blue"
  | "flying" => "light_purple"
  | "grass" => "green"
  | "poison" => "mauve"
  | "electric" => "yellow"
  | "ground" => "wheat"
  | "psychic" => "dark_pink"
  | "rock" => "brown"
  | "ice" => "light_blue"
  | "bug" => "kaki"
  | "dragon" => "purple"
  | "ghost" => "wine"
  | "dark" => "dark_brown"
  | "steel" => "grey"
  | "fairy" => "pink"
  | _ => "turquoise"
  };

let make = (~label, ~className=?, ~color=?, _children) => {
  ...component,
  render: (_self) =>
    <span
      className=([prepareClass(className), "ps-label", getColorClass(color)] |> String.concat(" "))>
      (se(label))
    </span>
};

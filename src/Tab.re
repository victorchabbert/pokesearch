[%bs.raw {|require("./tab.css")|}];

let component = ReasonReact.statelessComponent("Tab");

let se = ReasonReact.stringToElement;

let make = (~label: string, ~selected=false, ~onClick=?, _children) => {
  ...component,
  render: (_self) => {
    let className =
      [selected ? "ps-PokemonCard__sidebar-item--active " : "", "ps-PokemonCard__sidebar-item"]
      |> String.concat(" ");
    <div ?onClick className> <p className="ps-PokemonCard__sidebar-label"> (se(label)) </p> </div>
  }
};

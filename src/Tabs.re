let component = ReasonReact.statelessComponent("Tabs");

let make = (children) => {
  ...component,
  render: (_self) =>
    <nav className="ps-PokemonCard__sidebar"> (children |> ReasonReact.arrayToElement) </nav>
};

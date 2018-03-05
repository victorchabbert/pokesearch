[%bs.raw {|require("./pokemonList.css")|}];

let component = ReasonReact.statelessComponent("PokemonList");

let make = (children) => {
  ...component,
  render: (_self) =>
    <section className="ps-PokemonList">
      {children |> ReasonReact.arrayToElement}
    </section>
};

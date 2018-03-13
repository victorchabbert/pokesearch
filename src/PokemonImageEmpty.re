[%bs.raw {|require("./pokemonImageEmpty.css")|}];

let component = ReasonReact.statelessComponent("PokemonImageEmpty");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="ps-PokemonCard__picture-empty">
      <svg
        className="ps-PokemonCard__picture-empty-logo"
        xmlns="http://www.w3.org/2000/svg"
        viewBox="0 0 20 20">
        <path
          d="M0 4c0-1.1.9-2 2-2h16a2 2 0 0 1 2 2v12a2 2 0 0 1-2 2H2a2 2 0 0 1-2-2V4zm11 9l-3-3-6 6h16l-5-5-2 2zm4-4a2 2 0 1 0 0-4 2 2 0 0 0 0 4z"
        />
      </svg>
    </div>
};
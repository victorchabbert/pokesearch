let component = ReasonReact.statelessComponent("PokemonAbilities");

let se = ReasonReact.stringToElement;

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="ps-PokemonCard__tab-scroll">
      <div className="ps-PokemonCard__ability">
        <h4 className="ps-PokemonCard__ability-title"> (se("Static")) </h4>
        <p className="ps-PokemonCard__ability-description">
          (se("Has a 30% chance of paralyzing attacking Pokémon on contact."))
        </p>
      </div>
      <div className="ps-PokemonCard__ability">
        <h4 className="ps-PokemonCard__ability-title">
          (se("Lightning Rod"))
          <span className="ps-PokemonCard__ability-title--sub"> (se("hidden")) </span>
        </h4>
        <p className="ps-PokemonCard__ability-description">
          (
            se(
              "Redirects single-target electric moves to this Pokémon where possible.  Absorbs Electric moves, raising Special Attack one stage"
            )
          )
        </p>
      </div>
    </div>
};

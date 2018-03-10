[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let se = ReasonReact.stringToElement;

let pokemon: Pokemon.t = {
  id: 25,
  name: "Pikachu",
  weight: 60,
  height: 4,
  abilities: [
    {
      is_hidden: false,
      slot: 1,
      ability: {
        name: "static",
        effect: "Whenever a move makes contact with this Pokémon, the move's user has a 30% chance of being paralyzed. Pokémon that are immune to electric-type moves can still be paralyzed by this ability. Overworld: If the lead Pokémon has this ability, there is a 50% chance that encounters will be with an electric Pokémon, if applicable.",
        short_effect: "Has a 30% chance of paralyzing attacking Pokémon on contact."
      }
    },
    {
      is_hidden: true,
      slot: 3,
      ability: {
        name: "lightning-rod",
        effect: "All other Pokémon's single-target electric-type moves are redirected to this Pokémon if it is an eligible target. Other Pokémon's Electric moves raise this Pokémon's Special Attack one stage, negating any other effect on it, and cannot miss it. If the move's intended target also has this ability, the move is not redirected. When multiple Pokémon with this ability are possible targets for redirection, the move is redirected to the one with the highest Speed stat, or, in the case of a tie, to a random tied Pokémon. follow me takes precedence over this ability. If the Pokémon is a ground-type and thus immune to Electric moves, its immunity prevents the Special Attack boost.",
        short_effect: "Redirects single-target electric moves to this Pokémon where possible. Absorbs Electric moves, raising Special Attack one stage."
      }
    }
  ],
  stats: [],
  sprites: {
    back_default: "/img/25-back.png",
    front_default: "/img/25.png",
    back_shiny: "/img/25-back.png",
    front_shiny: "/img/25.png"
  },
  types: [{slot: 1, type_: {name: "electric"}}]
};

let make = (_children) => {
  ...component,
  render: (_self) =>
    <main className="ps-app">
      <h1 className="ps-title">
        <span className="ps-title--red"> (se("Poke")) </span>
        (se("search"))
      </h1>
      <section className="ps-Pokesearch">
        <Header> <SearchBar key="searchbar" /> </Header>
        <PokemonList>
          <PokemonCard key="1" pokemon />
          <PokemonCard key="2" pokemon />
        </PokemonList>
      </section>
    </main>
};

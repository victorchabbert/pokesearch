[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let se = ReasonReact.stringToElement;

let pokemon: Pokemon.t = {
  id: 25,
  name: "Pikachu",
  weight: 60,
  height: 4,
  abilities: [],
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
        <PokemonList> <PokemonCard key="1" pokemon /> </PokemonList>
      </section>
    </main>
};

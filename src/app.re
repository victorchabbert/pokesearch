[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let se = ReasonReact.stringToElement;

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
        <PokemonList> <PokemonCard key="1" /> </PokemonList>
      </section>
    </main>
};

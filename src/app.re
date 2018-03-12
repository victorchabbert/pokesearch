[%bs.raw {|require('./app.css')|}];

type state = {search: string};

type action =
  | ChangeValue(string);

let component = ReasonReact.reducerComponent("App");

let se = ReasonReact.stringToElement;

let updateSearch = (send) => {
  let update = PSUtils.Debounce.make((newValue) => send(ChangeValue(newValue)), ~wait=250);
  (newValue) => update |> PSUtils.Debounce.call(newValue)
};

let make = (_children) => {
  ...component,
  initialState: () => {search: ""},
  reducer: (action, _state) =>
    switch action {
    | ChangeValue(value) => ReasonReact.Update({search: value})
    },
  render: (self) =>
    <main className="ps-app">
      <h1 className="ps-title">
        <span className="ps-title--red"> (se("Poke")) </span>
        (se("search"))
      </h1>
      <section className="ps-Pokesearch">
        <Header> <SearchBar onChange=(updateSearch(self.send)) key="searchbar" /> </Header>
        <PokemonListContainer search=self.state.search />
      </section>
    </main>
};
/*
 <PokemonList>
   <PokemonContainer key="abra" name="abra" />
   <PokemonContainer key="pikachu" name="pikachu" />
   <PokemonContainer key="zubat" name="zubat" />
   <PokemonContainer key="baltoy" name="baltoy" />
   <PokemonContainer key="shedinja" name="shedinja" />
 </PokemonList>
 */

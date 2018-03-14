[%bs.raw {|require('./app.css')|}];

type state = {search: option(string)};

type action =
  | ChangeValue(option(string));

let emptyStringToNone = (str) => String.length(str) == 0 ? None : Some(str);

let component = ReasonReact.reducerComponent("App");

let se = ReasonReact.stringToElement;

let updateSearch = (send) => {
  let update =
    PSUtils.Debounce.make((newValue) => send(ChangeValue(emptyStringToNone(newValue))), ~wait=250);
  (newValue) => update |> PSUtils.Debounce.call(newValue)
};

let make = (_children) => {
  ...component,
  initialState: () => {search: None},
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
        <PokemonListContainer search=?self.state.search />
      </section>
    </main>
};

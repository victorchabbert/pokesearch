[%bs.raw {|require('./app.css')|}];

type state = {search: option(string)};

type action =
  | ChangeValue(option(string));

let emptyStringToNone = str => String.length(str) == 0 ? None : Some(str);

let component = ReasonReact.reducerComponent("App");

let se = ReasonReact.stringToElement;

let updateSearch = send => {
  let update =
    PSUtils.Debounce.make(newValue => send(ChangeValue(newValue)), ~wait=250);
  newValue => {
    let value = emptyStringToNone(newValue);
    ReasonReact.Router.push("/");
    update |> PSUtils.Debounce.call(value);
  };
};

let make = _children => {
  ...component,
  initialState: () => {search: None},
  reducer: (action, _state) =>
    switch action {
    | ChangeValue(value) => ReasonReact.Update({search: value})
    },
  render: self =>
    <main className="ps-app">
      <Link href="/" className="ps-title-href">
        <h1 className="ps-title">
          <span className="ps-title--red"> (se("Poke")) </span>
          (se("search"))
        </h1>
      </Link>
      <section className="ps-Pokesearch">
        <Header>
          <SearchBar onChange=(updateSearch(self.send)) key="searchbar" />
        </Header>
        <Router>
          ...(
               route =>
                 switch route {
                 | Search => <PokemonListContainer search=?self.state.search />
                 | PokemonDetail([name, ..._rest]) =>
                   <PokemonContainer name expanded=true />
                 | _ => ReasonReact.nullElement
                 }
             )
        </Router>
      </section>
      <BookmarkListContainer />
    </main>
};

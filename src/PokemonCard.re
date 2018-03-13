[%bs.raw {|require("./pokemonCard.css")|}];

type state = {
  active: int,
  expanded: bool
};

type action =
  | ToggleExpansion
  | ChangeTab(int);

let tabList = [|"Abilities", "Statistics", "Feed", "Impressions"|];

let component = ReasonReact.reducerComponent("PokemonCard");

let se = ReasonReact.stringToElement;

let accentBar = (types) => {
  let color = Label.getColorFromKeyword(types[0]##type_##name);
  let colorClass = Label.getColorClass(Js.Option.some(color));
  <div className=("ps-PokemonCard__bar " ++ colorClass) />
};

let make = (~pokemon, _children) => {
  ...component,
  initialState: () => {active: 0, expanded: false},
  reducer: (action, state) =>
    switch action {
    | ChangeTab(active) =>
      active != state.active ? ReasonReact.Update({...state, active}) : ReasonReact.NoUpdate
    | ToggleExpansion => ReasonReact.Update({...state, expanded: ! state.expanded})
    },
  render: (self) => {
    let activeTab =
      switch tabList[self.state.active] {
      | "Abilities" => <TabAbilities abilities=pokemon##abilities />
      | "Statistics" => <TabStatistics />
      | "Feed" => <TabFeed name=pokemon##name />
      | _ => ReasonReact.nullElement
      };
    <article className=((self.state.expanded ? "" : "ps-PokemonCard--short ") ++ "ps-PokemonCard")>
      <div className="ps-PokemonCard__header" onClick=((_e) => self.send(ToggleExpansion))>
        <PokemonImage sprites=?pokemon##sprites />
        <PokemonHeader
          name=pokemon##name
          types=pokemon##types
          height=pokemon##height
          weight=pokemon##weight
          id=pokemon##id
        />
      </div>
      <section className="ps-PokemonCard__details">
        <Tabs>
          (
            tabList
            |> Array.mapi(
                 (index, tabItem) =>
                   <Tab
                     key=(string_of_int(index))
                     label=tabItem
                     onClick=((_e) => self.send(ChangeTab(index)))
                     selected=(self.state.active == index)
                   />
               )
            |> ReasonReact.arrayToElement
          )
        </Tabs>
        activeTab
      </section>
      (accentBar(pokemon##types))
    </article>
  }
};

[%bs.raw {|require("./pokemonCard.css")|}];

type schema = {
  .
  "name": array(string),
  "base_stat": array(string)
};

type schemaResponse = {
  .
  "name": array(string),
  "base_stat": array(int)
};

[@bs.module]
external reshaper : (array('a), schema) => schemaResponse = "reshaper";

let formatOptions = stats => {
  let schema: schema = {"name": [|"String"|], "base_stat": [|"Number"|]};
  let pokemonData = reshaper(stats, schema);
  let baseStats =
    FrappeCharts.makeDataEntry(
      ~label="Pikachu",
      ~_type="bar",
      ~values=pokemonData##base_stat,
      ()
    );
  let data =
    FrappeCharts.makeData(
      ~labels=pokemonData##name,
      ~datasets=[|baseStats|],
      ()
    );
  FrappeCharts.makeOptions(~_type="bar", ~height=190, ~data, ());
};

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

let accentBar = types => {
  let color = Label.getColorFromKeyword(types[0]##type_##name);
  let colorClass = Label.getColorClass(Js.Option.some(color));
  <div className=("ps-PokemonCard__bar " ++ colorClass) />;
};

let make = (~pokemon, ~expanded=false, _children) => {
  ...component,
  initialState: () => {active: 0, expanded},
  reducer: (action, state) =>
    switch action {
    | ChangeTab(active) =>
      active != state.active ?
        ReasonReact.Update({...state, active}) : ReasonReact.NoUpdate
    | ToggleExpansion =>
      ReasonReact.Update({...state, expanded: ! state.expanded})
    },
  render: self => {
    let activeTab =
      switch tabList[self.state.active] {
      | "Abilities" => <TabAbilities abilities=pokemon##abilities />
      | "Statistics" =>
        <TabStatistics chartOptions=(formatOptions(pokemon##stats)) />
      | "Feed" => <TabFeed name=pokemon##name />
      | "Impressions" => <TabImpressions likes=pokemon##likes />
      | _ => ReasonReact.nullElement
      };
    <article
      className=(
        (self.state.expanded ? "" : "ps-PokemonCard--short ")
        ++ "ps-PokemonCard"
      )>
      <div
        className="ps-PokemonCard__header"
        onClick=(_e => self.send(ToggleExpansion))>
        <PokemonImage sprites=?pokemon##sprites />
        <PokemonHeader
          liked=(Js.to_bool(pokemon##liked))
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
            |> Array.mapi((index, tabItem) =>
                 <Tab
                   key=(string_of_int(index))
                   label=tabItem
                   onClick=(_e => self.send(ChangeTab(index)))
                   selected=(self.state.active == index)
                 />
               )
            |> ReasonReact.arrayToElement
          )
        </Tabs>
        activeTab
      </section>
      (accentBar(pokemon##types))
    </article>;
  }
};

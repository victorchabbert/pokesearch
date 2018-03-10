[%bs.raw {|require("./pokemonCard.css")|}];

type state = {active: int};

type action =
  | ChangeTab(int);

type tabItem = {
  label: string,
  component: Pokemon.t => ReasonReact.reactElement
};

let tabList = [|
  {label: "Abilities", component: (pokemon) => <TabAbilities abilities=pokemon.abilities />},
  {label: "Statistics", component: (_pokemon) => <TabStatistics />},
  {label: "Feed", component: (pokemon) => <TabFeed name=pokemon.name />},
  {label: "Impressions", component: (pokemon) => <TabAbilities abilities=pokemon.abilities />}
|];

let component = ReasonReact.reducerComponent("PokemonCard");

let se = ReasonReact.stringToElement;

let make = (~pokemon: Pokemon.t, _children) => {
  ...component,
  initialState: () => {active: 0},
  reducer: (action, state) =>
    switch action {
    | ChangeTab(active) =>
      active != state.active ? ReasonReact.Update({active: active}) : ReasonReact.NoUpdate
    },
  render: (self) => {
    let activeTab = tabList[self.state.active].component(pokemon);
    <article className="ps-PokemonCard">
      <PokemonImage />
      <PokemonHeader
        name=pokemon.name
        types=pokemon.types
        height=pokemon.height
        weight=pokemon.weight
        id=pokemon.id
      />
      <section className="ps-PokemonCard__details">
        <Tabs>
          (
            tabList
            |> Array.mapi(
                 (index, tabItem) =>
                   <Tab
                     key=(string_of_int(index))
                     label=tabItem.label
                     onClick=((_e) => self.send(ChangeTab(index)))
                     selected=(self.state.active == index)
                   />
               )
            |> ReasonReact.arrayToElement
          )
        </Tabs>
        activeTab
      </section>
      <div className="ps-PokemonCard__bar" />
    </article>
  }
};

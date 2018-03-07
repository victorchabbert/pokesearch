[%bs.raw {|require("./pokemonCard.css")|}];

type state = {active: int};

type action =
  | ChangeTab(int);

type tabItem = {
  label: string,
  component: Js.Option.t(ReasonReact.reactElement)
};

let tabList: array(tabItem) = [|
  {label: "Abilities", component: Js.Option.some(<PokemonAbilities />)},
  {label: "Statistics", component: None},
  {label: "Feed", component: None},
  {label: "Impressions", component: None}
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
    let activeTab =
      switch tabList[self.state.active].component {
      | Some(tabItem) => tabItem
      | None => se("Not found")
      };
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

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
      <header className="ps-PokemonCard__info">
        <h2 className="ps-PokemonCard__name"> (se(pokemon.name)) </h2>
        <div className="ps-PokemonCard__types">
          (
            pokemon.types
            |> List.map(
                 (t: Pokemon.typeItem) =>
                   <Label
                     key=(string_of_int(t.slot))
                     label=(String.capitalize(t.type_.name))
                     color=(Label.getColorFromKeyword(t.type_.name))
                     className="ps-PokemonCard__type"
                   />
               )
            |> Array.of_list
            |> ReasonReact.arrayToElement
          )
        </div>
        <h3 className="ps-PokemonCard__number">
          (se("#" ++ PSUtils.leftpad(string_of_int(pokemon.id), '0', ~len=3)))
        </h3>
        <div className="ps-PokemonCard__characteristics">
          <div className="ps-PokemonCard__physiognomy">
            <div className="ps-PokemonCard__physiognomy-item">
              <img src="./img/height.png" alt="height icon" />
              <p className="ps-PokemonCard__physiognomy-value">
                (
                  se(
                    (
                      pokemon.height
                      |> PSUtils.divideTen
                      |> string_of_float
                      |> PSUtils.appendZeroIfNonNumeric
                    )
                    ++ " m"
                  )
                )
              </p>
            </div>
            <div className="ps-PokemonCard__physiognomy-item">
              <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20">
                <path
                  d="M16 6v2h2l2 12H0L2 8h2V6a6 6 0 1 1 12 0zm-2 0a4 4 0 1 0-8 0v2h8V6zM4 10v2h2v-2H4zm10 0v2h2v-2h-2z"
                />
              </svg>
              <p className="ps-PokemonCard__physiognomy-value">
                (
                  se(
                    (
                      pokemon.weight
                      |> PSUtils.divideTen
                      |> string_of_float
                      |> PSUtils.appendZeroIfNonNumeric
                    )
                    ++ " kg"
                  )
                )
              </p>
            </div>
          </div>
          <div className="ps-PokemonCard__interactions">
            <svg
              className="ps-PokemonCard__heart"
              xmlns="http://www.w3.org/2000/svg"
              viewBox="0 0 20 20">
              <path
                d="M10 3.22l-.61-.6a5.5 5.5 0 0 0-7.78 7.77L10 18.78l8.39-8.4a5.5 5.5 0 0 0-7.78-7.77l-.61.61z"
              />
            </svg>
            <svg
              className="ps-PokemonCard__bookmark"
              xmlns="http://www.w3.org/2000/svg"
              viewBox="0 0 20 20">
              <path d="M2 2c0-1.1.9-2 2-2h12a2 2 0 0 1 2 2v18l-8-4-8 4V2zm2 0v15l6-3 6 3V2H4z" />
            </svg>
          </div>
        </div>
      </header>
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

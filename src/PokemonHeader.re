[%bs.raw {|require("./pokemonHeader.css")|}];

let component = ReasonReact.statelessComponent("PokemonHeader");

let se = ReasonReact.stringToElement;

let typeListToLabel = (types) =>
  Array.map(
    (t) =>
      <Label
        key=(string_of_int(t##slot))
        label=(String.capitalize(t##type_##name))
        color=(Label.getColorFromKeyword(t##type_##name))
        className="ps-PokemonCard__type"
      />,
    types
  );

let make = (~name, ~types, ~height, ~weight, ~id, _children) => {
  ...component,
  render: (_self) => {
    let typeList = types;
    <header className="ps-PokemonCard__info">
      <h2 className="ps-PokemonCard__name"> (se(name)) </h2>
      <div className="ps-PokemonCard__types">
        (typeListToLabel(typeList) |> ReasonReact.arrayToElement)
      </div>
      <h3 className="ps-PokemonCard__number"> (se("#" ++ PSUtils.leftpad(id, '0', ~len=3))) </h3>
      <div className="ps-PokemonCard__characteristics">
        <div className="ps-PokemonCard__physiognomy">
          <div className="ps-PokemonCard__physiognomy-item">
            <img src="./img/height.png" alt="height icon" />
            <p className="ps-PokemonCard__physiognomy-value">
              (
                se(
                  (
                    height |> PSUtils.divideTen |> string_of_float |> PSUtils.appendZeroIfNonNumeric
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
                    weight |> PSUtils.divideTen |> string_of_float |> PSUtils.appendZeroIfNonNumeric
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
  }
};

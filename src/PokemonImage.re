[%bs.raw {|require("./pokemonImage.css")|}];

type state = {
  shine: bool,
  flip: bool
};

type action =
  | ToggleShine
  | ToggleFlip;

let component = ReasonReact.reducerComponent("PokemonImage");

let se = ReasonReact.stringToElement;

let make = (~sprites, _children) => {
  ...component,
  initialState: () => {shine: false, flip: false},
  reducer: (action, state) =>
    switch action {
    | ToggleShine => ReasonReact.Update({...state, shine: ! state.shine})
    | ToggleFlip => ReasonReact.Update({...state, flip: ! state.flip})
    },
  render: (self) =>
    <figure
      className=(
        "ps-PokemonCard__picture" ++ (self.state.flip ? " ps-PokemonCard__picture--flipped" : "")
      )>
      (
        self.state.shine ?
          <div className="ps-PokemonCard__flipper">
            <img src=sprites##front_shiny alt="pikachu" />
            <img src=sprites##back_shiny alt="pikachu" />
          </div> :
          <div className="ps-PokemonCard__flipper">
            <img src=sprites##front_default alt="pikachu" />
            <img src=sprites##back_default alt="pikachu" />
          </div>
      )
      <div className="ps-PokemonCard__picture-controls">
        <div
          className=(
            (self.state.shine ? "ps-PokemonCard__picture-control--active " : "")
            ++ "ps-PokemonCard__picture-control"
          )>
          <svg
            className="ps-PokemonCard__control-icon"
            xmlns="http://www.w3.org/2000/svg"
            viewBox="0 0 20 20">
            <path
              d="M10 14a4 4 0 1 1 0-8 4 4 0 0 1 0 8zM9 1a1 1 0 1 1 2 0v2a1 1 0 1 1-2\n            0V1zm6.65 1.94a1 1 0 1 1 1.41 1.41l-1.4 1.4a1 1 0 1\n            1-1.41-1.41l1.4-1.4zM18.99 9a1 1 0 1 1 0 2h-1.98a1 1 0 1 1\n            0-2h1.98zm-1.93 6.65a1 1 0 1 1-1.41 1.41l-1.4-1.4a1 1 0 1 1\n            1.41-1.41l1.4 1.4zM11 18.99a1 1 0 1 1-2 0v-1.98a1 1 0 1 1 2\n            0v1.98zm-6.65-1.93a1 1 0 1 1-1.41-1.41l1.4-1.4a1 1 0 1 1 1.41\n            1.41l-1.4 1.4zM1.01 11a1 1 0 1 1 0-2h1.98a1 1 0 1 1 0\n            2H1.01zm1.93-6.65a1 1 0 1 1 1.41-1.41l1.4 1.4a1 1 0 1 1-1.41\n            1.41l-1.4-1.4z"
            />
          </svg>
          <span
            onClick=(
              (e) => {
                ReactEventRe.Synthetic.stopPropagation(e);
                self.send(ToggleShine)
              }
            )
            className="ps-label ps--black ps-PokemonCard__control-label">
            (se("Shiny"))
          </span>
        </div>
        <div className="ps-PokemonCard__picture-control">
          <svg
            className="ps-PokemonCard__control-icon"
            xmlns="http://www.w3.org/2000/svg"
            viewBox="0 0 20 20">
            <path
              d="M10 3v2a5 5 0 0 0-3.54 8.54l-1.41 1.41A7 7 0 0 1 10 3zm4.95 2.05A7 7 0 0 1 10 17v-2a5 5 0 0 0 3.54-8.54l1.41-1.41zM10 20l-4-4 4-4v8zm0-12V0l4 4-4 4z"
            />
          </svg>
          <span
            onClick=(
              (e) => {
                ReactEventRe.Synthetic.stopPropagation(e);
                self.send(ToggleFlip)
              }
            )
            className="ps-label ps--black ps-PokemonCard__control-label">
            (se("Flip"))
          </span>
        </div>
      </div>
    </figure>
};

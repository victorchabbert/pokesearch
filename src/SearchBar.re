[%bs.raw {|require('./searchBar.css')|}];

type state = {
  focused: bool,
  value: string
};

type action =
  | Focus
  | Blur
  | ChangeValue(string);

let component = ReasonReact.reducerComponent("SearchBar");

let make = (~onChange: string => unit, _children) => {
  ...component,
  initialState: () => {focused: false, value: ""},
  reducer: (action, state) =>
    switch action {
    | Focus => ReasonReact.Update({...state, focused: true})
    | Blur => ReasonReact.Update({...state, focused: false})
    | ChangeValue(value) => ReasonReact.Update({...state, value})
    },
  render: (self) => {
    let focused =
      [self.state.focused ? "ps-SearchBar--active" : "", "ps-SearchBar"] |> String.concat(" ");
    <div className=focused>
      <input
        className="ps-SearchBar__input"
        _type="search"
        onFocus=((_e) => self.send(Focus))
        onBlur=((_e) => self.send(Blur))
        onChange=(
          (e) => {
            let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value;
            self.send(ChangeValue(value));
            onChange(value)
          }
        )
      />
      <button className="ps-SearchBar__search-button">
        <svg
          className="ps-SearchBar__search" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20">
          <path
            d="M12.9 14.32a8 8 0 1 1 1.41-1.41l5.35 5.33-1.42 1.42-5.33-5.34zM8 14A6 6 0 1 0 8 2a6 6 0 0 0 0 12z"
          />
        </svg>
      </button>
    </div>
  }
};

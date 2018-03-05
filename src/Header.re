[%bs.raw {|require('./header.css')|}];

let component = ReasonReact.statelessComponent("Header");

let make = (children) => {
  ...component,
  render: (_self) =>
    <header className="ps-Pokesearch__header">
      {children |> ReasonReact.arrayToElement}
    </header>

}

[%bs.raw {|require('./searchBar.css')|}];

let component = ReasonReact.statelessComponent("SearchBar");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="ps-SearchBar">
      <input className="ps-SearchBar__input" _type="search" />
    </div>
};

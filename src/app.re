[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let se = ReasonReact.stringToElement;

let make = (_children) => {
  ...component,
  render: (_self) =>
    <main className="ps-app">
      <h1 className="ps-title">
        <span className="ps-title--red"> (ReasonReact.stringToElement("Poke")) </span>
        {ReasonReact.stringToElement("search")}
      </h1>
      <section className="ps-Pokesearch"></section>
    </main>
};

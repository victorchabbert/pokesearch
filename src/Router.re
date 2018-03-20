type route =
  | Search
  | PokemonDetail(list(string));

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch url.path {
  | ["pokemon", ...rest] => PokemonDetail(rest)
  | _ => Search
  };

let component = ReasonReact.reducerComponent("Router");

let make = children => {
  ...component,
  reducer,
  initialState: () => {
    route: ReasonReact.Router.dangerouslyGetInitialUrl() |> mapUrlToRoute
  },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> mapUrlToRoute))
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self => children(self.state.route)
};

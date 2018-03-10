type state = {
  initialized: bool,
  el: ref(option(Dom.element))
};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("TabFeed");

let setTwitterElement = (theRef, {ReasonReact.state}) => state.el := Js.Nullable.to_opt(theRef);

let se = ReasonReact.stringToElement;

type twitter = {. "widgets": {. [@bs.meth] load : unit => unit}};

[@bs.val] [@bs.scope "window"] [@bs.return nullable] external twttr : option(twitter) = "twttr";

[@bs.val] [@bs.scope "document"] external createElement : string => Dom.element = "createElement";

let createTwitterScript: unit => Dom.element = [%bs.raw
  {|
  function() {
    var node = document.createElement("script");
    node.src = "//platform.twitter.com/widgets.js";
    node.async = true;
    node.id = "twitter-wjs";
    return node;
  }
|}
];

let make = (~name, _children) => {
  ...component,
  initialState: () => {initialized: false, el: ref(None)},
  didMount: ({state}) =>
    switch twttr {
    | Some(tweets) =>
      tweets##widgets##load();
      ReasonReact.Update({...state, initialized: true})
    | None =>
      switch state.el^ {
      | Some(el) =>
        let parent = ReactDOMRe.domElementToObj(el);
        let twttrScript = createTwitterScript();
        ignore(parent##parentNode##appendChild(twttrScript));
        ReasonReact.Update({...state, initialized: true})
      | None =>
        Js.log("No element");
        ReasonReact.NoUpdate
      }
    },
  reducer: (action, _state) =>
    switch action {
    | Nothing => ReasonReact.NoUpdate
    },
  render: (self) => {
    let tweets =
      ReasonReact.cloneElement(
        <a className="twitter-timeline" href=("https://twitter.com/hashtag/" ++ name)>
          (self.state.initialized ? se("#" ++ name ++ " Tweets") : se("loading"))
        </a>,
        ~props={"data-widget-id": "972062166978367488", "ref": self.handle(setTwitterElement)},
        [||]
      );
    <div> tweets </div>
  }
};

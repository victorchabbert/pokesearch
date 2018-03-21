[%bs.raw {|require("./tabImpressions.css")|}];

type state = {
  chart: ref(option(FrappeCharts.t)),
  chartDom: ref(option(Dom.element))
};

type action =
  | Nothing;

let setChartDom = (theRef, {ReasonReact.state}) =>
  state.chartDom := Js.Nullable.to_opt(theRef);

type schema = {
  .
  "value": array(string),
  "likedAt": array(string)
};

type schemaResponse = {
  .
  "value": array(int),
  "likedAt": array(string)
};

[@bs.module]
external reshaper : (array('a), schema) => schemaResponse = "reshaper";

type likesData = {
  .
  "value": int,
  "likedAt": string
};

let makeOptions = likes =>
  if (Array.length(likes) == 0) {
    FrappeCharts.makeOptions(
      ~_type="line",
      ~height=190,
      ~data=FrappeCharts.makeData(~labels=[|"No data"|], ~datasets=[||], ()),
      ()
    );
  } else {
    Js.log2("chart", likes);
    let counter = ref(0);
    let likesData: array(likesData) =
      likes
      |> Array.map(like => {
           counter := counter^ + (Js.to_bool(like##disliked) ? (-1) : 1);
           let date =
             switch (Js.Json.decodeString(like##likedAt)) {
             | Some(dateString) => Js.Date.fromString(dateString)
             | None => Js.Date.fromFloat(Js.Date.now())
             };
           {"value": counter^, "likedAt": PSUtils.convertDate(date)};
         });
    let schema = {"value": [|"Number"|], "likedAt": [|"String"|]};
    let dataExtracted = reshaper(likesData, schema);
    let likesOptions =
      FrappeCharts.makeDataEntry(
        ~label="Likes",
        ~_type="line",
        ~values=dataExtracted##value,
        ()
      );
    let data =
      FrappeCharts.makeData(
        ~labels=dataExtracted##likedAt,
        ~datasets=[|likesOptions|],
        ()
      );
    FrappeCharts.makeOptions(~_type="line", ~height=190, ~data, ());
  };

let component = ReasonReact.reducerComponent("TabImpressions");

let make = (~likes, _children) => {
  ...component,
  initialState: () => {chart: ref(None), chartDom: ref(None)},
  didMount: ({state}) => {
    let chart =
      switch state.chartDom^ {
      | Some(el) => Some(FrappeCharts.make(el, makeOptions(likes)))
      | None => None
      };
    state.chart := chart;
    ReasonReact.NoUpdate;
  },
  reducer: (action, _state) =>
    switch action {
    | Nothing => ReasonReact.NoUpdate
    },
  render: self =>
    <div
      className="ps-PokemonCard__impressions"
      ref=(self.handle(setChartDom))
    />
};

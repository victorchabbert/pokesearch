[%bs.raw {|require("./tabStatistics.css")|}];

type state = {
  chart: ref(option(FrappeCharts.t)),
  chartDom: ref(option(Dom.element))
};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("TabStatistics");

let setChartDom = (theRef, {ReasonReact.state}) => state.chartDom := Js.Nullable.to_opt(theRef);

let make = (_children) => {
  ...component,
  initialState: () => {chart: ref(None), chartDom: ref(None)},
  didMount: ({state}) => {
    let chart =
      switch state.chartDom^ {
      | Some(el) =>
        Some(
          FrappeCharts.make(
            el,
            FrappeCharts.makeOptions(
              ~_type="bar",
              ~height=190,
              ~data=
                FrappeCharts.makeData(
                  ~labels=[|"1", "2"|],
                  ~datasets=[|
                    FrappeCharts.makeDataEntry(
                      ~label="Test 1",
                      ~_type="bar",
                      ~values=[|1, 2|],
                      ()
                    ),
                    FrappeCharts.makeDataEntry(~label="Test 2", ~_type="bar", ~values=[|3, 4|], ())
                  |],
                  ()
                ),
              ()
            )
          )
        )
      | None => None
      };
    state.chart := chart;
    ReasonReact.NoUpdate
  },
  reducer: (action, _state) =>
    switch action {
    | Nothing => ReasonReact.NoUpdate
    },
  render: (self) => <div className="ps-PokemonCard__statistics" ref=(self.handle(setChartDom)) />
};

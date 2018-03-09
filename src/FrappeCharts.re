/*
 [@bs.deriving {jsConverter: newType}]
 type chartTypes = [
   [@bs.as "axis-mixed"] | `AxisMixed
   [@bs.as "bar"] | `Bar
   [@bs.as "line"] | `Line
   [@bs.as "pie"] | `Pie
   [@bs.as "percentage"] | `Percentage
 ];

 type region = {. "label": string, "start": int, "end": int};

 type marker = {. "label": string, "value": int};

 type dataEntry = {. "label": string, "type": abs_chartTypes, "values": list(int)};

 type data = {
   .
   "labels": list(string),
   "datasets": list(dataEntry),
   "yMarkers": list(marker),
   "yRegions": list(region)
 };

 type options = {
   .
   "title": string, "type": string, "height": int, "colors": list(string), "data": data
 };

 [@bs.new] [@bs.module "frappe-charts"] external FrappeCharts : (string, options ) => unit = "Charts";

 let options: options = {.
   "title": "Test",
   "type": `Bar
 };

 FrappeCharts
 */
type region = Js.t({. "label": string, "start": int, "end": int});

type marker = Js.t({. "label": string, "value": int});

type dataEntry = Js.t({. "label": string, "type": string, "values": array(int)});

type options = Js.t({.});

type data = Js.t({.});

[@bs.obj]
external makeOptions :
  (
    ~title: string=?,
    ~_type: string=?,
    ~data: data=?,
    ~height: int=?,
    ~isNavigable: int=?,
    ~valuesOverPoint: int=?,
    unit
  ) =>
  options =
  "";

[@bs.obj]
external makeDataEntry :
  (~label: string=?, ~_type: string=?, ~values: array(int)=?, unit) => dataEntry =
  "";

[@bs.obj]
external makeData :
  (
    ~labels: array(string)=?,
    ~datasets: array(dataEntry)=?,
    ~yRegions: array(region)=?,
    ~yMarkers: array(marker)=?,
    unit
  ) =>
  data =
  "";

type t = {. [@bs.meth] update : data => unit};

[@bs.new] [@bs.module "frappe-charts/dist/frappe-charts.min.esm"]
external make : (Dom.element, options) => t =
  "default";

let dataObj =
  makeData(
    ~labels=[|"1", "2", "3"|],
    ~datasets=[|makeDataEntry(~label="Test", ~_type="bar", ~values=[|1, 2, 3, 4|], ())|],
    ()
  );
/*
 let charts = make("#test", makeOptions(~title="Hello", ~_type="bar", ~data=dataObj, ()));
 */

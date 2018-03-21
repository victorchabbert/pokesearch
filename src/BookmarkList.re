[%bs.raw {|require("./bookmarkList.css")|}];

let component = ReasonReact.statelessComponent("BookmarkList");

let se = ReasonReact.stringToElement;

let make = (~bookmarks, _children) => {
  ...component,
  render: _self =>
    <div className="ps-BookmarkList">
      (
        bookmarks
        |> Array.mapi((index, item) =>
             <Link
               key=(string_of_int(index))
               className="ps-BookmarkList__item"
               href=("/pokemon/" ++ item##name)>
               (se(item##name |> PSUtils.unhyphenate |> PSUtils.titlecase))
             </Link>
           )
        |> ReasonReact.arrayToElement
      )
    </div>
};

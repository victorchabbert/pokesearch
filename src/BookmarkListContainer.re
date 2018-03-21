module BookmarkListQuery = [%graphql
  {|
  query getUserBookmarks {
    bookmarks {
      name
      bookmarkedAt
    }
  }
|}
];

module Query = Apollo.Client.Query;

let component = ReasonReact.statelessComponent("BookmarkListContainer");

let se = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  render: _self => {
    let bookmarkListQuery = BookmarkListQuery.make();
    <Query query=bookmarkListQuery>
      ...(
           (response, parse) =>
             switch response {
             | Loading => ReasonReact.nullElement
             | Failed(_error) => ReasonReact.nullElement
             | Loaded(result) =>
               <BookmarkList bookmarks=(parse @@ result)##bookmarks />
             }
         )
    </Query>;
  }
};

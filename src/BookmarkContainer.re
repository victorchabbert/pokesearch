module TogglePokemonBookmark = [%graphql
  {|
  mutation togglePokemonBookmark($id: ID!, $name: String!) {
    bookmarkPokemon(id: $id, name: $name) {
      bookmarked {
        value
        bookmarkedAt
      }
    }
  }
|}
];

type state = {bookmark: bool};

type action =
  | Bookmark(bool);

let component = ReasonReact.reducerComponent("BookmarkContainer");

module Mutation = Apollo.Client.Mutation;

let make = (~id: string, ~name: string, ~bookmarked: bool, _children) => {
  ...component,
  initialState: () => {bookmark: bookmarked},
  reducer: (action, state) =>
    switch action {
    | Bookmark(value) =>
      value == state.bookmark ?
        ReasonReact.NoUpdate : ReasonReact.Update({bookmark: value})
    },
  render: self => {
    let toggleBookmark = bookmark => self.send(Bookmark(bookmark));
    let togglePokemonBookmarkMutation =
      TogglePokemonBookmark.make(~id, ~name, ());
    <Mutation>
      ...(
           (mutate, result) => {
             switch result {
             | NotCalled => ()
             | Loading => Js.log3("Bookmark loading", id, name)
             | Loaded(response) =>
               let parse = togglePokemonBookmarkMutation##parse;
               let pokemon = parse(response)##bookmarkPokemon;
               switch pokemon {
               | Some(pokemon) =>
                 switch pokemon##bookmarked {
                 | Some(_bookmark) => toggleBookmark(true)
                 | None => toggleBookmark(false)
                 }
               | None => Js.log("error parsing")
               };
             | Failed(error) => Js.log2("Bookmark error", error)
             };
             <svg
               onClick=(
                 event => {
                   ReactEventRe.Synthetic.stopPropagation(event);
                   mutate(togglePokemonBookmarkMutation);
                 }
               )
               className=(
                 [
                   "ps-PokemonCard__bookmark",
                   self.state.bookmark ?
                     "ps-PokemonCard__bookmark--active" : ""
                 ]
                 |> String.concat(" ")
               )
               xmlns="http://www.w3.org/2000/svg"
               viewBox="0 0 20 20">
               (
                 self.state.bookmark ?
                   <path
                     d="M2 2c0-1.1.9-2 2-2h12a2 2 0 0 1 2 2v18l-8-4-8 4V2z"
                   /> :
                   <path
                     d="M2 2c0-1.1.9-2 2-2h12a2 2 0 0 1 2 2v18l-8-4-8 4V2zm2 0v15l6-3 6 3V2H4z"
                   />
               )
             </svg>;
           }
         )
    </Mutation>;
  }
};

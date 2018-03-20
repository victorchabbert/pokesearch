module TogglePokemonLike = [%graphql
  {|
  mutation togglePokemonLike($id: ID!, $name: String!) {
    likePokemon(id: $id, name: $name) {
      liked
      likes {
        likedAt
      }
    }
  }
|}
];

type state = {liked: bool};

type action =
  | Like(bool);

let component = ReasonReact.reducerComponent("LikeContainer");

module Mutation = Apollo.Client.Mutation;

let make = (~id: string, ~name: string, ~liked: bool, _children) => {
  ...component,
  initialState: () => {liked: liked},
  reducer: (action, state) =>
    switch action {
    | Like(value) =>
      value == state.liked ?
        ReasonReact.NoUpdate : ReasonReact.Update({liked: value})
    },
  render: self => {
    let toggleLike = like => self.send(Like(like));
    let togglePokemonLikeMutation = TogglePokemonLike.make(~id, ~name, ());
    <Mutation>
      ...(
           (mutate, result) => {
             switch result {
             | NotCalled => ()
             | Loading => Js.log3("Like loading", id, name)
             | Loaded(response) =>
               let parse = togglePokemonLikeMutation##parse;
               let pokemon = parse(response)##likePokemon;
               switch pokemon {
               | Some(pokemon) => toggleLike(Js.to_bool(pokemon##liked))
               | None => Js.log("error parsing")
               };
             | Failed(error) => Js.log2("Like error", error)
             };
             <svg
               onClick=(
                 event => {
                   ReactEventRe.Synthetic.stopPropagation(event);
                   mutate(togglePokemonLikeMutation);
                 }
               )
               className=(
                 [
                   "ps-PokemonCard__heart",
                   self.state.liked ? "ps-PokemonCard__heart--active" : ""
                 ]
                 |> String.concat(" ")
               )
               xmlns="http://www.w3.org/2000/svg"
               viewBox="0 0 20 20">
               <path
                 d="M10 3.22l-.61-.6a5.5 5.5 0 0 0-7.78 7.77L10 18.78l8.39-8.4a5.5 5.5 0 0 0-7.78-7.77l-.61.61z"
               />
             </svg>;
           }
         )
    </Mutation>;
  }
};

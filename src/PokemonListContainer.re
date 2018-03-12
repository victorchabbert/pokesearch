module PokemonListQuery = [%graphql
  {|
  query getPokemons($search: String!) {
    pokemons(search: $search) {
      results {
        name
      }
    }
  }
|}
];

module Query = Apollo.Client.Query;

let component = ReasonReact.statelessComponent("PokemonListContainer");

let se = ReasonReact.stringToElement;

let make = (~search, _children) => {
  ...component,
  render: (_self) => {
    let pokemonListQuery = PokemonListQuery.make(~search, ());
    <Query query=pokemonListQuery>
      ...(
           (response, parse) =>
             switch response {
             | Loading => <div> (se("Loading...")) </div>
             | Failed(error) => <div> (se(error)) </div>
             | Loaded(result) =>
               switch (parse @@ result)##pokemons {
               | Some(pokemons) =>
                 <PokemonList>
                   (
                     pokemons##results
                     |> Js.Array.map(
                          (pokemon) => <PokemonContainer key=pokemon##name name=pokemon##name />
                        )
                     |> ReasonReact.arrayToElement
                   )
                 </PokemonList>
               | None => se("nothing")
               }
             }
         )
    </Query>
  }
};

module PokemonQuery = [%graphql
  {|
  query getPokemon($name: String!) {
    pokemon(name: $name) {
      id,
      name,
      weight,
      height,
      abilities {
        is_hidden,
        ability {
          name,
          effect_entries {
            short_effect
          }
        }
      },
      stats {
        base_stat
        name
      },
      sprites {
        front_default
        back_default
        front_shiny
        back_shiny
      },
      types {
        slot
        type_ {
          name
        }
      },
      likes {
        id
        disliked
        likedAt
      },
      liked
    }
  }
|}
];

module Query = Apollo.Client.Query;

let component = ReasonReact.statelessComponent("PokemonContainer");

let se = ReasonReact.stringToElement;

let make = (~name, _children) => {
  ...component,
  render: _self => {
    let pokemonQuery = PokemonQuery.make(~name, ());
    <Query query=pokemonQuery>
      ...(
           (response, parse) =>
             switch response {
             | Loading => <PokemonLoading name />
             | Failed(error) => <div> (se(error)) </div>
             | Loaded(result) =>
               switch (parse @@ result)##pokemon {
               | Some(pokemon) => <PokemonCard pokemon />
               | None => <div> (se("Nothing")) </div>
               }
             }
         )
    </Query>;
  }
};

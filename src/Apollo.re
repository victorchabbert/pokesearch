type dataObject = {. "__typename": string, "id": string, "results": array(Js.t({.}))};

let dataIdFromObject = (obj: dataObject) =>
  switch obj##__typename {
  | "Pokemon" => obj##id
  | "PokemonList" => "PokemonList" ++ string_of_int(Array.length(obj##results))
  | _ => obj##id
  };

let cache = ApolloInMemoryCache.createInMemoryCache(~dataIdFromObject, ());

let isProduction = Js.to_bool([%bs.raw {|process.env.NODE_ENV === "production"|}]);

let uri = "/graphql";

let httpLink = ApolloLinks.createHttpLink(~uri, ());

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient = ReasonApollo.createApolloClient(~cache, ~link=httpLink, ());
    }
  );

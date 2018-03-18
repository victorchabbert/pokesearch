type dataObject = {
  .
  "__typename": string,
  "id": string,
  "results": array(Js.t({.}))
};

let dataIdFromObject = (obj: dataObject) =>
  switch obj##__typename {
  | "Pokemon" => obj##id
  | "PokemonList" => "PokemonList" ++ string_of_int(Array.length(obj##results))
  | _ => obj##id
  };

let cache = ApolloInMemoryCache.createInMemoryCache(~dataIdFromObject, ());

let uri = "/graphql";

let httpLink = ApolloLinks.createHttpLink(~uri, ());

let contextHandler = () => {
  let _token = Authentication.getOrMakeToken();
  let headers = {
    "headers": {
      "user_token": {j|12345|j}
    }
  };
  headers;
};

let authLink = ApolloLinks.createContextLink(contextHandler);

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient =
        ReasonApollo.createApolloClient(
          ~cache,
          ~link=ApolloLinks.from([|authLink, httpLink|]),
          ()
        );
    }
  );

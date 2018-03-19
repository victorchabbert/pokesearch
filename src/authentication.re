module LocalForage = {
  [@bs.module "localforage"]
  external getItem : string => Js.Promise.t(Js.Json.t) = "";
  [@bs.module "localforage"]
  external setItem : (string, Js.Json.t) => Js.Promise.t(unit) = "";
};

module LocalStorage = {
  [@bs.scope ("window", "localStorage")] [@bs.val] [@bs.return nullable]
  external getItem : string => option(Js.Json.t) = "getItem";
  [@bs.scope ("window", "localStorage")] [@bs.val]
  external setItem : (string, Js.Json.t) => unit = "setItem";
};

let getRandomToken: unit => string = [%bs.raw
  {|
  function getRandomToken() {
      var randomPool = new Uint8Array(32);
      crypto.getRandomValues(randomPool);
      var hex = '';
      for (var i = 0; i < randomPool.length; ++i) {
          hex += randomPool[i].toString(16);
      }
      return hex;
  }
|}
];

let makeToken = () => {
  let token = getRandomToken();
  let tokenJson = Js.Json.string(token);
  LocalStorage.setItem("ps_user_token", tokenJson);
  token;
};

let getOrMakeToken = () => {
  let ut = LocalStorage.getItem("ps_user_token");
  switch ut {
  | Some(userTokenJson) =>
    switch (Js.Json.decodeString(userTokenJson)) {
    | Some(userToken) => userToken
    | None => makeToken()
    }
  | None => makeToken()
  };
};

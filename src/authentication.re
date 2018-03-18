module LocalForage = {
  [@bs.module "localforage"]
  external getItem : string => Js.Promise.t(Js.Json.t) = "";
  [@bs.module "localforage"]
  external setItem : (string, Js.Json.t) => Js.Promise.t(unit) = "";
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

let getOrMakeToken = () =>
  LocalForage.getItem("user_token")
  |> Js.Promise.then_(value => {
       let ut =
         switch (Js.Json.decodeString(value)) {
         | Some(userToken) => userToken
         | None =>
           let token = getRandomToken();
           let tokenJson = Js.Json.string(token);
           let _promise = LocalForage.setItem("user_token", tokenJson);
           token;
         };
       Js.Promise.resolve(ut);
     });

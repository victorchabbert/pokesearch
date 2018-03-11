[%bs.raw {|require("./tabAbilities.css")|}];

let component = ReasonReact.statelessComponent("TabAbilities");

let se = ReasonReact.stringToElement;

let abilityListToBlock = (abilities) =>
  Array.map(
    (abilityEntry) => {
      let hidden =
        Js.to_bool(abilityEntry##is_hidden) ?
          <span className="ps-PokemonCard__ability-title--sub"> (se("hidden")) </span> :
          ReasonReact.nullElement;
      <div key=abilityEntry##ability##name className="ps-PokemonCard__ability">
        <h4 className="ps-PokemonCard__ability-title">
          (se(abilityEntry##ability##name))
          hidden
        </h4>
        (
          abilityEntry##ability##effect_entries
          |> Array.map(
               (effect) =>
                 <p className="ps-PokemonCard__ability-description">
                   (se(effect##short_effect))
                 </p>
             )
          |> ReasonReact.arrayToElement
        )
      </div>
    },
    abilities
  );

let make = (~abilities, _children) => {
  ...component,
  render: (_self) => {
    let abilityList = abilities;
    <div className="ps-PokemonCard__tab-scroll">
      (abilityListToBlock(abilityList) |> ReasonReact.arrayToElement)
    </div>
  }
};

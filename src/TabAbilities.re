[%bs.raw {|require("./tabAbilities.css")|}];

let component = ReasonReact.statelessComponent("TabAbilities");

let se = ReasonReact.stringToElement;

let make = (~abilities: list(Pokemon.abilityItem), _children) => {
  ...component,
  render: (_self) =>
    <div className="ps-PokemonCard__tab-scroll">
      (
        abilities
        |> List.map(
             (pability: Pokemon.abilityItem) => {
               let hidden =
                 pability.is_hidden ?
                   <span className="ps-PokemonCard__ability-title--sub"> (se("hidden")) </span> :
                   ReasonReact.nullElement;
               <div key=pability.ability.name className="ps-PokemonCard__ability">
                 <h4 className="ps-PokemonCard__ability-title">
                   (se(pability.ability.name))
                   hidden
                 </h4>
                 <p className="ps-PokemonCard__ability-description">
                   (se(pability.ability.short_effect))
                 </p>
               </div>
             }
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>
};

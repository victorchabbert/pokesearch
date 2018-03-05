type abilityItem = {is_hidden: bool};

type stat = {base_stat: int};

type sprites = {
  back_default: string,
  front_default: string,
  back_shiny: string,
  front_shiny: string
};

type ptype = {name: string};

type typeItem = {
  slot: int,
  type_: ptype
};

type t = {
  id: int,
  name: string,
  weight: int,
  height: int,
  abilities: list(abilityItem),
  stats: list(stat),
  sprites,
  types: list(typeItem)
};

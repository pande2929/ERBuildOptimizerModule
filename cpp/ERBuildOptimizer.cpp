#include "./include/ERBuildOptimizer.h"
#include "./include/SubsetSum.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Populate passive status effects. Poison and bleed usually scale with ARC, but all others only scale with stones.
void ERBuildOptimizer::CalcPassives(Weapon &selected_weapon) {
  // Bleed Scaling
  if (selected_weapon.pass1_bleed > 0) {
	selected_weapon.max_bleed = CalculatePassive(selected_weapon.pass1_bleed,
												 selected_weapon.correction_arc,
												 selected_weapon.correction_pct_arc,
												 selected_weapon.bleed_stat_max_0,
												 selected_weapon.bleed_stat_max_1,
												 selected_weapon.bleed_stat_max_2,
												 selected_weapon.bleed_stat_max_3,
												 selected_weapon.bleed_stat_max_4,
												 selected_weapon.bleed_grow_0,
												 selected_weapon.bleed_grow_1,
												 selected_weapon.bleed_grow_2,
												 selected_weapon.bleed_grow_3,
												 selected_weapon.bleed_grow_4,
												 selected_weapon.bleed_adjustment_pt_grow_0,
												 selected_weapon.bleed_adjustment_pt_grow_1,
												 selected_weapon.bleed_adjustment_pt_grow_2,
												 selected_weapon.bleed_adjustment_pt_grow_3,
												 selected_weapon.bleed_adjustment_pt_grow_4);
  } else if (selected_weapon.pass2_bleed > 0) {
	selected_weapon.max_bleed = CalculatePassive(selected_weapon.pass2_bleed,
												 selected_weapon.correction_arc,
												 selected_weapon.correction_pct_arc,
												 selected_weapon.bleed_stat_max_0,
												 selected_weapon.bleed_stat_max_1,
												 selected_weapon.bleed_stat_max_2,
												 selected_weapon.bleed_stat_max_3,
												 selected_weapon.bleed_stat_max_4,
												 selected_weapon.bleed_grow_0,
												 selected_weapon.bleed_grow_1,
												 selected_weapon.bleed_grow_2,
												 selected_weapon.bleed_grow_3,
												 selected_weapon.bleed_grow_4,
												 selected_weapon.bleed_adjustment_pt_grow_0,
												 selected_weapon.bleed_adjustment_pt_grow_1,
												 selected_weapon.bleed_adjustment_pt_grow_2,
												 selected_weapon.bleed_adjustment_pt_grow_3,
												 selected_weapon.bleed_adjustment_pt_grow_4);
  } else if (selected_weapon.pass3_bleed) {
	selected_weapon.max_bleed = CalculatePassive(selected_weapon.pass3_bleed,
												 selected_weapon.correction_arc,
												 selected_weapon.correction_pct_arc,
												 selected_weapon.bleed_stat_max_0,
												 selected_weapon.bleed_stat_max_1,
												 selected_weapon.bleed_stat_max_2,
												 selected_weapon.bleed_stat_max_3,
												 selected_weapon.bleed_stat_max_4,
												 selected_weapon.bleed_grow_0,
												 selected_weapon.bleed_grow_1,
												 selected_weapon.bleed_grow_2,
												 selected_weapon.bleed_grow_3,
												 selected_weapon.bleed_grow_4,
												 selected_weapon.bleed_adjustment_pt_grow_0,
												 selected_weapon.bleed_adjustment_pt_grow_1,
												 selected_weapon.bleed_adjustment_pt_grow_2,
												 selected_weapon.bleed_adjustment_pt_grow_3,
												 selected_weapon.bleed_adjustment_pt_grow_4);
  }

  // Poison Scaling
  if (selected_weapon.pass1_poison > 0) {
	selected_weapon.max_poison = CalculatePassive(selected_weapon.pass1_poison,
												  selected_weapon.correction_arc,
												  selected_weapon.correction_pct_arc,
												  selected_weapon.poison_stat_max_0,
												  selected_weapon.poison_stat_max_1,
												  selected_weapon.poison_stat_max_2,
												  selected_weapon.poison_stat_max_3,
												  selected_weapon.poison_stat_max_4,
												  selected_weapon.poison_grow_0,
												  selected_weapon.poison_grow_1,
												  selected_weapon.poison_grow_2,
												  selected_weapon.poison_grow_3,
												  selected_weapon.poison_grow_4,
												  selected_weapon.poison_adjustment_pt_grow_0,
												  selected_weapon.poison_adjustment_pt_grow_1,
												  selected_weapon.poison_adjustment_pt_grow_2,
												  selected_weapon.poison_adjustment_pt_grow_3,
												  selected_weapon.poison_adjustment_pt_grow_4);
  } else if (selected_weapon.pass2_poison > 0) {
	selected_weapon.max_poison = CalculatePassive(selected_weapon.pass2_poison,
												  selected_weapon.correction_arc,
												  selected_weapon.correction_pct_arc,
												  selected_weapon.poison_stat_max_0,
												  selected_weapon.poison_stat_max_1,
												  selected_weapon.poison_stat_max_2,
												  selected_weapon.poison_stat_max_3,
												  selected_weapon.poison_stat_max_4,
												  selected_weapon.poison_grow_0,
												  selected_weapon.poison_grow_1,
												  selected_weapon.poison_grow_2,
												  selected_weapon.poison_grow_3,
												  selected_weapon.poison_grow_4,
												  selected_weapon.poison_adjustment_pt_grow_0,
												  selected_weapon.poison_adjustment_pt_grow_1,
												  selected_weapon.poison_adjustment_pt_grow_2,
												  selected_weapon.poison_adjustment_pt_grow_3,
												  selected_weapon.poison_adjustment_pt_grow_4);
  } else if (selected_weapon.pass3_poison > 0) {
	selected_weapon.max_poison = CalculatePassive(selected_weapon.pass3_poison,
												  selected_weapon.correction_arc,
												  selected_weapon.correction_pct_arc,
												  selected_weapon.poison_stat_max_0,
												  selected_weapon.poison_stat_max_1,
												  selected_weapon.poison_stat_max_2,
												  selected_weapon.poison_stat_max_3,
												  selected_weapon.poison_stat_max_4,
												  selected_weapon.poison_grow_0,
												  selected_weapon.poison_grow_1,
												  selected_weapon.poison_grow_2,
												  selected_weapon.poison_grow_3,
												  selected_weapon.poison_grow_4,
												  selected_weapon.poison_adjustment_pt_grow_0,
												  selected_weapon.poison_adjustment_pt_grow_1,
												  selected_weapon.poison_adjustment_pt_grow_2,
												  selected_weapon.poison_adjustment_pt_grow_3,
												  selected_weapon.poison_adjustment_pt_grow_4);
  }

  // Frostbite
  if (selected_weapon.pass1_frost > 0)
	selected_weapon.max_frostbite = selected_weapon.pass1_frost;
  else if (selected_weapon.pass2_frost > 0)
	selected_weapon.max_frostbite = selected_weapon.pass2_frost;
  else if (selected_weapon.pass3_frost > 0)
	selected_weapon.max_frostbite = selected_weapon.pass3_frost;

  // Sleep
  if (selected_weapon.pass1_sleep > 0)
	selected_weapon.max_sleep = selected_weapon.pass1_sleep;
  else if (selected_weapon.pass2_sleep > 0)
	selected_weapon.max_sleep = selected_weapon.pass2_sleep;
  else if (selected_weapon.pass3_sleep > 0)
	selected_weapon.max_sleep = selected_weapon.pass3_sleep;

  // Madness
  if (selected_weapon.pass1_madness > 0)
	selected_weapon.max_madness = selected_weapon.pass1_madness;
  else if (selected_weapon.pass2_madness > 0)
	selected_weapon.max_madness = selected_weapon.pass2_madness;
  else if (selected_weapon.pass3_madness > 0)
	selected_weapon.max_madness = selected_weapon.pass3_madness;

  // Scarlet Rot
  if (selected_weapon.pass1_scarlet_rot > 0)
	selected_weapon.max_scarlet_rot = selected_weapon.pass1_scarlet_rot;
  else if (selected_weapon.pass2_scarlet_rot > 0)
	selected_weapon.max_scarlet_rot = selected_weapon.pass2_scarlet_rot;
  else if (selected_weapon.pass3_scarlet_rot > 0)
	selected_weapon.max_scarlet_rot = selected_weapon.pass3_scarlet_rot;
}

// Calculate a passive effect
// Given by: base + base * passive_arcane_calc_correct * arc scaling
double ERBuildOptimizer::CalculatePassive(const int base,
										  const int correction_arc,
										  const double correction_pct_arc,
										  const int stat_max_0,
										  const int stat_max_1,
										  const int stat_max_2,
										  const int stat_max_3,
										  const int stat_max_4,
										  const int grow_0,
										  const int grow_1,
										  const int grow_2,
										  const int grow_3,
										  const int grow_4,
										  const double adj_pt_grow_0,
										  const double adj_pt_grow_1,
										  const double adj_pt_grow_2,
										  const double adj_pt_grow_3,
										  const double adj_pt_grow_4) const {

  // Build correction arrays
  int stat_max[5]{stat_max_0, stat_max_1, stat_max_2, stat_max_3, stat_max_4,};

  int grow[5]{grow_0, grow_1, grow_2, grow_3, grow_4,};

  double adj_pt_grow[5]{adj_pt_grow_0, adj_pt_grow_1, adj_pt_grow_2, adj_pt_grow_3, adj_pt_grow_4,};

  return base + base * CalculateCorrectFn(optimal_character.opt_arcane, stat_max, grow, adj_pt_grow) * correction_arc * correction_pct_arc
	  / 10000.0;
}

// Populate weapon skill damages and types.
void ERBuildOptimizer::CalcWeaponSkill(const Weapon &selected_weapon, const Tarnished &tarnished, WeaponSkill &selected_skill) {

  // base_damage = weapon.damage_physical * weapon.damage_pct_physical * selected_skill.atk_correct_physical / 100.0 + 4 * selected_skill.atk_physical
  double base_damage_physical =
	  selected_weapon.damage_physical * selected_weapon.damage_pct_physical * selected_skill.atk_correct_physical / 100.0
		  + 4 * selected_skill.atk_physical;
  double base_damage_magic = selected_weapon.damage_magic * selected_weapon.damage_pct_magic * selected_skill.atk_correct_magic / 100.0
	  + 4 * selected_skill.atk_magic;
  double base_damage_fire =
	  selected_weapon.damage_fire * selected_weapon.damage_pct_fire * selected_skill.atk_correct_fire / 100.0 + 4 * selected_skill.atk_fire;
  double base_damage_lightning =
	  selected_weapon.damage_lightning * selected_weapon.damage_pct_lightning * selected_skill.atk_correct_lightning / 100.0
		  + 4 * selected_skill.atk_lightning;
  double base_damage_holy =
	  selected_weapon.damage_holy * selected_weapon.damage_pct_holy * selected_skill.atk_correct_holy / 100.0 + 4 * selected_skill.atk_holy;

  bool two_hand_bonus = is_two_handing && !selected_skill.disable_2h_atk_bonus;

  AttributeTuple attribute_tuple
	  {tarnished.opt_strength, tarnished.opt_dexterity, tarnished.opt_intelligence, tarnished.opt_faith, tarnished.opt_arcane};

  double damage_physical =
	  CalculateCorrectedDamage(selected_weapon, attribute_tuple, DAMAGE_TYPE::PHYSICAL, base_damage_physical, two_hand_bonus);

  double damage_magic = CalculateCorrectedDamage(selected_weapon, attribute_tuple, DAMAGE_TYPE::MAGIC, base_damage_magic, two_hand_bonus);

  double damage_fire = CalculateCorrectedDamage(selected_weapon, attribute_tuple, DAMAGE_TYPE::FIRE, base_damage_fire, two_hand_bonus);

  double damage_lightning =
	  CalculateCorrectedDamage(selected_weapon, attribute_tuple, DAMAGE_TYPE::LIGHTNING, base_damage_lightning, two_hand_bonus);

  double damage_holy = CalculateCorrectedDamage(selected_weapon, attribute_tuple, DAMAGE_TYPE::HOLY, base_damage_holy, two_hand_bonus);

  selected_skill.max_physical_dmg = damage_physical;
  selected_skill.max_magic_dmg = damage_magic;
  selected_skill.max_fire_dmg = damage_fire;
  selected_skill.max_lightning_dmg = damage_lightning;
  selected_skill.max_holy_dmg = damage_holy;
  selected_skill.max_total_dmg = damage_physical + damage_magic + damage_fire + damage_lightning + damage_holy;
}

// Validate attributes against current weapon to ensure target level is attainable.
// Either target level will be too high, or target level will be too low.
int ERBuildOptimizer::Validate(const int min_max[][2]) const {
  int result = CALC_PROCEED;

  int min_attainable_level =
	  min_max[0][0] + min_max[1][0] + min_max[2][0] + min_max[3][0] + min_max[4][0] + optimal_character.vigor + optimal_character.mind
		  + optimal_character.endurance - LEVEL_OFFSET;

  int max_attainable_level =
	  min_max[0][1] + min_max[1][1] + min_max[2][1] + min_max[3][1] + min_max[4][1] + optimal_character.vigor + optimal_character.mind
		  + optimal_character.endurance - LEVEL_OFFSET;

  if (min_attainable_level > target_level) {
	// Minimum possibe attribute combo is too high for level.Decrease V, M, E, or raise Level
	return CALC_FAIL_LEVEL_LOW;
  } else if (max_attainable_level < target_level) {
	// Maximum possibe attribute combo is too low for level.Increase V, M, E, or lower Level
	return CALC_FAIL_LEVEL_HIGH;
  }

  return result;
}

// Python typed Constructor
ERBuildOptimizer::ERBuildOptimizer(const int target_level,
								   const bool is_two_handing,
								   const py::dict &character,
								   const int optimization_type) {
  this->target_level = target_level;
  this->is_two_handing = is_two_handing;
  this->optimization_type = optimization_type;

  // Fill out optimal_character with
  optimal_character.name = string(py::str(character["name"]));
  optimal_character.base_strength = stoi(string(py::str(character["base_strength"])));
  optimal_character.base_dexterity = stoi(string(py::str(character["base_dexterity"])));
  optimal_character.base_intelligence = stoi(string(py::str(character["base_intelligence"])));
  optimal_character.base_faith = stoi(string(py::str(character["base_faith"])));
  optimal_character.base_arcane = stoi(string(py::str(character["base_arcane"])));
  optimal_character.base_vigor = stoi(string(py::str(character["base_vigor"])));
  optimal_character.base_mind = stoi(string(py::str(character["base_mind"])));
  optimal_character.base_endurance = stoi(string(py::str(character["base_endurance"])));

  // User specified attributes
  optimal_character.vigor = stoi(string(py::str(character["vigor"])));
  optimal_character.mind = stoi(string(py::str(character["mind"])));
  optimal_character.endurance = stoi(string(py::str(character["endurance"])));

  // Optimized attributes
  optimal_character.opt_strength = stoi(string(py::str(character["opt_strength"])));
  optimal_character.opt_dexterity = stoi(string(py::str(character["opt_dexterity"])));
  optimal_character.opt_intelligence = stoi(string(py::str(character["opt_intelligence"])));
  optimal_character.opt_faith = stoi(string(py::str(character["opt_faith"])));
  optimal_character.opt_arcane = stoi(string(py::str(character["opt_arcane"])));
}

// Non-python typed Constructor
ERBuildOptimizer::ERBuildOptimizer(const int target_level,
								   const bool is_two_handing,
								   const Tarnished &character,
								   const int optimization_type) {
  this->target_level = target_level;
  this->is_two_handing = is_two_handing;
  this->optimization_type = optimization_type;
  optimal_character = character;
}

// Set weapon main hand and off hand weapons
void ERBuildOptimizer::SetWeapon(const bool main_hand, const py::dict &w) {
  Weapon weap;

  // convert from dict to weapon
  weap.id = stoi(py::str(w["id"]));
  weap.name = string(py::str(w["name"]));
  weap.weapon_type = string(py::str(w["weapon_type"]));
  weap.origin_weapon = string(py::str(w["origin_weapon"]));

  // Base Damage
  weap.damage_physical = stoi(py::str(w["damage_physical"]));
  weap.damage_magic = stoi(py::str(w["damage_magic"]));
  weap.damage_fire = stoi(py::str(w["damage_fire"]));
  weap.damage_lightning = stoi(py::str(w["damage_lightning"]));
  weap.damage_holy = stoi(py::str(w["damage_holy"]));

  // Required Stats
  weap.required_str = stoi(py::str(w["required_str"]));
  weap.required_dex = stoi(py::str(w["required_dex"]));
  weap.required_int = stoi(py::str(w["required_int"]));
  weap.required_fai = stoi(py::str(w["required_fai"]));
  weap.required_arc = stoi(py::str(w["required_arc"]));

  // Base Correction Values
  weap.correction_str = stoi(py::str(w["correction_str"]));
  weap.correction_dex = stoi(py::str(w["correction_dex"]));
  weap.correction_int = stoi(py::str(w["correction_int"]));
  weap.correction_fai = stoi(py::str(w["correction_fai"]));
  weap.correction_arc = stoi(py::str(w["correction_arc"]));

  // Bitmask
  weap.attack_element_correct_bitmask_str = string(py::str(w["attack_element_correct_bitmask_str"]));

  // Convert the string attack element correct bitmask into an integer one
  weap.attack_element_correct_bitmask = ConvertBitMask(weap.attack_element_correct_bitmask_str);

  // Reinforcement Values
  weap.damage_pct_physical = stod(py::str(w["damage_pct_physical"]));
  weap.damage_pct_magic = stod(py::str(w["damage_pct_magic"]));
  weap.damage_pct_fire = stod(py::str(w["damage_pct_fire"]));
  weap.damage_pct_lightning = stod(py::str(w["damage_pct_lightning"]));
  weap.damage_pct_holy = stod(py::str(w["damage_pct_holy"]));
  weap.damage_pct_stamina = stod(py::str(w["damage_pct_stamina"]));
  weap.damage_pct_poise = stod(py::str(w["damage_pct_poise"]));
  weap.correction_pct_str = stod(py::str(w["correction_pct_str"]));
  weap.correction_pct_dex = stod(py::str(w["correction_pct_dex"]));
  weap.correction_pct_int = stod(py::str(w["correction_pct_int"]));
  weap.correction_pct_fai = stod(py::str(w["correction_pct_fai"]));
  weap.correction_pct_arc = stod(py::str(w["correction_pct_arc"]));
  weap.base_damage_pct_overall = stod(py::str(w["base_damage_pct_overall"]));

  // Calc Correct Values

  // Physical
  weap.physical_calc_correct_id = stoi(py::str(w["physical_calc_correct_id"]));
  weap.physical_stat_max_0 = stoi(py::str(w["physical_stat_max_0"]));
  weap.physical_stat_max_1 = stoi(py::str(w["physical_stat_max_1"]));
  weap.physical_stat_max_2 = stoi(py::str(w["physical_stat_max_2"]));
  weap.physical_stat_max_3 = stoi(py::str(w["physical_stat_max_3"]));
  weap.physical_stat_max_4 = stoi(py::str(w["physical_stat_max_4"]));
  weap.physical_grow_0 = stoi(py::str(w["physical_grow_0"]));
  weap.physical_grow_1 = stoi(py::str(w["physical_grow_1"]));
  weap.physical_grow_2 = stoi(py::str(w["physical_grow_2"]));
  weap.physical_grow_3 = stoi(py::str(w["physical_grow_3"]));
  weap.physical_grow_4 = stoi(py::str(w["physical_grow_4"]));
  weap.physical_adjustment_pt_grow_0 = stod(py::str(w["physical_adjustment_pt_grow_0"]));
  weap.physical_adjustment_pt_grow_1 = stod(py::str(w["physical_adjustment_pt_grow_1"]));
  weap.physical_adjustment_pt_grow_2 = stod(py::str(w["physical_adjustment_pt_grow_2"]));
  weap.physical_adjustment_pt_grow_3 = stod(py::str(w["physical_adjustment_pt_grow_3"]));
  weap.physical_adjustment_pt_grow_4 = stod(py::str(w["physical_adjustment_pt_grow_4"]));

  // Magic
  weap.magic_calc_correct_id = stoi(py::str(w["magic_calc_correct_id"]));
  weap.magic_stat_max_0 = stoi(py::str(w["magic_stat_max_0"]));
  weap.magic_stat_max_1 = stoi(py::str(w["magic_stat_max_1"]));
  weap.magic_stat_max_2 = stoi(py::str(w["magic_stat_max_2"]));
  weap.magic_stat_max_3 = stoi(py::str(w["magic_stat_max_3"]));
  weap.magic_stat_max_4 = stoi(py::str(w["magic_stat_max_4"]));
  weap.magic_grow_0 = stoi(py::str(w["magic_grow_0"]));
  weap.magic_grow_1 = stoi(py::str(w["magic_grow_1"]));
  weap.magic_grow_2 = stoi(py::str(w["magic_grow_2"]));
  weap.magic_grow_3 = stoi(py::str(w["magic_grow_3"]));
  weap.magic_grow_4 = stoi(py::str(w["magic_grow_4"]));
  weap.magic_adjustment_pt_grow_0 = stod(py::str(w["magic_adjustment_pt_grow_0"]));
  weap.magic_adjustment_pt_grow_1 = stod(py::str(w["magic_adjustment_pt_grow_1"]));
  weap.magic_adjustment_pt_grow_2 = stod(py::str(w["magic_adjustment_pt_grow_2"]));
  weap.magic_adjustment_pt_grow_3 = stod(py::str(w["magic_adjustment_pt_grow_3"]));
  weap.magic_adjustment_pt_grow_4 = stod(py::str(w["magic_adjustment_pt_grow_4"]));

  // Fire
  weap.fire_calc_correct_id = stoi(py::str(w["fire_calc_correct_id"]));
  weap.fire_stat_max_0 = stoi(py::str(w["fire_stat_max_0"]));
  weap.fire_stat_max_1 = stoi(py::str(w["fire_stat_max_1"]));
  weap.fire_stat_max_2 = stoi(py::str(w["fire_stat_max_2"]));
  weap.fire_stat_max_3 = stoi(py::str(w["fire_stat_max_3"]));
  weap.fire_stat_max_4 = stoi(py::str(w["fire_stat_max_4"]));
  weap.fire_grow_0 = stoi(py::str(w["fire_grow_0"]));
  weap.fire_grow_1 = stoi(py::str(w["fire_grow_1"]));
  weap.fire_grow_2 = stoi(py::str(w["fire_grow_2"]));
  weap.fire_grow_3 = stoi(py::str(w["fire_grow_3"]));
  weap.fire_grow_4 = stoi(py::str(w["fire_grow_4"]));
  weap.fire_adjustment_pt_grow_0 = stod(py::str(w["fire_adjustment_pt_grow_0"]));
  weap.fire_adjustment_pt_grow_1 = stod(py::str(w["fire_adjustment_pt_grow_1"]));
  weap.fire_adjustment_pt_grow_2 = stod(py::str(w["fire_adjustment_pt_grow_2"]));
  weap.fire_adjustment_pt_grow_3 = stod(py::str(w["fire_adjustment_pt_grow_3"]));
  weap.fire_adjustment_pt_grow_4 = stod(py::str(w["fire_adjustment_pt_grow_4"]));

  // Lightning
  weap.lightning_calc_correct_id = stoi(py::str(w["lightning_calc_correct_id"]));
  weap.lightning_stat_max_0 = stoi(py::str(w["lightning_stat_max_0"]));
  weap.lightning_stat_max_1 = stoi(py::str(w["lightning_stat_max_1"]));
  weap.lightning_stat_max_2 = stoi(py::str(w["lightning_stat_max_2"]));
  weap.lightning_stat_max_3 = stoi(py::str(w["lightning_stat_max_3"]));
  weap.lightning_stat_max_4 = stoi(py::str(w["lightning_stat_max_4"]));
  weap.lightning_grow_0 = stoi(py::str(w["lightning_grow_0"]));
  weap.lightning_grow_1 = stoi(py::str(w["lightning_grow_1"]));
  weap.lightning_grow_2 = stoi(py::str(w["lightning_grow_2"]));
  weap.lightning_grow_3 = stoi(py::str(w["lightning_grow_3"]));
  weap.lightning_grow_4 = stoi(py::str(w["lightning_grow_4"]));
  weap.lightning_adjustment_pt_grow_0 = stod(py::str(w["lightning_adjustment_pt_grow_0"]));
  weap.lightning_adjustment_pt_grow_1 = stod(py::str(w["lightning_adjustment_pt_grow_1"]));
  weap.lightning_adjustment_pt_grow_2 = stod(py::str(w["lightning_adjustment_pt_grow_2"]));
  weap.lightning_adjustment_pt_grow_3 = stod(py::str(w["lightning_adjustment_pt_grow_3"]));
  weap.lightning_adjustment_pt_grow_4 = stod(py::str(w["lightning_adjustment_pt_grow_4"]));

  // Holy
  weap.holy_calc_correct_id = stoi(py::str(w["holy_calc_correct_id"]));
  weap.holy_stat_max_0 = stoi(py::str(w["holy_stat_max_0"]));
  weap.holy_stat_max_1 = stoi(py::str(w["holy_stat_max_1"]));
  weap.holy_stat_max_2 = stoi(py::str(w["holy_stat_max_2"]));
  weap.holy_stat_max_3 = stoi(py::str(w["holy_stat_max_3"]));
  weap.holy_stat_max_4 = stoi(py::str(w["holy_stat_max_4"]));
  weap.holy_grow_0 = stoi(py::str(w["holy_grow_0"]));
  weap.holy_grow_1 = stoi(py::str(w["holy_grow_1"]));
  weap.holy_grow_2 = stoi(py::str(w["holy_grow_2"]));
  weap.holy_grow_3 = stoi(py::str(w["holy_grow_3"]));
  weap.holy_grow_4 = stoi(py::str(w["holy_grow_4"]));
  weap.holy_adjustment_pt_grow_0 = stod(py::str(w["holy_adjustment_pt_grow_0"]));
  weap.holy_adjustment_pt_grow_1 = stod(py::str(w["holy_adjustment_pt_grow_1"]));
  weap.holy_adjustment_pt_grow_2 = stod(py::str(w["holy_adjustment_pt_grow_2"]));
  weap.holy_adjustment_pt_grow_3 = stod(py::str(w["holy_adjustment_pt_grow_3"]));
  weap.holy_adjustment_pt_grow_4 = stod(py::str(w["holy_adjustment_pt_grow_4"]));

  // Poison
  weap.poison_calc_correct_id = stoi(py::str(w["poison_calc_correct_id"]));
  weap.poison_stat_max_0 = stoi(py::str(w["poison_stat_max_0"]));
  weap.poison_stat_max_1 = stoi(py::str(w["poison_stat_max_1"]));
  weap.poison_stat_max_2 = stoi(py::str(w["poison_stat_max_2"]));
  weap.poison_stat_max_3 = stoi(py::str(w["poison_stat_max_3"]));
  weap.poison_stat_max_4 = stoi(py::str(w["poison_stat_max_4"]));
  weap.poison_grow_0 = stoi(py::str(w["poison_grow_0"]));
  weap.poison_grow_1 = stoi(py::str(w["poison_grow_1"]));
  weap.poison_grow_2 = stoi(py::str(w["poison_grow_2"]));
  weap.poison_grow_3 = stoi(py::str(w["poison_grow_3"]));
  weap.poison_grow_4 = stoi(py::str(w["poison_grow_4"]));
  weap.poison_adjustment_pt_grow_0 = stod(py::str(w["poison_adjustment_pt_grow_0"]));
  weap.poison_adjustment_pt_grow_1 = stod(py::str(w["poison_adjustment_pt_grow_1"]));
  weap.poison_adjustment_pt_grow_2 = stod(py::str(w["poison_adjustment_pt_grow_2"]));
  weap.poison_adjustment_pt_grow_3 = stod(py::str(w["poison_adjustment_pt_grow_3"]));
  weap.poison_adjustment_pt_grow_4 = stod(py::str(w["poison_adjustment_pt_grow_4"]));

  // Bleed
  weap.bleed_calc_correct_id = stoi(py::str(w["bleed_calc_correct_id"]));
  weap.bleed_stat_max_0 = stoi(py::str(w["bleed_stat_max_0"]));
  weap.bleed_stat_max_1 = stoi(py::str(w["bleed_stat_max_1"]));
  weap.bleed_stat_max_2 = stoi(py::str(w["bleed_stat_max_2"]));
  weap.bleed_stat_max_3 = stoi(py::str(w["bleed_stat_max_3"]));
  weap.bleed_stat_max_4 = stoi(py::str(w["bleed_stat_max_4"]));
  weap.bleed_grow_0 = stoi(py::str(w["bleed_grow_0"]));
  weap.bleed_grow_1 = stoi(py::str(w["bleed_grow_1"]));
  weap.bleed_grow_2 = stoi(py::str(w["bleed_grow_2"]));
  weap.bleed_grow_3 = stoi(py::str(w["bleed_grow_3"]));
  weap.bleed_grow_4 = stoi(py::str(w["bleed_grow_4"]));
  weap.bleed_adjustment_pt_grow_0 = stod(py::str(w["bleed_adjustment_pt_grow_0"]));
  weap.bleed_adjustment_pt_grow_1 = stod(py::str(w["bleed_adjustment_pt_grow_1"]));
  weap.bleed_adjustment_pt_grow_2 = stod(py::str(w["bleed_adjustment_pt_grow_2"]));
  weap.bleed_adjustment_pt_grow_3 = stod(py::str(w["bleed_adjustment_pt_grow_3"]));
  weap.bleed_adjustment_pt_grow_4 = stod(py::str(w["bleed_adjustment_pt_grow_4"]));

  // Passives

  weap.pass1_poison = stoi(py::str(w["pass1_poison"]));
  weap.pass1_scarlet_rot = stoi(py::str(w["pass1_scarlet_rot"]));
  weap.pass1_bleed = stoi(py::str(w["pass1_bleed"]));
  weap.pass1_death = stoi(py::str(w["pass1_death"]));
  weap.pass1_frost = stoi(py::str(w["pass1_frost"]));
  weap.pass1_sleep = stoi(py::str(w["pass1_sleep"]));
  weap.pass1_madness = stoi(py::str(w["pass1_madness"]));

  weap.pass2_poison = stoi(py::str(w["pass2_poison"]));
  weap.pass2_scarlet_rot = stoi(py::str(w["pass2_scarlet_rot"]));
  weap.pass2_bleed = stoi(py::str(w["pass2_bleed"]));
  weap.pass2_death = stoi(py::str(w["pass2_death"]));
  weap.pass2_frost = stoi(py::str(w["pass2_frost"]));
  weap.pass2_sleep = stoi(py::str(w["pass2_sleep"]));
  weap.pass2_madness = stoi(py::str(w["pass2_madness"]));

  weap.pass3_poison = stoi(py::str(w["pass3_poison"]));
  weap.pass3_scarlet_rot = stoi(py::str(w["pass3_scarlet_rot"]));
  weap.pass3_bleed = stoi(py::str(w["pass3_bleed"]));
  weap.pass3_death = stoi(py::str(w["pass3_death"]));
  weap.pass3_frost = stoi(py::str(w["pass3_frost"]));
  weap.pass3_sleep = stoi(py::str(w["pass3_sleep"]));
  weap.pass3_madness = stoi(py::str(w["pass3_madness"]));

  // Maximized Values (will be needed by the template for display)
  weap.max_physical_dmg = stod(py::str(w["max_physical_dmg"]));
  weap.max_magic_dmg = stod(py::str(w["max_magic_dmg"]));
  weap.max_fire_dmg = stod(py::str(w["max_fire_dmg"]));
  weap.max_lightning_dmg = stod(py::str(w["max_lightning_dmg"]));
  weap.max_holy_dmg = stod(py::str(w["max_holy_dmg"]));
  weap.max_total_dmg = stod(py::str(w["max_total_dmg"]));

  weap.max_poison = stod(py::str(w["max_poison"]));
  weap.max_bleed = stod(py::str(w["max_bleed"]));
  weap.max_frostbite = stod(py::str(w["max_frostbite"]));
  weap.max_sleep = stod(py::str(w["max_sleep"]));
  weap.max_madness = stod(py::str(w["max_madness"]));
  weap.max_scarlet_rot = stod(py::str(w["max_scarlet_rot"]));

  if (main_hand) {
	mh_weapon = weap;
  } else {
	oh_weapon = weap;
	dual_wield = true;
  }
}

// Get calculation_result
int ERBuildOptimizer::GetCalculationResult() {
  return calculation_result;
}

// Converts a string bitmask to an integer one.
// On the DB side, string bitmask is a concatenation of AttackElementCorrectParam table columns.
inline int ERBuildOptimizer::ConvertBitMask(const std::string mask) {
  size_t length = mask.length();
  int bitmask = 0;

  for (size_t i = 0; i < length; i++) {
	bitmask |= ((char)mask[i] - '0') << (length - i - 1);
  }

  return bitmask;
}

// Entry point for the optimization work.
void ERBuildOptimizer::Optimize() {
  // Build min-max subset constraints.
  // Mins must be: greatest of the attr_req mainhand, attr_req offhand, and attr_base in class
  // Maxes can either go up to 99, OR min + 1 if not a scaling (correction > 0) attribute.

  int min_max[5][2]{};

  // Constrain strength range
  vector<int> attr = {optimal_character.base_strength, mh_weapon.required_str};

  if (dual_wield) {
	attr.push_back(oh_weapon.required_str);
  }

  // Reverse sort
  sort(attr.begin(), attr.end(), greater<int>());
  min_max[0][0] = attr[0];            // Min

  if (mh_weapon.correction_str > 0 || (dual_wield && oh_weapon.correction_str > 0)) {
	min_max[0][1] = MAX_ATTRIBUTE;      // Max
  } else {
	min_max[0][1] = attr[0];        // Max
  }

  // Constrain dexterity range
  attr.clear();
  attr.push_back(optimal_character.base_dexterity);
  attr.push_back(mh_weapon.required_dex);

  if (dual_wield) {
	attr.push_back(oh_weapon.required_dex);
  }

  // Reverse sort
  sort(attr.begin(), attr.end(), greater<int>());
  min_max[1][0] = attr[0];                // Min

  if (mh_weapon.correction_dex > 0 || (dual_wield && oh_weapon.correction_dex > 0)) {
	min_max[1][1] = MAX_ATTRIBUTE;      // Max
  } else {
	min_max[1][1] = attr[0];        // Max
  }

  // Constrain intelligence range
  attr.clear();
  attr.push_back(optimal_character.base_intelligence);
  attr.push_back(mh_weapon.required_int);

  if (dual_wield) {
	attr.push_back(oh_weapon.required_int);
  }

  // Reverse sort
  sort(attr.begin(), attr.end(), greater<int>());
  min_max[2][0] = attr[0];                // Min
  if (mh_weapon.correction_int > 0 || (dual_wield && oh_weapon.correction_int > 0)) {
	min_max[2][1] = MAX_ATTRIBUTE;      // Max
  } else {
	min_max[2][1] = attr[0];        // Max
  }

  // Constrain faith range
  attr.clear();
  attr.push_back(optimal_character.base_faith);
  attr.push_back(mh_weapon.required_fai);

  if (dual_wield) {
	attr.push_back(oh_weapon.required_fai);
  }

  // Reverse sort
  sort(attr.begin(), attr.end(), greater<int>());
  min_max[3][0] = attr[0];                // Min
  if (mh_weapon.correction_fai > 0 || (dual_wield && oh_weapon.correction_fai > 0)) {
	min_max[3][1] = MAX_ATTRIBUTE;      // Max
  } else {
	min_max[3][1] = attr[0];        // Max
  }

  // Constrain arcane range
  attr.clear();
  attr.push_back(optimal_character.base_arcane);
  attr.push_back(mh_weapon.required_arc);

  if (dual_wield) {
	attr.push_back(oh_weapon.required_arc);
  }

  // Reverse sort
  sort(attr.begin(), attr.end(), greater<int>());
  min_max[4][0] = attr[0];                // Min
  if (mh_weapon.correction_arc > 0 || (dual_wield && oh_weapon.correction_arc > 0)) {
	min_max[4][1] = MAX_ATTRIBUTE;      // Max
  } else {
	min_max[4][1] = attr[0];        // Max
  }

  // Ensure target level is actually reachable.
  // Three scenarios are possible:
  // 1. Scaling attribute maximums and VIG, MIND, END will always be less than target level. (Target level too high.)
  // 2. Scaling attribute minimums and VIG, MIND, END will always be greater than target level. (Target level too low.)
  // 3. A range of scaling attributes exists that can equal target level.
  calculation_result = Validate(min_max);
  if (calculation_result != CALC_PROCEED)
	return;

  // Determine the upper limit of attribute points that will be spread between STR, DEX, INT, FAI, and ARC
  int subset_target = target_level + LEVEL_OFFSET - optimal_character.vigor - optimal_character.mind - optimal_character.endurance;


  // Get all possible solution sets that add to subset_target. The optimal combination of attributes will be one of these returned subsets.
  vector<unsigned long long> solution_sets = SubsetSum::GetAllSubsets(subset_target, min_max);

  size_t solution_count = solution_sets.size();

  std::function<void(AttributeTuple &, ERBuildOptimizer &)> eval_func = EvaluateByAR;

  if (optimization_type == OPTIMIZE_SKILL) {
	std::function<void(int, int, int, int, int, ERBuildOptimizer &)> eval_func = EvaluateBySkillAR;
  }

  AttributeTuple attribute_tuple;

  // Evaluate all the solution sets and their permutations.
  for (size_t i = 0; i < solution_count; i++) {
	attribute_tuple.strength = (int)((solution_sets[i] & STR_MASK) >> 32);
	attribute_tuple.dexterity = (int)((solution_sets[i] & DEX_MASK) >> 24);
	attribute_tuple.intelligence = (int)((solution_sets[i] & INT_MASK) >> 16);
	attribute_tuple.faith = (int)((solution_sets[i] & FAI_MASK) >> 8);
	attribute_tuple.arcane = (int)(solution_sets[i] & ARC_MASK);

	// Depending, evaluation criteria, maybe come up with something a bit more elegant.
	eval_func(attribute_tuple, *this);
  }

  // Calculate passive status effect values.
  CalcPassives(mh_weapon);

  // Calculate weapon skill damage
  CalcWeaponSkill(mh_weapon, optimal_character, mh_skill);

  if (dual_wield) {
	CalcPassives(oh_weapon);
	CalcWeaponSkill(oh_weapon, optimal_character, oh_skill);
  }
}

// Evaluate a solution set.

void ERBuildOptimizer::EvaluateByAR(const AttributeTuple &attribute_tuple, ERBuildOptimizer &er) {
  // Calculate mainhand damages
  double mh_physical_damage = CalculateCorrectedDamage(er.mh_weapon,
													   attribute_tuple,
													   DAMAGE_TYPE::PHYSICAL,
													   er.mh_weapon.damage_physical * er.mh_weapon.damage_pct_physical,
													   er.is_two_handing);
  double mh_magic_damage = CalculateCorrectedDamage(er.mh_weapon,
													attribute_tuple,
													DAMAGE_TYPE::MAGIC,
													er.mh_weapon.damage_magic * er.mh_weapon.damage_pct_magic,
													er.is_two_handing);
  double mh_fire_damage = CalculateCorrectedDamage(er.mh_weapon,
												   attribute_tuple,
												   DAMAGE_TYPE::FIRE,
												   er.mh_weapon.damage_fire * er.mh_weapon.damage_pct_fire,
												   er.is_two_handing);
  double mh_lightning_damage = CalculateCorrectedDamage(er.mh_weapon,
														attribute_tuple,
														DAMAGE_TYPE::LIGHTNING,
														er.mh_weapon.damage_lightning * er.mh_weapon.damage_pct_lightning,
														er.is_two_handing);
  double mh_holy_damage = CalculateCorrectedDamage(er.mh_weapon,
												   attribute_tuple,
												   DAMAGE_TYPE::HOLY,
												   er.mh_weapon.damage_holy * er.mh_weapon.damage_pct_holy,
												   er.is_two_handing);

  double mh_total_damage = mh_physical_damage + mh_magic_damage + mh_fire_damage + mh_lightning_damage + mh_holy_damage;
  double total_damage = mh_total_damage;

  double oh_physical_damage = 0;
  double oh_magic_damage = 0;
  double oh_fire_damage = 0;
  double oh_lightning_damage = 0;
  double oh_holy_damage = 0;
  double oh_total_damage = 0;

  // Add off-hand damages
  if (er.dual_wield) {
	oh_physical_damage = CalculateCorrectedDamage(er.oh_weapon,
												  attribute_tuple,
												  DAMAGE_TYPE::PHYSICAL,
												  er.mh_weapon.damage_physical * er.mh_weapon.damage_pct_physical,
												  er.is_two_handing);
	oh_magic_damage = CalculateCorrectedDamage(er.oh_weapon,
											   attribute_tuple,
											   DAMAGE_TYPE::MAGIC,
											   er.mh_weapon.damage_magic * er.mh_weapon.damage_pct_magic,
											   er.is_two_handing);
	oh_fire_damage = CalculateCorrectedDamage(er.oh_weapon,
											  attribute_tuple,
											  DAMAGE_TYPE::FIRE,
											  er.mh_weapon.damage_fire * er.mh_weapon.damage_pct_fire,
											  er.is_two_handing);
	oh_lightning_damage = CalculateCorrectedDamage(er.oh_weapon,
												   attribute_tuple,
												   DAMAGE_TYPE::LIGHTNING,
												   er.mh_weapon.damage_lightning * er.mh_weapon.damage_pct_lightning,
												   er.is_two_handing);
	oh_holy_damage = CalculateCorrectedDamage(er.oh_weapon,
											  attribute_tuple,
											  DAMAGE_TYPE::HOLY,
											  er.mh_weapon.damage_holy * er.mh_weapon.damage_pct_holy,
											  er.is_two_handing);

	oh_total_damage = oh_physical_damage + oh_magic_damage + oh_fire_damage + oh_lightning_damage + oh_holy_damage;
	total_damage += oh_total_damage;
  }

  // Check if this is a new best
  if (total_damage > er.highest_damage) {
	er.highest_damage = total_damage;

	// Record new max damages
	er.mh_weapon.max_physical_dmg = mh_physical_damage;
	er.mh_weapon.max_magic_dmg = mh_magic_damage;
	er.mh_weapon.max_fire_dmg = mh_fire_damage;
	er.mh_weapon.max_lightning_dmg = mh_lightning_damage;
	er.mh_weapon.max_holy_dmg = mh_holy_damage;
	er.mh_weapon.max_total_dmg = mh_total_damage;

	if (er.dual_wield) {
	  er.oh_weapon.max_physical_dmg = oh_physical_damage;
	  er.oh_weapon.max_magic_dmg = oh_magic_damage;
	  er.oh_weapon.max_fire_dmg = oh_fire_damage;
	  er.oh_weapon.max_lightning_dmg = oh_lightning_damage;
	  er.oh_weapon.max_holy_dmg = oh_holy_damage;
	  er.oh_weapon.max_total_dmg = oh_total_damage;
	}

	er.optimal_character.opt_strength = attribute_tuple.strength;
	er.optimal_character.opt_dexterity = attribute_tuple.dexterity;
	er.optimal_character.opt_intelligence = attribute_tuple.intelligence;
	er.optimal_character.opt_faith = attribute_tuple.faith;
	er.optimal_character.opt_arcane = attribute_tuple.arcane;

	// Indicate that at least one solution set was found.
	er.calculation_result = CALC_SUCCESS;
  }
}

// Determine which values to use for correction function
inline double ERBuildOptimizer::CalculateCorrectFn(const double attribute,
												   const int stat_max[],
												   const int grow[],
												   const double adj_pt_grow[]) {

  // IF(B$2 > 80, ADD(90, MULTIPLY(20, DIVIDE(B$2 - 80, 70))),
  // IF(B$2 > 60, ADD(75, MULTIPLY(15, DIVIDE(B$2 - 60, 20))),
  // IF(B$2 > 18, ADD(25, MULTIPLY(50, MINUS(1, POW(MINUS(1, DIVIDE(B$2 - 18, 42)), 1.2)))),
  // MULTIPLY(25, POW(DIVIDE(B$2 - 1, 17), 1.2))))),

  // Determine which max, grow, and adj_pt_grow values to use
  if (attribute > stat_max[3])
	return CalcCorrectFnInner(attribute, stat_max[3], stat_max[4], grow[3], grow[4], adj_pt_grow[3]);
  else if (attribute > stat_max[2])
	return CalcCorrectFnInner(attribute, stat_max[2], stat_max[3], grow[2], grow[3], adj_pt_grow[2]);
  else if (attribute > stat_max[1])
	return CalcCorrectFnInner(attribute, stat_max[1], stat_max[2], grow[1], grow[2], adj_pt_grow[1]);
  else
	return CalcCorrectFnInner(attribute, stat_max[0], stat_max[1], grow[0], grow[1], adj_pt_grow[0]);
}

// Inline portion of calc correction function. Separated out for readability.
inline double ERBuildOptimizer::CalcCorrectFnInner(const double attribute,
												   const int stat_max,
												   const int stat_max_n,
												   const int grow,
												   const int grow_n,
												   const double adj_grow) {
  if (adj_grow < 0)
	return grow + (grow_n - grow) * (1 - pow(1 - (attribute - stat_max) / (double)(stat_max_n - stat_max), abs(adj_grow)));
  else
	return grow + (grow_n - grow) * pow((attribute - stat_max) / (double)(stat_max_n - stat_max), adj_grow);
}

// Set main hand and off hand weapon skills.
void ERBuildOptimizer::SetWeaponSkill(const bool main_hand, const py::dict &s) {
  WeaponSkill skill;

  skill.id = stoi(string(py::str(s["id"])));
  skill.name = string(py::str(s["name"]));
  skill.weapon_id = stoi(string(py::str(s["weapon_id"])));

  skill.atk_correct_physical = stoi(string(py::str(s["atk_correct_physical"])));
  skill.atk_correct_magic = stoi(string(py::str(s["atk_correct_magic"])));
  skill.atk_correct_fire = stoi(string(py::str(s["atk_correct_fire"])));
  skill.atk_correct_lightning = stoi(string(py::str(s["atk_correct_lightning"])));
  skill.atk_correct_holy = stoi(string(py::str(s["atk_correct_holy"])));
  skill.atk_correct_stamina = stoi(string(py::str(s["atk_correct_stamina"])));

  skill.atk_correct_speffect_point = stoi(string(py::str(s["atk_correct_speffect_point"])));
  skill.atk_correct_speffect_power = stoi(string(py::str(s["atk_correct_speffect_power"])));
  skill.atk_correct_speffect_damage = stoi(string(py::str(s["atk_correct_speffect_damage"])));

  skill.atk_physical = stoi(string(py::str(s["atk_physical"])));
  skill.atk_magic = stoi(string(py::str(s["atk_magic"])));
  skill.atk_fire = stoi(string(py::str(s["atk_fire"])));
  skill.atk_lightning = stoi(string(py::str(s["atk_lightning"])));
  skill.atk_holy = stoi(string(py::str(s["atk_holy"])));
  skill.atk_stamina = stoi(string(py::str(s["atk_stamina"])));

  skill.status_correct_point = stoi(string(py::str(s["status_correct_point"])));
  skill.attack_element_correct_id = stoi(string(py::str(s["attack_element_correct_id"])));

  skill.add_base_attack = stoi(string(py::str(s["add_base_attack"])));
  skill.disable_2h_atk_bonus = stoi(string(py::str(s["disable_2h_atk_bonus"])));

  skill.sub_category1 = stoi(string(py::str(s["sub_category1"])));
  skill.sub_category2 = stoi(string(py::str(s["sub_category2"])));

  skill.target_speffect0 = stoi(string(py::str(s["target_speffect0"])));
  skill.target_speffect1 = stoi(string(py::str(s["target_speffect1"])));
  skill.target_speffect2 = stoi(string(py::str(s["target_speffect2"])));
  skill.target_speffect3 = stoi(string(py::str(s["target_speffect3"])));
  skill.target_speffect4 = stoi(string(py::str(s["target_speffect4"])));

  if (main_hand) {
	mh_skill = skill;
  } else {
	oh_skill = skill;
  }
}

void ERBuildOptimizer::EvaluateBySkillAR(const int s, const int d, const int i, const int f, const int a, ERBuildOptimizer &er) {
  // TODO
}

// Calculate corrected damage
double ERBuildOptimizer::CalculateCorrectedDamage(const Weapon &selected_weapon,
												  const AttributeTuple &attribute_tuple,
												  const DAMAGE_TYPE damage_type,
												  const double base_damage,
												  const bool is_two_handing) {
  int mask = 0;
  int stat_max[5]{};
  int grow[5]{};
  double adj_pt_grow[5]{};

  // Weapon scaling by attribute
  int correction[5]
	  {selected_weapon.correction_str, selected_weapon.correction_dex, selected_weapon.correction_int, selected_weapon.correction_fai,
	   selected_weapon.correction_arc};

  // Reinforcement
  double correction_pct[5]{selected_weapon.correction_pct_str, selected_weapon.correction_pct_dex, selected_weapon.correction_pct_int,
						   selected_weapon.correction_pct_fai, selected_weapon.correction_pct_arc};

  switch (damage_type) {
	case DAMAGE_TYPE::PHYSICAL:
	  // Masks
	  mask = PH_STR;

	  // Attack Correction Values
	  stat_max[0] = selected_weapon.physical_stat_max_0;
	  stat_max[1] = selected_weapon.physical_stat_max_1;
	  stat_max[2] = selected_weapon.physical_stat_max_2;
	  stat_max[3] = selected_weapon.physical_stat_max_3;
	  stat_max[4] = selected_weapon.physical_stat_max_4;
	  grow[0] = selected_weapon.physical_grow_0;
	  grow[1] = selected_weapon.physical_grow_1;
	  grow[2] = selected_weapon.physical_grow_2;
	  grow[3] = selected_weapon.physical_grow_3;
	  grow[4] = selected_weapon.physical_grow_4;
	  adj_pt_grow[0] = selected_weapon.physical_adjustment_pt_grow_0;
	  adj_pt_grow[1] = selected_weapon.physical_adjustment_pt_grow_1;
	  adj_pt_grow[2] = selected_weapon.physical_adjustment_pt_grow_2;
	  adj_pt_grow[3] = selected_weapon.physical_adjustment_pt_grow_3;
	  adj_pt_grow[4] = selected_weapon.physical_adjustment_pt_grow_4;
	  break;
	case DAMAGE_TYPE::MAGIC:
	  // Masks
	  mask = MA_STR;

	  // Attack Correction Values
	  stat_max[0] = selected_weapon.magic_stat_max_0;
	  stat_max[1] = selected_weapon.magic_stat_max_1;
	  stat_max[2] = selected_weapon.magic_stat_max_2;
	  stat_max[3] = selected_weapon.magic_stat_max_3;
	  stat_max[4] = selected_weapon.magic_stat_max_4;
	  grow[0] = selected_weapon.magic_grow_0;
	  grow[1] = selected_weapon.magic_grow_1;
	  grow[2] = selected_weapon.magic_grow_2;
	  grow[3] = selected_weapon.magic_grow_3;
	  grow[4] = selected_weapon.magic_grow_4;
	  adj_pt_grow[0] = selected_weapon.magic_adjustment_pt_grow_0;
	  adj_pt_grow[1] = selected_weapon.magic_adjustment_pt_grow_1;
	  adj_pt_grow[2] = selected_weapon.magic_adjustment_pt_grow_2;
	  adj_pt_grow[3] = selected_weapon.magic_adjustment_pt_grow_3;
	  adj_pt_grow[4] = selected_weapon.magic_adjustment_pt_grow_4;

	  break;
	case DAMAGE_TYPE::FIRE:
	  // Masks
	  mask = FI_STR;

	  // Attack Correction Values
	  stat_max[0] = selected_weapon.fire_stat_max_0;
	  stat_max[1] = selected_weapon.fire_stat_max_1;
	  stat_max[2] = selected_weapon.fire_stat_max_2;
	  stat_max[3] = selected_weapon.fire_stat_max_3;
	  stat_max[4] = selected_weapon.fire_stat_max_4;
	  grow[0] = selected_weapon.fire_grow_0;
	  grow[1] = selected_weapon.fire_grow_1;
	  grow[2] = selected_weapon.fire_grow_2;
	  grow[3] = selected_weapon.fire_grow_3;
	  grow[4] = selected_weapon.fire_grow_4;
	  adj_pt_grow[0] = selected_weapon.fire_adjustment_pt_grow_0;
	  adj_pt_grow[1] = selected_weapon.fire_adjustment_pt_grow_1;
	  adj_pt_grow[2] = selected_weapon.fire_adjustment_pt_grow_2;
	  adj_pt_grow[3] = selected_weapon.fire_adjustment_pt_grow_3;
	  adj_pt_grow[4] = selected_weapon.fire_adjustment_pt_grow_4;

	  break;
	case DAMAGE_TYPE::LIGHTNING:
	  // Masks
	  mask = LI_STR;

	  // Attack Correction Values
	  stat_max[0] = selected_weapon.lightning_stat_max_0;
	  stat_max[1] = selected_weapon.lightning_stat_max_1;
	  stat_max[2] = selected_weapon.lightning_stat_max_2;
	  stat_max[3] = selected_weapon.lightning_stat_max_3;
	  stat_max[4] = selected_weapon.lightning_stat_max_4;
	  grow[0] = selected_weapon.lightning_grow_0;
	  grow[1] = selected_weapon.lightning_grow_1;
	  grow[2] = selected_weapon.lightning_grow_2;
	  grow[3] = selected_weapon.lightning_grow_3;
	  grow[4] = selected_weapon.lightning_grow_4;
	  adj_pt_grow[0] = selected_weapon.lightning_adjustment_pt_grow_0;
	  adj_pt_grow[1] = selected_weapon.lightning_adjustment_pt_grow_1;
	  adj_pt_grow[2] = selected_weapon.lightning_adjustment_pt_grow_2;
	  adj_pt_grow[3] = selected_weapon.lightning_adjustment_pt_grow_3;
	  adj_pt_grow[4] = selected_weapon.lightning_adjustment_pt_grow_4;

	  break;
	default:
	  // Masks
	  mask = HO_STR;

	  // Attack Correction Values
	  stat_max[0] = selected_weapon.holy_stat_max_0;
	  stat_max[1] = selected_weapon.holy_stat_max_1;
	  stat_max[2] = selected_weapon.holy_stat_max_2;
	  stat_max[3] = selected_weapon.holy_stat_max_3;
	  stat_max[4] = selected_weapon.holy_stat_max_4;
	  grow[0] = selected_weapon.holy_grow_0;
	  grow[1] = selected_weapon.holy_grow_1;
	  grow[2] = selected_weapon.holy_grow_2;
	  grow[3] = selected_weapon.holy_grow_3;
	  grow[4] = selected_weapon.holy_grow_4;
	  adj_pt_grow[0] = selected_weapon.holy_adjustment_pt_grow_0;
	  adj_pt_grow[1] = selected_weapon.holy_adjustment_pt_grow_1;
	  adj_pt_grow[2] = selected_weapon.holy_adjustment_pt_grow_2;
	  adj_pt_grow[3] = selected_weapon.holy_adjustment_pt_grow_3;
	  adj_pt_grow[4] = selected_weapon.holy_adjustment_pt_grow_4;

	  break;
  }

  double strength = attribute_tuple.strength;

  // What if we... two handed?
  //        ---> <---
  if (is_two_handing) {
	strength *= 1.5;
  }

  double corrected_damage = base_damage;

  // Go through each attribute for the damage type being evaluated.

  int aec_bitmask = selected_weapon.attack_element_correct_bitmask;

  // Strength
  if (aec_bitmask & mask) {
	corrected_damage +=
		base_damage * correction[0] * correction_pct[0] * CalculateCorrectFn(strength, stat_max, grow, adj_pt_grow) / 10000.0;
  }

  // Dexterity
  if (aec_bitmask & mask >> 1) {
	corrected_damage +=
		base_damage * correction[1] * correction_pct[1] * CalculateCorrectFn(attribute_tuple.dexterity, stat_max, grow, adj_pt_grow)
			/ 10000.0;
  }

  // Intelligence
  if (aec_bitmask & mask >> 2) {
	corrected_damage +=
		base_damage * correction[2] * correction_pct[2] * CalculateCorrectFn(attribute_tuple.intelligence, stat_max, grow, adj_pt_grow)
			/ 10000.0;
  }

  // Faith
  if (aec_bitmask & mask >> 3) {
	corrected_damage +=
		base_damage * correction[3] * correction_pct[3] * CalculateCorrectFn(attribute_tuple.faith, stat_max, grow, adj_pt_grow) / 10000.0;
  }

  // Arcane
  if (aec_bitmask & mask >> 4) {
	corrected_damage +=
		base_damage * correction[4] * correction_pct[4] * CalculateCorrectFn(attribute_tuple.arcane, stat_max, grow, adj_pt_grow) / 10000.0;
  }

  return corrected_damage;
}



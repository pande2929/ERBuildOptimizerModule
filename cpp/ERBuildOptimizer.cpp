#include "./include/ERBuildOptimizer.h"
#include "./include/SubsetSum.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Populate passive status effects. Poison and bleed usually scale with ARC, but all others only scale with stones.
void ERBuildOptimizer::CalcPassives(Weapon &weapon) const {
	// Bleed Scaling
	if (weapon.pass1_bleed > 0) {
		weapon.max_bleed = CalculatePassive(weapon.pass1_bleed,
											optimal_character.opt_arcane,
											weapon.correction_arc,
											weapon.correction_pct_arc,
											weapon.bleed_stat_max_0,
											weapon.bleed_stat_max_1,
											weapon.bleed_stat_max_2,
											weapon.bleed_stat_max_3,
											weapon.bleed_stat_max_4,
											weapon.bleed_grow_0,
											weapon.bleed_grow_1,
											weapon.bleed_grow_2,
											weapon.bleed_grow_3,
											weapon.bleed_grow_4,
											weapon.bleed_adjustment_pt_grow_0,
											weapon.bleed_adjustment_pt_grow_1,
											weapon.bleed_adjustment_pt_grow_2,
											weapon.bleed_adjustment_pt_grow_3,
											weapon.bleed_adjustment_pt_grow_4);
	} else if (weapon.pass2_bleed > 0) {
		weapon.max_bleed = CalculatePassive(weapon.pass2_bleed,
											optimal_character.opt_arcane,
											weapon.correction_arc,
											weapon.correction_pct_arc,
											weapon.bleed_stat_max_0,
											weapon.bleed_stat_max_1,
											weapon.bleed_stat_max_2,
											weapon.bleed_stat_max_3,
											weapon.bleed_stat_max_4,
											weapon.bleed_grow_0,
											weapon.bleed_grow_1,
											weapon.bleed_grow_2,
											weapon.bleed_grow_3,
											weapon.bleed_grow_4,
											weapon.bleed_adjustment_pt_grow_0,
											weapon.bleed_adjustment_pt_grow_1,
											weapon.bleed_adjustment_pt_grow_2,
											weapon.bleed_adjustment_pt_grow_3,
											weapon.bleed_adjustment_pt_grow_4);
	} else if (weapon.pass3_bleed) {
		weapon.max_bleed = CalculatePassive(weapon.pass3_bleed,
											optimal_character.opt_arcane,
											weapon.correction_arc,
											weapon.correction_pct_arc,
											weapon.bleed_stat_max_0,
											weapon.bleed_stat_max_1,
											weapon.bleed_stat_max_2,
											weapon.bleed_stat_max_3,
											weapon.bleed_stat_max_4,
											weapon.bleed_grow_0,
											weapon.bleed_grow_1,
											weapon.bleed_grow_2,
											weapon.bleed_grow_3,
											weapon.bleed_grow_4,
											weapon.bleed_adjustment_pt_grow_0,
											weapon.bleed_adjustment_pt_grow_1,
											weapon.bleed_adjustment_pt_grow_2,
											weapon.bleed_adjustment_pt_grow_3,
											weapon.bleed_adjustment_pt_grow_4);
	}

	// Poison Scaling
	if (weapon.pass1_poison > 0) {
		weapon.max_poison = CalculatePassive(weapon.pass1_poison,
											 optimal_character.opt_arcane,
											 weapon.correction_arc,
											 weapon.correction_pct_arc,
											 weapon.poison_stat_max_0,
											 weapon.poison_stat_max_1,
											 weapon.poison_stat_max_2,
											 weapon.poison_stat_max_3,
											 weapon.poison_stat_max_4,
											 weapon.poison_grow_0,
											 weapon.poison_grow_1,
											 weapon.poison_grow_2,
											 weapon.poison_grow_3,
											 weapon.poison_grow_4,
											 weapon.poison_adjustment_pt_grow_0,
											 weapon.poison_adjustment_pt_grow_1,
											 weapon.poison_adjustment_pt_grow_2,
											 weapon.poison_adjustment_pt_grow_3,
											 weapon.poison_adjustment_pt_grow_4);
	} else if (weapon.pass2_poison > 0) {
		weapon.max_poison = CalculatePassive(weapon.pass2_poison,
											 optimal_character.opt_arcane,
											 weapon.correction_arc,
											 weapon.correction_pct_arc,
											 weapon.poison_stat_max_0,
											 weapon.poison_stat_max_1,
											 weapon.poison_stat_max_2,
											 weapon.poison_stat_max_3,
											 weapon.poison_stat_max_4,
											 weapon.poison_grow_0,
											 weapon.poison_grow_1,
											 weapon.poison_grow_2,
											 weapon.poison_grow_3,
											 weapon.poison_grow_4,
											 weapon.poison_adjustment_pt_grow_0,
											 weapon.poison_adjustment_pt_grow_1,
											 weapon.poison_adjustment_pt_grow_2,
											 weapon.poison_adjustment_pt_grow_3,
											 weapon.poison_adjustment_pt_grow_4);
	} else if (weapon.pass3_poison > 0) {
		weapon.max_poison = CalculatePassive(weapon.pass3_poison,
											 optimal_character.opt_arcane,
											 weapon.correction_arc,
											 weapon.correction_pct_arc,
											 weapon.poison_stat_max_0,
											 weapon.poison_stat_max_1,
											 weapon.poison_stat_max_2,
											 weapon.poison_stat_max_3,
											 weapon.poison_stat_max_4,
											 weapon.poison_grow_0,
											 weapon.poison_grow_1,
											 weapon.poison_grow_2,
											 weapon.poison_grow_3,
											 weapon.poison_grow_4,
											 weapon.poison_adjustment_pt_grow_0,
											 weapon.poison_adjustment_pt_grow_1,
											 weapon.poison_adjustment_pt_grow_2,
											 weapon.poison_adjustment_pt_grow_3,
											 weapon.poison_adjustment_pt_grow_4);
	}

	// Frostbite
	if (weapon.pass1_frost > 0)
		weapon.max_frostbite = weapon.pass1_frost;
	else if (weapon.pass2_frost > 0)
		weapon.max_frostbite = weapon.pass2_frost;
	else if (weapon.pass3_frost > 0)
		weapon.max_frostbite = weapon.pass3_frost;

	// Sleep
	if (weapon.pass1_sleep > 0)
		weapon.max_sleep = weapon.pass1_sleep;
	else if (weapon.pass2_sleep > 0)
		weapon.max_sleep = weapon.pass2_sleep;
	else if (weapon.pass3_sleep > 0)
		weapon.max_sleep = weapon.pass3_sleep;

	// Madness
	if (weapon.pass1_madness > 0)
		weapon.max_madness = weapon.pass1_madness;
	else if (weapon.pass2_madness > 0)
		weapon.max_madness = weapon.pass2_madness;
	else if (weapon.pass3_madness > 0)
		weapon.max_madness = weapon.pass3_madness;

	// Scarlet Rot
	if (weapon.pass1_scarlet_rot > 0)
		weapon.max_scarlet_rot = weapon.pass1_scarlet_rot;
	else if (weapon.pass2_scarlet_rot > 0)
		weapon.max_scarlet_rot = weapon.pass2_scarlet_rot;
	else if (weapon.pass3_scarlet_rot > 0)
		weapon.max_scarlet_rot = weapon.pass3_scarlet_rot;

	if (isnan(weapon.max_poison))
		weapon.max_poison = 0;
	if (isnan(weapon.max_bleed))
		weapon.max_bleed = 0;
	if (isnan(weapon.max_frostbite))
		weapon.max_frostbite = 0;
	if (isnan(weapon.max_sleep))
		weapon.max_sleep = 0;
	if (isnan(weapon.max_madness))
		weapon.max_madness = 0;
	if (isnan(weapon.max_scarlet_rot))
		weapon.max_scarlet_rot = 0;
}

// Calculate a passive effect
// Given by: base + base * passive_arcane_calc_correct * arc scaling
double ERBuildOptimizer::CalculatePassive(const int base,
										  const int arcane,
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
										  const double adj_pt_grow_4) {

	// Build correction arrays
	int stat_max[5]{stat_max_0, stat_max_1, stat_max_2, stat_max_3, stat_max_4,};
	int grow[5]{grow_0, grow_1, grow_2, grow_3, grow_4,};
	double adj_pt_grow[5]{adj_pt_grow_0, adj_pt_grow_1, adj_pt_grow_2, adj_pt_grow_3, adj_pt_grow_4,};

	return base + base * CalculateCorrectFn(arcane, stat_max, grow, adj_pt_grow) * correction_arc * correction_pct_arc / 10000.0;
}

// Populate weapon skill damages and types.
void ERBuildOptimizer::CalcWeaponSkill(const Weapon &selected_weapon, const Tarnished &tarnished, WeaponSkill &selected_skill) const {
	// Calculate base damage.
	double base_damage_physical =
		selected_weapon.damage_physical * selected_weapon.damage_pct_physical * selected_skill.atk_correct_physical / 100.0
			+ 4 * selected_skill.atk_physical;
	double base_damage_magic = selected_weapon.damage_magic * selected_weapon.damage_pct_magic * selected_skill.atk_correct_magic / 100.0
		+ 4 * selected_skill.atk_magic;
	double base_damage_fire =
		selected_weapon.damage_fire * selected_weapon.damage_pct_fire * selected_skill.atk_correct_fire / 100.0
			+ 4 * selected_skill.atk_fire;
	double base_damage_lightning =
		selected_weapon.damage_lightning * selected_weapon.damage_pct_lightning * selected_skill.atk_correct_lightning / 100.0
			+ 4 * selected_skill.atk_lightning;
	double base_damage_holy =
		selected_weapon.damage_holy * selected_weapon.damage_pct_holy * selected_skill.atk_correct_holy / 100.0
			+ 4 * selected_skill.atk_holy;

	bool two_hand_bonus = is_two_handing && !selected_skill.disable_2h_atk_bonus;

	AttributeTuple attribute_tuple{
		tarnished.opt_strength,
		tarnished.opt_dexterity,
		tarnished.opt_intelligence,
		tarnished.opt_faith,
		tarnished.opt_arcane
	};

	CorrectionTuple scaling_tuple{};

	GetWeaponSkillScaling(selected_weapon, selected_skill, scaling_tuple, DAMAGE_TYPE::PHYSICAL);

	double damage_physical =
		CalculateCorrectedDamage(selected_weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::PHYSICAL,
								 base_damage_physical,
								 two_hand_bonus,
								 selected_weapon.attack_element_correct_bitmask);

	GetWeaponSkillScaling(selected_weapon, selected_skill, scaling_tuple, DAMAGE_TYPE::MAGIC);

	double damage_magic =
		CalculateCorrectedDamage(selected_weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::MAGIC,
								 base_damage_magic,
								 two_hand_bonus,
								 selected_weapon.attack_element_correct_bitmask);

	GetWeaponSkillScaling(selected_weapon, selected_skill, scaling_tuple, DAMAGE_TYPE::FIRE);

	double damage_fire =
		CalculateCorrectedDamage(selected_weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::FIRE,
								 base_damage_fire,
								 two_hand_bonus,
								 selected_weapon.attack_element_correct_bitmask);

	GetWeaponSkillScaling(selected_weapon, selected_skill, scaling_tuple, DAMAGE_TYPE::LIGHTNING);

	double damage_lightning =
		CalculateCorrectedDamage(selected_weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::LIGHTNING,
								 base_damage_lightning,
								 two_hand_bonus, selected_weapon.attack_element_correct_bitmask);

	GetWeaponSkillScaling(selected_weapon, selected_skill, scaling_tuple, DAMAGE_TYPE::HOLY);

	double damage_holy =
		CalculateCorrectedDamage(selected_weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::HOLY,
								 base_damage_holy,
								 two_hand_bonus,
								 selected_weapon.attack_element_correct_bitmask);

	// Check for NaNs
	if (isnan(damage_physical))
		damage_physical= 0;
	if (isnan(damage_magic))
		damage_magic= 0;
	if (isnan(damage_fire))
		damage_fire = 0;
	if (isnan(damage_lightning))
		damage_lightning = 0;
	if (isnan(damage_holy))
		damage_holy = 0;

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
		// Minimum possible attribute combo is too high for level.Decrease V, M, E, or raise Level
		return CALC_FAIL_LEVEL_LOW;
	} else if (max_attainable_level < target_level) {
		// Maximum possible attribute combo is too low for level.Increase V, M, E, or lower Level
		return CALC_FAIL_LEVEL_HIGH;
	}

	return result;
}

// Python typed Constructor
ERBuildOptimizer::ERBuildOptimizer(const int target_level,
								   const bool is_two_handing,
								   const py::dict &character,
								   const int mh_optimization_type,
								   const int oh_optimization_type) {
	this->target_level = target_level;
	this->is_two_handing = is_two_handing;
	this->mh_optimization_type = (OPTIMIZATION_TYPE)mh_optimization_type;
	this->oh_optimization_type = (OPTIMIZATION_TYPE)oh_optimization_type;

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

// Set weapon main hand and off hand weapons
void ERBuildOptimizer::SetWeapon(const bool main_hand, const py::dict &w) {
	Weapon weapon;

	// convert from dict to weapon
	weapon.id = stoi(py::str(w["id"]));
	weapon.name = string(py::str(w["name"]));
	weapon.weapon_type = string(py::str(w["weapon_type"]));
	weapon.origin_weapon = string(py::str(w["origin_weapon"]));

	// Base Damage
	weapon.damage_physical = stoi(py::str(w["damage_physical"]));
	weapon.damage_magic = stoi(py::str(w["damage_magic"]));
	weapon.damage_fire = stoi(py::str(w["damage_fire"]));
	weapon.damage_lightning = stoi(py::str(w["damage_lightning"]));
	weapon.damage_holy = stoi(py::str(w["damage_holy"]));

	// Required Stats
	weapon.required_str = stoi(py::str(w["required_str"]));
	weapon.required_dex = stoi(py::str(w["required_dex"]));
	weapon.required_int = stoi(py::str(w["required_int"]));
	weapon.required_fai = stoi(py::str(w["required_fai"]));
	weapon.required_arc = stoi(py::str(w["required_arc"]));

	// Base Correction Values
	weapon.correction_str = stoi(py::str(w["correction_str"]));
	weapon.correction_dex = stoi(py::str(w["correction_dex"]));
	weapon.correction_int = stoi(py::str(w["correction_int"]));
	weapon.correction_fai = stoi(py::str(w["correction_fai"]));
	weapon.correction_arc = stoi(py::str(w["correction_arc"]));

	// Bitmask
	weapon.attack_element_correct_bitmask_str = string(py::str(w["attack_element_correct_bitmask_str"]));

	// Convert the string attack element correct bitmask into an integer one
	weapon.attack_element_correct_bitmask = ConvertBitMask(weapon.attack_element_correct_bitmask_str);

	// Reinforcement Values
	weapon.damage_pct_physical = stod(py::str(w["damage_pct_physical"]));
	weapon.damage_pct_magic = stod(py::str(w["damage_pct_magic"]));
	weapon.damage_pct_fire = stod(py::str(w["damage_pct_fire"]));
	weapon.damage_pct_lightning = stod(py::str(w["damage_pct_lightning"]));
	weapon.damage_pct_holy = stod(py::str(w["damage_pct_holy"]));
	weapon.damage_pct_stamina = stod(py::str(w["damage_pct_stamina"]));
	weapon.damage_pct_poise = stod(py::str(w["damage_pct_poise"]));
	weapon.correction_pct_str = stod(py::str(w["correction_pct_str"]));
	weapon.correction_pct_dex = stod(py::str(w["correction_pct_dex"]));
	weapon.correction_pct_int = stod(py::str(w["correction_pct_int"]));
	weapon.correction_pct_fai = stod(py::str(w["correction_pct_fai"]));
	weapon.correction_pct_arc = stod(py::str(w["correction_pct_arc"]));
	weapon.base_damage_pct_overall = stod(py::str(w["base_damage_pct_overall"]));

	// Calc Correct Values

	// Physical
	weapon.physical_calc_correct_id = stoi(py::str(w["physical_calc_correct_id"]));
	weapon.physical_stat_max_0 = stoi(py::str(w["physical_stat_max_0"]));
	weapon.physical_stat_max_1 = stoi(py::str(w["physical_stat_max_1"]));
	weapon.physical_stat_max_2 = stoi(py::str(w["physical_stat_max_2"]));
	weapon.physical_stat_max_3 = stoi(py::str(w["physical_stat_max_3"]));
	weapon.physical_stat_max_4 = stoi(py::str(w["physical_stat_max_4"]));
	weapon.physical_grow_0 = stoi(py::str(w["physical_grow_0"]));
	weapon.physical_grow_1 = stoi(py::str(w["physical_grow_1"]));
	weapon.physical_grow_2 = stoi(py::str(w["physical_grow_2"]));
	weapon.physical_grow_3 = stoi(py::str(w["physical_grow_3"]));
	weapon.physical_grow_4 = stoi(py::str(w["physical_grow_4"]));
	weapon.physical_adjustment_pt_grow_0 = stod(py::str(w["physical_adjustment_pt_grow_0"]));
	weapon.physical_adjustment_pt_grow_1 = stod(py::str(w["physical_adjustment_pt_grow_1"]));
	weapon.physical_adjustment_pt_grow_2 = stod(py::str(w["physical_adjustment_pt_grow_2"]));
	weapon.physical_adjustment_pt_grow_3 = stod(py::str(w["physical_adjustment_pt_grow_3"]));
	weapon.physical_adjustment_pt_grow_4 = stod(py::str(w["physical_adjustment_pt_grow_4"]));

	// Magic
	weapon.magic_calc_correct_id = stoi(py::str(w["magic_calc_correct_id"]));
	weapon.magic_stat_max_0 = stoi(py::str(w["magic_stat_max_0"]));
	weapon.magic_stat_max_1 = stoi(py::str(w["magic_stat_max_1"]));
	weapon.magic_stat_max_2 = stoi(py::str(w["magic_stat_max_2"]));
	weapon.magic_stat_max_3 = stoi(py::str(w["magic_stat_max_3"]));
	weapon.magic_stat_max_4 = stoi(py::str(w["magic_stat_max_4"]));
	weapon.magic_grow_0 = stoi(py::str(w["magic_grow_0"]));
	weapon.magic_grow_1 = stoi(py::str(w["magic_grow_1"]));
	weapon.magic_grow_2 = stoi(py::str(w["magic_grow_2"]));
	weapon.magic_grow_3 = stoi(py::str(w["magic_grow_3"]));
	weapon.magic_grow_4 = stoi(py::str(w["magic_grow_4"]));
	weapon.magic_adjustment_pt_grow_0 = stod(py::str(w["magic_adjustment_pt_grow_0"]));
	weapon.magic_adjustment_pt_grow_1 = stod(py::str(w["magic_adjustment_pt_grow_1"]));
	weapon.magic_adjustment_pt_grow_2 = stod(py::str(w["magic_adjustment_pt_grow_2"]));
	weapon.magic_adjustment_pt_grow_3 = stod(py::str(w["magic_adjustment_pt_grow_3"]));
	weapon.magic_adjustment_pt_grow_4 = stod(py::str(w["magic_adjustment_pt_grow_4"]));

	// Fire
	weapon.fire_calc_correct_id = stoi(py::str(w["fire_calc_correct_id"]));
	weapon.fire_stat_max_0 = stoi(py::str(w["fire_stat_max_0"]));
	weapon.fire_stat_max_1 = stoi(py::str(w["fire_stat_max_1"]));
	weapon.fire_stat_max_2 = stoi(py::str(w["fire_stat_max_2"]));
	weapon.fire_stat_max_3 = stoi(py::str(w["fire_stat_max_3"]));
	weapon.fire_stat_max_4 = stoi(py::str(w["fire_stat_max_4"]));
	weapon.fire_grow_0 = stoi(py::str(w["fire_grow_0"]));
	weapon.fire_grow_1 = stoi(py::str(w["fire_grow_1"]));
	weapon.fire_grow_2 = stoi(py::str(w["fire_grow_2"]));
	weapon.fire_grow_3 = stoi(py::str(w["fire_grow_3"]));
	weapon.fire_grow_4 = stoi(py::str(w["fire_grow_4"]));
	weapon.fire_adjustment_pt_grow_0 = stod(py::str(w["fire_adjustment_pt_grow_0"]));
	weapon.fire_adjustment_pt_grow_1 = stod(py::str(w["fire_adjustment_pt_grow_1"]));
	weapon.fire_adjustment_pt_grow_2 = stod(py::str(w["fire_adjustment_pt_grow_2"]));
	weapon.fire_adjustment_pt_grow_3 = stod(py::str(w["fire_adjustment_pt_grow_3"]));
	weapon.fire_adjustment_pt_grow_4 = stod(py::str(w["fire_adjustment_pt_grow_4"]));

	// Lightning
	weapon.lightning_calc_correct_id = stoi(py::str(w["lightning_calc_correct_id"]));
	weapon.lightning_stat_max_0 = stoi(py::str(w["lightning_stat_max_0"]));
	weapon.lightning_stat_max_1 = stoi(py::str(w["lightning_stat_max_1"]));
	weapon.lightning_stat_max_2 = stoi(py::str(w["lightning_stat_max_2"]));
	weapon.lightning_stat_max_3 = stoi(py::str(w["lightning_stat_max_3"]));
	weapon.lightning_stat_max_4 = stoi(py::str(w["lightning_stat_max_4"]));
	weapon.lightning_grow_0 = stoi(py::str(w["lightning_grow_0"]));
	weapon.lightning_grow_1 = stoi(py::str(w["lightning_grow_1"]));
	weapon.lightning_grow_2 = stoi(py::str(w["lightning_grow_2"]));
	weapon.lightning_grow_3 = stoi(py::str(w["lightning_grow_3"]));
	weapon.lightning_grow_4 = stoi(py::str(w["lightning_grow_4"]));
	weapon.lightning_adjustment_pt_grow_0 = stod(py::str(w["lightning_adjustment_pt_grow_0"]));
	weapon.lightning_adjustment_pt_grow_1 = stod(py::str(w["lightning_adjustment_pt_grow_1"]));
	weapon.lightning_adjustment_pt_grow_2 = stod(py::str(w["lightning_adjustment_pt_grow_2"]));
	weapon.lightning_adjustment_pt_grow_3 = stod(py::str(w["lightning_adjustment_pt_grow_3"]));
	weapon.lightning_adjustment_pt_grow_4 = stod(py::str(w["lightning_adjustment_pt_grow_4"]));

	// Holy
	weapon.holy_calc_correct_id = stoi(py::str(w["holy_calc_correct_id"]));
	weapon.holy_stat_max_0 = stoi(py::str(w["holy_stat_max_0"]));
	weapon.holy_stat_max_1 = stoi(py::str(w["holy_stat_max_1"]));
	weapon.holy_stat_max_2 = stoi(py::str(w["holy_stat_max_2"]));
	weapon.holy_stat_max_3 = stoi(py::str(w["holy_stat_max_3"]));
	weapon.holy_stat_max_4 = stoi(py::str(w["holy_stat_max_4"]));
	weapon.holy_grow_0 = stoi(py::str(w["holy_grow_0"]));
	weapon.holy_grow_1 = stoi(py::str(w["holy_grow_1"]));
	weapon.holy_grow_2 = stoi(py::str(w["holy_grow_2"]));
	weapon.holy_grow_3 = stoi(py::str(w["holy_grow_3"]));
	weapon.holy_grow_4 = stoi(py::str(w["holy_grow_4"]));
	weapon.holy_adjustment_pt_grow_0 = stod(py::str(w["holy_adjustment_pt_grow_0"]));
	weapon.holy_adjustment_pt_grow_1 = stod(py::str(w["holy_adjustment_pt_grow_1"]));
	weapon.holy_adjustment_pt_grow_2 = stod(py::str(w["holy_adjustment_pt_grow_2"]));
	weapon.holy_adjustment_pt_grow_3 = stod(py::str(w["holy_adjustment_pt_grow_3"]));
	weapon.holy_adjustment_pt_grow_4 = stod(py::str(w["holy_adjustment_pt_grow_4"]));

	// Poison
	weapon.poison_calc_correct_id = stoi(py::str(w["poison_calc_correct_id"]));
	weapon.poison_stat_max_0 = stoi(py::str(w["poison_stat_max_0"]));
	weapon.poison_stat_max_1 = stoi(py::str(w["poison_stat_max_1"]));
	weapon.poison_stat_max_2 = stoi(py::str(w["poison_stat_max_2"]));
	weapon.poison_stat_max_3 = stoi(py::str(w["poison_stat_max_3"]));
	weapon.poison_stat_max_4 = stoi(py::str(w["poison_stat_max_4"]));
	weapon.poison_grow_0 = stoi(py::str(w["poison_grow_0"]));
	weapon.poison_grow_1 = stoi(py::str(w["poison_grow_1"]));
	weapon.poison_grow_2 = stoi(py::str(w["poison_grow_2"]));
	weapon.poison_grow_3 = stoi(py::str(w["poison_grow_3"]));
	weapon.poison_grow_4 = stoi(py::str(w["poison_grow_4"]));
	weapon.poison_adjustment_pt_grow_0 = stod(py::str(w["poison_adjustment_pt_grow_0"]));
	weapon.poison_adjustment_pt_grow_1 = stod(py::str(w["poison_adjustment_pt_grow_1"]));
	weapon.poison_adjustment_pt_grow_2 = stod(py::str(w["poison_adjustment_pt_grow_2"]));
	weapon.poison_adjustment_pt_grow_3 = stod(py::str(w["poison_adjustment_pt_grow_3"]));
	weapon.poison_adjustment_pt_grow_4 = stod(py::str(w["poison_adjustment_pt_grow_4"]));

	// Bleed
	weapon.bleed_calc_correct_id = stoi(py::str(w["bleed_calc_correct_id"]));
	weapon.bleed_stat_max_0 = stoi(py::str(w["bleed_stat_max_0"]));
	weapon.bleed_stat_max_1 = stoi(py::str(w["bleed_stat_max_1"]));
	weapon.bleed_stat_max_2 = stoi(py::str(w["bleed_stat_max_2"]));
	weapon.bleed_stat_max_3 = stoi(py::str(w["bleed_stat_max_3"]));
	weapon.bleed_stat_max_4 = stoi(py::str(w["bleed_stat_max_4"]));
	weapon.bleed_grow_0 = stoi(py::str(w["bleed_grow_0"]));
	weapon.bleed_grow_1 = stoi(py::str(w["bleed_grow_1"]));
	weapon.bleed_grow_2 = stoi(py::str(w["bleed_grow_2"]));
	weapon.bleed_grow_3 = stoi(py::str(w["bleed_grow_3"]));
	weapon.bleed_grow_4 = stoi(py::str(w["bleed_grow_4"]));
	weapon.bleed_adjustment_pt_grow_0 = stod(py::str(w["bleed_adjustment_pt_grow_0"]));
	weapon.bleed_adjustment_pt_grow_1 = stod(py::str(w["bleed_adjustment_pt_grow_1"]));
	weapon.bleed_adjustment_pt_grow_2 = stod(py::str(w["bleed_adjustment_pt_grow_2"]));
	weapon.bleed_adjustment_pt_grow_3 = stod(py::str(w["bleed_adjustment_pt_grow_3"]));
	weapon.bleed_adjustment_pt_grow_4 = stod(py::str(w["bleed_adjustment_pt_grow_4"]));

	// Passives

	weapon.pass1_poison = stoi(py::str(w["pass1_poison"]));
	weapon.pass1_scarlet_rot = stoi(py::str(w["pass1_scarlet_rot"]));
	weapon.pass1_bleed = stoi(py::str(w["pass1_bleed"]));
	weapon.pass1_death = stoi(py::str(w["pass1_death"]));
	weapon.pass1_frost = stoi(py::str(w["pass1_frost"]));
	weapon.pass1_sleep = stoi(py::str(w["pass1_sleep"]));
	weapon.pass1_madness = stoi(py::str(w["pass1_madness"]));

	weapon.pass2_poison = stoi(py::str(w["pass2_poison"]));
	weapon.pass2_scarlet_rot = stoi(py::str(w["pass2_scarlet_rot"]));
	weapon.pass2_bleed = stoi(py::str(w["pass2_bleed"]));
	weapon.pass2_death = stoi(py::str(w["pass2_death"]));
	weapon.pass2_frost = stoi(py::str(w["pass2_frost"]));
	weapon.pass2_sleep = stoi(py::str(w["pass2_sleep"]));
	weapon.pass2_madness = stoi(py::str(w["pass2_madness"]));

	weapon.pass3_poison = stoi(py::str(w["pass3_poison"]));
	weapon.pass3_scarlet_rot = stoi(py::str(w["pass3_scarlet_rot"]));
	weapon.pass3_bleed = stoi(py::str(w["pass3_bleed"]));
	weapon.pass3_death = stoi(py::str(w["pass3_death"]));
	weapon.pass3_frost = stoi(py::str(w["pass3_frost"]));
	weapon.pass3_sleep = stoi(py::str(w["pass3_sleep"]));
	weapon.pass3_madness = stoi(py::str(w["pass3_madness"]));

	// Maximized Values (will be needed by the template for display)
	weapon.max_physical_dmg = stod(py::str(w["max_physical_dmg"]));
	weapon.max_magic_dmg = stod(py::str(w["max_magic_dmg"]));
	weapon.max_fire_dmg = stod(py::str(w["max_fire_dmg"]));
	weapon.max_lightning_dmg = stod(py::str(w["max_lightning_dmg"]));
	weapon.max_holy_dmg = stod(py::str(w["max_holy_dmg"]));
	weapon.max_total_dmg = stod(py::str(w["max_total_dmg"]));

	weapon.max_poison = stod(py::str(w["max_poison"]));
	weapon.max_bleed = stod(py::str(w["max_bleed"]));
	weapon.max_frostbite = stod(py::str(w["max_frostbite"]));
	weapon.max_sleep = stod(py::str(w["max_sleep"]));
	weapon.max_madness = stod(py::str(w["max_madness"]));
	weapon.max_scarlet_rot = stod(py::str(w["max_scarlet_rot"]));

	if (main_hand) {
		mh_weapon = weapon;
		using_main_hand = true;
	} else {
		oh_weapon = weapon;
		using_off_hand = true;
	}
}

// Get calculation_result
int ERBuildOptimizer::GetCalculationResult() const {
	return calculation_result;
}

// Converts a string bitmask to an integer one.
// On the DB side, string bitmask is a concatenation of AttackElementCorrectParam table columns.
inline int ERBuildOptimizer::ConvertBitMask(const std::string &mask) {
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
	// Mins must be: greatest of the attr_req main hand, attr_req offhand, and attr_base in class
	// Maxes can either go up to 99, OR min + 1 if not a scaling (correction > 0) attribute.

	int min_max[5][2]{};

	// Constrain strength range
	vector<int> attr = {optimal_character.base_strength};

	if (using_main_hand) {
		mh_weapon.required_str;
	}

	if (using_off_hand) {
		attr.push_back(oh_weapon.required_str);
	}

	// Reverse sort
	sort(attr.begin(), attr.end(), greater<int>());
	min_max[0][0] = attr[0];            // Min

	if (using_main_hand && mh_weapon.correction_str > 0 || (using_off_hand && oh_weapon.correction_str > 0)) {
		min_max[0][1] = MAX_ATTRIBUTE;      // Max
	} else {
		min_max[0][1] = attr[0];        // Max
	}

	// Constrain dexterity range
	attr.clear();
	attr.push_back(optimal_character.base_dexterity);

	if (using_main_hand) {
		attr.push_back(mh_weapon.required_dex);
	}

	if (using_off_hand) {
		attr.push_back(oh_weapon.required_dex);
	}

	// Reverse sort
	sort(attr.begin(), attr.end(), greater<int>());
	min_max[1][0] = attr[0];                // Min

	if (using_main_hand && mh_weapon.correction_dex > 0 || (using_off_hand && oh_weapon.correction_dex > 0)) {
		min_max[1][1] = MAX_ATTRIBUTE;      // Max
	} else {
		min_max[1][1] = attr[0];        // Max
	}

	// Constrain intelligence range
	attr.clear();
	attr.push_back(optimal_character.base_intelligence);

	if (using_main_hand) {
		attr.push_back(mh_weapon.required_int);
	}

	if (using_off_hand) {
		attr.push_back(oh_weapon.required_int);
	}

	// Reverse sort
	sort(attr.begin(), attr.end(), greater<int>());
	min_max[2][0] = attr[0];                // Min
	if (using_main_hand && mh_weapon.correction_int > 0 || (using_off_hand && oh_weapon.correction_int > 0)) {
		min_max[2][1] = MAX_ATTRIBUTE;      // Max
	} else {
		min_max[2][1] = attr[0];        // Max
	}

	// Constrain faith range
	attr.clear();
	attr.push_back(optimal_character.base_faith);

	if (using_main_hand) {
		attr.push_back(mh_weapon.required_fai);
	}

	if (using_off_hand) {
		attr.push_back(oh_weapon.required_fai);
	}

	// Reverse sort
	sort(attr.begin(), attr.end(), greater<int>());
	min_max[3][0] = attr[0];                // Min
	if (using_main_hand && mh_weapon.correction_fai > 0 || (using_off_hand && oh_weapon.correction_fai > 0)) {
		min_max[3][1] = MAX_ATTRIBUTE;      // Max
	} else {
		min_max[3][1] = attr[0];        // Max
	}

	// Constrain arcane range
	attr.clear();
	attr.push_back(optimal_character.base_arcane);

	if (using_main_hand) {
		attr.push_back(mh_weapon.required_arc);
	}

	if (using_off_hand) {
		attr.push_back(oh_weapon.required_arc);
	}

	// Reverse sort
	sort(attr.begin(), attr.end(), greater<int>());
	min_max[4][0] = attr[0];                // Min
	if (using_main_hand && mh_weapon.correction_arc > 0 || (using_off_hand && oh_weapon.correction_arc > 0)) {
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

	// Validate optimization type. We can't optimize for say, fire damage, if the weapon doesn't scale with fire.
	calculation_result = ValidateOptimization();
	if (calculation_result != CALC_PROCEED)
		return;

	// Determine the upper limit of attribute points that will be spread between STR, DEX, INT, FAI, and ARC
	int subset_target = target_level + LEVEL_OFFSET - optimal_character.vigor - optimal_character.mind - optimal_character.endurance;

	// Get all possible solution sets that add to subset_target. The optimal combination of attributes will be one of these returned subsets.
	vector<unsigned long long> solution_sets = SubsetSum::GetAllSubsets(subset_target, min_max);

	// Determine which evaluation function(s) to use.
	std::function<double(AttributeTuple &, bool, ERBuildOptimizer &)> mh_eval_func;
	std::function<double(AttributeTuple &, bool, ERBuildOptimizer &)> oh_eval_func;

	if (using_main_hand)
		mh_eval_func = GetOptEvaluator(mh_optimization_type);
	if (using_main_hand)
		oh_eval_func = GetOptEvaluator(oh_optimization_type);

	AttributeTuple attribute_tuple;
	size_t solution_count = solution_sets.size();

	double mh_result, oh_result, result;

	// Evaluate all the solution sets and their permutations.
	for (size_t i = 0; i < solution_count; i++) {
		// Populate an attribute tuple.
		attribute_tuple.strength = (int)((solution_sets[i] & STR_MASK) >> 32);
		attribute_tuple.dexterity = (int)((solution_sets[i] & DEX_MASK) >> 24);
		attribute_tuple.intelligence = (int)((solution_sets[i] & INT_MASK) >> 16);
		attribute_tuple.faith = (int)((solution_sets[i] & FAI_MASK) >> 8);
		attribute_tuple.arcane = (int)(solution_sets[i] & ARC_MASK);

		mh_result = 0;
		oh_result = 0;

		// Get main hand and off hand results separately.
		if (using_main_hand) {
			mh_result = mh_eval_func(attribute_tuple, true, *this);
		}
		if (using_off_hand) {
			oh_result = oh_eval_func(attribute_tuple, true, *this);
		}

		// Add both weapon results together.
		result = mh_result + oh_result;

		// See if we have a new highest result.
		if (result > highest_result + EVAL_THRESHOLD) {
			optimal_character.opt_strength = attribute_tuple.strength;
			optimal_character.opt_dexterity = attribute_tuple.dexterity;
			optimal_character.opt_intelligence = attribute_tuple.intelligence;
			optimal_character.opt_faith = attribute_tuple.faith;
			optimal_character.opt_arcane = attribute_tuple.arcane;

			highest_result = result;
			calculation_result = CALC_SUCCESS;
		}
	}

	if (calculation_result != CALC_SUCCESS) {
		// If we are here at this point, it means no solution was reached after trying every possible subset.
		calculation_result = CALC_FAIL_NULL_RESULT;
	}

	// Calculate resultant stats.
	if (using_main_hand) {
		CalcWeaponDamage(mh_weapon, optimal_character);
		CalcPassives(mh_weapon);
		CalcWeaponSkill(mh_weapon, optimal_character, mh_skill);
	}

	if (using_off_hand) {
		CalcWeaponDamage(oh_weapon, optimal_character);
		CalcPassives(oh_weapon);
		CalcWeaponSkill(oh_weapon, optimal_character, oh_skill);
	}
}

// Determine which evaluation function should be used, based on the selected optimization type.
std::function<double(AttributeTuple &, bool, ERBuildOptimizer &)> ERBuildOptimizer::GetOptEvaluator(OPTIMIZATION_TYPE optimization_type) {
	// Weapon attack
	if (optimization_type >= OPTIMIZATION_TYPE::DAMAGE_TOTAL && optimization_type <= OPTIMIZATION_TYPE::DAMAGE_HOLY) {
		return EvaluateWeaponDamage;
	}

	// Weapon skill
	if (optimization_type == OPTIMIZATION_TYPE::DAMAGE_SKILL) {
		return EvaluateSkillDamage;
	}

	// Status effects
	if (optimization_type >= OPTIMIZATION_TYPE::STATUS_POISON) {
		return EvaluateStatusEffect;
	}
}

// Evaluate by Weapon Damage
double ERBuildOptimizer::EvaluateWeaponDamage(const AttributeTuple &attribute_tuple, bool main_hand, ERBuildOptimizer &er) {
	// 0: total, 1: physical, 2: magic, 3: fire, 4: lightning, 5: holy
	double damage[6]{0, 0, 0, 0, 0, 0};
	Weapon *weapon;
	OPTIMIZATION_TYPE optimization_type;

	if (main_hand) {
		weapon = &er.mh_weapon;
		optimization_type = er.mh_optimization_type;
	} else {
		weapon = &er.oh_weapon;
		optimization_type = er.oh_optimization_type;
	}

	CorrectionTuple scaling_tuple{
		.correction_str =  weapon->correction_str,
		.correction_dex =  weapon->correction_dex,
		.correction_int =  weapon->correction_int,
		.correction_fai =  weapon->correction_fai,
		.correction_arc =  weapon->correction_arc
	};

	// Get physical damage.
	damage[1] = CalculateCorrectedDamage(*weapon,
										 attribute_tuple,
										 scaling_tuple,
										 DAMAGE_TYPE::PHYSICAL,
										 weapon->damage_physical * weapon->damage_pct_physical,
										 er.is_two_handing, weapon->attack_element_correct_bitmask);

	// Get magic damage.
	damage[2] = CalculateCorrectedDamage(*weapon,
										 attribute_tuple,
										 scaling_tuple,
										 DAMAGE_TYPE::MAGIC,
										 weapon->damage_magic * weapon->damage_pct_magic,
										 er.is_two_handing, weapon->attack_element_correct_bitmask);

	// Get fire damage.
	damage[3] = CalculateCorrectedDamage(*weapon,
										 attribute_tuple,
										 scaling_tuple,
										 DAMAGE_TYPE::FIRE,
										 weapon->damage_fire * weapon->damage_pct_fire,
										 er.is_two_handing, weapon->attack_element_correct_bitmask);

	// Get lightning damage.
	damage[4] = CalculateCorrectedDamage(*weapon,
										 attribute_tuple,
										 scaling_tuple,
										 DAMAGE_TYPE::LIGHTNING,
										 weapon->damage_lightning * weapon->damage_pct_lightning,
										 er.is_two_handing, weapon->attack_element_correct_bitmask);

	// Get holy damage.
	damage[5] = CalculateCorrectedDamage(*weapon,
										 attribute_tuple,
										 scaling_tuple,
										 DAMAGE_TYPE::HOLY,
										 weapon->damage_holy * weapon->damage_pct_holy,
										 er.is_two_handing, weapon->attack_element_correct_bitmask);

	// Get total damage.
	damage[0] = damage[1] + damage[2] + damage[3] + damage[4] + damage[5];

	// Return the desired damage type.
	return damage[optimization_type];
}

double ERBuildOptimizer::EvaluateSkillDamage(const AttributeTuple &attribute_tuple, bool main_hand, ERBuildOptimizer &er) {
	Weapon *weapon;
	WeaponSkill *skill;

	if (main_hand) {
		weapon = &er.mh_weapon;
		skill = &er.mh_skill;
	} else {
		weapon = &er.oh_weapon;
		skill = &er.oh_skill;
	}

	// Calculate base damage.
	double base_damage_physical =
		weapon->damage_physical * weapon->damage_pct_physical * skill->atk_correct_physical / 100.0 + 4 * skill->atk_physical;
	double base_damage_magic = weapon->damage_magic * weapon->damage_pct_magic * skill->atk_correct_magic / 100.0 + 4 * skill->atk_magic;
	double base_damage_fire = weapon->damage_fire * weapon->damage_pct_fire * skill->atk_correct_fire / 100.0 + 4 * skill->atk_fire;
	double base_damage_lightning =
		weapon->damage_lightning * weapon->damage_pct_lightning * skill->atk_correct_lightning / 100.0 + 4 * skill->atk_lightning;
	double base_damage_holy = weapon->damage_holy * weapon->damage_pct_holy * skill->atk_correct_holy / 100.0 + 4 * skill->atk_holy;

	// Determine if the two-handed attack bonus is applied.
	bool two_hand_bonus = er.is_two_handing && !skill->disable_2h_atk_bonus;

	CorrectionTuple scaling_tuple{};

	GetWeaponSkillScaling(*weapon, *skill, scaling_tuple, DAMAGE_TYPE::PHYSICAL);

	double damage_physical =
		CalculateCorrectedDamage(*weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::PHYSICAL,
								 base_damage_physical,
								 two_hand_bonus,
								 weapon->attack_element_correct_bitmask);

	GetWeaponSkillScaling(*weapon, *skill, scaling_tuple, DAMAGE_TYPE::MAGIC);

	double damage_magic =
		CalculateCorrectedDamage(*weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::MAGIC,
								 base_damage_magic,
								 two_hand_bonus,
								 weapon->attack_element_correct_bitmask);

	GetWeaponSkillScaling(*weapon, *skill, scaling_tuple, DAMAGE_TYPE::FIRE);

	double damage_fire =
		CalculateCorrectedDamage(*weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::FIRE,
								 base_damage_fire,
								 two_hand_bonus,
								 weapon->attack_element_correct_bitmask);

	GetWeaponSkillScaling(*weapon, *skill, scaling_tuple, DAMAGE_TYPE::LIGHTNING);

	double damage_lightning =
		CalculateCorrectedDamage(*weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::LIGHTNING,
								 base_damage_lightning,
								 two_hand_bonus, weapon->attack_element_correct_bitmask);

	GetWeaponSkillScaling(*weapon, *skill, scaling_tuple, DAMAGE_TYPE::HOLY);

	double damage_holy =
		CalculateCorrectedDamage(*weapon,
								 attribute_tuple,
								 scaling_tuple,
								 DAMAGE_TYPE::HOLY,
								 base_damage_holy,
								 two_hand_bonus,
								 weapon->attack_element_correct_bitmask);

	// Return the result.
	return damage_physical + damage_magic + damage_fire + damage_lightning + damage_holy;
}

// Evaluate by Status Effect
double ERBuildOptimizer::EvaluateStatusEffect(const AttributeTuple &attribute_tuple, bool main_hand, ERBuildOptimizer &er) {
	// 0: poison, 1: bleed, 2: frost, 3: sleep, 4: madness, 5: scarlet rot
	double status[6]{0, 0, 0, 0, 0, 0};
	Weapon *weapon;
	OPTIMIZATION_TYPE optimization_type;

	if (main_hand) {
		weapon = &er.mh_weapon;
		optimization_type = er.mh_optimization_type;
	} else {
		weapon = &er.oh_weapon;
		optimization_type = er.oh_optimization_type;
	}

	// Poison Scaling
	if (weapon->pass1_poison > 0) {
		status[0] = CalculatePassive(weapon->pass1_poison,
									 attribute_tuple.arcane,
									 weapon->correction_arc,
									 weapon->correction_pct_arc,
									 weapon->poison_stat_max_0,
									 weapon->poison_stat_max_1,
									 weapon->poison_stat_max_2,
									 weapon->poison_stat_max_3,
									 weapon->poison_stat_max_4,
									 weapon->poison_grow_0,
									 weapon->poison_grow_1,
									 weapon->poison_grow_2,
									 weapon->poison_grow_3,
									 weapon->poison_grow_4,
									 weapon->poison_adjustment_pt_grow_0,
									 weapon->poison_adjustment_pt_grow_1,
									 weapon->poison_adjustment_pt_grow_2,
									 weapon->poison_adjustment_pt_grow_3,
									 weapon->poison_adjustment_pt_grow_4);
	} else if (weapon->pass2_poison > 0) {
		status[0] = CalculatePassive(weapon->pass2_poison,
									 attribute_tuple.arcane,
									 weapon->correction_arc,
									 weapon->correction_pct_arc,
									 weapon->poison_stat_max_0,
									 weapon->poison_stat_max_1,
									 weapon->poison_stat_max_2,
									 weapon->poison_stat_max_3,
									 weapon->poison_stat_max_4,
									 weapon->poison_grow_0,
									 weapon->poison_grow_1,
									 weapon->poison_grow_2,
									 weapon->poison_grow_3,
									 weapon->poison_grow_4,
									 weapon->poison_adjustment_pt_grow_0,
									 weapon->poison_adjustment_pt_grow_1,
									 weapon->poison_adjustment_pt_grow_2,
									 weapon->poison_adjustment_pt_grow_3,
									 weapon->poison_adjustment_pt_grow_4);
	} else if (weapon->pass3_poison > 0) {
		status[0] = CalculatePassive(weapon->pass3_poison,
									 attribute_tuple.arcane,
									 weapon->correction_arc,
									 weapon->correction_pct_arc,
									 weapon->poison_stat_max_0,
									 weapon->poison_stat_max_1,
									 weapon->poison_stat_max_2,
									 weapon->poison_stat_max_3,
									 weapon->poison_stat_max_4,
									 weapon->poison_grow_0,
									 weapon->poison_grow_1,
									 weapon->poison_grow_2,
									 weapon->poison_grow_3,
									 weapon->poison_grow_4,
									 weapon->poison_adjustment_pt_grow_0,
									 weapon->poison_adjustment_pt_grow_1,
									 weapon->poison_adjustment_pt_grow_2,
									 weapon->poison_adjustment_pt_grow_3,
									 weapon->poison_adjustment_pt_grow_4);
	}

	// Bleed Scaling
	if (weapon->pass1_bleed > 0) {
		status[1] = CalculatePassive(weapon->pass1_bleed,
									 attribute_tuple.arcane,
									 weapon->correction_arc,
									 weapon->correction_pct_arc,
									 weapon->bleed_stat_max_0,
									 weapon->bleed_stat_max_1,
									 weapon->bleed_stat_max_2,
									 weapon->bleed_stat_max_3,
									 weapon->bleed_stat_max_4,
									 weapon->bleed_grow_0,
									 weapon->bleed_grow_1,
									 weapon->bleed_grow_2,
									 weapon->bleed_grow_3,
									 weapon->bleed_grow_4,
									 weapon->bleed_adjustment_pt_grow_0,
									 weapon->bleed_adjustment_pt_grow_1,
									 weapon->bleed_adjustment_pt_grow_2,
									 weapon->bleed_adjustment_pt_grow_3,
									 weapon->bleed_adjustment_pt_grow_4);
	} else if (weapon->pass2_bleed > 0) {
		status[1] = CalculatePassive(weapon->pass2_bleed,
									 attribute_tuple.arcane,
									 weapon->correction_arc,
									 weapon->correction_pct_arc,
									 weapon->bleed_stat_max_0,
									 weapon->bleed_stat_max_1,
									 weapon->bleed_stat_max_2,
									 weapon->bleed_stat_max_3,
									 weapon->bleed_stat_max_4,
									 weapon->bleed_grow_0,
									 weapon->bleed_grow_1,
									 weapon->bleed_grow_2,
									 weapon->bleed_grow_3,
									 weapon->bleed_grow_4,
									 weapon->bleed_adjustment_pt_grow_0,
									 weapon->bleed_adjustment_pt_grow_1,
									 weapon->bleed_adjustment_pt_grow_2,
									 weapon->bleed_adjustment_pt_grow_3,
									 weapon->bleed_adjustment_pt_grow_4);
	} else if (weapon->pass3_bleed) {
		status[1] = CalculatePassive(weapon->pass3_bleed,
									 attribute_tuple.arcane,
									 weapon->correction_arc,
									 weapon->correction_pct_arc,
									 weapon->bleed_stat_max_0,
									 weapon->bleed_stat_max_1,
									 weapon->bleed_stat_max_2,
									 weapon->bleed_stat_max_3,
									 weapon->bleed_stat_max_4,
									 weapon->bleed_grow_0,
									 weapon->bleed_grow_1,
									 weapon->bleed_grow_2,
									 weapon->bleed_grow_3,
									 weapon->bleed_grow_4,
									 weapon->bleed_adjustment_pt_grow_0,
									 weapon->bleed_adjustment_pt_grow_1,
									 weapon->bleed_adjustment_pt_grow_2,
									 weapon->bleed_adjustment_pt_grow_3,
									 weapon->bleed_adjustment_pt_grow_4);
	}

	// Frostbite
	if (weapon->pass1_frost > 0)
		status[2] = weapon->pass1_frost;
	else if (weapon->pass2_frost > 0)
		status[2] = weapon->pass2_frost;
	else if (weapon->pass3_frost > 0)
		status[2] = weapon->pass3_frost;

	// Sleep
	if (weapon->pass1_sleep > 0)
		status[3] = weapon->pass1_sleep;
	else if (weapon->pass2_sleep > 0)
		status[3] = weapon->pass2_sleep;
	else if (weapon->pass3_sleep > 0)
		status[3] = weapon->pass3_sleep;

	// Madness
	if (weapon->pass1_madness > 0)
		status[4] = weapon->pass1_madness;
	else if (weapon->pass2_madness > 0)
		status[4] = weapon->pass2_madness;
	else if (weapon->pass3_madness > 0)
		status[4] = weapon->pass3_madness;

	// Scarlet Rot
	if (weapon->pass1_scarlet_rot > 0)
		status[5] = weapon->pass1_scarlet_rot;
	else if (weapon->pass2_scarlet_rot > 0)
		status[5] = weapon->pass2_scarlet_rot;
	else if (weapon->pass3_scarlet_rot > 0)
		status[5] = weapon->pass3_scarlet_rot;

	// You see what I did here? I thought it was clever.
	return status[optimization_type - OPTIMIZATION_TYPE::STATUS_POISON];
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

	skill.attack_element_correct_bitmask = stoi(string(py::str(s["attack_element_correct_bitmask"])));

	skill.overwrite_str_correct_phys = stoi(string(py::str(s["overwrite_str_correct_phys"])));
	skill.overwrite_dex_correct_phys = stoi(string(py::str(s["overwrite_dex_correct_phys"])));
	skill.overwrite_int_correct_phys = stoi(string(py::str(s["overwrite_int_correct_phys"])));
	skill.overwrite_fai_correct_phys = stoi(string(py::str(s["overwrite_fai_correct_phys"])));
	skill.overwrite_arc_correct_phys = stoi(string(py::str(s["overwrite_arc_correct_phys"])));

	skill.overwrite_str_correct_magic = stoi(string(py::str(s["overwrite_str_correct_magic"])));
	skill.overwrite_dex_correct_magic = stoi(string(py::str(s["overwrite_dex_correct_magic"])));
	skill.overwrite_int_correct_magic = stoi(string(py::str(s["overwrite_int_correct_magic"])));
	skill.overwrite_fai_correct_magic = stoi(string(py::str(s["overwrite_fai_correct_magic"])));
	skill.overwrite_arc_correct_magic = stoi(string(py::str(s["overwrite_arc_correct_magic"])));
	skill.overwrite_str_correct_fire = stoi(string(py::str(s["overwrite_str_correct_fire"])));
	skill.overwrite_dex_correct_fire = stoi(string(py::str(s["overwrite_dex_correct_fire"])));
	skill.overwrite_int_correct_fire = stoi(string(py::str(s["overwrite_int_correct_fire"])));
	skill.overwrite_fai_correct_fire = stoi(string(py::str(s["overwrite_fai_correct_fire"])));
	skill.overwrite_arc_correct_fire = stoi(string(py::str(s["overwrite_arc_correct_fire"])));
	skill.overwrite_str_correct_lightning = stoi(string(py::str(s["overwrite_str_correct_lightning"])));
	skill.overwrite_dex_correct_lightning = stoi(string(py::str(s["overwrite_dex_correct_lightning"])));
	skill.overwrite_int_correct_lightning = stoi(string(py::str(s["overwrite_int_correct_lightning"])));
	skill.overwrite_fai_correct_lightning = stoi(string(py::str(s["overwrite_fai_correct_lightning"])));
	skill.overwrite_arc_correct_lightning = stoi(string(py::str(s["overwrite_arc_correct_lightning"])));
	skill.overwrite_str_correct_holy = stoi(string(py::str(s["overwrite_str_correct_holy"])));
	skill.overwrite_dex_correct_holy = stoi(string(py::str(s["overwrite_dex_correct_holy"])));
	skill.overwrite_int_correct_holy = stoi(string(py::str(s["overwrite_int_correct_holy"])));
	skill.overwrite_fai_correct_holy = stoi(string(py::str(s["overwrite_fai_correct_holy"])));
	skill.overwrite_arc_correct_holy = stoi(string(py::str(s["overwrite_arc_correct_holy"])));

	if (main_hand) {
		mh_skill = skill;
	} else {
		oh_skill = skill;
	}
}

// Calculate corrected damage
double ERBuildOptimizer::CalculateCorrectedDamage(const Weapon &selected_weapon,
												  const AttributeTuple &attribute_tuple,
												  const CorrectionTuple &scaling_tuple,
												  const DAMAGE_TYPE damage_type,
												  const double base_damage,
												  const bool is_two_handing,
												  const int aec_bitmask) {
	int mask = 0;
	int stat_max[5]{};
	int grow[5]{};
	double adj_pt_grow[5]{};

	// Weapon scaling by attribute
	int correction[5]{
		selected_weapon.correction_str,
		selected_weapon.correction_dex,
		selected_weapon.correction_int,
		selected_weapon.correction_fai,
		selected_weapon.correction_arc
	};

	// Reinforcement
	double correction_pct[5]{
		selected_weapon.correction_pct_str,
		selected_weapon.correction_pct_dex,
		selected_weapon.correction_pct_int,
		selected_weapon.correction_pct_fai,
		selected_weapon.correction_pct_arc
	};

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
			base_damage * correction[3] * correction_pct[3] * CalculateCorrectFn(attribute_tuple.faith, stat_max, grow, adj_pt_grow)
				/ 10000.0;
	}

	// Arcane
	if (aec_bitmask & mask >> 4) {
		corrected_damage +=
			base_damage * correction[4] * correction_pct[4] * CalculateCorrectFn(attribute_tuple.arcane, stat_max, grow, adj_pt_grow)
				/ 10000.0;
	}

	return corrected_damage;
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

// Calculate weapon damage.
void ERBuildOptimizer::CalcWeaponDamage(Weapon &weapon, const Tarnished &tarnished) const {
	AttributeTuple attribute_tuple{
		.strength = tarnished.opt_strength,
		.dexterity = tarnished.opt_dexterity,
		.intelligence = tarnished.opt_intelligence,
		.faith = tarnished.opt_faith,
		.arcane = tarnished.opt_arcane
	};

	CorrectionTuple scaling_tuple{
		.correction_str =  weapon.correction_str,
		.correction_dex =  weapon.correction_dex,
		.correction_int =  weapon.correction_int,
		.correction_fai =  weapon.correction_fai,
		.correction_arc =  weapon.correction_arc,
	};

	// Get physical damage.
	weapon.max_physical_dmg = CalculateCorrectedDamage(weapon,
													   attribute_tuple,
													   scaling_tuple,
													   DAMAGE_TYPE::PHYSICAL,
													   weapon.damage_physical * weapon.damage_pct_physical,
													   is_two_handing, weapon.attack_element_correct_bitmask);

	// Get magic damage.
	weapon.max_magic_dmg = CalculateCorrectedDamage(weapon,
													attribute_tuple,
													scaling_tuple,
													DAMAGE_TYPE::MAGIC,
													weapon.damage_magic * weapon.damage_pct_magic,
													is_two_handing, weapon.attack_element_correct_bitmask);

	// Get fire damage.
	weapon.max_fire_dmg = CalculateCorrectedDamage(weapon,
												   attribute_tuple,
												   scaling_tuple,
												   DAMAGE_TYPE::FIRE,
												   weapon.damage_fire * weapon.damage_pct_fire,
												   is_two_handing, weapon.attack_element_correct_bitmask);

	// Get lightning damage.
	weapon.max_lightning_dmg = CalculateCorrectedDamage(weapon,
														attribute_tuple,
														scaling_tuple,
														DAMAGE_TYPE::LIGHTNING,
														weapon.damage_lightning * weapon.damage_pct_lightning,
														is_two_handing, weapon.attack_element_correct_bitmask);

	// Get holy damage.
	weapon.max_holy_dmg = CalculateCorrectedDamage(weapon,
												   attribute_tuple,
												   scaling_tuple,
												   DAMAGE_TYPE::HOLY,
												   weapon.damage_holy * weapon.damage_pct_holy,
												   is_two_handing, weapon.attack_element_correct_bitmask);

	// Check for NaNs
	if (isnan(weapon.max_physical_dmg))
		weapon.max_physical_dmg = 0;
	if (isnan(weapon.max_magic_dmg))
		weapon.max_magic_dmg = 0;
	if (isnan(weapon.max_fire_dmg))
		weapon.max_fire_dmg = 0;
	if (isnan(weapon.max_lightning_dmg))
		weapon.max_lightning_dmg = 0;
	if (isnan(weapon.max_holy_dmg))
		weapon.max_holy_dmg = 0;


	// Get total damage.
	weapon.max_total_dmg =
		weapon.max_physical_dmg + weapon.max_magic_dmg + weapon.max_fire_dmg + weapon.max_lightning_dmg + weapon.max_holy_dmg;
}

// Determine weapon skill scaling. Most skills utilize default weapon scaling, but some do not.
void ERBuildOptimizer::GetWeaponSkillScaling(const Weapon &weapon,
											 WeaponSkill &skill,
											 CorrectionTuple &scaling_tuple,
											 DAMAGE_TYPE damage_type) {
	// Test if default weapon scaling is being overridden. -1 means no.
	if (skill.attack_element_correct_id == -1) {
		// Use weapon defaults.
		scaling_tuple.correction_str = weapon.correction_str;
		scaling_tuple.correction_dex = weapon.correction_dex;
		scaling_tuple.correction_int = weapon.correction_int;
		scaling_tuple.correction_fai = weapon.correction_fai;
		scaling_tuple.correction_arc = weapon.correction_arc;
	} else {
		// Set scaling overrides.
		switch (damage_type) {
		case DAMAGE_TYPE::MAGIC:
			scaling_tuple.correction_str =
				skill.overwrite_str_correct_magic != -1 ? skill.overwrite_str_correct_magic : weapon.correction_str;
			scaling_tuple.correction_str =
				skill.overwrite_dex_correct_magic != -1 ? skill.overwrite_dex_correct_magic : weapon.correction_dex;
			scaling_tuple.correction_str =
				skill.overwrite_int_correct_magic != -1 ? skill.overwrite_int_correct_magic : weapon.correction_int;
			scaling_tuple.correction_str =
				skill.overwrite_fai_correct_magic != -1 ? skill.overwrite_fai_correct_magic : weapon.correction_fai;
			scaling_tuple.correction_str =
				skill.overwrite_arc_correct_magic != -1 ? skill.overwrite_arc_correct_magic : weapon.correction_arc;
			break;
		case DAMAGE_TYPE::FIRE:
			scaling_tuple.correction_str =
				skill.overwrite_str_correct_fire != -1 ? skill.overwrite_str_correct_fire : weapon.correction_str;
			scaling_tuple.correction_str =
				skill.overwrite_dex_correct_fire != -1 ? skill.overwrite_dex_correct_fire : weapon.correction_dex;
			scaling_tuple.correction_str =
				skill.overwrite_int_correct_fire != -1 ? skill.overwrite_int_correct_fire : weapon.correction_int;
			scaling_tuple.correction_str =
				skill.overwrite_fai_correct_fire != -1 ? skill.overwrite_fai_correct_fire : weapon.correction_fai;
			scaling_tuple.correction_str =
				skill.overwrite_arc_correct_fire != -1 ? skill.overwrite_arc_correct_fire : weapon.correction_arc;
			break;
		case DAMAGE_TYPE::LIGHTNING:
			scaling_tuple.correction_str = skill.overwrite_str_correct_lightning != -1 ? skill.overwrite_str_correct_lightning : weapon
				.correction_str;
			scaling_tuple.correction_str =
				skill.overwrite_dex_correct_lightning != -1 ? skill.overwrite_dex_correct_lightning : weapon.correction_dex;
			scaling_tuple.correction_str =
				skill.overwrite_int_correct_lightning != -1 ? skill.overwrite_int_correct_lightning : weapon.correction_int;
			scaling_tuple.correction_str =
				skill.overwrite_fai_correct_lightning != -1 ? skill.overwrite_fai_correct_lightning : weapon.correction_fai;
			scaling_tuple.correction_str =
				skill.overwrite_arc_correct_lightning != -1 ? skill.overwrite_arc_correct_lightning : weapon.correction_arc;
			break;
		case DAMAGE_TYPE::HOLY:
			scaling_tuple.correction_str =
				skill.overwrite_str_correct_holy != -1 ? skill.overwrite_str_correct_holy : weapon.correction_str;
			scaling_tuple.correction_str =
				skill.overwrite_dex_correct_holy != -1 ? skill.overwrite_dex_correct_holy : weapon.correction_dex;
			scaling_tuple.correction_str =
				skill.overwrite_int_correct_holy != -1 ? skill.overwrite_int_correct_holy : weapon.correction_int;
			scaling_tuple.correction_str =
				skill.overwrite_fai_correct_holy != -1 ? skill.overwrite_fai_correct_holy : weapon.correction_fai;
			scaling_tuple.correction_str =
				skill.overwrite_arc_correct_holy != -1 ? skill.overwrite_arc_correct_holy : weapon.correction_arc;
			break;
		default:
			scaling_tuple.correction_str =
				skill.overwrite_str_correct_phys != -1 ? skill.overwrite_str_correct_phys : weapon.correction_str;
			scaling_tuple.correction_str =
				skill.overwrite_dex_correct_phys != -1 ? skill.overwrite_dex_correct_phys : weapon.correction_dex;
			scaling_tuple.correction_str =
				skill.overwrite_int_correct_phys != -1 ? skill.overwrite_int_correct_phys : weapon.correction_int;
			scaling_tuple.correction_str =
				skill.overwrite_fai_correct_phys != -1 ? skill.overwrite_fai_correct_phys : weapon.correction_fai;
			scaling_tuple.correction_str =
				skill.overwrite_arc_correct_phys != -1 ? skill.overwrite_arc_correct_phys : weapon.correction_arc;
			break;
		}
	}
}

// Validate that we're not optimizing for a non-scaling damage type.
int ERBuildOptimizer::ValidateOptimization() const {
	if (using_main_hand) {
		switch (mh_optimization_type) {
		case OPTIMIZATION_TYPE::DAMAGE_PHYSICAL:
			if (mh_weapon.attack_element_correct_bitmask & PH_STR || mh_weapon.attack_element_correct_bitmask & PH_DEX || mh_weapon.attack_element_correct_bitmask & PH_INT || mh_weapon.attack_element_correct_bitmask & PH_FAI  || mh_weapon.attack_element_correct_bitmask & PH_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_MAGIC:
			if (mh_weapon.attack_element_correct_bitmask & MA_STR || mh_weapon.attack_element_correct_bitmask & MA_DEX || mh_weapon.attack_element_correct_bitmask & MA_INT || mh_weapon.attack_element_correct_bitmask & MA_FAI  || mh_weapon.attack_element_correct_bitmask & MA_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_FIRE:
			if (mh_weapon.attack_element_correct_bitmask & FI_STR || mh_weapon.attack_element_correct_bitmask & FI_DEX || mh_weapon.attack_element_correct_bitmask & FI_INT || mh_weapon.attack_element_correct_bitmask & FI_FAI  || mh_weapon.attack_element_correct_bitmask & FI_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_LIGHTNING:
			if (mh_weapon.attack_element_correct_bitmask & LI_STR || mh_weapon.attack_element_correct_bitmask & LI_DEX || mh_weapon.attack_element_correct_bitmask & LI_INT || mh_weapon.attack_element_correct_bitmask & PH_FAI  || mh_weapon.attack_element_correct_bitmask & LI_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_HOLY:
			if (mh_weapon.attack_element_correct_bitmask & HO_STR || mh_weapon.attack_element_correct_bitmask & HO_DEX || mh_weapon.attack_element_correct_bitmask & HO_INT || mh_weapon.attack_element_correct_bitmask & HO_FAI  || mh_weapon.attack_element_correct_bitmask & HO_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_POISON:
			if (mh_weapon.pass1_poison || mh_weapon.pass2_poison || mh_weapon.pass3_poison)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_BLEED:
			if (mh_weapon.pass1_bleed || mh_weapon.pass2_bleed || mh_weapon.pass3_bleed)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_FROSTBITE:
			if (mh_weapon.pass1_frost || mh_weapon.pass2_frost || mh_weapon.pass3_frost)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_SLEEP:
			if (mh_weapon.pass1_sleep || mh_weapon.pass2_sleep || mh_weapon.pass3_sleep)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_MADNESS:
			if (mh_weapon.pass1_madness || mh_weapon.pass2_madness || mh_weapon.pass3_madness)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_SCARLET_ROT:
			if (mh_weapon.pass1_scarlet_rot || mh_weapon.pass2_scarlet_rot || mh_weapon.pass3_scarlet_rot)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_SKILL:
			if (mh_skill.id != 0)
				return CALC_PROCEED;
		}
	}

	if (using_off_hand) {
		switch (oh_optimization_type) {
		case OPTIMIZATION_TYPE::DAMAGE_PHYSICAL:
			if (oh_weapon.attack_element_correct_bitmask & PH_STR || oh_weapon.attack_element_correct_bitmask & PH_DEX || oh_weapon.attack_element_correct_bitmask & PH_INT || oh_weapon.attack_element_correct_bitmask & PH_FAI  || oh_weapon.attack_element_correct_bitmask & PH_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_MAGIC:
			if (oh_weapon.attack_element_correct_bitmask & MA_STR || oh_weapon.attack_element_correct_bitmask & MA_DEX || oh_weapon.attack_element_correct_bitmask & MA_INT || oh_weapon.attack_element_correct_bitmask & MA_FAI  || oh_weapon.attack_element_correct_bitmask & MA_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_FIRE:
			if (oh_weapon.attack_element_correct_bitmask & FI_STR || oh_weapon.attack_element_correct_bitmask & FI_DEX || oh_weapon.attack_element_correct_bitmask & FI_INT || oh_weapon.attack_element_correct_bitmask & FI_FAI  || oh_weapon.attack_element_correct_bitmask & FI_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_LIGHTNING:
			if (oh_weapon.attack_element_correct_bitmask & LI_STR || oh_weapon.attack_element_correct_bitmask & LI_DEX || oh_weapon.attack_element_correct_bitmask & LI_INT || oh_weapon.attack_element_correct_bitmask & PH_FAI  || oh_weapon.attack_element_correct_bitmask & LI_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_HOLY:
			if (oh_weapon.attack_element_correct_bitmask & HO_STR || oh_weapon.attack_element_correct_bitmask & HO_DEX || oh_weapon.attack_element_correct_bitmask & HO_INT || oh_weapon.attack_element_correct_bitmask & HO_FAI  || oh_weapon.attack_element_correct_bitmask & HO_ARC)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_POISON:
			if (oh_weapon.pass1_poison || oh_weapon.pass2_poison || oh_weapon.pass3_poison)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_BLEED:
			if (oh_weapon.pass1_bleed || oh_weapon.pass2_bleed || oh_weapon.pass3_bleed)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_FROSTBITE:
			if (oh_weapon.pass1_frost || oh_weapon.pass2_frost || oh_weapon.pass3_frost)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_SLEEP:
			if (oh_weapon.pass1_sleep || oh_weapon.pass2_sleep || oh_weapon.pass3_sleep)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_MADNESS:
			if (oh_weapon.pass1_madness || oh_weapon.pass2_madness || oh_weapon.pass3_madness)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::STATUS_SCARLET_ROT:
			if (oh_weapon.pass1_scarlet_rot || oh_weapon.pass2_scarlet_rot || oh_weapon.pass3_scarlet_rot)
				return CALC_PROCEED;
			break;
		case OPTIMIZATION_TYPE::DAMAGE_SKILL:
			if (oh_skill.id != 0)
				return CALC_PROCEED;
		}
	}

	return CALC_FAIL_INVALID_OPT;
}



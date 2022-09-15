#ifndef  PYMODELS_H
#define PYMODELS_H

#include <string>

using namespace std;

// Tarnished model
struct Tarnished {
	// Default constructor
	Tarnished() = default;

	// Base attributes
	string name;
	int base_strength = 0;
	int base_dexterity = 0;
	int base_intelligence = 0;
	int base_faith = 0;
	int base_arcane = 0;
	int base_vigor = 0;
	int base_mind = 0;
	int base_endurance = 0;

	// User specified attributes
	int vigor = 0;
	int mind = 0;
	int endurance = 0;

	// Optimized attributes
	int opt_strength = 0;
	int opt_dexterity = 0;
	int opt_intelligence = 0;
	int opt_faith = 0;
	int opt_arcane = 0;
};

// weapon model
struct Weapon {

	// Default constructor
	Weapon() = default;

	int id = 0;
	string name;
	string weapon_type;
	string origin_weapon;

	// Base Damage
	int damage_physical = 0;
	int damage_magic = 0;
	int damage_fire = 0;
	int damage_lightning = 0;
	int damage_holy = 0;

	// Required Stats
	int required_str = 0;
	int required_dex = 0;
	int required_int = 0;
	int required_fai = 0;
	int required_arc = 0;

	// Base Correction Values
	int correction_str = 0;
	int correction_dex = 0;
	int correction_int = 0;
	int correction_fai = 0;
	int correction_arc = 0;

	// Bitmask
	string attack_element_correct_bitmask_str;
	int attack_element_correct_bitmask = 0;

	// Reinforcement Values
	double damage_pct_physical = 0.0;
	double damage_pct_magic = 0.0;
	double damage_pct_fire = 0.0;
	double damage_pct_lightning = 0.0;
	double damage_pct_holy = 0.0;
	double damage_pct_stamina = 0.0;
	double damage_pct_poise = 0.0;
	double correction_pct_str = 0.0;
	double correction_pct_dex = 0.0;
	double correction_pct_int = 0.0;
	double correction_pct_fai = 0.0;
	double correction_pct_arc = 0.0;
	double base_damage_pct_overall = 0.0;

	// Calc Correct Values

	// Physical
	int physical_calc_correct_id = 0;
	int physical_stat_max_0 = 0;
	int physical_stat_max_1 = 0;
	int physical_stat_max_2 = 0;
	int physical_stat_max_3 = 0;
	int physical_stat_max_4 = 0;
	int physical_grow_0 = 0;
	int physical_grow_1 = 0;
	int physical_grow_2 = 0;
	int physical_grow_3 = 0;
	int physical_grow_4 = 0;
	double physical_adjustment_pt_grow_0 = 0;
	double physical_adjustment_pt_grow_1 = 0;
	double physical_adjustment_pt_grow_2 = 0;
	double physical_adjustment_pt_grow_3 = 0;
	double physical_adjustment_pt_grow_4 = 0;

	// Magic
	int magic_calc_correct_id = 0;
	int magic_stat_max_0 = 0;
	int magic_stat_max_1 = 0;
	int magic_stat_max_2 = 0;
	int magic_stat_max_3 = 0;
	int magic_stat_max_4 = 0;
	int magic_grow_0 = 0;
	int magic_grow_1 = 0;
	int magic_grow_2 = 0;
	int magic_grow_3 = 0;
	int magic_grow_4 = 0;
	double magic_adjustment_pt_grow_0 = 0;
	double magic_adjustment_pt_grow_1 = 0;
	double magic_adjustment_pt_grow_2 = 0;
	double magic_adjustment_pt_grow_3 = 0;
	double magic_adjustment_pt_grow_4 = 0;

	// Fire
	int fire_calc_correct_id = 0;
	int fire_stat_max_0 = 0;
	int fire_stat_max_1 = 0;
	int fire_stat_max_2 = 0;
	int fire_stat_max_3 = 0;
	int fire_stat_max_4 = 0;
	int fire_grow_0 = 0;
	int fire_grow_1 = 0;
	int fire_grow_2 = 0;
	int fire_grow_3 = 0;
	int fire_grow_4 = 0;
	double fire_adjustment_pt_grow_0 = 0;
	double fire_adjustment_pt_grow_1 = 0;
	double fire_adjustment_pt_grow_2 = 0;
	double fire_adjustment_pt_grow_3 = 0;
	double fire_adjustment_pt_grow_4 = 0;

	// Lightning
	int lightning_calc_correct_id = 0;
	int lightning_stat_max_0 = 0;
	int lightning_stat_max_1 = 0;
	int lightning_stat_max_2 = 0;
	int lightning_stat_max_3 = 0;
	int lightning_stat_max_4 = 0;
	int lightning_grow_0 = 0;
	int lightning_grow_1 = 0;
	int lightning_grow_2 = 0;
	int lightning_grow_3 = 0;
	int lightning_grow_4 = 0;
	double lightning_adjustment_pt_grow_0 = 0;
	double lightning_adjustment_pt_grow_1 = 0;
	double lightning_adjustment_pt_grow_2 = 0;
	double lightning_adjustment_pt_grow_3 = 0;
	double lightning_adjustment_pt_grow_4 = 0;

	// Holy
	int holy_calc_correct_id = 0;
	int holy_stat_max_0 = 0;
	int holy_stat_max_1 = 0;
	int holy_stat_max_2 = 0;
	int holy_stat_max_3 = 0;
	int holy_stat_max_4 = 0;
	int holy_grow_0 = 0;
	int holy_grow_1 = 0;
	int holy_grow_2 = 0;
	int holy_grow_3 = 0;
	int holy_grow_4 = 0;
	double holy_adjustment_pt_grow_0 = 0;
	double holy_adjustment_pt_grow_1 = 0;
	double holy_adjustment_pt_grow_2 = 0;
	double holy_adjustment_pt_grow_3 = 0;
	double holy_adjustment_pt_grow_4 = 0;

	// Poison
	int poison_calc_correct_id = 0;
	int poison_stat_max_0 = 0;
	int poison_stat_max_1 = 0;
	int poison_stat_max_2 = 0;
	int poison_stat_max_3 = 0;
	int poison_stat_max_4 = 0;
	int poison_grow_0 = 0;
	int poison_grow_1 = 0;
	int poison_grow_2 = 0;
	int poison_grow_3 = 0;
	int poison_grow_4 = 0;
	double poison_adjustment_pt_grow_0 = 0;
	double poison_adjustment_pt_grow_1 = 0;
	double poison_adjustment_pt_grow_2 = 0;
	double poison_adjustment_pt_grow_3 = 0;
	double poison_adjustment_pt_grow_4 = 0;

	// Bleed
	int bleed_calc_correct_id = 0;
	int bleed_stat_max_0 = 0;
	int bleed_stat_max_1 = 0;
	int bleed_stat_max_2 = 0;
	int bleed_stat_max_3 = 0;
	int bleed_stat_max_4 = 0;
	int bleed_grow_0 = 0;
	int bleed_grow_1 = 0;
	int bleed_grow_2 = 0;
	int bleed_grow_3 = 0;
	int bleed_grow_4 = 0;
	double bleed_adjustment_pt_grow_0 = 0;
	double bleed_adjustment_pt_grow_1 = 0;
	double bleed_adjustment_pt_grow_2 = 0;
	double bleed_adjustment_pt_grow_3 = 0;
	double bleed_adjustment_pt_grow_4 = 0;

	// Passives

	int pass1_poison = 0;
	int pass1_scarlet_rot = 0;
	int pass1_bleed = 0;
	int pass1_death = 0;
	int pass1_frost = 0;
	int pass1_sleep = 0;
	int pass1_madness = 0;

	int pass2_poison = 0;
	int pass2_scarlet_rot = 0;
	int pass2_bleed = 0;
	int pass2_death = 0;
	int pass2_frost = 0;
	int pass2_sleep = 0;
	int pass2_madness = 0;

	int pass3_poison = 0;
	int pass3_scarlet_rot = 0;
	int pass3_bleed = 0;
	int pass3_death = 0;
	int pass3_frost = 0;
	int pass3_sleep = 0;
	int pass3_madness = 0;

	// Maximized Values(will be needed by the template for display)
	double max_physical_dmg = 0;
	double max_magic_dmg = 0;
	double max_fire_dmg = 0;
	double max_lightning_dmg = 0;
	double max_holy_dmg = 0;
	double max_total_dmg = 0;

	double max_poison = 0;
	double max_bleed = 0;
	double max_frostbite = 0;
	double max_sleep = 0;
	double max_madness = 0;
	double max_scarlet_rot = 0;
};

// WeaponSkill model
struct WeaponSkill {
	int id = 0;
	string name;
	int weapon_id = 0;
	int atk_correct_physical = 0;
	int atk_correct_magic = 0;
	int atk_correct_fire = 0;
	int atk_correct_lightning = 0;
	int atk_correct_holy = 0;
	int atk_correct_stamina = 0;
	int atk_correct_speffect_point = 0;
	int atk_correct_speffect_power = 0;
	int atk_correct_speffect_damage = 0;
	int atk_physical = 0;
	int atk_magic = 0;
	int atk_fire = 0;
	int atk_lightning = 0;
	int atk_holy = 0;
	int atk_stamina = 0;
	int status_correct_point = 0;
	int attack_element_correct_id = 0;
	int add_base_attack = 0;
	int disable_2h_atk_bonus = 0;
	int sub_category1 = 0;
	int sub_category2 = 0;
	int target_speffect0 = 0;
	int target_speffect1 = 0;
	int target_speffect2 = 0;
	int target_speffect3 = 0;
	int target_speffect4 = 0;

	int attack_element_correct_bitmask = 0;
	int overwrite_str_correct_phys = 0;
	int overwrite_dex_correct_phys = 0;
	int overwrite_int_correct_phys = 0;
	int overwrite_fai_correct_phys = 0;
	int overwrite_arc_correct_phys = 0;
	int overwrite_str_correct_magic = 0;
	int overwrite_dex_correct_magic = 0;
	int overwrite_int_correct_magic = 0;
	int overwrite_fai_correct_magic = 0;
	int overwrite_arc_correct_magic = 0;
	int overwrite_str_correct_fire = 0;
	int overwrite_dex_correct_fire = 0;
	int overwrite_int_correct_fire = 0;
	int overwrite_fai_correct_fire = 0;
	int overwrite_arc_correct_fire = 0;
	int overwrite_str_correct_lightning = 0;
	int overwrite_dex_correct_lightning = 0;
	int overwrite_int_correct_lightning = 0;
	int overwrite_fai_correct_lightning = 0;
	int overwrite_arc_correct_lightning = 0;
	int overwrite_str_correct_holy = 0;
	int overwrite_dex_correct_holy = 0;
	int overwrite_int_correct_holy = 0;
	int overwrite_fai_correct_holy = 0;
	int overwrite_arc_correct_holy = 0;

	// Maximized Values(will be needed by the template for display)
	double max_physical_dmg = 0;
	double max_magic_dmg = 0;
	double max_fire_dmg = 0;
	double max_lightning_dmg = 0;
	double max_holy_dmg = 0;
	double max_total_dmg = 0;

	double max_poison = 0;
	double max_bleed = 0;
	double max_frostbite = 0;
	double max_sleep = 0;
	double max_madness = 0;
	double max_scarlet_rot = 0;
};

#endif // ! PYMODELS_H
#ifndef ERBUILD_OPTIMIZER_H
#define ERBUILD_OPTIMIZER_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include "pymodels.h"

// The 5 damage types
enum class DAMAGE_TYPE {
  PHYSICAL, MAGIC, FIRE, LIGHTNING, HOLY
};

namespace py = pybind11;

enum OPTIMIZATION_TYPE {
  DAMAGE_TOTAL,
  DAMAGE_PHYSICAL,
  DAMAGE_MAGIC,
  DAMAGE_FIRE,
  DAMAGE_LIGHTNING,
  DAMAGE_HOLY,
  DAMAGE_SKILL,
  STATUS_POISON,
  STATUS_BLEED,
  STATUS_FROSTBITE,
  STATUS_SLEEP,
  STATUS_MADNESS,
  STATUS_SCARLET_ROT
};

struct AttributeTuple {
  int strength = 0;
  int dexterity = 0;
  int intelligence = 0;
  int faith = 0;
  int arcane = 0;
};

struct CorrectionTuple {
  int correction_str = 0;
  int correction_dex = 0;
  int correction_int = 0;
  int correction_fai = 0;
  int correction_arc = 0;
};

struct CorrectionPctTuple {
  double correct_pct_str = 0.0;
  double correct_pct_dex = 0.0;
  double correct_pct_int = 0.0;
  double correct_pct_fai = 0.0;
  double correct_pct_arc = 0.0;
};

// Build optimizer class.
class ERBuildOptimizer {
 private:
  // Constants
  int const LEVEL_OFFSET = 79;
  int const MAX_ATTRIBUTE = 99;

  // Scaling masks
  static int const PH_STR = 0x1000000;       // Physical(STR) Scaling
  static int const PH_DEX = 0x0800000;       // Physical(DEX) Scaling
  static int const PH_INT = 0x0400000;       // Physical(INT) Scaling
  static int const PH_FAI = 0x0200000;       // Physical(FAI) Scaling
  static int const PH_ARC = 0x0100000;       // Physical(ARC) Scaling
  static int const MA_STR = 0x0080000;       // Magic(STR) Scaling
  static int const MA_DEX = 0x0040000;       // Magic(DEX) Scaling
  static int const MA_INT = 0x0020000;       // Magic(INT) Scaling
  static int const MA_FAI = 0x0010000;       // Magic(FAI) Scaling
  static int const MA_ARC = 0x0008000;       // Magic(ARC) Scaling
  static int const FI_STR = 0x0004000;       // Fire(STR) Scaling
  static int const FI_DEX = 0x0002000;       // Fire(DEX) Scaling
  static int const FI_INT = 0x0001000;       // Fire(INT) Scaling
  static int const FI_FAI = 0x0000800;       // Fire(FAI) Scaling
  static int const FI_ARC = 0x0000400;       // Fire(ARC) Scaling
  static int const LI_STR = 0x0000200;       // Lightning(STR) Scaling
  static int const LI_DEX = 0x0000100;       // Lightning(DEX) Scaling
  static int const LI_INT = 0x0000080;       // Lightning(INT) Scaling
  static int const LI_FAI = 0x0000040;       // Lightning(FAI) Scaling
  static int const LI_ARC = 0x0000020;       // Lightning(ARC) Scaling
  static int const HO_STR = 0x0000010;       // Holy(STR) Scaling
  static int const HO_DEX = 0x0000008;       // Holy(DEX) Scaling
  static int const HO_INT = 0x0000004;       // Holy(INT) Scaling
  static int const HO_FAI = 0x0000002;       // Holy(FAI) Scaling
  static int const HO_ARC = 0x0000001;       // Holy(ARC) Scaling

  unsigned long long const STR_MASK = 0xFF00000000;
  unsigned long long const DEX_MASK = 0x00FF000000;
  unsigned long long const INT_MASK = 0x0000FF0000;
  unsigned long long const FAI_MASK = 0x000000FF00;
  unsigned long long const ARC_MASK = 0x00000000FF;

  static int const CALC_PROCEED = -1;
  static int const CALC_SUCCESS = 0;
  static int const CALC_FAIL_LEVEL_HIGH = 1;
  static int const CALC_FAIL_LEVEL_LOW = 2;

  //bool dual_wield = false;
  bool using_main_hand = false;
  bool using_off_hand = false;

  int target_level = 0;
  bool is_two_handing = false;
  int correct_bitmask = 0;
  double highest_result = 0;
  int calculation_result = CALC_PROCEED;

  double CalculatePassive(const int base, const int correction_arc, const double correction_pct_arc, const int stat_max_0,
						  const int stat_max_1, const int stat_max_2, const int stat_max_3, const int stat_max_4, const int grow_0,
						  const int grow_1, const int grow_2, const int grow_3, const int grow_4, const double adj_pt_grow_0,
						  const double adj_pt_grow_1, const double adj_pt_grow_2, const double adj_pt_grow_3,
						  const double adj_pt_grow_4) const;


  static double EvaluateWeaponDamage(const Weapon &weapon, const AttributeTuple &attribute_tuple, const bool is_two_handing, const OPTIMIZATION_TYPE optimization_type);
  static void EvaluateSkillDamage(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);
  static void EvaluateStatusPoison(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);
  static void EvaluateStatusBleed(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);
  static void EvaluateStatusFrostbite(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);
  static void EvaluateStatusSleep(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);
  static void EvaluateStatusMadness(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);
  static void EvaluateStatusScarletRot(const AttributeTuple & attribute_tuple, ERBuildOptimizer &er);


  void CalcWeaponDamage(Weapon &weapon, const Tarnished &tarnished);
  void CalcPassives(Weapon &weapon);
  void CalcWeaponSkill(const Weapon &weapon, const Tarnished &tarnished, WeaponSkill &selected_skill);
  int Validate(const int min_max[][2]) const;
  static double CalculateCorrectedDamage(const Weapon &selected_weapon, const AttributeTuple &attribute_tuple, const CorrectionTuple & scaling_tuple,
										 const DAMAGE_TYPE damage_type, const double base_damage, const bool is_two_handing, const int attack_element_correct_bitmask);
  static inline double CalculateCorrectFn(const double attribute, const int stat_max[], const int grow[], const double adj_pt_grow[]);
  static inline double CalcCorrectFnInner(const double attribute, const int stat_max, const int stat_max_n, const int grow,
										  const int grow_n, const double adj_grow);
  static inline int ConvertBitMask(const std::string mask);
  static void GetWeaponSkillScaling(const Weapon &weapon, WeaponSkill &skill, CorrectionTuple &scaling_tuple, DAMAGE_TYPE damage_type);

 public:
  ERBuildOptimizer(const int target_level, const bool is_two_handing, const Tarnished &character, const int optimization_type);
  ERBuildOptimizer(const int target_level, const bool is_two_handing, const py::dict &character, const int optimization_type);
  void SetWeapon(const bool main_hand, const py::dict &w);
  void SetWeaponSkill(const bool main_hand, const py::dict &skill);
  void Optimize();
  int GetCalculationResult();

  Tarnished optimal_character;
  Weapon mh_weapon;
  Weapon oh_weapon;
  WeaponSkill mh_skill;
  WeaponSkill oh_skill;
  OPTIMIZATION_TYPE mh_optimization_type;
  OPTIMIZATION_TYPE oh_optimization_type;
};

#endif // ERBUILD_OPTIMIZER_H
// test_utils.hpp

#ifndef TEST_UTILS_HPP
# define TEST_UTILS_HPP

# include "HueAffinity.hpp"
# include <string>

const char*	hueName(HueAffinity::Hue h);
const char*	tierName(HueAffinity::Tier t);

void		dump(const HueAffinity& a, const char* label);

bool		equals(const HueAffinity& a, const HueAffinity& b);

int			fail(const char* msg);
int			pass(const char* msg);

bool		saveToString(const HueAffinity& a, std::string& out);
bool		loadFromString(HueAffinity& a, const std::string& in);

bool		validateSavedTierColumn(const std::string& saved);

#endif

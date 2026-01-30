// tests.cpp
/*
cd ~/ColorGame/code/misc/HueAffinity

c++ -std=c++98 -Wall -Werror -Wextra \
    tests.cpp HueAffinity.cpp HueTestUtils.cpp -I . -o test

./test

cat save.text
*/

#include "HueAffinity.hpp"
#include "HueTestUtils.hpp"
#include <iostream>
#include <cstdlib>	// rand, srand
static int	test_roundtrip_and_column(void)
{
	HueAffinity a;
	HueAffinity b;
	std::string saved;

	// exercise thresholds
	a.addXp(HueAffinity::VERDANT, 999);
	a.addXp(HueAffinity::VERDANT, 1);
	a.addXp(HueAffinity::VERDANT, 4000);
	a.addXp(HueAffinity::VERDANT, 15000);

	a.addXp(HueAffinity::CRIMSON, 1200);

	if (!saveToString(a, saved))
		return (fail("saveToString failed"));

	if (!validateSavedTierColumn(saved))
		return (fail("saved tier column mismatch vs XP"));

	if (!loadFromString(b, saved))
		return (fail("loadFromString failed"));

	if (!equals(a, b))
	{
		dump(a, "A (before save)");
		dump(b, "B (after load)");
		return (fail("roundtrip mismatch"));
	}

	return (pass("roundtrip OK + tier column valid"));
}

static int	test_load_ignores_column(void)
{
	const char* bad =
		"HUEAFFINITY_V1\n"
		"20000 0\n"	// should be 3, but load ignores
		"1200  0\n"	// should be 1, but load ignores
		"0     3\n"
		"0     3\n"
		"0     3\n"
		"0     3\n";

	HueAffinity a;

	if (!loadFromString(a, std::string(bad)))
		return (fail("load should ignore tier column but failed"));

	if (a.getTier(HueAffinity::VERDANT) != HueAffinity::MASTER)
		return (fail("VERDANT tier not derived correctly from XP"));

	if (a.getTier(HueAffinity::CRIMSON) != HueAffinity::ADEPT)
		return (fail("CRIMSON tier not derived correctly from XP"));

	return (pass("load ignores column and derives tier from XP"));
}

static int	test_fuzz(void)
{
	// deterministic seed so failures are reproducible
	std::srand(1337);

	const int iterations = 200;
	const int opsPerIter = 200;

	for (int it = 0; it < iterations; ++it)
	{
		HueAffinity a;
		HueAffinity b;
		std::string saved;

		for (int op = 0; op < opsPerIter; ++op)
		{
			int h = std::rand() % HueAffinity::HUE_COUNT;

			// amounts: mostly small, sometimes bigger
			int r = std::rand() % 1000;
			int amount = 1;

			if (r < 800)        amount = 1 + (std::rand() % 50);       // 1..50
			else if (r < 980)   amount = 51 + (std::rand() % 500);     // 51..550
			else                amount = 551 + (std::rand() % 20000);  // 551..20550

			a.addXp(static_cast<HueAffinity::Hue>(h), amount);
		}

		if (!saveToString(a, saved))
			return (fail("fuzz: saveToString failed"));

		if (!validateSavedTierColumn(saved))
			return (fail("fuzz: saved tier column mismatch vs XP"));

		if (!loadFromString(b, saved))
			return (fail("fuzz: loadFromString failed"));

		if (!equals(a, b))
		{
			dump(a, "FUZZ A (before save)");
			dump(b, "FUZZ B (after load)");
			return (fail("fuzz: roundtrip mismatch"));
		}
	}

	return (pass("fuzz OK (roundtrip + column validation)"));
}

int	main(void)
{
	int status = 0;

	status |= test_roundtrip_and_column();
	status |= test_load_ignores_column();
	status |= test_fuzz();

	if (status == 0)
		std::cout << "\nAll tests OK.\n";
	else
		std::cout << "\nSome tests FAILED.\n";

	return (status);
}

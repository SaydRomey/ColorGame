
#ifndef PRISMWALKER_HPP
# define PRISMWALKER_HPP

# include <string>
# include <vector>
# include <memory>
# include <unordered_map>
# include "Color.hpp"
# include "Skill.hpp"
# include "Artifact.hpp"

class Prismwalker
{
	public:
		// Constructors and destructor
		Prismwalker();
		Prismwalker(const Prismwalker& other);
		Prismwalker& operator=(const Prismwalker& other);
		~Prismwalker();

		// Core mechanics
		void	bindHue(const HueType& hue);
		void	unbindHue(const HueType& hue);
		void	activateHueAbility();
		void	useUltimate();
		void	speakDialogue();

		// Utility
		bool	hasBoundHue(HueType hue) const;
		void	absorbArtifact(const Artifact& artifact);
		void	displayStatus() const;

private:
	std::string							name_;
	std::vector<HueType>				boundHues_;
	std::unordered_map<HueType, Skill>	hueAbilities_;
	std::vector<Artifact>				artifacts_;
	int									maxBoundHues_;
	bool								prismaticUnlocked_;

	void	unlockPrismaticBurst();
};

#endif

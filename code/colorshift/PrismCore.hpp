
#ifndef PRISMCORE_HPP
# define PRISMCORE_HPP

# include <vector>
# include <string>
# include "Hue.hpp"

class PrismCore
{
	private:
		std::vector<Hue>	_boundHues;

	public:
		static constexpr int	MAX_HUES = 3;

		PrismCore();
		~PrismCore();

		bool	isHueBound(HueType type) const;
		bool	bindHue(const Hue& hue);
		void	replaceHue(int index, const Hue& newHue);
		void	unbindHue(HueType type);

		const std::vector<Hue>&	getBoundHues() const;
		std::string				describeState() const;
};

#endif // PRISMCORE_HPP

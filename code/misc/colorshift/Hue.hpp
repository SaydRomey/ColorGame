
#ifndef HUE_HPP
# define HUE_HPP

# include <string>

enum class HueType
{
	NONE,
	RED,
	GREEN,
	BLUE,
	PURPLE,
	YELLOW,
	BROWN
};

class Hue
{
	private:
		HueType		_type;
		std::string	_name;
		std::string	_personalityTrait;
		std::string	_visualCue;

	public:
		Hue(HueType t = HueType::NONE);
		~Hue();

		HueType		getType() const;
		std::string	getName() const;
		std::string	getPersonalityTrait() const;
		std::string	getVisualCue() const;

		bool operator==(const Hue& other) const;
};

#endif // HUE_HPP

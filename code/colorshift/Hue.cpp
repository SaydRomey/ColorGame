
#include "Hue.hpp"

Hue::Hue(HueType t) : _type(t)
{
	switch (t)
	{
		case HueType::RED:
			_name = "Red";
			_personalityTrait = "Bold";
			_visualCue = "Embers";
			break;
		case HueType::GREEN:
			_name = "Green";
			_personalityTrait = "Patient";
			_visualCue = "Vines";
			break;
		case HueType::BLUE:
			_name = "Blue";
			_personalityTrait = "Logical";
			_visualCue = "Mist";
			break;
		case HueType::PURPLE:
			_name = "Purple";
			_personalityTrait = "Empathetic";
			_visualCue = "Dreamflakes";
			break;
		case HueType::YELLOW:
			_name = "Yellow";
			_personalityTrait = "Witty";
			_visualCue = "Sparks";
			break;
		case HueType::BROWN:
			_name = "Brown";
			_personalityTrait = "Grim";
			_visualCue = "Dust";
			break;
		default:
			_name = "None";
			_personalityTrait = "";
			_visualCue = "";
			break;
	}
}

Hue::~Hue() = default;

HueType		Hue::getType() const { return (_type); }
std::string	Hue::getName() const { return (_name); }
std::string	Hue::getPersonalityTrait() const { return (_personalityTrait); }
std::string	Hue::getVisualCue() const { return (_visualCue); }

bool	Hue::operator==(const Hue& other) const { return (_type == other._type); }



/////

struct Hue {
	HueType type;
	std::string name;
	std::string personalityTrait;
	std::string visualCue; // e.g., "veins", "aura", etc.

	Hue(HueType t = HueType::NONE)
		: type(t) {
		switch (t) {
			case HueType::RED:
				name = "Red";
				personalityTrait = "Bold";
				visualCue = "Embers";
				break;
			case HueType::GREEN:
				name = "Green";
				personalityTrait = "Patient";
				visualCue = "Vines";
				break;
			// Add others here...
			default:
				name = "None";
				personalityTrait = "";
				visualCue = "";
				break;
		}
	}

	bool operator==(const Hue& other) const {
		return type == other.type;
	}
};


// Prism Core Logic

class PrismCore {
	private:
		std::vector<Hue> boundHues; // Max 3
	
	public:
		static constexpr int MAX_HUES = 3;
	
		bool isHueBound(HueType type) const {
			return std::any_of(boundHues.begin(), boundHues.end(),
							   [type](const Hue& h) { return h.type == type; });
		}
	
		bool bindHue(Hue hue) {
			if (isHueBound(hue.type)) {
				return false; // Already bound
			}
	
			if (boundHues.size() < MAX_HUES) {
				boundHues.push_back(hue);
				return true;
			}
	
			// Too many — return false to trigger choice in UI
			return false;
		}
	
		void replaceHue(int index, Hue newHue) {
			if (index >= 0 && index < boundHues.size()) {
				boundHues[index] = newHue;
			}
		}
	
		void unbindHue(HueType type) {
			boundHues.erase(std::remove_if(boundHues.begin(), boundHues.end(),
							 [type](const Hue& h) { return h.type == type; }),
							 boundHues.end());
		}
	
		const std::vector<Hue>& getBoundHues() const {
			return boundHues;
		}
	
		// For Godot: export as string or variant
		std::string describeState() const {
			std::string result = "Bound Hues: ";
			for (const auto& hue : boundHues) {
				result += hue.name + " ";
			}
			return result;
		}
	};


// Once we move this logic into Godot (via C++ GDNative or GDExtension), we’ll expose it like this:

String get_active_visual_cues() const {
	String result;
	for (const auto& hue : boundHues) {
		result += hue.visualCue + ",";
	}
	return result.trim_suffix(",");
}

// Then we can apply shaders, trails, aura effects, etc., based on visualCue

/////

// Example usage:

PrismCore prism;

Hue red(HueType::RED);
Hue green(HueType::GREEN);
Hue blue(HueType::BLUE);
Hue purple(HueType::PURPLE);

// Try binding 3 hues
prism.bindHue(red);
prism.bindHue(green);
prism.bindHue(blue);

// Now try binding a 4th
if (!prism.bindHue(purple)) {
	std::cout << "Prism full. Choose hue to replace:\n";
	auto hues = prism.getBoundHues();
	for (int i = 0; i < hues.size(); ++i) {
		std::cout << i << ": " << hues[i].name << "\n";
	}
	// Simulate player choosing to replace index 1
	prism.replaceHue(1, purple);
}

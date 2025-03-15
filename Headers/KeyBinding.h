//
// Created by Johnnie on 3/14/2025.
//

#ifndef ALPHA_SQUADRON_SOURCE_KEYBINDING_H_
#define ALPHA_SQUADRON_SOURCE_KEYBINDING_H_
#include <SFML/Window/Keyboard.hpp>

#include <map>
#include <vector>


namespace LocalPlayerAction
{
	enum ActionType
	{
		AccelerateNegX,
		AcceleratePosX,
		AccelerateNegY,
		AcceleratePosY,
		Fire,
		LaunchMissile,
		ActionCount
	};
}

class KeyBinding
{
 public:
	typedef LocalPlayerAction::ActionType ActionType;


 public:
	explicit KeyBinding(int controlPreconfiguration);

	void assignKey(ActionType action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(ActionType action) const;

	bool checkAction(sf::Keyboard::Key key, ActionType& out) const;
	std::vector<ActionType> getRealtimeActions() const;


 private:
	void initializeActions();


 private:
	std::map<sf::Keyboard::Key, ActionType> m_keyMap;
};

bool IsRealtimeAction(LocalPlayerAction::ActionType action);

#endif //ALPHA_SQUADRON_SOURCE_KEYBINDING_H_

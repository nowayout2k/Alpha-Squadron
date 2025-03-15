//
// Created by Johnnie on 2/20/2025.
//

#ifndef ALPHA_SQUADRON_HEADERS_MULTIPLAYERGAMESTATE_H_
#define ALPHA_SQUADRON_HEADERS_MULTIPLAYERGAMESTATE_H_

#include "SFML/Network.hpp"
#include "StateStack.h"
#include "GameServer.h"

class MultiplayerGameState : public State
{
 public:
	MultiplayerGameState(StateStack& stack, Context context, bool isHost);
	virtual void render();
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
 private:
	void updateBroadcastMessage(sf::Time elapsedTime);
	void handlePacket(sf::Int32 packetType, sf::Packet& packet);
	virtual void onActivate();
	void onDestroy();

	void disableAllRealtimeActions();

	typedef  std::unique_ptr<Player> PlayerPtr;
	World m_world;
	sf::RenderWindow& m_window;
	std::map<int, PlayerPtr> m_players;
	std::vector<sf::Int32> m_localPlayerIdentifiers;
	sf::TcpSocket m_socket;
	bool m_connected;
	std::unique_ptr<GameServer> m_gameServer;
	sf::Clock m_tickClock;
	std::vector<std::string> m_broadcasts;
	sf::Text m_broadcastText;
	sf::Time m_broadcastElapsedTime;

	sf::Text m_playerInvitationText;
	sf::Time m_playerInvitationTime;

	sf::Text m_failedConnectionText;
	sf::Clock m_failedConnectionClock;

	bool m_activeState;
	bool m_hasFocus;
	bool m_host;
	bool m_gameStarted;
	sf::Time m_clientTimeout;
	sf::Time m_timeSinceLastPacket;
};

#endif //ALPHA_SQUADRON_HEADERS_MULTIPLAYERGAMESTATE_H_

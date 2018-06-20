#pragma once

#include "TemplateSingleton.h"
#include "PlayerData.h"
#include "Constans.h"



class GameManager : public TemplateSingleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	void initPlayerData();
	void destroyPlayerData();
	PlayerData * getPlayerData();

	void savePlayerData();
	void loadPlayerData();

	PlayerDeck* getAllDeck() {
		return AllDeck;
	};
	PlayerDeck* getPreDeck() {
		return PreDeck;
	};
	PlayerDeck* getFightDeck() {
		return FightDeck;
	};
	PlayerDeck* gettestDeck() {
		return testDeck;
	};

	PlayerDeck testDeck[PRE_DECK_MAX];
	PlayerDeck AllDeck[ALL_DECK_MAX];
	PlayerDeck PreDeck[PRE_DECK_MAX];
	PlayerDeck FightDeck[PRE_DECK_MAX];

private:
	PlayerData * _playerData;
};
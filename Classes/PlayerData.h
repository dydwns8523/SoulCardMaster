#pragma once

#include "cocos2d.h"
#include "Constans.h"


USING_NS_CC;

using namespace std;

class PlayerDeck
{
public:
	int numofcard;
	int type;
	string cname;
	int attribute;
	int grade;
	int cost;
	int atk;
	int hp;
	int sk1;
	int sk2;
	int sk3;
	PlayerDeck();
	~PlayerDeck();
};

class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	void loadData();
	bool parseJson(const char * json);
	void saveData();
	string createJson();


public:
	string _name;
	int _hp;
	int _gold;
	float _atk;
	bool _dead;

	PlayerDeck AllDeck[ALL_DECK_MAX];
	PlayerDeck PreDeck[PRE_DECK_MAX];
	PlayerDeck FightDeck[PRE_DECK_MAX];
	PlayerDeck testDeck[PRE_DECK_MAX];
	
	PlayerDeck* gettestDeck() {
		return testDeck;
	};
	PlayerDeck* getAllDeck() {
		return AllDeck;
	};
	PlayerDeck* getPreDeck() {
		return PreDeck;
	};
	PlayerDeck* getFightDeck() {
		return FightDeck;
	};

	ValueMap _PreDeck;
	ValueMap _AllDeck;
};

class Player
{
public:
	String name;
	bool isDead;
	int gold;
	int attack;
	int health;
};

class CardData
{
public:
	CardData(int num, int ty, string str, int att, int gra, int co, int at, int heal
		, int a, int b, int c);
	~CardData();
	int numofcard;
	int type;
	string cname;
	int attribute;
	int grade;
	int cost;
	int atk;
	int hp;
	int sk1;
	int sk2;
	int sk3;
	
};

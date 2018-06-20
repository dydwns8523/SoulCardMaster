#include "GameManager.h"

GameManager::GameManager()
{
	initPlayerData();
}

GameManager::~GameManager()
{
	destroyPlayerData();
}

void GameManager::initPlayerData()
{
	_playerData = new (std::nothrow) PlayerData();
}

void GameManager::destroyPlayerData()
{
	if (_playerData)
	{
		//delete _playerData;
		//_playerData = nullptr;
		// 아랫줄 과 같은 의미
		CC_SAFE_DELETE(_playerData);
	}
}

PlayerData * GameManager::getPlayerData()
{
	return _playerData;
}

void GameManager::savePlayerData()
{
	_playerData->saveData();
}

void GameManager::loadPlayerData()
{
	_playerData->loadData();
}

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
		// �Ʒ��� �� ���� �ǹ�
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

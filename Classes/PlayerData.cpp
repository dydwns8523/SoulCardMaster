#include "PlayerData.h"

#include "json\rapidjson.h"
#include "json\document.h"
#include "json\stringbuffer.h"
#include "json\prettywriter.h"
#include "Constans.h"
#include "HelloWorldScene.h"
#include "GameManager.h"


using namespace rapidjson;




PlayerData::PlayerData()
	:_name("None"), _hp(0), _gold(1000000), _atk(0), _dead(false)
{
}

PlayerData::~PlayerData()
{
}

void PlayerData::loadData()
{
	FileUtils * util = FileUtils::getInstance();

	string json = util->getStringFromFile("data/test_data.json");
	parseJson(json.c_str());

	log("name : %s, hp : %d, gold : %d, atk : %f, dead : %d", _name.c_str(), _hp, _gold, _atk, _dead);

}

bool PlayerData::parseJson(const char * json)
{
	if (strcmp(json, "") == 0)
		return false;

	Document doc;
	doc.Parse<0>(json);

	if (doc.HasParseError())
		return false;

	// JSON에 KEY_NAME 이있는지 그리고 그 멤버가 스트링 형식인지 확인하는 작업
	if (doc.HasMember(KEY_NAME) && doc[KEY_NAME].IsString())
		_name = doc[KEY_NAME].GetString();

	_hp = doc[KEY_HP].GetInt();
	_gold = doc[KEY_GOLD].GetInt();
	_atk = doc[KEY_ATK].GetInt();
	_dead = doc[KEY_DEAD].GetBool();

	// 멤버를 여러개 가지는 배열의 값을 가져오는 방법

	// 배열을 맵에 저장
	if (doc.IsObject())
	{
		if (doc.HasMember(KEY_ARR_MAP1) && doc[KEY_ARR_MAP1].IsArray())
		{
			const rapidjson::Value & arr = doc[KEY_ARR_MAP1];

			for (int i = 0; i < arr.Size(); i++)
			{
				// [ { " name " : " value " } ]
				const char * name = arr[i].MemberBegin()->name.GetString();
				const char * value = arr[i].MemberBegin()->value.GetString();

				_PreDeck[name] = value;
			}
		}
	}

	// 배열을 맵에 저장
	if (doc.IsObject())
	{
		if (doc.HasMember(KEY_ARR_MAP2) && doc[KEY_ARR_MAP2].IsArray())
		{
			const rapidjson::Value & arr = doc[KEY_ARR_MAP2];

			for (int i = 0; i < arr.Size(); i++)
			{
				// [ { " name " : " value " } ]
				const char * name = arr[i].MemberBegin()->name.GetString();
				const char * value = arr[i].MemberBegin()->value.GetString();

				_AllDeck[name] = value;
			}
		}
	}
	return false;
}

void PlayerData::saveData()
{
	FileUtils * util = FileUtils::getInstance();

	// JSON에 파일 저장
	util->writeStringToFile(createJson(), "data/character_data.json");

}

string PlayerData::createJson()
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType & allocator = doc.GetAllocator();
	PlayerDeck * AllDeck = GameManager::getInstance()->getAllDeck();
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();

	rapidjson::Value name(rapidjson::kStringType);
	name.SetString(_name.c_str(), _name.length(), allocator);
	doc.AddMember(KEY_NAME, name, allocator);

	// HP 저장
	rapidjson::Value hp(rapidjson::kNumberType);
	hp.SetInt(_hp);
	//hp = _hp;
	doc.AddMember(KEY_HP, hp, allocator);

	// gold 저장
	rapidjson::Value gold(rapidjson::kNumberType);
	gold.SetInt(_gold);
	doc.AddMember(KEY_GOLD, gold, allocator);

	// ATK 저장
	rapidjson::Value atk(rapidjson::kNumberType);
	atk.SetInt(_atk);
	doc.AddMember(KEY_ATK, atk, allocator);

	// DEAD 저장
	rapidjson::Value dead(rapidjson::kFalseType);
	dead.SetBool(_dead);
	doc.AddMember(KEY_DEAD, dead, allocator);

	// 멤버를 여러개 가지는 배열
	rapidjson::Value jsonArr(rapidjson::kArrayType);

	// 맵(현재덱)을 배열로 저장1
	rapidjson::Value mapArr1(rapidjson::kArrayType);

	for (int i = 0; i < PRE_DECK_MAX; i++)
	{
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember(KEY_NUMCARD, PreDeck[i].numofcard, allocator);
		object.AddMember(KEY_TYPE, PreDeck[i].type, allocator);
		rapidjson::Value name(rapidjson::kStringType);
		name.SetString(PreDeck[i].cname.c_str(), PreDeck[i].cname.size(), allocator);
		object.AddMember(KEY_CNAME, name, allocator);
		object.AddMember(KEY_ATTRI, PreDeck[i].attribute, allocator);
		object.AddMember(KEY_GRADE, PreDeck[i].grade, allocator);
		object.AddMember(KEY_COST, PreDeck[i].cost, allocator);
		object.AddMember(KEY_ATK, PreDeck[i].atk, allocator);
		object.AddMember(KEY_HP, PreDeck[i].hp, allocator);
		object.AddMember(KEY_SK1, PreDeck[i].sk1, allocator);
		object.AddMember(KEY_SK2, PreDeck[i].sk2, allocator);
		object.AddMember(KEY_SK3, PreDeck[i].sk3, allocator);

		mapArr1.PushBack(object, allocator);
	}

	doc.AddMember(KEY_ARR_MAP1, mapArr1, allocator);

	// 맵(총덱)을 배열로 저장2
	rapidjson::Value mapArr2(rapidjson::kArrayType);

	for (int i = 0; i < ALL_DECK_MAX; i++)
	{
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember(KEY_NUMCARD, AllDeck[i].numofcard, allocator);
		object.AddMember(KEY_TYPE, AllDeck[i].type, allocator);
		rapidjson::Value name(rapidjson::kStringType);
		name.SetString(AllDeck[i].cname.c_str(), AllDeck[i].cname.size(), allocator);
		object.AddMember(KEY_CNAME, name, allocator);
		object.AddMember(KEY_ATTRI, AllDeck[i].attribute, allocator);
		object.AddMember(KEY_GRADE, AllDeck[i].grade, allocator);
		object.AddMember(KEY_COST, AllDeck[i].cost, allocator);
		object.AddMember(KEY_ATK, AllDeck[i].atk, allocator);
		object.AddMember(KEY_HP, AllDeck[i].hp, allocator);
		object.AddMember(KEY_SK1, AllDeck[i].sk1, allocator);
		object.AddMember(KEY_SK2, AllDeck[i].sk2, allocator);
		object.AddMember(KEY_SK3, AllDeck[i].sk3, allocator);

		mapArr2.PushBack(object, allocator);
	}

	

	doc.AddMember(KEY_ARR_MAP2, mapArr2, allocator);

	// 문자열로 변환
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char * result = buffer.GetString();
	string str(result);

	return str;
}


PlayerDeck::PlayerDeck()
{
	numofcard = 0;
	type = 10;
	cname = "";
	attribute = 0;
	grade = 0;
	cost = 0;
	atk = 0;
	hp = 0;
	sk1 = 0;
	sk2 = 0;
	sk3 = 0;
}

CardData::CardData(int num, int ty, string str, int att, int gra, int co, int at, int heal, int a, int b, int c)
{
	numofcard = num;
	type = ty;
	cname = str;
	attribute = att;
	grade = gra;
	cost = co;
	atk = at;
	hp = heal;
	sk1 = a;
	sk2 = b;
	sk3 = c;
}

CardData::~CardData()
{
}

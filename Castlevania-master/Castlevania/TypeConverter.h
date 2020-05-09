#include <unordered_map>
#include <string>

///Object Layer
const enum ObjectID
{
	OPlayer,
	OWall,
	OGround,
	OMoneyBagTrigger,
	OTorch,
	ONextmap,
	OPortal,
	OMoneyBag,
	OCastle,
	OCam,
	OSpawner,
	OStair,
	OBirck,
	OCandle,
	ODoor,
	OBoss,
	OBossBorder,
	OBossTrigger,
	OWater,
	OBridge,
	OSpearGuard,
	OEnemyTrigger,
	OBat,
	OGhost,
	OMonkey
};

// Map objectlayer voi ten trong tiled map editor
const auto string2EntityType = std::unordered_map<std::string, ObjectID>
{
	{ "Player", ObjectID::OPlayer},
	{ "Wall", ObjectID::OWall },
	{ "Ground", ObjectID::OGround },
	{ "MoneyBagTrigger", ObjectID::OMoneyBagTrigger },
	{ "Camera", ObjectID::OCam},
	{ "Torch", ObjectID::OTorch },
	{ "Nextmap", ObjectID::ONextmap },
	{ "Portal", ObjectID::OPortal },
	{ "MoneyBag", ObjectID::OMoneyBag },
	{ "Castle", ObjectID::OCastle},
	{ "BossTrigger", ObjectID::OBossTrigger },
	{ "BossBorder", ObjectID::OBossBorder },
	{ "BOSS", ObjectID::OBoss },
	{ "Door", ObjectID::ODoor },
	{ "Brick", ObjectID::OBirck },
	{ "Spawner", ObjectID::OSpawner },
	{ "Stair", ObjectID::OStair },
	{ "Candle", ObjectID::OCandle },
	{ "Water", ObjectID::OWater },
	{"Bridge",ObjectID::OBridge},
	{"SpearGuard",ObjectID::OSpearGuard},
	{"EnemyTrigger",ObjectID::OEnemyTrigger},
	{"Bat",ObjectID::OBat},
	{"Ghost",ObjectID::OGhost},
	{"Monkey",ObjectID::OMonkey}
};


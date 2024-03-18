#include "PreCompile.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveChild("Assets\\Map\\City\\001\\Obj");

	std::shared_ptr<GameEngineSprite> aa = GameEngineSprite::CreateFolder("Obj001",Dir.GetStringPath());

	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->SetSprite("Obj001",0);
	Renderer->SetSampler("POINT");
}

void Map::Update(float _Delta)
{
}

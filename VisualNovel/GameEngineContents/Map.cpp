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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Map\\City\\001\\Back");

		GameEngineSprite::CreateFolder("TestBack", Dir.GetStringPath());
	}

	BackRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BackRenderer->SetSprite("TestBack", 0);
	BackRenderer->SetSampler("POINT");
	BackRenderer->SetRenderOrder(0);
	BackRenderer->Transform.SetLocalPosition({ 0,0,250 });

	ObjRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ObjRenderer->SetSprite("TestBack", 1);
	ObjRenderer->SetSampler("POINT");
	ObjRenderer->SetRenderOrder(1);
}

void Map::Update(float _Delta)
{
}

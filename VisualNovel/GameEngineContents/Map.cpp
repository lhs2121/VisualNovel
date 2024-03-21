#include "PreCompile.h"
#include "Map.h"
#include "ContentsSpriteRenderer.h"
#include <fstream>
#include <GameEngineCore\GameEngineBlend.h>

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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Map\\City\\001\\Platform");

		GameEngineSprite::CreateFolder("TestObj", Dir.GetStringPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Map\\City\\001\\Tile");

		std::shared_ptr<GameEngineSprite> TileSet = GameEngineSprite::CreateFolder("Tile", Dir.GetStringPath());
	}

	{
		std::shared_ptr<GameEngineTileMap> TileMap = CreateComponent<GameEngineTileMap>();
		TileMap->CreateTileMap({ 100,100,{32,32},"Tile" });
		TileMap->SetRenderOrder(3);

		LoadTileMapFromCSV(TileMap);
	}

	{
		BackRenderer = CreateComponent<ContentsSpriteRenderer>();
		BackRenderer->SetSprite("TestBack");
		BackRenderer->SetOverlayTexture("Test3.png");
		BackRenderer->SetRenderOrder(0);
		BackRenderer->Transform.SetLocalPosition({ 0,0,250 });
	}

	{
		ObjRenderer = CreateComponent<ContentsSpriteRenderer>();
		ObjRenderer->SetSprite("TestObj");
		ObjRenderer->SetOverlayTexture("Test2.png");
		ObjRenderer->SetRenderOrder(1);
		ObjRenderer->Transform.SetLocalPosition({ 0,100,150 });
	}
	
	GameEngineInput::AddInputObject(this);
}

void Map::LoadTileMapFromCSV(std::shared_ptr<GameEngineTileMap> tileMap)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Assets");
	Dir.MoveChild("Assets\\Map\\City\\001\\Tile\\info.csv");

	std::ifstream file(Dir.GetStringPath());

	if (!file.is_open())
	{
		return;
	}

	std::string line;

	int y = 0;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);

		std::string line;

		int x = 0;

		while (std::getline(iss, line, ','))
		{

			std::string::size_type pos = line.find('_');

			if (pos != std::string::npos && pos != line.size() - 1)
			{
				std::string spriteName = line.substr(0, pos);

				int index = std::stoi(line.substr(pos + 1));


				tileMap->SetTileIndex({ (ULONG)x, (ULONG)y, (UINT)index, spriteName });
			}
			++x;
		}
		++y;
	}

	file.close();
}

void Map::Update(float _Delta)
{
	if (InputIsPress(VK_UP))
	{
		ObjRenderer->OverlayInfoValue.Intensity += _Delta;
		BackRenderer->OverlayInfoValue.Intensity += _Delta;
	}
	if (InputIsPress(VK_DOWN))
	{
		ObjRenderer->OverlayInfoValue.Intensity -= _Delta;
		BackRenderer->OverlayInfoValue.Intensity -= _Delta;
		if (ObjRenderer->OverlayInfoValue.Intensity <= 0.0f)
		{
			ObjRenderer->OverlayInfoValue.Intensity = 0.0f;
			BackRenderer->OverlayInfoValue.Intensity = 0.0f;
		}
	}
	if (InputIsPress(VK_LEFT))
	{
		ObjRenderer->OverlayInfoValue.OverlayUVPlus.X += _Delta;
		BackRenderer->OverlayInfoValue.OverlayUVPlus.X += _Delta;
	}
	if (InputIsPress(VK_RIGHT))
	{
		ObjRenderer->OverlayInfoValue.OverlayUVPlus.X -= _Delta;
		BackRenderer->OverlayInfoValue.OverlayUVPlus.X -= _Delta;
	}
}

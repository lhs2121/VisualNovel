#include "PreCompile.h"
#include "Map.h"
#include "ContentsSpriteRenderer.h"
#include "ContentsTileMapRenderer.h"
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

		BackRenderer = CreateComponent<ContentsSpriteRenderer>();
		BackRenderer->SetRenderOrder(0);
		BackRenderer->Transform.SetLocalPosition({ 0,0,350 });

		BackRenderer->SetSprite("TestBack");
		BackRenderer->SetOverlay("Test2.png");
		BackRenderer->EnableOverlay();
		BackRenderer->EnableFlicker();
		BackRenderer->SetFlicker(7, 0.5f, 10.0f);
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Map\\City\\001\\Platform");

		GameEngineSprite::CreateFolder("TestObj", Dir.GetStringPath());

		ObjRenderer = CreateComponent<ContentsSpriteRenderer>();
		ObjRenderer->SetRenderOrder(1);
		ObjRenderer->Transform.SetLocalPosition({ 0,100,150 });

		ObjRenderer->SetSprite("TestObj");
		ObjRenderer->SetOverlay("Test2.png");
		ObjRenderer->EnableOverlay();
		ObjRenderer->EnableFlicker();
		ObjRenderer->SetFlicker(5, 1, 5.0f);
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Map\\City\\001\\Tile");

		GameEngineSprite::CreateFolder("Tile", Dir.GetStringPath());

		TileMapRenderer = CreateComponent<ContentsTileMapRenderer>();
		TileMapRenderer->CreateTileMap({ 100,100,{32,32},"Tile" });
		LoadTileMapFromCSV(TileMapRenderer);

		TileMapRenderer->SetRenderOrder(2);
		TileMapRenderer->SetOverlay("Test7.png");
		TileMapRenderer->SetFlicker(7, 5, 3.5f);

		TileMapRenderer->EnableOverlay();
		TileMapRenderer->EnableFlicker();
	}

	GameEngineInput::AddInputObject(this);
}

void Map::Update(float _Delta)
{
}

void Map::LoadTileMapFromCSV(std::shared_ptr<ContentsTileMapRenderer> TileMapRenderer)
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
				TileMapRenderer->SetTileIndex({ (ULONG)x, (ULONG)y, (UINT)index, spriteName });
			}
			++x;
		}
		++y;
	}
	file.close();
}
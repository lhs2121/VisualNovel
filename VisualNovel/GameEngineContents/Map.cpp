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
		BackRenderer = CreateComponent<ContentsSpriteRenderer>();
		BackRenderer->SetRenderOrder(0);
		BackRenderer->Transform.SetLocalPosition({ 0,0,350 });

		BackRenderer->SwitchOverlay("Test2.png");
		BackRenderer->SetSprite("TestBack");
		BackRenderer->SwitchFlickerEffect();
	}

	{
		ObjRenderer = CreateComponent<ContentsSpriteRenderer>();
		ObjRenderer->SetRenderOrder(1);
		ObjRenderer->Transform.SetLocalPosition({ 0,100,150 });

		ObjRenderer->SwitchOverlay("Test2.png");
		ObjRenderer->SetSprite("TestObj");
		ObjRenderer->SwitchFlickerEffect();
		ObjRenderer->SetFlickerInfo(5, 1, 5.0f);
	}

	{
		TileMapRenderer = CreateComponent<ContentsTileMapRenderer>();
		TileMapRenderer->CreateTileMap({ 100,100,{32,32},"Tile" });
		TileMapRenderer->SetRenderOrder(2);
		LoadTileMapFromCSV(TileMapRenderer);

		TileMapRenderer->SwitchOverlay("Test7.png");
		TileMapRenderer->SwitchFlickerEffect();
		TileMapRenderer->SetFlickerInfo(7, 1, 3.5f);
	}

	GameEngineInput::AddInputObject(this);
}

void Map::LoadTileMapFromCSV(std::shared_ptr<ContentsTileMapRenderer> TileMap)
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


				TileMap->SetTileIndex({ (ULONG)x, (ULONG)y, (UINT)index, spriteName });
			}
			++x;
		}
		++y;
	}

	file.close();
}

void Map::Update(float _Delta)
{
}

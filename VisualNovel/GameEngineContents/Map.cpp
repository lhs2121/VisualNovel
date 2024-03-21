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

		BackRenderer->SetSprite("TestBack");
		BackRenderer->EnableOverlay("Test2.png");
		BackRenderer->EnableFlicker();
		BackRenderer->SetFlicker(7, 0.5f, 10.0f);
	}

	/*{
		ObjRenderer = CreateComponent<ContentsSpriteRenderer>();
		ObjRenderer->SetRenderOrder(1);
		ObjRenderer->Transform.SetLocalPosition({ 0,100,150 });

		ObjRenderer->SetSprite("TestObj");
		ObjRenderer->EnableOverlay("Test2.png");
		ObjRenderer->EnableFlicker();
		ObjRenderer->SetFlicker(5, 1, 5.0f);
	}

	{
		TileMapRenderer = CreateComponent<ContentsTileMapRenderer>();
		TileMapRenderer->CreateTileMap({ 100,100,{32,32},"Tile" });
		TileMapRenderer->SetRenderOrder(2);
		LoadTileMapFromCSV(TileMapRenderer);

		TileMapRenderer->EnableOverlay("Test7.png");
		TileMapRenderer->EnableFlicker();
		TileMapRenderer->SetFlicker(7, 1, 3.5f);
	}*/

	GameEngineInput::AddInputObject(this);
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

void Map::Update(float _Delta)
{
	if (InputIsDown('K'))
	{
		BackRenderer->DisableOverlay();
	}
	if (InputIsDown('L'))
	{
		BackRenderer->EnableOverlay();
	}
	if (InputIsDown('H'))
	{
		BackRenderer->EnableFlicker();
	}
	if (InputIsDown('J'))
	{
		BackRenderer->DisableFlicker();
	}
	if (InputIsPress('B'))
	{
		BackRenderer->EnableTextureScrolling({1,-2});
	}
	if (InputIsDown('N'))
	{
		BackRenderer->DisableTextureScrolling();
	}
}

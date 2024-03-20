#include "PreCompile.h"
#include "Map.h"
#include <fstream>

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
		Dir.MoveChild("Assets\\Map\\City\\001\\Tile");

		std::shared_ptr<GameEngineSprite> TileSet = GameEngineSprite::CreateFolder("Tile", Dir.GetStringPath());
	}

	{
		std::shared_ptr<GameEngineTileMap> TileMap = CreateComponent<GameEngineTileMap>();
		TileMap->CreateTileMap({ 100,100,{32,32},"Tile" });
		TileMap->SetRenderOrder(3);
		LoadTileMapFromCSV(TileMap);
	}

	BackRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BackRenderer->SetSprite("TestBack");
	BackRenderer->SetSampler("POINT");
	BackRenderer->SetRenderOrder(0);
	BackRenderer->Transform.SetLocalPosition({ 0,0,250 });

	//ObjRenderer = CreateComponent<GameEngineSpriteRenderer>();
	//ObjRenderer->SetSprite("TestObj");
	//ObjRenderer->SetSampler("POINT");
	//ObjRenderer->SetRenderOrder(1);
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
}

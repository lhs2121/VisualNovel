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

		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::CreateFolder("BackGroundLayers", Dir.GetStringPath());
		int SpriteCount = Sprite->GetSpriteCount();

		std::vector<float> ScrollSpeeds =
		{
			1.1f,
			0.9f,
			0.8f,
			0.7f,
			0.6f,
			0.5f,
			0.4f,
			0.3f,
			0.2f,
			0.1f,
		};

		for (int i = 0; i < SpriteCount; i++)
		{
			std::shared_ptr<ContentsSpriteRenderer> Renderer = CreateComponent<ContentsSpriteRenderer>();
			Renderer->SetSprite("BackGroundLayers", i);
			Renderer->SetOverlay("Test0.png");
			Renderer->SetFlicker(5.0f, 1.3f, 1.8f);
			Renderer->SetRenderOrder(SpriteCount - i);

			Renderer->EnableOverlay();
			Renderer->EnableFlicker();

			Renderer->EnableSpriteScrolling({ 0.1f * ScrollSpeeds[i], 0.0f });
			Renderer->EnableTextureScrolling({ 0.1f * ScrollSpeeds[i], 0.0f });

			BackRenderers.push_back(Renderer);
		}
	}

	/*{
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
	}*/

	/*{
		BackRenderer = CreateComponent<ContentsSpriteRenderer>();
		BackRenderer->SetRenderOrder(0);
		BackRenderer->Transform.SetLocalPosition({ 0,0,350 });

		BackRenderer->SetSprite("TestBack");
		BackRenderer->EnableOverlay("Test2.png");
		BackRenderer->EnableFlicker();
		BackRenderer->SetFlicker(7, 0.5f, 10.0f);
	}

	{
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

void Map::Update(float _Delta)
{
	if (OverlayChange == false)
	{
		float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
		if (CameraPos.Z <= -359.018433f)
		{
			for (std::shared_ptr<ContentsSpriteRenderer> Renderer : BackRenderers)
			{
				Renderer->SetOverlay("Test8.png");
			}
			OverlayChange = true;
		}
	}
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
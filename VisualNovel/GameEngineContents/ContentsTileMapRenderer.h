#pragma once
#include "ContentsTileMapRenderer.h"

// Ό³Έν :
class ContentsTileMapRenderer : public ContentsSpriteRenderer
{
public:
	// constrcuter destructer
	ContentsTileMapRenderer();
	~ContentsTileMapRenderer();

	// delete Function
	ContentsTileMapRenderer(const ContentsTileMapRenderer& _Other) = delete;
	ContentsTileMapRenderer(ContentsTileMapRenderer&& _Other) noexcept = delete;
	ContentsTileMapRenderer& operator=(const ContentsTileMapRenderer& _Other) = delete;
	ContentsTileMapRenderer& operator=(ContentsTileMapRenderer&& _Other) noexcept = delete;

	//                       100           100            50 50 
	void CreateTileMap(const CreateTileParameter& _Parameter);
	// void SetTile(size_t _TileCountX, size_t _TileCountY, float4 TileScale);

	//size_t X;
	//size_t Y;
	//unsigned int Index = 0;
	//std::string_view SpriteName = "";
	void SetTileIndex(const SetTileParameterIndex& _Parameter);

	void SetTilePos(const SetTileParameterPos& _Parameter);

	void ExpandRenderedTileMap(int _Size)
	{
		TileMapExpansionSize = _Size;
	}

	std::shared_ptr<class GameEngineSampler> Sampler;

	float4 PosToIndex(float4 _Pos)
	{
		float4 Index = { static_cast<float>(_Pos.iX() / TileData.TileScale.iX()), static_cast<float>(_Pos.iY() / TileData.TileScale.iY()) };
		return Index;
	}

	float4 IndexToPos(float4 _Index)
	{
		float4 Pos = { _Index.X * TileData.TileScale.X, _Index.Y * TileData.TileScale.Y };
		return Pos;
	}

protected:
	void Start();
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	CreateTileParameter TileData;

	std::shared_ptr<GameEngineSprite> DefaultSprite;

	std::vector<std::vector<Tile>> Tiles;

	int TileMapExpansionSize = 0;
};
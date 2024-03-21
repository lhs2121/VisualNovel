#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ContentsTileMapRenderer;
class ContentsSpriteRenderer;
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LoadTileMapFromCSV(std::shared_ptr<ContentsTileMapRenderer> TileMapRenderer);

	std::shared_ptr<ContentsTileMapRenderer> TileMapRenderer;
	std::shared_ptr<ContentsSpriteRenderer> BackRenderer;
	std::shared_ptr<ContentsSpriteRenderer> ObjRenderer;
};
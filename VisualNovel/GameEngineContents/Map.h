#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	void LoadTileMapFromCSV(std::shared_ptr<class ContentsTileMapRenderer> TileMap);

	std::shared_ptr<class ContentsSpriteRenderer> BackRenderer;
	std::shared_ptr<class ContentsSpriteRenderer> ObjRenderer;
};
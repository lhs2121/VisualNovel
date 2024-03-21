#pragma once
#include <GameEngineCore/GameEngineTileMap.h>

// Ό³Έν :
class OverlayInfo;
class ContentsTileMapRenderer : public GameEngineTileMap
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

	void SwitchOverlay(std::string _FileName);
	OverlayInfo OverlayInfoValue;
protected:
	std::shared_ptr<class GameEngineTexture> OverlayTexture;
};
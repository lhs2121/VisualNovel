#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
class ContentsSpriteRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	ContentsSpriteRenderer();
	~ContentsSpriteRenderer();

	// delete Function
	ContentsSpriteRenderer(const ContentsSpriteRenderer& _Other) = delete;
	ContentsSpriteRenderer(ContentsSpriteRenderer&& _Other) noexcept = delete;
	ContentsSpriteRenderer& operator=(const ContentsSpriteRenderer& _Other) = delete;
	ContentsSpriteRenderer& operator=(ContentsSpriteRenderer&& _Other) noexcept = delete;

	void SetOverlayTexture(std::string _FileName);
	OverlayInfo OverlayInfoValue;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

	std::shared_ptr<class GameEngineTexture> OverlayTexture;
};
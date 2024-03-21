#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

struct OverlayInfo
{
	float Intensity = 1.0f;
	float4 OverlayUVPlus = float4::ZERO;
	float4 OverlayUVMul = float4::ONE;
};

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
	void SetOverlayInfo(float Intensity, float4 OverlayUVPlus, float4 OverlayUVMul);

	OverlayInfo OverlayInfoValue;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

	std::shared_ptr<class GameEngineTexture> OverlayTexture;
};
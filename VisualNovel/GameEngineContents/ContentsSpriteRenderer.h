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

	void EnableOverlay();
	void EnableOverlay(std::string _TextureName);
	void DisableOverlay();

	void EnableFlicker();
	void DisableFlicker();

	void EnableTextureScrolling(float4 _Vector);
	void DisableTextureScrolling();

	void SetOverlay(float Intensity, float4 OverlayUVPlus, float4 OverlayUVMul);
	void SetFlicker(float _Max, float _Min, float _Speed);

	OverlayInfo OverlayInfoValue;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

	float4 ScrollingVector;

	float MaxIntensity = 4.5f;
	float MinIntensity = 2.0f;
	float IntensitySpeed = 0.5f;

	bool IsFlicker = false;
	bool IsOverlay = false;
	bool IsScrolling = false;

	std::shared_ptr<class GameEngineTexture> OverlayTexture;
};
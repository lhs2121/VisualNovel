#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// ���� :
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

	void EnableSpriteScrolling(float4 Dir);
	void DisableSpriteScrolling();

	void EnableTextureScrolling(float4 Dir);
	void DisableTextureScrolling();

	void SetOverlay(float Intensity, float4 OverlayUVPlus, float4 OverlayUVMul);
	void SetFlicker(float _Max, float _Min, float _Speed);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

	OverlayInfo OverlayInfoValue;
	float4 ShaderScrollingVector;
	float4 SpriteScrollingVector;

	float MaxIntensity = 4.5f;
	float MinIntensity = 2.0f;
	float IntensitySpeed = 0.5f;

	bool IsFlicker = false;
	bool IsOverlay = false;
	bool IsScrolling = false;
	bool IsSpriteScrolling = false;	

	std::shared_ptr<class GameEngineTexture> OverlayTexture;
};
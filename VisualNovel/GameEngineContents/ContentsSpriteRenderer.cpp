#include "PreCompile.h"
#include "ContentsSpriteRenderer.h"

ContentsSpriteRenderer::ContentsSpriteRenderer()
{
}

ContentsSpriteRenderer::~ContentsSpriteRenderer()
{
}

void ContentsSpriteRenderer::Start()
{
	GameEngineSpriteRenderer::Start();
}

void ContentsSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineSpriteRenderer::Render(_Camera, _Delta);
}

void ContentsSpriteRenderer::SwitchOverlay(std::string _TextureName)
{
	if (nullptr == GameEngineTexture::Find(_TextureName))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Overlay");
		OverlayTexture = GameEngineTexture::Load(Dir.PlusFilePath(_TextureName));
	}
	else
	{
		OverlayTexture = GameEngineTexture::Find(_TextureName);
	}


	GameEngineSpriteRenderer::SetMaterial("ContentsMaterial");
	GetShaderResHelper().SetTexture("OverlayTex", OverlayTexture);
	GetShaderResHelper().SetSampler("OverlayTexSampler", "EngineBaseWRAPSampler");
	GetShaderResHelper().SetConstantBufferLink("OverlayInfo", OverlayInfoValue);
}

void ContentsSpriteRenderer::SwitchFlickerEffect()
{
	IsFlicker = !IsFlicker;
}

void ContentsSpriteRenderer::SetOverlayInfo(OverlayInfo _Info)
{
	OverlayInfoValue = _Info;
}

void ContentsSpriteRenderer::SetFlickerInfo(float _Max, float _Min, float _Speed)
{
	MaxIntensity = _Max;
	MinIntensity = _Min;
	IntensitySpeed = _Speed;
}

void ContentsSpriteRenderer::Update(float _Delta)
{
	GameEngineSpriteRenderer::Update(_Delta);

	if (IsFlicker == false)
	{
		return;
	}

	float Intensity = OverlayInfoValue.Intensity;
	if (Intensity > MaxIntensity)
	{
		OverlayInfoValue.Intensity = MaxIntensity;
		IntensitySpeed *= -1;
	}
	else if (Intensity < MinIntensity)
	{
		OverlayInfoValue.Intensity = MinIntensity;
		IntensitySpeed *= -1;
	}
	OverlayInfoValue.Intensity += IntensitySpeed * _Delta;

}
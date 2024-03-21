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

void ContentsSpriteRenderer::EnableOverlay()
{
	if (OverlayTexture == nullptr)
	{
		OverlayTexture = GameEngineTexture::Find("NSet.png");
	}

	GameEngineSpriteRenderer::SetMaterial("ContentsMaterial");
	GetShaderResHelper().SetTexture("OverlayTex", OverlayTexture);
	GetShaderResHelper().SetSampler("OverlayTexSampler", "EngineBaseWRAPSampler");
	GetShaderResHelper().SetConstantBufferLink("OverlayInfo", OverlayInfoValue);

	IsOverlay = true;
}

void ContentsSpriteRenderer::EnableOverlay(std::string _TextureName)
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
		if (OverlayTexture == nullptr)
		{
			OverlayTexture = GameEngineTexture::Find(_TextureName);
		}
	}

	GameEngineSpriteRenderer::SetMaterial("ContentsMaterial");
	GetShaderResHelper().SetTexture("OverlayTex", OverlayTexture);
	GetShaderResHelper().SetSampler("OverlayTexSampler", "EngineBaseWRAPSampler");
	GetShaderResHelper().SetConstantBufferLink("OverlayInfo", OverlayInfoValue);

	IsOverlay = true;
}

void ContentsSpriteRenderer::DisableOverlay()
{
	GameEngineRenderer::SetMaterial("2DTexture");

	IsOverlay = false;
}

void ContentsSpriteRenderer::EnableFlicker()
{
	IsFlicker = true;
}

void ContentsSpriteRenderer::DisableFlicker()
{
	OverlayInfoValue.Intensity = 1.0f;
	IsFlicker = false;
}

void ContentsSpriteRenderer::EnableTextureScrolling(float4 _Vector)
{
	ScrollingVector = { -_Vector.X, _Vector.Y };
	IsScrolling = true;
}

void ContentsSpriteRenderer::DisableTextureScrolling()
{
	OverlayInfoValue.OverlayUVPlus = float4::ZERO;
	OverlayInfoValue.OverlayUVMul = float4::ONE;
	IsScrolling = false;
}

void ContentsSpriteRenderer::SetOverlay(float Intensity, float4 OverlayUVPlus, float4 OverlayUVMul)
{
	OverlayInfoValue = { Intensity ,OverlayUVPlus,OverlayUVMul };
}

void ContentsSpriteRenderer::SetFlicker(float _Max, float _Min, float _Speed)
{
	MaxIntensity = _Max;
	MinIntensity = _Min;
	IntensitySpeed = _Speed;
}

void ContentsSpriteRenderer::Update(float _Delta)
{
	GameEngineSpriteRenderer::Update(_Delta);

	if (IsOverlay == false)
	{
		return;
	}

	if (IsFlicker == true)
	{
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

	if (IsScrolling == true)
	{
		OverlayInfoValue.OverlayUVPlus += ScrollingVector * _Delta;
	}


}
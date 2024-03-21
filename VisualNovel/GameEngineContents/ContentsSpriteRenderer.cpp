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

void ContentsSpriteRenderer::Update(float _Delta)
{
	GameEngineSpriteRenderer::Update(_Delta);
}

void ContentsSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineSpriteRenderer::Render(_Camera, _Delta);
}

void ContentsSpriteRenderer::SetOverlayTexture(std::string _FileName)
{
	if (nullptr == GameEngineTexture::Find(_FileName))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Overlay");
		OverlayTexture = GameEngineTexture::Load(Dir.PlusFilePath(_FileName));
	}
	else
	{
		OverlayTexture = GameEngineTexture::Find(_FileName);
	}


	GameEngineSpriteRenderer::SetMaterial("ContentsMaterial");
	GetShaderResHelper().SetTexture("OverlayTex", OverlayTexture);
	GetShaderResHelper().SetSampler("OverlayTexSampler", "EngineBaseWRAPSampler");
	GetShaderResHelper().SetConstantBufferLink("OverlayInfo", OverlayInfoValue);
}

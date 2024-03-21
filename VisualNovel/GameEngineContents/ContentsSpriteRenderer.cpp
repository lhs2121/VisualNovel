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
	GameEngineSpriteRenderer::SetMaterial("ContentsMaterial");
	GetShaderResHelper().SetConstantBufferLink("OverlayInfo", OverlayInfoValue);
	GetShaderResHelper().SetSampler("OverlayTexSampler", "EngineBaseWRAPSampler");
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
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Assets");
	Dir.MoveChild("Assets\\Overlay");
	OverlayTexture = GameEngineTexture::Load(Dir.PlusFilePath(_FileName));
	GetShaderResHelper().SetTexture("OverlayTex", OverlayTexture);
}

void ContentsSpriteRenderer::SetOverlayInfo(float Intensity, float4 OverlayUVPlus, float4 OverlayUVMul)
{
	OverlayInfoValue = { Intensity ,OverlayUVPlus ,OverlayUVMul };
}


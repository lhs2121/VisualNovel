#include "PreCompile.h"
#include "ContentsTileMapRenderer.h"

ContentsTileMapRenderer::ContentsTileMapRenderer()
{
}

ContentsTileMapRenderer::~ContentsTileMapRenderer()
{
}

void ContentsTileMapRenderer::SwitchOverlay(std::string _FileName)
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


#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineMaterial.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "ContensWindow.h"
#include "TitleLevel.h"
#include "CityLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	{
		D3D11_BLEND_DESC desc = { 0 };
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = TRUE;  // 블렌딩 활성화
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;  // 소스 색상은 알파 값의 비례로 사용
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  // 대상 색상은 1에서 알파 값의 비례로 사용 (알파 값의 반전)
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;  // 블렌딩 연산: 소스 색상과 대상 색상을 더함
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;  // 소스 알파 값을 그대로 사용
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;  // 대상 알파 값을 무시
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;  // 알파 값에 대한 블렌딩 연산: 덧셈
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;  // 모든 색상 요소 쓰기

		std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("ContentsBlend", desc);

		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("ContentsMaterial");
		Mat->SetVertexShader("ContentsShader_VS");
		Mat->SetPixelShader("ContentsShader_PS");
		Mat->SetBlendState("ContentsBlend");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

    // GameEngineRenderTarget::IsDepth = false;
	GameEngineLevel::OffDebug();
	GameEngineGUI::CreateGUIWindow<ContensWindow>("ContensWindow");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<CityLevel>("CityLevel");
	GameEngineCore::ChangeLevel("CityLevel");
	//안녕
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}



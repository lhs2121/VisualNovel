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

		desc.RenderTarget[0].BlendEnable = TRUE;  // ���� Ȱ��ȭ
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;  // �ҽ� ������ ���� ���� ��ʷ� ���
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  // ��� ������ 1���� ���� ���� ��ʷ� ��� (���� ���� ����)
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;  // ���� ����: �ҽ� ����� ��� ������ ����
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;  // �ҽ� ���� ���� �״�� ���
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;  // ��� ���� ���� ����
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;  // ���� ���� ���� ���� ����: ����
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;  // ��� ���� ��� ����

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
	//�ȳ�
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}



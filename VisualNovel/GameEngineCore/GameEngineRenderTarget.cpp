#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineCore.h"

bool GameEngineRenderTarget::IsDepth = true;

GameEngineRenderUnit GameEngineRenderTarget::MergeUnit;

void GameEngineRenderTarget::MergeRenderUnitInit()
{
	GameEngineRenderTarget::MergeUnit.SetMesh("FullRect");
	GameEngineRenderTarget::MergeUnit.SetMaterial("TargetMerge");
};

GameEngineRenderTarget::GameEngineRenderTarget() 
{
}

GameEngineRenderTarget::~GameEngineRenderTarget() 
{
}


// ���̷�Ʈ���� �������� �ϰ� �츮�� �ᱹ device�� ���ؽ�Ʈ��
void GameEngineRenderTarget::Clear()
{
	for (size_t i = 0; i < RTV.size(); i++)
	{
		GameEngineCore::GetContext()->ClearRenderTargetView(RTV[i], ClearColor[i].Arr1D);
	}

	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	if (nullptr != DSV)
	{
		GameEngineCore::GetContext()->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void GameEngineRenderTarget::Setting()
{
	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	if (0 >=  RTV.size())
	{
		MsgBoxAssert("��������� ���� ����Ÿ���� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (false == IsDepth)
	{
		DSV = nullptr;
	}

	// 8�� �̻� ������ ������.
	GameEngineCore::GetContext()->OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], DSV);
	GameEngineCore::GetContext()->RSSetViewports(static_cast<UINT>(ViewPorts.size()), &ViewPorts[0]);
}

void GameEngineRenderTarget::AddNewTexture(DXGI_FORMAT _Format, float4 _Scale, float4 _ClearColor)
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };
	Desc.ArraySize = 1;
	Desc.Width = _Scale.uiX();
	Desc.Height = _Scale.uiY();
	Desc.Format = _Format;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.MipLevels = 1;
	// ����Ʈ
	// �� �ؽ�ó�� �޸𸮸� �׷���ī�尡 ������ �ض�.
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	// �뵵 ����Ÿ������ ����ϱ� ���ؼ� �����.
	// D3D11_BIND_SHADER_RESOURCE �ؽ�ó�� ���̴��� �����Ҽ� �ְ� �ϱ� ���ؼ� �����.

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Create(Desc);

	AddNewTexture(Tex, _ClearColor);
}

void GameEngineRenderTarget::AddNewTexture(std::shared_ptr<GameEngineTexture> _Texture, float4 _ClearColor)
{
	std::shared_ptr<GameEngineTexture> Tex = _Texture;

	Textures.push_back(Tex);

	// ����Ʈ�� ����
	D3D11_VIEWPORT ViewPortData;
	ViewPortData.TopLeftX = 0;
	ViewPortData.TopLeftY = 0;
	ViewPortData.Width = static_cast<float>(_Texture->GetScale().uiX());
	ViewPortData.Height = static_cast<float>(_Texture->GetScale().uiY());
	ViewPortData.MinDepth = 0.0f;
	ViewPortData.MaxDepth = 1.0f;

	RTV.push_back(Tex->GetRTV());
	SRV.push_back(Tex->GetSRV());
	ClearColor.push_back(_ClearColor);
	ViewPorts.push_back(ViewPortData);

}

void GameEngineRenderTarget::CreateDepthTexture(int _Index/* = 0*/)
{
	// �ؽ�ó�� ���� ����� ù��° �۾�
	D3D11_TEXTURE2D_DESC Desc = {0,};

	// �ؽ�ó�� 3�������� ������̳��ε�.
	Desc.ArraySize = 1;

	Desc.Width = Textures[_Index]->GetScale().uiX();
	Desc.Height = Textures[_Index]->GetScale().uiY();

	// 0~���� 1������ float�̱� ������. 
	// 1����Ʈ�� ����� 24��Ʈ float�� ����ϴ�.
	// ���� 8��Ʈ�� ���ٽ��̶�� ������ ����ϴµ� ���� �����帮�ڽ��ϴ�.
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.MipLevels = 1;
	// �׷���ī�忡 �־����.
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	DepthTexture = GameEngineTexture::Create(Desc);
}

void GameEngineRenderTarget::Copy(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget)
{
	Clear();
	Merge(ThisTarget, _Target, _CopyTarget);
}

void GameEngineRenderTarget::Merge(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget)
{
	Setting();

	MergeUnit.ShaderResHelper.SetTexture("DiffuseTex", _Target->Textures[_CopyTarget]);
	MergeUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "POINT");
	MergeUnit.Render();
	MergeUnit.ShaderResHelper.AllShaderResourcesReset();
}

void GameEngineRenderTarget::PostEffect(float _DeltaTime)
{
	for (std::shared_ptr<Effect>& Effect : Effects)
	{
		if (false == Effect->IsUpdate())
		{
			continue;
		}

		Effect->RenderBaseInfoValue.DeltaTime = _DeltaTime;
		Effect->RenderBaseInfoValue.AccDeltaTime += _DeltaTime;
		Effect->EffectProcess(_DeltaTime);
	}
}

void GameEngineRenderTarget::EffectInit(Effect* _Effect)
{
	_Effect->EffectTarget = this;
	_Effect->Start();
}
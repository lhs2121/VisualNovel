#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineMaterial.h>

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
	GameEngineLevel::OffDebug();
    GameEngineRenderTarget::IsDepth = false;
	//GameEngineGUI::CreateGUIWindow<gui>("gui");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<CityLevel>("CityLevel");
	GameEngineCore::ChangeLevel("CityLevel");
	//¾È³ç
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}



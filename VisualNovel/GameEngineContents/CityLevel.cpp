#include "PreCompile.h"
#include "CityLevel.h"
#include "Map.h"
#include <GameEngineCore\FadePostEffect.h>

CityLevel::CityLevel()
{
}

CityLevel::~CityLevel()
{
}

void CityLevel::Start()
{
	LevelMap = CreateActor<Map>();

	MainCamera = GetMainCamera();
	MainCamera->SetProjectionType(EPROJECTIONTYPE::Perspective);
	MainCamera->Transform.SetLocalPosition({ 0,0,-630 });
	
	GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
    GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 0.078, 0.576 });

	GameEngineInput::AddInputObject(this);
	
}

void CityLevel::Update(float _Delta)
{
	if (InputIsPress('W'))
	{
		float4 Force = { 0,CameraSpeed * _Delta };
		MainCamera->Transform.AddWorldPosition(Force);
	}
	if (InputIsPress('A'))
	{
		float4 Force = { -CameraSpeed * _Delta,0 };
		MainCamera->Transform.AddWorldPosition(Force);
	}
	if (InputIsPress('S'))
	{
		float4 Force = { 0,-CameraSpeed * _Delta };
		MainCamera->Transform.AddWorldPosition(Force);
	}
	if (InputIsPress('D'))
	{
		float4 Force = { CameraSpeed * _Delta,0 };
		MainCamera->Transform.AddWorldPosition(Force);
	}
	if (InputIsPress('Q'))
	{
		float4 Force = { 0,0,CameraSpeed * _Delta };
		MainCamera->Transform.AddWorldPosition(Force);
	}
	if (InputIsPress('E'))
	{
		float4 Force = { 0,0,-CameraSpeed * _Delta };
		MainCamera->Transform.AddWorldPosition(Force);
	}
}

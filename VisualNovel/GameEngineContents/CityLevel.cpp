#include "PreCompile.h"
#include "CityLevel.h"
#include "Map.h"

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
	MainCamera->Transform.SetLocalPosition({ 0,0,-500 });

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

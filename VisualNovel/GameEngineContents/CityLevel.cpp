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
	MainCamera->Transform.SetLocalPosition({ 33.121792f,-180.763336f,0.0f });

	GetLevelRenderTarget()->CreateEffect<FadePostEffect>();

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1.0f, 0.078f, 0.576f });

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Sound");


		GameEngineSound::SoundLoad(Dir.PlusFilePath("TestSong.mp3"));
		BGM = GameEngineSound::SoundPlay("TestSong.mp3");
	}


	GameEngineInput::AddInputObject(this);
}

void CityLevel::Update(float _Delta)
{
	float4 CameraPos = MainCamera->Transform.GetWorldPosition();

	if (CameraPos.Z >= -359.018433f)
	{
		MainCamera->Transform.AddLocalPosition({ 0,0,-13.0f * _Delta });
	}

	if (InputIsDown('P'))
	{
		BGM.TogglePausePlay();
	}

	//CameraInputUpdate(_Delta);
}

void CityLevel::CameraInputUpdate(float _Delta)
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

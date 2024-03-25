#include "PreCompile.h"
#include "IntroLevel.h"
#include <GameEngineCore\FadePostEffect.h>

IntroLevel::IntroLevel()
{
}

IntroLevel::~IntroLevel()
{
}

void IntroLevel::Start()
{
}

void IntroLevel::Update(float _Delta)
{
	if (OverlayChange == false)
	{
		float4 CameraPos = MainCamera->Transform.GetWorldPosition();
		if (CameraPos.Z <= -359.018433f)
		{
			for (std::shared_ptr<ContentsSpriteRenderer> Renderer : BackRenderers)
			{
				Renderer->SetOverlay("Test8.png");
			}
			OverlayChange = true;
		}
		else
		{
			MainCamera->Transform.AddLocalPosition({ 0,0,-13.0f * _Delta });
		}
	}

	if (InputIsDown('P'))
	{
		BGM.TogglePausePlay();
	}
}

void IntroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int SpriteCount = 0;
	if (nullptr == GameEngineSprite::Find(("BackGroundLayers")))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Map\\City\\001\\Back");

		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::CreateFolder("BackGroundLayers", Dir.GetStringPath());
		SpriteCount = Sprite->GetSpriteCount();
	}
	
	std::vector<float> ScrollSpeeds =
	{
		1.1f,
		0.9f,
		0.8f,
		0.7f,
		0.6f,
		0.5f,
		0.4f,
		0.3f,
		0.2f,
		0.1f,
	};

	std::shared_ptr<GameEngineActor> AniActor = CreateActor<GameEngineActor>();

	for (int i = 0; i < SpriteCount; i++)
	{
		std::shared_ptr<ContentsSpriteRenderer> Renderer = AniActor->CreateComponent<ContentsSpriteRenderer>();
		Renderer->SetSprite("BackGroundLayers", i);
		Renderer->SetOverlay("Test0.png");
		Renderer->SetFlicker(5.0f, 1.3f, 1.8f);
		Renderer->SetRenderOrder(SpriteCount - i);

		Renderer->EnableOverlay();
		Renderer->EnableFlicker();
		Renderer->EnableSpriteScrolling({ 0.1f * ScrollSpeeds[i], 0.0f });
		Renderer->EnableTextureScrolling({ 0.1f * ScrollSpeeds[i], 0.0f });

		BackRenderers.push_back(Renderer);
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets\\Sound");

		GameEngineSound::SoundLoad(Dir.PlusFilePath("TestSong.mp3"));
		BGM = GameEngineSound::SoundPlay("TestSong.mp3");
	}

	MainCamera = GetMainCamera();
	MainCamera->SetProjectionType(EPROJECTIONTYPE::Perspective);
	MainCamera->Transform.SetLocalPosition({ 33.121792f,-180.763336f,0.0f });

	GetLevelRenderTarget()->CreateEffect<FadePostEffect>();

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1.0f, 0.078f, 0.576f });
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGM.Stop();
}

void IntroLevel::Release()
{
}

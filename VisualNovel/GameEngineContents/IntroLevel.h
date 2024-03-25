#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class IntroLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	IntroLevel();
	~IntroLevel();

	// delete Function
	IntroLevel(const IntroLevel& _Other) = delete;
	IntroLevel(IntroLevel&& _Other) noexcept = delete;
	IntroLevel& operator=(const IntroLevel& _Other) = delete;
	IntroLevel& operator=(IntroLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override; 
	void Release() override;
	bool OverlayChange = false;
	float CameraSpeed = 350.0f;
	GameEngineSoundPlayer BGM;
	std::shared_ptr<GameEngineCamera> MainCamera;
	std::vector<std::shared_ptr<ContentsSpriteRenderer>> BackRenderers;
};
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CityLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CityLevel();
	~CityLevel();

	// delete Function
	CityLevel(const CityLevel& _Other) = delete;
	CityLevel(CityLevel&& _Other) noexcept = delete;
	CityLevel& operator=(const CityLevel& _Other) = delete;
	CityLevel& operator=(CityLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void CameraInputUpdate(float _Delta);

	float CameraSpeed = 350.0f;

	std::shared_ptr<class Map> LevelMap;
	std::shared_ptr<GameEngineCamera> MainCamera;
};
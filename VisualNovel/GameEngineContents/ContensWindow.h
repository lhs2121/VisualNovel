#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class Tab
{
public:
	std::string Name;
	int Index;

	virtual void OnGUI(GameEngineLevel* _Level, float _Delta) = 0;
	Tab(std::string_view _Name)
	{
		Name = _Name;
	}
};

class TestTab : public Tab
{
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _Delta);

public:
	TestTab(std::string_view _Name) : Tab(_Name)
	{
	}
};

class LevelTab : public Tab
{
	std::vector<std::string> Levels;

	void OnGUI(GameEngineLevel* _Level, float _Delta);

public:
	LevelTab(std::string_view _Name) : Tab(_Name)
	{
	}
};

// Ό³Έν :
class ContensWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

	std::shared_ptr<Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<Tab>> Tabs;

};
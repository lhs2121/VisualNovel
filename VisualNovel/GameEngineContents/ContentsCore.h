#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineCore.h>

// ���� :
class ContentsCore : public GameEngineObject
{
public:
	static std::string GetWindowTitle()
	{
		return "MainWindow";
	}

	static float4 GetStartWindowSize()
	{
		return {1366, 789};
	}

	static float4 GetStartWindowPos()
	{
		return { 100, 100 };
	}

	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:

};


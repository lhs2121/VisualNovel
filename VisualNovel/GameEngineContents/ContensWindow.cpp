#include "PreCompile.h"
#include "GameEngineContents\ContensWindow.h"


void ContensWindow::Start()
{
	Tabs.push_back(std::make_shared<TestTab>("Test"));
	Tabs.push_back(std::make_shared<LevelTab>("LevelTab"));
}

void ContensWindow::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		ImGui::SameLine();
		if(ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _Delta);
	}
}

void TestTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	std::string CameraPos = _Level->GetMainCamera()->Transform.GetWorldPosition().ToString();

	if (ImGui::Button("MousePos"))
	{

	}

	if (ImGui::Button(MousePos.c_str()))
	{

	}

	if (ImGui::Button("CameraPos"))
	{

	}

	if (ImGui::Button(CameraPos.c_str()))
	{

	}

	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	std::list<std::shared_ptr<GameEngineObject>> ObjectLists = _Level->GetObjectGroupInt(0);

	std::vector<std::shared_ptr<GameEngineObject>> Objects;

	for (std::shared_ptr<GameEngineObject> Ptr : ObjectLists)
	{
		Objects.push_back(Ptr);
	}


	if (Objects.size())
	{
		std::vector<std::string> Names;

		for (std::shared_ptr<GameEngineObject> Ptr : Objects)
		{
			Names.push_back(Ptr->GetName());
		}

		//Names.push_back("aaaa");
		//Names.push_back("bbbb");

		std::vector<const char*> CNames;

		for (size_t i = 0; i < Names.size(); i++)
		{
			CNames.push_back(Names[i].c_str());
		}

		if (ImGui::ListBox("ObjectList", &Select, &CNames[0], static_cast<int>(Names.size())))
		{
			SelectObject = Objects[Select];
		}

		if (nullptr != SelectObject)
		{
			if (ImGui::Button("Select Object Off"))
			{
				SelectObject->Off();
			}

		}
	}
}

void LevelTab::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
	}

	static const char* items[] = { "Item 1", "Item 2", "Item 3", "Item 4" };
	static int currentItem = 0; // 현재 선택된 항목의 인덱스

	// 리스트박스 생성
	if (ImGui::ListBox("##listbox", &currentItem, items, IM_ARRAYSIZE(items))) 
	{
		// 리스트박스에서 항목을 선택했을 때 처리할 작업
	}

}

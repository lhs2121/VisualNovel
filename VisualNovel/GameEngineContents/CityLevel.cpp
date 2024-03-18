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
}

void CityLevel::Update(float _Delta)
{
}

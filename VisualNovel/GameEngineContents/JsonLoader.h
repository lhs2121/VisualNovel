#pragma once
#include "json.hpp"

class JsonLoader
{
public:
	// constrcuter destructer
	JsonLoader() {};
	~JsonLoader() {};

	// delete Function
	JsonLoader(const JsonLoader& _Other) = delete;
	JsonLoader(JsonLoader&& _Other) noexcept = delete;
	JsonLoader& operator=(const JsonLoader& _Other) = delete;
	JsonLoader& operator=(JsonLoader&& _Other) noexcept = delete;

};
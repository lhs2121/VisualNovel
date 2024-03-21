#pragma once


enum class UpdateOrder
{

};

enum class RenderOrder
{

};

enum class UIRenderOrder
{

};

enum class ColOrder
{

};

struct OverlayInfo
{
	float Intensity = 1.0f;
	float4 OverlayUVPlus = float4::ZERO;
	float4 OverlayUVMul = float4::ONE;
};
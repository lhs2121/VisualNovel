#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader() 
{
}

GameEngineShader::~GameEngineShader() 
{
}

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow)
{
	ShaderTypeValue = _Type;

	switch (_Type)
	{
	case ShaderType::None:
	{
		MsgBoxAssert("���̴� Ÿ���� �߸����Խ��ϴ�.");
		break;
	}
	case ShaderType::Vertex:
		Version = "vs";
		break;
	case ShaderType::Geometry:
		Version = "gs";
		break;
	case ShaderType::Pixel:
		Version = "ps";
		break;
	case ShaderType::Max:
	{
		MsgBoxAssert("���̴� Ÿ���� �߸����Խ��ϴ�.");
		break;
	}
	default:
		break;
	}

	Version += "_";
	Version += std::to_string(_VersionHigh); // 5
	Version += "_";
	Version += std::to_string(_VersionLow); // 5

	// "vs_5_0"
}


void GameEngineShader::ShaderResCheck()
{
	ResHelper.ShaderResCheck(EntryName, this, BinaryCode);
}

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

bool GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	_File.Open(FileOpenType::Read, FileDataType::Text);

	GameEngineSerializer Ser;
	_File.DataAllRead(Ser);

	std::string_view ShaderCode = Ser.GetStringView();

	{
		size_t EntryIndex = ShaderCode.find("_VS(");

		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineVertexShader::Load(_File.GetStringPath(), EntryName);

		}
	}

	{
		// find �տ��� ���� ������ ����Ʈ ��ġ�� �˷��ݴϴ�.
		size_t EntryIndex = ShaderCode.find("_GS(");

		if (EntryIndex != std::string::npos)
		{

			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			// GameEngineVertexShader::Load(_File.GetStringPath(), EntryName);
		}
	}

	{
		// find �տ��� ���� ������ ����Ʈ ��ġ�� �˷��ݴϴ�.
		size_t EntryIndex = ShaderCode.find("_PS(");
		// ��ã������ ���ɴϴ�.
		if (EntryIndex != std::string::npos)
		{
			// ���� ������ ��ġ�������� ������ ã�� �Ƽ� 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);
			GameEnginePixelShader::Load(_File.GetStringPath(), EntryName);
		}
	}



	return true;
}


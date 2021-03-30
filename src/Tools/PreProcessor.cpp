#include "Common/Common.h"
#include "Common/WindowsCommon.h"
#include "Common/String.cpp"
#include "Storage/MetaInfo.h"
#include "Storage/StorageHandler.h"
#include "Maths/MathDef.h"

/*
This is a example of how we generate and save metainfo of each entiy
struct MetaInfo_Sarasa : MetaInfo
{
	union
	{
		struct
		{
			int member1;
			char member2[50];
			float member3;
			bool member4;
		};
		void* members;
	} data;

	MetaInfo_Sarasa() : MetaInfo()
	{
		memberTypes = "memberT1;memberT2;memberT3;memberT4";
		memberNames =  "member1;member2;member3;member4";
		index = 4;
		data.members = malloc(index);
	}

	static void* CreateInstance()
	{
		return new MetaInfo_Sarasa();
	}
	
};

EntityFactory LoadFactoryInstenceHandler()
{
	EntityFactory factory;
	Func *FactoryInstenceHandler[4];

	FactoryInstenceHandler[0] = MetaInfo_Sarasa::CreateInstance;

	factory.FactoryInstenceHandlerT = FactoryInstenceHandler;
}*/

struct MetaDataMember
{
	char* type;
	char* name;
	char* defaultValue;
};

struct MetaDataContainer
{
	char* structName;
	std::vector<MetaDataMember> members;
};

struct LineNode {
	String value = String(100);
	bool flagedAsMetadata = false;
	LineNode* previousLine;
	LineNode* nextLine;
};

void ParseFileContent(StringConst& fileContent, LineNode* lines)
{
	LineNode lineNode = {};

	// we save first line
	lines = &lineNode;

	//char const* characters = fileContent.c_str();

	while (char character = *fileContent)
	{
		
		if (character == '\r')
		{
			++fileContent;
			character = *fileContent;
		}


		if (character == '\n')
		{
			// We create a new line node and switch to curren variable.
			LineNode newLineNode = {};
			newLineNode.previousLine = &lineNode;
			lineNode.nextLine = &newLineNode;
			lineNode = newLineNode;
		}
		else
		{
			if (character == '@')
			{
				lineNode.flagedAsMetadata = true;
			}

			Append(lineNode.value, character);
		}
		
		++lineNode.value;
	}
}


int main(int argc, char** argv)
{
#if TARGET_WINDOWS
	AttachConsole(ATTACH_PARENT_PROCESS);
	// Handles returned by GetStdHandle can be used by applications that need to read from or write to the console.
	g_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	Strings fileList = GetFileListFromFolder("src\\Game");

	Strings::iterator const itEnd = fileList.end();
	for (Strings::iterator it = fileList.begin(); it != itEnd; it++)
	{
		StringConst fileContent = ReadFile(c_str(*it));

		if (IsEmpty(fileContent))
			continue;
		
		LineNode lineNode;
		ParseFileContent(fileContent, &lineNode);

		if (true){
			continue;
		}
		//char* fileContentCopy = nullptr;
		//strcpy(fileContentCopy, fileContent.c_str());

	}
	
	
}







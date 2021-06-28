#include <stdio.h>
#include "../Core/Common.h"
#include "../Core/WindowsCommon.h"
#include "../Core/String.h"
#include "../Core/StorageHandler.h"
#include "../Core/MathDef.h"
#include "../Core/MetaInfo.h"

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


struct LineNode
{
	String* value;
	LineNode* previousLine;
	LineNode* nextLine;
	bool isHeaderLine = false;
};

static String metaCantRecProt = "protect:"_s;
static String metaCantRecPriv = "private:"_s;
static String metaCanRec = "public:"_s;
static String metaClassHeader = "class"_s;
static String metaHeaderEntity = "entity"_s;
static char const* emptyChar = "";
static char const* withSpaceChar = " ";

bool StringMatch(String& stringToControl, char const& input, u8& countHelper)
{
	bool result = false;
	if (input == *stringToControl)
	{
		stringToControl++;
		countHelper++;

		if (countHelper == stringToControl.size)
		{
			ResetCharPosition(stringToControl);
			countHelper = 0;
			result = true;
		}
	}
	else if (countHelper > 0)
	{
		ResetCharPosition(stringToControl);
		countHelper = 0;
	}

	return result;
}

void ParseFileContent(String& fileContent, LineNode* lines)
{
	LineNode lineNode = {};

	// we save first line
	lines = &lineNode;

	u8 metaCantRecProtCount = 0;
	u8 metaCantRecPrivCount = 0;
	u8 metaCanRecCount = 0;
	u8 classHeaderCountOne = 0;
	u8 classHeaderCountTwo = 0;
	u32 braceHeadeCountr = 0;

	StringBuilder strBuilder(100);
	bool canRec = true;
	bool isClassHeaderLine = false;
	bool isClassHeaderToMeta = false;

	while (char const character = *fileContent)
	{
		if (character == '\r')
		{
			fileContent++;
			continue;
		}

		if (!isClassHeaderToMeta)
		{
			if (!isClassHeaderLine)
			{
				isClassHeaderLine = StringMatch(metaClassHeader, character, classHeaderCountOne);
			}
			else
			{
				lineNode.isHeaderLine = isClassHeaderToMeta = StringMatch(metaHeaderEntity, character, classHeaderCountTwo);
			}
		}
		else
		{
			if (character == '{')
			{
				braceHeadeCountr++;
			}
			else if (character == '}')
			{
				braceHeadeCountr--;

				if (braceHeadeCountr == 0)
				{
					canRec = true;
					isClassHeaderToMeta = true;
				}
			}

			if (canRec)
			{
				canRec = !StringMatch(metaCantRecProt, character, metaCantRecProtCount);
				canRec &= !StringMatch(metaCantRecPriv, character, metaCantRecPrivCount);
			}
			else
			{
				canRec |= StringMatch(metaCanRec, character, metaCanRecCount);
			}
		}

		// TODO : need avoid empty lines

		if (!canRec)
		{
			RestartStringBuilder(strBuilder);
			fileContent++;
			continue;
		}

		Append(strBuilder, character);

		if (character == '\n')
		{
			if (!isClassHeaderToMeta)
			{
				RestartStringBuilder(strBuilder);
				fileContent++;
				continue;
			}

			lineNode.value = MakeString(strBuilder);
			RestartStringBuilder(strBuilder);
			// We create a new line node and switch to curren variable.
			LineNode newLineNode = {};
			newLineNode.previousLine = &lineNode;
			lineNode.nextLine = &newLineNode;
			lineNode = newLineNode;
		}

		fileContent++;
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
		String const* fileName = *it;
		String* fileContent = ReadFile(fileName);

		if (IsEmpty(*fileContent))
			continue;

		LineNode lineNode;
		ParseFileContent(*fileContent, &lineNode);

		// TODO : check if I need prevent create file if content are empty

		LineNode* currentLine = &lineNode;
		MetaInfo metaInfo;
		while (currentLine)
		{
			u8 classHeaderCountOne = 0;
			bool classHeaderMatch = false;
			StringBuilder strBuilder(100);
			bool recClassHeader = false;
			while (char const character = **currentLine->value)
			{
				if (currentLine->isHeaderLine)
				{
					if (!classHeaderMatch)
					{
						classHeaderMatch = StringMatch(metaClassHeader, character, classHeaderCountOne);
						currentLine->value++;
						continue;
					}
					else if (character == *emptyChar || character == *withSpaceChar)
					{
						if (recClassHeader)
						{
							break;
						}
						currentLine->value++;
						continue;
					}
					else
					{
						recClassHeader = true;
						Append(strBuilder, character);
					}
				}
			}


			currentLine = currentLine->nextLine;
		}

		std::FILE* fp = fopen(*fileName + "_gen.cpp", "rb");

		if (true) {
			continue;
		}

		//File* file = fopen(it + ".gen.cpp"_sc);

		//char* fileContentCopy = nullptr;
		//strcpy(fileContentCopy, fileContent.c_str());

	}


}







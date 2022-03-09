#include <stdio.h>
#include "../Core/Common.h"
#include "../Core/WindowsCommon.h"
#include "../Core/String.h"
#include "../Core/StorageHandler.h"
#include "../Core/MathDef.h"
#include "../Core/MetaInfo.h"
#include "../Core/HashTable.h"

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
	String* type;
	String* name;
};

struct MetaDataContainer
{
	String* className;
	std::vector<MetaDataMember> members;
};

enum HeaderType
{
	NONE_HEADER_TYPE,
	META_HEADER_TYPE,
	CLASS_HEADER_TYPE,
	STRUCT_HEADER_TYPE,
	ENUM_HEADER_TYPE
};


struct LineNode
{
	String* value;
	LineNode* previousLine;
	LineNode* nextLine;
	HeaderType HeaderType = NONE_HEADER_TYPE;
};

static String protectTag = "protect"_s;
static String privateTag = "private"_s;
static String publicTag = "public"_s;
static String classTag = "class"_s;
static String entityTag = "Entity"_s;
static String structTag = "struct"_s;
static String enumTag = "enum"_s;
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
	u8 classTagCount = 0;
	u8 enumTagCount = 0;
	u8 structTagCount = 0;
	u8 publicTagCount = 0;
	u8 entityTagCount = 0;
	u32 braceHeadeCountr = 0;

	StringBuilder strBuilder(100);
	bool canRec = true;
	bool isClassHeaderLine = false;
	bool isHeaderLine = false;
	bool isClassHeaderPublicLabel = false;
	bool skipLine = false;

	while (char const character = *fileContent)
	{
		if (character == '\r')
		{
			fileContent++;
			continue;
		}

		if (character == '\n')
		{
			lineNode.value = MakeString(strBuilder);
			RestartStringBuilder(strBuilder);
			// We create a new line node and switch to curren variable.
			LineNode newLineNode = {};
			newLineNode.previousLine = &lineNode;
			lineNode.nextLine = &newLineNode;
			lineNode = newLineNode;

			fileContent++;
			continue;

		}

		if (!isHeaderLine)
		{
			// we check by header type
			if (lineNode.HeaderType == NONE_HEADER_TYPE)
			{
				// check if current line contains the string "class"
				if (StringMatch(classTag, character, classTagCount))
				{
					isClassHeaderLine = true;
					lineNode.HeaderType = CLASS_HEADER_TYPE;
				}

				if (StringMatch(enumTag, character, enumTagCount))
				{
					isHeaderLine = true;
					lineNode.HeaderType = ENUM_HEADER_TYPE;
				}

				if (StringMatch(structTag, character, structTagCount))
				{
					isHeaderLine = true;
					lineNode.HeaderType = STRUCT_HEADER_TYPE;
				}
			}
			else if (isClassHeaderLine)
			{

				if (!isClassHeaderPublicLabel)
				{
					//check if current line contains the string "public"
					isClassHeaderPublicLabel = StringMatch(publicTag, character, publicTagCount);
				}
				else
				{
					//check if current line cotains the string "entity"
					if (StringMatch(entityTag, character, entityTagCount))
					{
						lineNode.HeaderType = META_HEADER_TYPE;
						isHeaderLine = true;
						isClassHeaderPublicLabel = false;
					}

				}
			}
		}
		else
		{
			isClassHeaderLine = false;

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
					isHeaderLine = true;
				}
			}

			if (canRec)
			{
				skipLine = character == '(';

				canRec = !StringMatch(protectTag, character, metaCantRecProtCount);
				canRec &= !StringMatch(privateTag, character, metaCantRecPrivCount);
			}
			else
			{
				canRec |= StringMatch(publicTag, character, publicTagCount);
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

		fileContent++;
	}
}

int main(int argc, char** argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

#if TARGET_WINDOWS
	AttachConsole(ATTACH_PARENT_PROCESS);
	// Handles returned by GetStdHandle can be used by applications that need to read from or write to the console.
	g_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	Strings fileList = GetFileListFromFolder("src\\Game");

	HashTable<MetaDataContainer>* hashTable = CreateHashTable<MetaDataContainer>();

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
		MetaDataContainer* metaInfo;
		while (currentLine)
		{

			switch (currentLine->HeaderType)
			{
			case META_HEADER_TYPE:
			{
				u8 classHeaderCountOne = 0;
				bool classHeaderMatch = false;
				StringBuilder strBuilder(100);
				bool recClassHeader = false;

				while (char const character = **currentLine->value)
				{
					if (currentLine->HeaderType)
					{
						if (!classHeaderMatch)
						{
							// we skip the string "class" to get only the class name string
							classHeaderMatch = StringMatch(classTag, character, classHeaderCountOne);
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

				metaInfo = new  MetaDataContainer();
				metaInfo->className = MakeString(strBuilder);
				HashTableSet(hashTable, metaInfo->className, metaInfo);
				
				break;
			}
			case CLASS_HEADER_TYPE:
				break;
			case STRUCT_HEADER_TYPE:
				break;
			case ENUM_HEADER_TYPE:
			{
				MetaDataMember metaDataMember;

			}
				break;

			default:
			{
				break;
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







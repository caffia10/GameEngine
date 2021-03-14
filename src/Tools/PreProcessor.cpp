#include "Common/Common.h"
#include "Common/WindowsCommon.h"
#include "Storage/MetaInfo.h"
#include "Storage/StorageHandler.h"
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

int main(int argc, char** argv)
{
#if TARGET_WINDOWS
	AttachConsole(ATTACH_PARENT_PROCESS);
	// Handles returned by GetStdHandle can be used by applications that need to read from or write to the console.
	g_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	std::vector<char const*> const fileList = GetFileListFromFolder("/src/Game");

	for (size_t i = 0; i < count; i++)
	{
		/* code */
	}
	
	
}







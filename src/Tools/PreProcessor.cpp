#include <stdlib.h>
#include "Storage/MetaInfo.h"

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
	g_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	
}







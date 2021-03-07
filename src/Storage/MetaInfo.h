struct MetaInfo
{
	int index;
	char* memberTypes;
	char* memberNames;
};

typedef void* Func();

struct EntityFactory
{
	int totalEntitys;
	Func **FactoryInstenceHandlerT;
};
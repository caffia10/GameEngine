
#ifndef META_INFO_H
#define META_INFO_H

#include "MathDef.h"
#include "String.h"


struct MetaInfoProperty
{
	u64 index;
	String* name;
	String* type;
	void* (*gett)();
	void(*setter)(void*);
};

struct MetaInfo
{
	String* className;
	void* instance;
	MetaInfoProperty* properties;
};


/*
void Test(){
	MetaInfoProperty pt;

	void* t = pt.gett();

	pt.setter(t);
}*/

typedef void* Func();

struct EntityFactory
{
	int totalEntitys;
	Func **FactoryInstenceHandlerT;
};
#endif // META_INFO_H
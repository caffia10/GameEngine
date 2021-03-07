
#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "Common.h"
#include "Maths/MathDef.h"

#define P_READ_ONLY 0x0001
#define P_EDIT_ANYWHERE 0X002

#define PROPERTY(p_type_args)

struct Component
{
    u8 Id;
    char name[50];

    virtual void Initialize();
    virtual void OnUpdate();
    virtual void Release();
};

typedef std::vector<Component>::iterator ComponentIterator;

class Entity
{
public:    
    u8 Id;
    char name[50];

    void AddComponent(Component component) { components.push_back(component);}
    void RemoveComponent(u8 componentId)
    { 
        ComponentIterator const itEnd = components.end();
        for (ComponentIterator it = components.begin(); it != itEnd; ++it)
        {
            if (it->Id == componentId)
            {
                components.erase(it);
            }
        }
    }

    Component& GetComponetById(u8 componentId) 
    { 
        ComponentIterator const itEnd = components.end();
        for (ComponentIterator it = components.begin(); it != itEnd; it++)
        {
            if (it->Id == componentId)
            {
                return *it;
            }
        }
    }

    Component& GetComponetByIndex(u32 index) 
    { 
        for (u32 i = 0; i != components.size(); i++)
        {
            if (index == i)
            {
                return components[index];
            }
        }
    }

    virtual void Initialize()
    {
        ComponentIterator const itEnd = components.end();
        for (ComponentIterator it = components.begin(); it != itEnd; it++)
        {
            it->Initialize();
        }
        
    }

    virtual void OnUpdate()
    {
        ComponentIterator const itEnd = components.end();
        for (ComponentIterator it = components.begin(); it != itEnd; it++)
        {
            it->OnUpdate();
        }
        
    }

    virtual void Release()
    {
        ComponentIterator const itEnd = components.end();
        for (ComponentIterator it = components.begin(); it != itEnd; it++)
        {
            it->Release();
        }
        
        components.clear();
    }

private:

    std::vector<Component> components;
    
};

#endif // ENGINE_H
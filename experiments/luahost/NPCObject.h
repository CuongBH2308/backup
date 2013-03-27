#ifndef _NPCOBJECT_H
#define _NPCOBJECT_H

#include <string>

class NPCObject
{
public:
	NPCObject(const char* name): _name(name) {}
	void attack();
	std::string name()
	{
		return _name;
	}

private:
	std::string _name;
};
#endif

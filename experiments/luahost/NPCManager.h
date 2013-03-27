#ifndef _NPCMANAGER_H
#define _NPCMANAGER_H
#include <vector>

class NPCObject;

class NPCManager
{
public:
	static NPCManager* get();

	void addNPC(const char* name);

	void removeNPC(const char* name);

	void dump();

private:
	typedef std::vector<NPCObject*> NPCObjects;
	NPCObjects npcObjs;
};

#endif

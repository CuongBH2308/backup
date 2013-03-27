#include "NPCManager.h"
#include "NPCObject.h"
#include <algorithm>

using namespace std;


NPCManager* NPCManager::get()
{
	static NPCManager npcMgr;
	return &npcMgr;
}

void NPCManager::addNPC(const char* name)
{
	npcObjs.push_back(new NPCObject(name));
}

void NPCManager::removeNPC(const char* name)
{
	NPCObjects::iterator it = std::remove_if(npcObjs.begin(), npcObjs.end(), [&name](NPCObject* npc) {return npc->name() == name;});
	npcObjs.erase(it, npcObjs.end());
}

void NPCManager::dump()
{
	for_each(npcObjs.begin(), npcObjs.end(), [](NPCObject* npc) {printf("%s\n", npc->name().c_str());});

}


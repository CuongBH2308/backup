#include "stdafx.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

typedef unsigned int uint;
class Action
{
public:
	virtual void Doit() = 0;
	virtual void Undo() = 0;
};

typedef vector<Action*> ActionList;
class ActionManager
{
public:
	static ActionManager* Get()
	{
		static ActionManager _instance;
		return &_instance;
	}
	ActionManager():_curIndex(-1){}

	void Action(Action* pAction)
	{
		// branch processing...
		if(_actionList.size() != _curIndex + 1)
		{
			ActionList list;
			list.resize(_actionList.size() - _curIndex - 1);
			std::copy(_actionList.begin() + _curIndex + 1, _actionList.end(), list.begin());
			_actionList.resize(_curIndex + 1);
			_branches.insert(std::make_pair(_curIndex, list));
		}

		// do it
		cout << "Do Action: ";
		pAction->Doit();

		// add to list
		_actionList.push_back(pAction);
		_curIndex += 1;

	}


	void Undo()
	{
		if(_curIndex == -1)
		{
			cout << "Action List is empty" << endl;
		}

		cout << "Undo Action: ";
		_actionList[_curIndex]->Undo();

		_curIndex -= 1;
	}

	void Redo()
	{
		// branch processing
		if(_branches.count(_curIndex) > 0)
		{
			cout << "You have an alternative redo branch here" << endl;
		}

		_curIndex += 1;

		cout << "Redo Action: ";
		_actionList[_curIndex]->Doit();
	}

private:
	ActionList _actionList;
	uint _curIndex;
	multimap<uint, ActionList> _branches;
};

int g_value = 0;

class PlusAction: public Action
{
public:
	PlusAction(int a):_a(a){}
	virtual void Doit(){g_value += _a; cout << "g_value = " << g_value << endl;}
	virtual void Undo(){g_value -= _a; cout << "g_value = " << g_value << endl;}

private:
	int _a;
};

class MinusAction: public Action
{
public:
	MinusAction(int a):_a(a){}
	virtual void Doit(){g_value -= _a; cout << "g_value = " << g_value << endl;}
	virtual void Undo(){g_value += _a; cout << "g_value = " << g_value << endl;}

private:
	int _a;
};

int main()
{
	ActionManager::Get()->Action(new PlusAction(5));
	ActionManager::Get()->Action(new MinusAction(1));
	ActionManager::Get()->Action(new MinusAction(1));
	ActionManager::Get()->Action(new PlusAction(7));
	ActionManager::Get()->Action(new PlusAction(7));
	ActionManager::Get()->Action(new PlusAction(7));
	ActionManager::Get()->Action(new MinusAction(4));

	ActionManager::Get()->Undo();
	ActionManager::Get()->Undo();
	ActionManager::Get()->Undo();
	ActionManager::Get()->Action(new MinusAction(7));

	ActionManager::Get()->Undo();

	ActionManager::Get()->Redo();


	
}
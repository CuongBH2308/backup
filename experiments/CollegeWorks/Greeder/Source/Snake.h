// Snake.h: interface for the CSnake class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAKE_H__4264D3D6_15B7_4D2E_8ECF_F9CABB727CC0__INCLUDED_)
#define AFX_SNAKE_H__4264D3D6_15B7_4D2E_8ECF_F9CABB727CC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include <iterator>
#define BODYSIZE 20
#define XBEGIN   159
#define YBEGIN   0

extern bool bRun;

using namespace std;

typedef struct _Point{
	int x;
	int y;
	bool operator==(_Point& p ){
		if(x==p.x&&y==p.y){
			return true;
		}
		return false;
	};
}Point,*pPoint;

/*bool Point::operator==(_Point& p ){
	if(x==p.x&&y==p.y){
		return true;
	}
	return false;
}
*/


typedef enum{UP = 1,DOWN = 2,LEFT = -1,RIGHT = -2,PAUSE = 0} Direction;

class CSnake  
{
public:
	CSnake();
	virtual ~CSnake();
	Point GetPointCoor(int i);
	int GetCount();
	void move(Point food);
	void SetDirection(Direction dir);
	Direction GetDirection();
    bool  IsFoodExist();
	bool  CheckFoodCollision(Point p);
	bool  CheckCollision(Point p);
	void  Setfood();
	bool  CheckSelfCollision();
	Point GetHead();
	bool  IsDead();
	void  Reset();
	void  SetLevel(int lev);
	int   GetLevel();
	int   GetScore();
	int   GetLength();

	

	
    
private:
	deque<Point> m_SnakeList;
	int m_lever;
	int m_length;
	int m_score;
	bool m_ismoved;
	bool m_isdead;
	bool m_isfood;
	Direction m_direction;


};

#endif // !defined(AFX_SNAKE_H__4264D3D6_15B7_4D2E_8ECF_F9CABB727CC0__INCLUDED_)

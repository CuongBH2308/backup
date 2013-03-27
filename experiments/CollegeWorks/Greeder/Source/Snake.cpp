// Snake.cpp: implementation of the CSnake class.
//
//////////////////////////////////////////////////////////////////////

#include "Snake.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnake::CSnake():m_lever(1),m_length(8),m_score(0),m_ismoved(true),
         m_isdead(false),m_isfood(true),m_direction(RIGHT)
{
	for(int i = 0;i<8;i++){
		Point p = {i,0};
		m_SnakeList.push_back(p);
	}
}

CSnake::~CSnake()
{

}


Point CSnake::GetPointCoor(int i){
	Point p = m_SnakeList.at(i);
	p.x = p.x*BODYSIZE + XBEGIN + BODYSIZE/2;
	p.y = p.y*BODYSIZE + YBEGIN + BODYSIZE/2;
	return p;
}

int CSnake::GetCount(){
	return m_SnakeList.size();
}


void CSnake::move(Point food){
	Point p = m_SnakeList.back();
	Point ptail = m_SnakeList.front();
	
	switch(m_direction){
	case UP:
		p.y -= 1;
	
		break;
	case DOWN:
		p.y += 1;
		
		break;
	case LEFT:
		p.x -= 1;
		
		break;
	case RIGHT:
		p.x += 1;
	
		break;
	case PAUSE:
		break;
	default:break;
	}
	
	if(CheckCollision(p) == false){
		m_SnakeList.pop_front();
		m_SnakeList.push_back(p);
	}
	
	
	p = m_SnakeList.back();
	if(p==food){

		m_SnakeList.push_front(ptail);// eat the food and put it at the tail
		m_isfood = false;
		//add score correspond to its level
		m_score+=m_lever;
		//increase the length
		m_length++;
		
	}
}


void CSnake::SetDirection(Direction dir){
//	static int num = 0;
	if(dir == PAUSE ){
	//	num++;
	//	if(num%2==1)
	//		bRun=false;
	//	else 
	//		bRun=true;

	    return;
	}
	if(m_direction*dir<0)  m_direction = dir;
}


Direction CSnake::GetDirection(){
	return m_direction;
}

bool CSnake::IsFoodExist(){
	return m_isfood;
}


bool CSnake::CheckFoodCollision(Point p){
	deque<Point>::iterator iter;
	for(iter = m_SnakeList.begin();iter != m_SnakeList.end();iter++){
		if(p == *iter){
			return true;
		}
	}
	return false;
}

bool CSnake::CheckSelfCollision(){
	Point p = m_SnakeList.back();
	deque<Point>::iterator iter;
	for(iter = m_SnakeList.begin();iter != m_SnakeList.end()-1;iter++){
		if(p == *iter){
			return true;
		}
	}
	return false;

}
//p为蛇头的下一个位置,在改变之前先进行判断
bool CSnake::CheckCollision(Point p){
	if(CheckSelfCollision() == true){
		m_isdead = true;
		return m_isdead;
	}
	if((p.x<0||p.y<0||p.x>31||p.y>23) == true){
		m_isdead = true;
		return m_isdead;
	}
	
	m_isdead = false;
    return m_isdead;
	
}

void CSnake::Setfood(){
	m_isfood = true;
}


Point CSnake::GetHead(){
	return m_SnakeList.back();
}

bool CSnake::IsDead(){
	return m_isdead;
}


void CSnake::Reset(){
	
	m_lever = 1;
	m_length = 8;
	m_score = 0;
	m_ismoved = true;
	
	m_isdead = false; 
	m_isfood = true;
	m_direction = RIGHT;
	m_SnakeList.clear();
	for(int i = 0;i<8;i++){
		Point p = {i,0};
		m_SnakeList.push_back(p);
	}
}


void CSnake::SetLevel(int lev){
	m_lever = lev;
}

int CSnake::GetLevel(){
	return m_lever;
}

int CSnake::GetScore(){
	return m_score;
}
int CSnake::GetLength(){
	return m_length;
}
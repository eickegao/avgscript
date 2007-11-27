#ifndef OBJECTLIST_H_
#define OBJECTLIST_H_
#include "datatype.h"
#include <list>
using namespace std;

/**
 * @brief ֱ�ߵ���ʾ������Ҫ�����������ߡ�
 */
struct  CLineObject
{
	CPointf p1;
	CPointf p2;
	int     color;
};

class CLineObjectList
{
	CLineObjectList(){m_flag = true;};
	void Push(CLineObject* object);
	void Clear();
	int  Size();
	void SetShowFlag(int flag){ m_flag = flag; };
private:
	list<CLineObject*> m_linelist;
	int  m_flag;	
};
/**
 * @brief ���ε���ʾ������Ҫ�������������Ρ�
 */
struct  CRectObject
{
	CRectf  rect;
	int     color;
};

class CRectObjectList
{
	CRectObjectList(){m_flag = true;};
	void Push(CRectObject* object);
	void Clear();
	int  Size();
	void SetShowFlag(int flag){ m_flag = flag; };
private:
	list<CRectObject*> m_linelist;
	int  m_flag;	
};

#endif

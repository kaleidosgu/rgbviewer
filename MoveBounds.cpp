#include "StdAfx.h"
#include "MoveBounds.h"

CMoveBounds::CMoveBounds(void)
{
	m_rect.h = 0;
	m_rect.w = 0;
	m_rect.x = 0;
	m_rect.y = 0;
}

CMoveBounds::CMoveBounds(int x, int y, int w, int h)
{
	m_rect.h = h;
	m_rect.w = w;
	m_rect.x = x;
	m_rect.y = y;
}
bool CMoveBounds::MoveAvailable( int x, int y )
{
	bool bResultX = false;
	bool bResultY = false;
	if( m_rect.x <= x && ( m_rect.x + m_rect.w ) >= x )
	{
		bResultX = true;
	}
	if( m_rect.y <= y && ( m_rect.y + m_rect.h ) >= y )
	{
		bResultY = true;
	}
	return bResultX && bResultY;
}
CMoveBounds::~CMoveBounds(void)
{
}

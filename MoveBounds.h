#pragma once
#include "SDL_video.h"

struct SDL_Rect;
class CMoveBounds
{
public:
	CMoveBounds(void);
	CMoveBounds(int x, int y, int w, int h );
	bool MoveAvailable( int x, int y );
	virtual ~CMoveBounds(void);
private:
	SDL_Rect m_rect;
};

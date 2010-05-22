#pragma once
#include "SDL.h"
struct SDL_Surface;
class CMoveBounds;
class CEntity
{
public:
	CEntity(void);
	virtual ~CEntity(void);
	void Create( int x, int y, const std::string& strRest );
	void SetMVelocity( int vx, int vy );
	void OnDraw();
	void OperateEntity( Uint8 *keystates );
	void SetMoveBound( CMoveBounds* pMoveBnd );
		
private:
	int m_nX;
	int m_nY;
	int m_nMvx;
	int m_nMvy;
	SDL_Surface* m_pDrawSurface;
	CMoveBounds* m_pMoveBnd;
};

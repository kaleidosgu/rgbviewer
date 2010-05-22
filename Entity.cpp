#include "StdAfx.h"
#include "Entity.h"
#include "SDL.h"
#include "SDL_image.h"
#include "../uiwndbaseinsdl/src/GlobalSurface.h"
#include "MoveBounds.h"

CEntity::CEntity(void)
:m_nX(0),m_nY(0),m_nMvx(0),m_nMvy(0)
,m_pDrawSurface(0),m_pMoveBnd(0)
{

}

CEntity::~CEntity(void)
{
	if( m_pDrawSurface )
	{
		SDL_FreeSurface( m_pDrawSurface );
	}
}

void CEntity::Create( int x, int y, const std::string& strRest )
{
	SDL_Surface* loadedImage = IMG_Load( strRest.c_str() );

	const char *message = IMG_GetError();

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        m_pDrawSurface = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
}
void CEntity::SetMVelocity( int vx, int vy )
{
	m_nMvx = vx;
	m_nMvy = vy;
}
void CEntity::OnDraw()
{
	//Rectangle to hold the offsets
    SDL_Rect offset;

	//Get offsets
    offset.x = m_nX;
    offset.y = m_nY;

    //Blit the surface
    SDL_BlitSurface( m_pDrawSurface, NULL, g_pScreen, &offset );
}

void CEntity::OperateEntity( Uint8 *keystates )
{
	int x = m_nX;
	int y = m_nY;
	bool bMove = false;
	if( keystates[ SDLK_DOWN ] )
	{
		y = m_nY + m_nMvy;
		bMove = true;
	}
	if( keystates[ SDLK_UP ] )
	{
		y = m_nY - m_nMvy;
		bMove = true;
	}
	if( keystates[ SDLK_RIGHT ] )
	{
		x = m_nX + m_nMvx;
		bMove = true;
	}
	if( keystates[ SDLK_LEFT ] )
	{
		x = m_nX - m_nMvx;
		bMove = true;
	}
	if( bMove && m_pMoveBnd )
	{
		if( m_pMoveBnd->MoveAvailable( x, y ))
		{
			m_nX = x;
			m_nY = y;
		}
	}
}
void CEntity::SetMoveBound( CMoveBounds* pMoveBnd )
{
	m_pMoveBnd = pMoveBnd;
}
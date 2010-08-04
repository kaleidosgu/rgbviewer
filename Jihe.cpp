// Jihe.cpp : Defines the entry point for the console application.
//The headers
#include "stdafx.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../uiwndbaseinsdl/src/GlobalSurface.h"
#include "../uiwndbaseinsdl/src/DrawRect.h"
#include "Entity.h"
#include "GlobalInfo.h"
#include "../uiwndbaseinsdl/src/FontManager.h"
#include "../uiwndbaseinsdl/src/DrawText.h"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

enum COLOR_BAR_ATTR { COLOR_BAR_WIDTH = 30, COLOR_BAR_HEIGHT = 256, COLOR_BAR_X = 200, COLOR_BAR_Y = 150, COLOR_BAR_SPAN = 50 };
enum COLOR_POINT_ATTR { POINT_WIDTH = COLOR_BAR_WIDTH, POINT_HEIGHT = 5 };


//TTF_Font *font = NULL;
bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    g_pScreen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT , SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( g_pScreen == NULL )
    {
        return false;
    }

	if( TTF_Init() == -1 )
	{
		return false;
	}

    //Set the window caption
    SDL_WM_SetCaption( "Jihe test", NULL );

    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}
void getChar( char* buffer, size_t length, int number )
{
	sprintf_s(buffer,length,"%d",number);
}
int integerLimit( int integer )
{
	int result = integer;
	if( result < 0 )
	{
		result = 0;
	}
	else if( result > 255 )
	{
		result = 255;
	}
	return result;
}
int main( int argc, char* args[] )
{
    //Initialize
    if( init() == false )
    {
        return 1;
    }

	int crR = 0;
	int crB = 0;
	int crG = 0;

	//font
	//font = TTF_OpenFont( "lazy.ttf", 16 );

	SDL_Event event;
	bool quit = false;
	
	CEntity bg;
	bg.Create(0,0,"bg.png");

	//目标颜色矩形的背景。
	CDrawRect rcBG;
	rcBG.SetRectAttr(280,0,90,90);
	rcBG.SetColor(crR,crG,crB);

	//目标颜色。随着三个rgb变化后产生的颜色的矩形。
	CDrawRect rcDist;
	rcDist.SetRectAttr(300,20,50,50);
	rcDist.SetColor(200,255,255);

	//三个颜色条.
	CDrawRect rcRed;
	rcRed.SetRectAttr(COLOR_BAR_X,COLOR_BAR_Y,COLOR_BAR_WIDTH,COLOR_BAR_HEIGHT + POINT_HEIGHT );
	rcRed.SetColor(255,0,0);

	CDrawRect rcGreen;
	rcGreen.SetRectAttr(COLOR_BAR_X + COLOR_BAR_SPAN,COLOR_BAR_Y,COLOR_BAR_WIDTH,COLOR_BAR_HEIGHT + POINT_HEIGHT );
	rcGreen.SetColor(0,255,0);

	CDrawRect rcBlue;
	rcBlue.SetRectAttr(COLOR_BAR_X + COLOR_BAR_SPAN*2,COLOR_BAR_Y,COLOR_BAR_WIDTH,COLOR_BAR_HEIGHT + POINT_HEIGHT );
	rcBlue.SetColor(0,0,255);


	CDrawRect rcRedPoint;
	rcRedPoint.SetRectAttr(rcRed.GetRect().x,COLOR_BAR_Y + crR,POINT_WIDTH, POINT_HEIGHT);
	rcRedPoint.SetColor(255,255,0);

	CDrawRect rcBluePoint;
	rcBluePoint.SetRectAttr(rcBlue.GetRect().x,COLOR_BAR_Y + crG,POINT_WIDTH, POINT_HEIGHT);
	rcBluePoint.SetColor(255,255,0);

	CDrawRect rcGreenPoint;
	rcGreenPoint.SetRectAttr(rcGreen.GetRect().x,COLOR_BAR_Y + crB,POINT_WIDTH, POINT_HEIGHT);
	rcGreenPoint.SetColor(255,255,0);


	SDL_Color crColor = { 255, 255, 255 };

	char buffer[32] = {0};
	getChar(buffer,32,crR);
	//msgRed = TTF_RenderText_Solid( font, buffer, crColor );*/

	CDrawText infoText;
	infoText.SetColor( crColor );
	infoText.SetFontAttr ("lazy.ttf",16);
	infoText.SetText( "   ASD control RGB DOWN, qwe control RGB UP");
	infoText.SetPos(0,460);

	CDrawText redText;
	redText.SetColor( crColor );
	redText.SetFontAttr( "lazy.ttf",16 );
	redText.SetText(buffer);


	getChar(buffer,32,crG);
	CDrawText greenText;
	greenText.SetColor( crColor );
	greenText.SetFontAttr( "lazy.ttf",16 );
	greenText.SetText(buffer);

	getChar(buffer,32,crB);
	CDrawText blueText;
	blueText.SetColor( crColor );
	blueText.SetFontAttr( "lazy.ttf",16 );
	blueText.SetText(buffer);
	
	SDL_Rect offset;
	offset.y = COLOR_BAR_Y - 20;
	int nLastTime = SDL_GetTicks();
	int nWholeTime = 0;
	while( quit == false )
    {
		bg.OnDraw();
		infoText.OnDraw();
        //While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //If s was pressed
                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
					quit = true;
				}
				else if( event.key.keysym.sym == SDLK_SPACE )
				{
				}
			}
        }
		////////////////////////////////

		int nCurTime = SDL_GetTicks();
		nWholeTime = nWholeTime + (nCurTime - nLastTime );

		Uint8 *keystates = SDL_GetKeyState( NULL );
		if( nWholeTime > 50000 )
		{
			nWholeTime = 0;
			bool bRes = false;
			if (keystates[SDLK_a] )
			{
				bRes = true;
				crR = integerLimit(++crR);
			}
			else if (keystates[SDLK_q] )
			{
				bRes = true;
				crR = integerLimit(--crR);
			}
			if (keystates[SDLK_s] )
			{
				bRes = true;
				crG = integerLimit(++crG);
			}
			else if (keystates[SDLK_w] )
			{
				bRes = true;
				crG = integerLimit(--crG);
			}
			if (keystates[SDLK_d] )
			{
				bRes = true;
				crB = integerLimit(++crB);
			}
			else if (keystates[SDLK_e] )
			{
				bRes = true;
				crB = integerLimit(--crB);
			}
			if( bRes )
			{
				rcBG.SetColor(crR,crG,crB);
				rcRedPoint.SetPos(rcRedPoint.GetRect().x, COLOR_BAR_Y + crR );
				rcGreenPoint.SetPos(rcGreenPoint.GetRect().x, COLOR_BAR_Y + crG );
				rcBluePoint.SetPos(rcBluePoint.GetRect().x, COLOR_BAR_Y + crB );
				
				getChar(buffer,32,crR);
				//msgRed = TTF_RenderText_Solid( font, buffer, crColor );
				redText.SetText(buffer);
				getChar(buffer,32,crG);
				greenText.SetText(buffer);
				getChar(buffer,32,crB);
				blueText.SetText(buffer);
			}
		}
		////////////////////////////////

		rcBG.OnDraw();
		rcDist.OnDraw();

		rcRed.OnDraw();
		rcGreen.OnDraw();
		rcBlue.OnDraw();

		rcRedPoint.OnDraw();
		rcBluePoint.OnDraw();
		rcGreenPoint.OnDraw();

    
		//Get offsets
		offset.x = COLOR_BAR_X;
		//Blit
		//SDL_BlitSurface( msgRed, NULL, g_pScreen, &offset );
		redText.SetPos( offset.x, offset.y );
		redText.OnDraw();

		offset.x += COLOR_BAR_SPAN ;
		greenText.SetPos( offset.x, offset.y );
		greenText.OnDraw();
		offset.x += COLOR_BAR_SPAN ;
		blueText.SetPos( offset.x, offset.y );
		blueText.OnDraw();

        //Update the screen
        if( SDL_Flip( g_pScreen ) == -1 )
        {
            return 1;    
        }
    }

	//Free the surface and quit SDL
    clean_up();

    return 0;
}

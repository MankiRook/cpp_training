#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "tools.h"
#include <time.h>
#include "SAT.h"
#include <random>
#include "Polygon.h"

using namespace std;

/*Variables*/

//The window we'll be rendering to
SDL_Window* pWindow = nullptr;
SDL_Renderer* pRenderer = nullptr;
TTF_Font *pFont = nullptr;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
SDL_Rect* TEXT_SIZE;

//Polygons
Polygon B;
Polygon A;

/*Prototypes*/
inline SDL_Texture* loadTexture( const string file );
SDL_Texture* loadFromRenderedText( std::string textureText, SDL_Color textColor );
bool init();
bool loadMedia();
void close();
void random();
void draw();

/*LOAD TEXTURE*/
inline SDL_Texture* loadTexture( const string file )
{

    SDL_Texture* pLoadedTexture = nullptr;
    string path = getCurrentDir() + "\\" + file;

    //Load Surface
    SDL_Surface* pTempSurface = IMG_Load(path.c_str());

    if( pTempSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL Error: %s \n\n", path.c_str(), SDL_GetError() );
        return nullptr;
    }
    else
    {
        pLoadedTexture = SDL_CreateTextureFromSurface( pRenderer, pTempSurface );

        if( pLoadedTexture == nullptr )
        {
            printf( "Unable to create Texture %s! SDL Error: %s \n\n", path.c_str(), SDL_GetError() );
            return nullptr;
        }
    }
    //Free Surface
    SDL_FreeSurface( pTempSurface );

    return pLoadedTexture;
}
/*LOAD TEXT*/
SDL_Texture* loadFromRenderedText( std::string text, SDL_Color textColor )
{
    SDL_Texture* textTexture = nullptr;
    SDL_Surface* tempSurface = TTF_RenderText_Solid( pFont, text.c_str(), textColor);
    if( tempSurface == nullptr )
    {
        logSDLError( "Unable to render text surface!" );
    }
    else
    {
        TEXT_SIZE->w = tempSurface->w;
        TEXT_SIZE->h = tempSurface->h;

        textTexture = SDL_CreateTextureFromSurface( pRenderer, tempSurface );
        if( textTexture == nullptr )
        {
            logSDLError( "Unable to create text_texture" );
        }
    }
    return textTexture;
}

/*INIT*/
bool init()
{
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        pWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED |
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if( pWindow == nullptr )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }

        //SET Window size
        SDL_GetWindowSize( pWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT );

        //Create renderer
        pRenderer = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED );

        if( pRenderer == nullptr)
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }

        //Initalize SDL_Image
        if( !IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP ))
        {
            printf( "SDL_Image could not be initalized! SDL Error: %s\n", IMG_GetError() );
            success = false;
        }
        if( TTF_Init() == -1)
        {
             printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
             success = false;
        }
    }

    srand(time(NULL));
    return success;
}

/*LOADMEDIA*/
bool loadMedia()
{
    bool success = true;

    //Open the font
    pFont = TTF_OpenFont( "monospaced_bold.ttf", 12);
    if( pFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    return success;
}

/*CLOSE*/
void close()
{
    //Free font
    TTF_CloseFont( pFont );
    pFont = nullptr;

    //Destroy window
    SDL_DestroyWindow( pWindow );
    pWindow = nullptr;

    //Destroy Renderer
    SDL_DestroyRenderer( pRenderer);
    pRenderer = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
/*DRAW*/
void random()
{
    A.points.clear();
    A.points.push_back(Point{ static_cast<float>(rand()%SCREEN_WIDTH), static_cast<float>(rand()%SCREEN_HEIGHT) });
    A.points.push_back(Point{ static_cast<float>(rand()%SCREEN_WIDTH), static_cast<float>(rand()%SCREEN_HEIGHT) });
    A.points.push_back(Point{ static_cast<float>(rand()%SCREEN_WIDTH), static_cast<float>(rand()%SCREEN_HEIGHT) });

    B.points.clear();
    B.points.push_back(Point{ static_cast<float>(rand()%SCREEN_WIDTH), static_cast<float>(rand()%SCREEN_HEIGHT) });
    B.points.push_back(Point{ static_cast<float>(rand()%SCREEN_WIDTH), static_cast<float>(rand()%SCREEN_HEIGHT) });
    B.points.push_back(Point{ static_cast<float>(rand()%SCREEN_WIDTH), static_cast<float>(rand()%SCREEN_HEIGHT) });
}
void draw()
{
    if(checkCollision( A, B))
    {
        SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    else
    {
        SDL_SetRenderDrawColor(pRenderer, 0x00, 0xFF, 0x00, 0xFF);
    }

    //Draw Polygon A
    for(unsigned int i = 0; i<A.points.size()-1; i++)
    {
        SDL_RenderDrawLine(pRenderer, A.points.at(i).x, A.points.at(i).y, A.points.at(i+1).x, A.points.at(i+1).y );
    }

    //Last Line
    SDL_RenderDrawLine(pRenderer, A.points.at(0).x, A.points.at(0).y, A.points.at(B.points.size()-1).x, A.points.at(B.points.size()-1).y );

    //Draw Polygon B
    for(unsigned int t = 0; t<B.points.size()-1; t++)
    {
        SDL_RenderDrawLine(pRenderer, B.points.at(t).x, B.points.at(t).y, B.points.at(t+1).x, B.points.at(t+1).y );
    }

    //Last Line
    SDL_RenderDrawLine(pRenderer, B.points.at(0).x, B.points.at(0).y, B.points.at(B.points.size()-1).x, B.points.at(B.points.size()-1).y );

}
/*MAIN*/
int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;

            //Event handler
            SDL_Event e;

            random();

            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.repeat ==0 )
                    {
                        //User presses a key
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_e:
                                random();
                                break;
                            case SDLK_RETURN:
                                random();
                                break;
                            case SDLK_SPACE:
                                random();
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear( pRenderer);

                //Draw things
                draw();

                //Update Screen
                SDL_RenderPresent( pRenderer);
            }
        }
    }

    //Free resources and close SDL
    close();
    return 0;
}

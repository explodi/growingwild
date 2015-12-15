

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"
#include <stdio.h>
#import "Cat.h"
#import "Timer.h"

// CONSTANTS
#define PTM_RATIO 32.0
#define FRAMES_PER_SECOND 30

// frame
int frame=0;
Timer fps;

// Box2D World
b2Vec2 gravity = b2Vec2(0.0f, -8.0f);

b2World *world=new b2World(gravity);





//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init()
{
    // Create ball body and shape
    b2Body *ballBody;
    b2BodyDef ballBodyDef;
    ballBodyDef.type=b2_dynamicBody;
    ballBody = world->CreateBody(&ballBodyDef);

    b2CircleShape circle;
    circle.m_radius = 26.0/PTM_RATIO;
    
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.2f;
    ballShapeDef.restitution = 0.8f;
    ballBody->CreateFixture(&ballShapeDef);
    
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load splash image
    gXOut = SDL_LoadBMP( "data/cat.bmp" );
    if( gXOut == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
        success = false;
    }
    
    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gXOut );
    gXOut = NULL;
    
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    // Create new Cat
    
    Cat cat;
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
            
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //While application is running
            while( !quit )
            {
                //Start the frame timer
                fps.start();
                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }
                //Set texture based on current keystate
                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                if( currentKeyStates[ SDL_SCANCODE_UP ] )
                {
                    cat.jump();
                    
                    
                    
                    

                }
                // Cat position
                SDL_Rect cat_rect;
                
                // B2D world step
                
                world->Step(1, 10, 10);
                
                // B2D loop
                printf("loop");
                for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
                    cat_rect.x=b->GetPosition().x;
                    cat_rect.y=(b->GetPosition().y*-1);
                    printf("%d",cat_rect.y);
                    cat_rect.w=20;
                    cat_rect.h=30;
                    //    ballData.position = ccp(b->GetPosition().x * PTM_RATIO,
                    //      b->GetPosition().y * PTM_RATIO);
                    //  ballData.rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
                }

                //Apply the image
                SDL_BlitSurface( gXOut, NULL, gScreenSurface, &cat_rect );
                
                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
            }
            //Increment the frame counter
            frame++;
            //If we want to cap the frame rate
            if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
            {
                //Sleep the remaining frame time
                SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}
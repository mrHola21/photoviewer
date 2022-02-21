
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

unsigned const int SCREEN_WIDTH = 640;
unsigned const int SCREEN_HEIGHT = 480;

void init();
void loadMedia();
void close();
SDL_Texture *loadTexture(std::string path);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("K boi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_JPG);
}

void close()
{

    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}

SDL_Texture *loadTexture(std::string path)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

int main()
{
    init();
    texture = loadTexture("data/PNG/ujju.png");
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}
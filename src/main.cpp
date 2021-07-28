#include <SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/websocket.h>
#endif
#include <stdlib.h>
#include <string>
#include <iostream>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;

void drawRandomPixels()
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    Uint8 *pixels = (Uint8 *)surface->pixels;

    for (int i = 0; i < 1048576; i++)
    {
        char randomByte = rand() % 255;
        pixels[i] = randomByte;
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(screenTexture);
}


int main(int argc, char *argv[])
{
    //bool done = false;
    //std::string input;
 
    //while (!done) {
    //    std::cout << "Enter Command: ";
    //    //std::getline(std::cin, input);
 
    //    if (input == "quit") {
    //        done = true;
    //    } else if (input == "help") {
    //        std::cout
    //            << "\nCommand List:\n"
    //            << "help: Display this help text\n"
    //            << "quit: Exit the program\n"
    //            << std::endl;
    //    } else {
    //        std::cout << "Unrecognized Command" << std::endl;
    //    }
    //}
 
    //return 0;

    //EmscriptenWebSocketCreateAttributes attributes;
    //attributes.protocols = "binary,base64";
    //attributes.url = "localhost";
    //int socket = emscripten_websocket_new(&attributes);
    //emscripten_websocket_send_binary(socket, );
    //emscripten_websocket_close()
    //emscripten_websocket_set_onmessage_callback()



    SDL_Init(SDL_INIT_VIDEO);
    //SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
    window = SDL_CreateWindow("nice", 0, 0, 512, 512, ::SDL_WINDOW_RESIZABLE | ::SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, 0);
    surface = SDL_CreateRGBSurface(0, 512, 512, 32, 0, 0, 0, 0);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(drawRandomPixels, 0, 1);
    #else
    while(true)
    {
        drawRandomPixels();
    }
    #endif


}
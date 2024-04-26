#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    int running = 1;
    int color = 0; // 0 for white, 1 for black
    int fullscreen = 0; // 0 for windowed, 1 for fullscreen
    int windowWidth = 400;
    int windowHeight = 300;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Black&White", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION || event.type == SDL_KEYDOWN) {
                // Toggle color on mouse click, mouse movement, or any key press
                color = (color == 0) ? 1 : 0;
            }
            if (event.type == SDL_KEYDOWN) {
                // Toggle fullscreen mode on F11 key press
                if (event.key.keysym.sym == SDLK_F11) {
                    fullscreen = !fullscreen;
                    if (fullscreen) {
                        SDL_DisplayMode DM;
                        SDL_GetCurrentDisplayMode(0, &DM);
                        windowWidth = DM.w;
                        windowHeight = DM.h;
                        SDL_SetWindowSize(window, windowWidth, windowHeight);
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    } else {
                        // Exit fullscreen mode
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_SetWindowSize(window, 400, 300); // Set back to original size
                    }
                }
                // Close program on Esc key press
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        // Set color
        if (color == 0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Render changes
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

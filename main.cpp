#include <iostream>
#include <string>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"

// Compatible with Lesson2 assets

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
 * Log SDL-related error.
 *
 * @param msg The error message to prepend to SDL's error.
 */
void logSdlError(const std::string &msg) {
    std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}

/**
 * Load BMP image into a texture on renderer.
 *
 * @param file The BMP image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went awry
 */
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
    // Avoid dangling ptr
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        cleanup(loadedImage);
        if (texture == nullptr) {
            logSdlError("CreateTextureFromSurface");
        }
    } else {
        logSdlError("LoadBMP");
    }
    return texture;
}

/**
 * @brief renderTexture
 *
 * Draw a SDL texture to a renderer at given position, maintaining
 * texture's original scale.
 *
 * @param tex
 * @param ren
 * @param x
 * @param y
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(ren, tex, NULL, &destination);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSdlError("SDL_Init");
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSdlError("SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cleanup(win);
        logSdlError("SDL_CreateRenderer");
        SDL_Quit();
        return 1;
    }

    std::string backgroundImgPath = getResourcePath("Lesson2") + "background.bmp";
    std::string smileyImgPath = getResourcePath("Lesson2") + "smiley.bmp";
    SDL_Texture *backgroundTex = loadTexture(backgroundImgPath, ren);
    SDL_Texture *smileyTex = loadTexture(smileyImgPath, ren);
    if (backgroundTex == nullptr || smileyTex == nullptr) {
        cleanup(backgroundTex, smileyTex, ren, win);
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        SDL_RenderClear(ren);

        // Background
        int bW, bH;
        SDL_QueryTexture(backgroundTex, NULL, NULL, &bW, &bH);
        renderTexture(backgroundTex, ren, 0, 0);
        renderTexture(backgroundTex, ren, bW, 0);
        renderTexture(backgroundTex, ren, 0, bH);
        renderTexture(backgroundTex, ren, bW, bH);

        // Foreground
        int sW, sH;
        SDL_QueryTexture(smileyTex, NULL, NULL, &sW, &sH);
        int x = SCREEN_WIDTH / 2 - sW / 2;
        int y = SCREEN_HEIGHT / 2 - sH / 2;
        renderTexture(smileyTex, ren, x, y);

        SDL_RenderPresent(ren);
        SDL_Delay(1000);
    }

    cleanup(backgroundTex, smileyTex, ren, win);
    SDL_Quit();
}

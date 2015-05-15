//
// Created by Daniel Gregoire on 5/14/15.
//

#ifndef SDLTUTORIAL_CLEANUP_H
#define SDLTUTORIAL_CLEANUP_H

#include<utility>
#include<SDL.h>
#include <iostream>

/**
 * Recursive template to clean up SDL artifacts,
 * one at a time.
 */
template<typename T, typename... Args>
void cleanup(T *t, Args&&... args) {
    cleanup(t);
    // Recurse
    cleanup(std::forward<Args>(args)...);
}

/**
 * These specializations serve to free the passed
 * argument and also provide the recursion base case
 * for the template above.
 *
 * It is safe to pass nullptr's in, so we don't have to worry
 * about whether or not things were even ever initialized.
 */
template<>
void cleanup<SDL_Window>(SDL_Window *win) {
    if (!win) { return; }
    SDL_DestroyWindow(win);
}
template<>
void cleanup<SDL_Renderer>(SDL_Renderer *ren) {
    if (!ren) { return; }
    SDL_DestroyRenderer(ren);
}
template<>
void cleanup<SDL_Texture>(SDL_Texture *tex) {
    if (!tex) { return; }
    SDL_DestroyTexture(tex);
}
template<>
void cleanup<SDL_Surface>(SDL_Surface *surf) {
    if (!surf) { return; }
    SDL_FreeSurface(surf);
}

#endif //SDLTUTORIAL_CLEANUP_H

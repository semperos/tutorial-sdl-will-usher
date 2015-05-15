//
// Created by Daniel Gregoire on 5/14/15.
//
#ifndef SDLTUTORIAL_RES_PATH_H
#define SDLTUTORIAL_RES_PATH_H

#include<iostream>
#include<string>
#include<SDL.h>

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

/**
 * Get resource path for resources located in res/<subDir>.
 * Assumed the project is structured a particular way.
 *
 * bin/
 *     executable
 * res/
 *     Lesson1/
 *     Lesson2/
 *
 * Paths returned will be absolute.
 */
std::string getResourcePath(const std::string &subDir = "") {
    // Platform-specific path separator
#ifdef _WIN32
    const char PATH_SEP = '\\';
    #else
    const char PATH_SEP = '/';
#endif

    // Base resource path
    static std::string baseRes;
    if (baseRes.empty()) {
        // SDL returns NULL on problem here
        char *basePath = SDL_GetBasePath();
        if (basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }

        // Handle out-of-source build directory
        size_t pos = baseRes.rfind("SdlTutorial-build");
        baseRes = baseRes.substr(0, pos) + "SdlTutorial" + PATH_SEP + "res" + PATH_SEP;
    }
    // Allow appending further subdir
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

#endif //SDLTUTORIAL_RES_PATH_H

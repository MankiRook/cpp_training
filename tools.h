//Includes
#include <string>
#include <iostream>
#include <SDL_image.h>
//Used fo pathmanagment
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

/**
* Log an SDL error with some error message to the output stream of your choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
**/
inline void logSDLError(const string &msg)
{
    cout << msg << " error: " << SDL_GetError() << endl;
}

/**
* Returns the path to the current working directory
* Works on Windows and on Linux/Unix
*@return string The Current Directory
**/
inline  string getCurrentDir()
{
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return NULL;
    }
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    return cCurrentPath;
}

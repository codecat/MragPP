#ifndef MRAGPP_EXAMPLE_H_INCLUDED
#define MRAGPP_EXAMPLE_H_INCLUDED

#if WINDOWS
#include <Windows.h>
#include <direct.h>

#ifdef _SDL_H
#include <SDL2/SDL_main.h>
#endif

#define MAIN int main(int argc, char* argv[])
#else
#include <unistd.h>
#include <errno.h>

#define MAIN int main()
#endif

/**
 * All this function does is traverse the parent folders to find
 * the "examples_content" folder. It will then change the current
 * working directory so that it's inside of that folder.
 *
 * If the folder can't be found anywhere, this will either crash
 * or infinite loop, so the folder should be there.
 */
inline void FindExampleContentPath()
{
#if WINDOWS
	DWORD dwFlags = 0;
	do {
		dwFlags = GetFileAttributesA("examples_content");
		if(dwFlags == INVALID_FILE_ATTRIBUTES) {
			_chdir("..");
		}
	} while(dwFlags == INVALID_FILE_ATTRIBUTES);
	_chdir("examples_content/");
#else
	while(access("examples_content/", F_OK) != 0) {
		if(errno == ENOENT || errno == ENOTDIR) {
			chdir("..");
		} else {
			break;
		}
	}
	chdir("examples_content/");
#endif
	char szCwd[300];
	getcwd(szCwd, 300);
	printf("Cwd: %s\n", szCwd);
}

#endif

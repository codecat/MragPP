#ifndef MRAGPP_EXAMPLE_H_INCLUDED
#define MRAGPP_EXAMPLE_H_INCLUDED

#if WINDOWS
#include <Windows.h>
#else
#include <unistd.h>
#include <errno.h>
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
		dwFlags = GetFileAttributesA("content");
		if(dwFlags == INVALID_FILE_ATTRIBUTES) {
			_chdir("..");
		}
	} while(dwFlags == INVALID_FILE_ATTRIBUTES);
#else
  while(access("examples_content/", F_OK) != 0) {
		if(errno == ENOENT || errno == ENOTDIR) {
			chdir("..");
		} else {
			break;
		}
	}
#endif
	chdir("examples_content/");
	char szCwd[300];
	getcwd(szCwd, 300);
	printf("Cwd: %s\n", szCwd);
}

#endif

#ifdef _WIN32
#  include <direct.h>
#else
#  include <unistd.h>
#endif
#include <stdio.h>

int main() {
    char *cwd = NULL;
    char path[1024] = {0};
#ifdef _WIN32
    cwd = _getcwd(path, 1024);
#else
    cwd = getcwd(path, 1024);
#endif
    if (cwd) {
	printf("%s\n", cwd);
	return 0;
    }
    return -1;
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */

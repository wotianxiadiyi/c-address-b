#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

int main(int argc, char *argv[])
{
    if (argc-1 < 1) {
        const char *msg = "usage: nocat <file>\n";
        write(STDOUT_FILENO, msg, strlen(msg));
        return 1;
    }

    const char *path = argv[1];
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        const char *msg = "nocat: unable to open file \'";
        write(STDOUT_FILENO, msg, strlen(msg));
        write(STDOUT_FILENO, path, strlen(path));
        write(STDOUT_FILENO, "\'\n", 2);
        return 2;
    }

    // print out contents of file
    char c;
    while (read(fd, &c, 1) != 0) {
        write(STDOUT_FILENO, &c, 1);
    }

    return 0;
}

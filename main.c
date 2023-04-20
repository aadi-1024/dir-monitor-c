#include <stdio.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define PATH_MAX 4096

int main(int argc, char** argv) {
    //if (argc < 2) {
    //    printf("Enter path to monitor\n");
    //    return 1;
    //}

    int fd = inotify_init();
    if (fd == -1) {
        printf("File descriptor could not be created");
        return 1;
    }
    int wd = inotify_add_watch(fd, "/home/aaditya/Apps", IN_CREATE);
    size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1;
    struct inotify_event* event = malloc(bufsiz);
    char* name;
    char* cmd = malloc(PATH_MAX);
    strcpy(cmd, "flatpak install -y ~/Apps/");
    while (1) {
        read(fd, event, bufsiz);
        name = event->name;
	strcat(cmd, name);
    strcat(cmd, " > /dev/null");

	system(cmd);
    
    strcpy(cmd, "");
    printf("Done! Installed %s\n", name);
    }
}

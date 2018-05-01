#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "../h/readMmap.h"

using namespace std;

void MmapRead::read(){
    printf(" - Reading %s file\n", this->targetFile.c_str());
    int fd;
    int *map;  /* mmapped array of int's */

    struct stat fileStat = {0};

    fd = open(this->targetFile.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }//if fd

    fstat(fd, &fileStat);

    map = (int*)mmap(0, fileStat.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }//if map

    int totalCharsRead = 0;
    /* Read the file int-by-int from the mmap
     */
    for (off_t i = 1; i <= fileStat.st_size; ++i) {
        map[i];
        totalCharsRead += 1;
    }//for

    printf("-- %d chars read using mmap(). --\n", totalCharsRead);

    if (munmap(map, fileStat.st_size) == -1) {
        perror("Error un-mmapping the file");
    }

    close(fd);

}//read
#include <ctime>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

using namespace std;


void read_file(char *filePath){
    printf(" - Reading %s file\n", filePath);
    int fd;
    int *map;  /* mmapped array of int's */

    struct stat fileStat = {0};

    fd = open(filePath, O_RDONLY);
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

    int totalLines = 0;
    /* Read the file int-by-int from the mmap
     */
    for (off_t i = 1; i <= fileStat.st_size; ++i) {
        //rintf("%d: %d\n", i, map[i]);
        map[i];
        totalLines += 1;
    }

    printf("%d read\n", totalLines);

    if (munmap(map, fileStat.st_size) == -1) {
        perror("Error un-mmapping the file");
    }

    close(fd);

}//read_file


int main(int argc, char *argv[]){
    char * filepath = argv[1];

    int startTime = clock();
    read_file(filepath);
    int endTime = clock();

    cout << "time: " << (endTime - startTime) / double(CLOCKS_PER_SEC) << endl;
    return 0;
}//main

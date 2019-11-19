#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char * argv[]){
  // DIR * dir = opendir(".");
  DIR * dir;
  char directory[512];
  if (argc = 1){
    fgets(directory, sizeof(directory), stdin);
    directory[strlen(directory) - 1] = '\0';
  }
  else{
    strcpy(directory, argv[1]);
  }
  dir = opendir(directory);
  if (dir == NULL){
    printf("%s\n", strerror(errno));
    return 0;
  }
  struct dirent * nextFile = readdir(dir);
  int size = 0;
  while(nextFile != NULL){
    // printf("%s %d\n", nextFile->d_name, nextFile->d_type);
    struct stat info;
    stat(nextFile -> d_name, &info);
    printf("Name: %s\n", nextFile->d_name);
    if (nextFile->d_type == 4){
      printf("Type: directory\n");
      printf("Size: %ld", info.st_size );
    }
    else if (nextFile->d_type == 8){
      printf("Type: file\n");
      printf("Size: %ld bytes", info.st_size );
      size += info.st_size;
    }
    nextFile = readdir(dir);
    printf("\n..........................\n");
  }
  printf("Total directory size(normal files): %d bytes\n", size);
  return 0;
}

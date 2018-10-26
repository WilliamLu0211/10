#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int random_int(){
  int fd = open("/dev/random", O_RDONLY);
  if (!(fd + 1)){
    printf("open failed: %s\n", strerror(errno));
    return 0;
  }

  char buff[4];
  int n = read(fd, buff, 4);
  if (!(n + 1)){
    printf("read failed: %s\n", strerror(errno));
    return 0;
  }
  // buff[4] = 0;

  int x = 0;
  for (int i = 0; i < 4; i ++){
    // printf("%d ~ ", buff[i]);
    // printf("%x\n", buff[i]);
    x = x << 8;
    x += buff[i];
  }
  return x;
}

int main(){
  // printf("%x\n", random_int());

  int fd, n;

  int arr[10];
  printf("Generating random numbers:\n");
  for (int i = 0; i < 10; i ++){
    arr[i] = random_int();
    printf("\trandom %d: %d\n", i, arr[i]);
  }
  printf("\n");

  fd = open("new_file.txt", O_WRONLY | O_CREAT, 0777);
  if (!(fd + 1)){
    printf("open failed: %s\n", strerror(errno));
    return 0;
  }

  printf("Writing numbers to file...\n\n");
  n = write(fd, arr, 40);
  if (!(n + 1)){

    printf("write failed: %s\n", strerror(errno));
    return 0;
  }

  int foo[10];
  fd = open("new_file.txt", O_RDONLY);
  if (!(fd + 1)){
    printf("open failed: %s\n", strerror(errno));
    return 0;
  }

  printf("Reading numbers from file...\n\n");
  n = read(fd, foo, 40);
  if (!(n + 1)){
    printf("read failed: %s\n", strerror(errno));
    return 0;
  }

  printf("Verification that written values were the same:\n");
  for (int i = 0; i < 10; i ++)
    printf("\trandom %d: %d\n", i, foo[i]);

  return 0;
}

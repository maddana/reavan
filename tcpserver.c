#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
extern int errno;
struct emp{
int id;
char name[20];
};
struct emp *newnode;
main ()
{
  newnode=malloc(sizeof(struct emp));
  int ret, ret1, ret2, fd;
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd == -1)
    {
      printf("sd=%d and errno =%d\n", sd, errno);
      exit(1);
    }
  else
    printf("sd=%d\n", sd);
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof (serv_addr));
  serv_addr.sin_family = PF_INET;
  serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  serv_addr.sin_port = htons (2400);

  ret = bind(sd,(struct sockaddr *) &serv_addr, sizeof (serv_addr));
  if (ret == -1)
    {
      printf("bind=%d,errno=%d\n", ret, errno);
      exit(1);
    }
  else
    printf("Bind=%d\n", ret);
  ret1 = listen(sd, 10);
  if (ret1 == -1)
    {
      printf("Listen=%d and errno=%d\n", ret1, errno);
      exit(1);
    }
  else
    printf("Listen=%d\n", ret1);
  struct sockaddr_in from_addr;
  char buf[4096];
  int fromsize = sizeof(struct sockaddr_in);
  int connected_sd;
  while (1)
    {
      connected_sd = accept(sd,(struct sockaddr *) &from_addr, &fromsize);
      if (connected_sd == -1)
        {
          printf("connected_sd=%d and errno=%d\n", connected_sd, errno);
          exit (1);
        }
      else
        {
          printf("connected_sd=%d\n", connected_sd);
/*        fd = open("server1.txt",O_RDWR, S_IRWXU);
          if(fd < 0)
            {
              printf("File Descriptor=%d and errno=%d\n", fd, errno);
              exit(1);
            }*/
            newnode->id=20;
            strcpy(newnode->name,"rajesh");
            sprintf(buf,"%d %s",newnode->id,newnode->name);
          //ret = read (fd, buf, 256);
          //printf("listen returned = %d\n", ret);
          write(connected_sd, buf,sizeof(buf));
          //close(fd);
        }
    }
}

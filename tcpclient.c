#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
extern int errno;
main ()
{
  int ret;
  int sd, fd;
  int ret1;
  int buf[256];
  sd = socket (PF_INET, SOCK_STREAM, 0);
  printf ("sd = %d\n", sd);
  if (sd == -1)
    {
      printf ("sd = %d, errno = %d\n", errno);
      exit (1);
    }
  struct sockaddr_in serv_addr;
  memset (&serv_addr, 0, sizeof (serv_addr));
  serv_addr.sin_family = PF_INET;
  if (inet_pton (AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr) <= 0)
    {
      printf ("inet_pton ERROR. errno is %d\n", errno);
      exit (1);
    }
  serv_addr.sin_port = htons (2400);
  ret = connect (sd, (struct sockaddr *) &serv_addr, sizeof (serv_addr));
  printf ("connect  returned = %d\n", ret);
  fd = open ("server1.txt", O_RDWR, S_IRWXU);
  if (fd < 0)
    {
      printf ("fd=%d and errno=%d\n", fd, errno);
      exit (1);
    }
  while ((ret1 = read (sd, buf, 256)) > 0)
    {
 //     write (1, buf, ret1);
        puts(buf);
    }
  // close (fd);
  if (ret1 == -1)
    {
      printf ("ret = %d, errno = %d\n", errno);
      exit (1);
    }
}

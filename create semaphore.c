#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include<errno.h>
#include<sys/stat.h>
extern int errno;
main ()
{

  int semid = semget (ftok ("shmprj",80), 2, IPC_CREAT | S_IRWXU);

  printf ("setget returned %d\n", semid);
  if (semid == -1)
    {
      printf ("errno = %d\n", errno);
      exit (1);
    }
}

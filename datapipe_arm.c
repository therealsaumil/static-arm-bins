/* 

The following is an interesting snippet of code I wrote recently. It 
makes a data pipe between a listen port on the machine it's being run on 
and a port on a remote machine. For example, running
  datapipe 2222 23 your.machine.com

would create a port 2222 on the local machine that, if telnetted to, would
be the same as telnetting to port 23 on your.machine.com. This can be used
for a variety of purposes: redirect IRC connections so that identd shows
the username of the datapipe process; redirect sendmail direct connections
for the same reason; even use on a firewall machine to give access to an
internal service (ftpd, for instance). Cascaded datapipes make for
interesting traceback dilemmas. Questions and comments accepted.

Compile with:
    cc -o datapipe -O datapipe.c
On boxes without strerror() (like SunOS 4.x), compile with:
    cc -o datapipe -O -DSTRERROR datapipe.c

Run as:
    datapipe localport remoteport remotehost

It will fork itself into the background.

**** SAUMIL'S NOTE: to compile datapipe for solaris:

     gcc -o datapipe_solaris -O datapipe.c -lnsl -lsocket

     ignore all the warnings :-)

/*
 * Datapipe - Create a listen socket to pipe connections to another
 * machine/port. 'localport' accepts connections on the machine running    
 * datapipe, which will connect to 'remoteport' on 'remotehost'. Fairly
 * standard 500 xxxx extended errors are used if something drastic
 * happens.
 *
 * (c) 1995 Todd Vierling
 *
 * Define STRERROR while compiling on a SunOS 4.x box
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

/*#include <linux/time.h>*/

#ifdef STRERROR
extern char *sys_errlist[];
extern int sys_nerr;
char *undef = "Undefined error";

char *strerror(error)  
  int error;  
{ 
  if (error > sys_nerr)
    return undef;
  return sys_errlist[error];
}
#endif

main(argc, argv)  
  int argc;  
  char **argv;  
{ 
  int lsock, csock, osock;
  FILE *cfile;
  char buf[4096];
  struct sockaddr_in laddr, caddr, oaddr;
  int caddrlen = sizeof(caddr);
  fd_set fdsr, fdse;
  struct hostent *h;
  struct servent *s;
  int nbyt;
  unsigned long a;
  unsigned short oport;

  if (argc != 4) {
    fprintf(stderr,"Usage: %s localport remoteport remotehost\n",argv[0]);
    return 30;
  }
  a = inet_addr(argv[3]);
  if (!(h = gethostbyname(argv[3])) &&
      !(h = gethostbyaddr(&a, 4, AF_INET))) {
    perror(argv[3]);
    return 25;
  }
  oport = atol(argv[2]);
  laddr.sin_port = htons((unsigned short)(atol(argv[1])));
  if ((lsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    perror("socket");
    return 20;
  }
  laddr.sin_family = AF_INET;
  laddr.sin_addr.s_addr = htonl(0);
  if (bind(lsock, &laddr, sizeof(laddr))) {
    perror("bind");
    return 20;
  }
  if (listen(lsock, 1)) {
    perror("listen");
    return 20;
  }
  if ((nbyt = fork()) == -1) {
    perror("fork");
    return 20;
  }
  if (nbyt > 0)
    return 0;
  setsid();
  while ((csock = accept(lsock, &caddr, &caddrlen)) != -1) {
    cfile = fdopen(csock,"r+");
    if ((nbyt = fork()) == -1) {
      fprintf(cfile, "500 fork: %s\n", strerror(errno));
      shutdown(csock,2);
      fclose(cfile);
      continue;
    }
    if (nbyt == 0)
      goto gotsock;
    fclose(cfile);
    while (waitpid(-1, NULL, WNOHANG) > 0);
  }
  return 20;

 gotsock:
  if ((osock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    fprintf(cfile, "500 socket: %s\n", strerror(errno));
    goto quit1;
  }
  oaddr.sin_family = h->h_addrtype;
  oaddr.sin_port = htons(oport);
  memcpy(&oaddr.sin_addr, h->h_addr, h->h_length);
  if (connect(osock, &oaddr, sizeof(oaddr))) {
    fprintf(cfile, "500 connect: %s\n", strerror(errno));
    goto quit1;
  }
  while (1) {
    FD_ZERO(&fdsr);
    FD_ZERO(&fdse);
    FD_SET(csock,&fdsr);
    FD_SET(csock,&fdse);
    FD_SET(osock,&fdsr);
    FD_SET(osock,&fdse);
    if (select(20, &fdsr, NULL, &fdse, NULL) == -1) {
      fprintf(cfile, "500 select: %s\n", strerror(errno));
      goto quit2;
    }
    if (FD_ISSET(csock,&fdsr) || FD_ISSET(csock,&fdse)) {
      if ((nbyt = read(csock,buf,4096)) <= 0)
	goto quit2;
      if ((write(osock,buf,nbyt)) <= 0)
	goto quit2;
    } else if (FD_ISSET(osock,&fdsr) || FD_ISSET(osock,&fdse)) {
      if ((nbyt = read(osock,buf,4096)) <= 0)
	goto quit2;
      if ((write(csock,buf,nbyt)) <= 0)
	goto quit2;
    }
  }

 quit2:
  shutdown(osock,2);
  close(osock);
 quit1:
  fflush(cfile);
  shutdown(csock,2);
 quit0:
  fclose(cfile);
  return 0;
}


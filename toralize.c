/* toralizer.c */

#include "toralize.h"

Req *request(struct sockaddr_in *sock2)
{
  Req *req;

  req = malloc(reqsize);
  req->vn = 4;                               // version number
  req->cd = 1;                               // command code
  req->dstport = sock2->sin_port;            // destination port
  req->dstip = sock2->sin_addr.s_addr;       // destination IP
  strncpy((char *)req->userid, USERNAME, 8); // user ID
  /*
    In the whole project there are some attributes or variables
    which in string type with specific length like `USERNAME`,
    in function `strncpy` above, the length is 8
    but the value was defined (`toraliz`) is 7 character length
    the left one is for `null terminator` (`\0`) character
  */
  return req;
}

int connect(int s2, const struct sockaddr *sock2, socklen_t address_len)
{
  Req *req;
  Res *res;
  struct sockaddr_in sock;

  int s;
  int success;
  int (*p)(int, const struct sockaddr *, socklen_t);

  char buf[ressize];

  // Assign funtion poiter to p with function name `connect`
  p = dlsym(RTLD_NEXT, "connect");

  /*
    AF_INET is a constant used in network programming
    to specify the address family for IPv4
    (Internet Protocol Version 4 | 32-bit).
    When creating a socket in programming languages
    (like C, C++, or Python),
    you must provide an "address family",
    and AF_INET represents IPv4 addresses.

    SOCK_STREAM: Indicates that this socket will use the TCP protocol
    (a reliable, connection-oriented data transmission protocol).
  */
  s = socket(AF_INET, SOCK_STREAM, 0);

  if (s < 0)
  {
    perror("Invalid socket"); // system error messages

    return -1;
  }

  // Specify the "family" of the address used for network communication
  sock.sin_family = AF_INET;

  /*
    The port number used for network communication.
    htons() ensures the correct byte order when transmitting data
    over the network
  */
  sock.sin_port = htons(PROXYPORT);

  // Internet address manipulation routines
  sock.sin_addr.s_addr = inet_addr(PROXY);

  /*
    (struct sockaddr *)&sock:
    sock is a sockaddr_in structure,
    containing information about the IP address and
    port number you want to connect to.
    sockaddr_in is a structure that contains detailed information
    for the IPv4 protocol.
    However, the connect function requires the address
    to be passed as a sockaddr (generic type),
    so we need to cast it to (struct sockaddr *) to ensure the correct format.

    sizeof(sock)
    The connect function needs to know the length of the address you are passing
    to ensure the connection is established correctly.

    Terminal command (tm) : man 2 connect
    Upon successful completion, a value of 0 is returned.
    Otherwise, a value of -1 is returned and
    the global integer variable errno is set to indicate the error.

    Prerequisite: Your device must be installed `tor`
    to run toralize

    PROXY and PROXY_PORT which were declared
    in toralize.h
    127.0.0.1 9050 is the default port value of tor
  */
  if (p(s, (struct sockaddr *)&sock, sizeof(sock)))
  {
    perror("Connect failed\n");

    return -1;
  }

  printf("Connect to proxy\n");

  req = request((struct sockaddr_in *)sock2);
  write(s, req, reqsize);  // send request to socket s
  memset(buf, 0, ressize); // initialize buf data

  if (read(s, buf, ressize) < 1) // assign request response to buf
  {
    perror("Read buffer error");

    free(req); // free up memory
    close(s);  // close socket s

    return -1;
  }

  res = (Res *)buf;
  success = (res->cd == 90); // 90: request granted

  if (!success)
  {
    fprintf(stderr, "Unable to traverse the proxy, error code: %d\n", res->cd);

    free(req);
    close(s);

    return -1;
  }

  printf("Connect through the proxy.\n");

  /*
  Duplicate s to s2.
  This action keep s is always be the original socket
  */
  dup2(s, s2);
  free(req);

  return 0;
}

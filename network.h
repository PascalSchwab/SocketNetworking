#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define ERROR 1
#define SUCCESS 0

#include "src/socket.h"
#include "src/client.h"
#include "src/server.h"

#endif
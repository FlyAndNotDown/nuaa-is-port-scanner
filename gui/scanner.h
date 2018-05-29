#ifndef SCANNER_H
#define SCANNER_H

#endif // SCANNER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>

// 端口范围
#define MIN_PORT_NUM 0
#define MAX_PORT_NUM 65535

// tcp connect 扫描
int tcp_connect_scan(char *, int);
// 判断ip地址是否合法
int is_ip_address_legal(char *);

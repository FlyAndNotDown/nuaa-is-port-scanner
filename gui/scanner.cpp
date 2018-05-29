#include "scanner.h"

int tcp_connect_scan(char *ip, int port) {
    int sockfd, len, fcntl_status, connect_status;
    struct sockaddr_in addr;
    // 超时
    struct timeval timeout;
    fd_set fdr, fdw;

    // 将地址结构体清零
    memset(&addr, 0, sizeof(addr));
    memset(&timeout, 0, sizeof(timeout));

    // 设置为IP通信
    addr.sin_family = AF_INET;
    // 设置地址结构体中的IP地址
    addr.sin_addr.s_addr = inet_addr(ip);
    // 设置地址结构体中的端口号
    addr.sin_port = htons(port);

    // 创建socket套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // 如果失败则返回false
        return 0;
    }

    // 设置套接字为非阻塞
    fcntl_status = fcntl(sockfd, F_GETFL, 0);
    if (fcntl_status < 0) {
        close(sockfd);
        return 0;
    }
    fcntl_status |= O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, fcntl_status) < 0) {
        close(sockfd);
        return 0;
    }

    // 尝试连接
    connect_status = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if (connect_status != 0) {
        if (errno == EINPROGRESS) {
            FD_ZERO(&fdr);
            FD_ZERO(&fdw);
            FD_SET(sockfd, &fdr);
            FD_SET(sockfd, &fdw);
            // 设置1s超时
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;
            connect_status = select(sockfd + 1, &fdr, &fdw, NULL, &timeout);

            // 如果连接超时或者调用失败
            if (connect_status <= 0 || connect_status == 2) {
                close(sockfd);
                return 0;
            }

            // 如果连接成功
            if (connect_status == 1 && FD_ISSET(sockfd, &fdw)) {
                close(sockfd);
                return 1;
            }
            close(sockfd);
            return 0;
        }
    }

    return 1;

    // // 尝试建立连接
    // if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
    //     // 连接失败则返回false
    //     return 0;
    // } else {
    //     // 连接成功则关闭socket套接字返回true
    //     close(sockfd);
    //     return 1;
    // }
}

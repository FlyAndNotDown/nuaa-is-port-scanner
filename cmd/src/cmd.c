#include "../include/cmd.h"

typedef struct {
    int pthread_num;
    char *ip;
    int port;
    int end;
} scan_thread_args, *scan_thread_args_ptr;

void *scan_thread(void *);

int main(int argc, char *argv[]) {
    pthread_t *pthreads;
    scan_thread_args_ptr args_array;
    int i, pthread_num;

    if (argc < 5) {
        printf("Usage: ./scanner_cmd ip startPort endPort threadNum\n");
        printf("Example: ./scanner_cmd 127.0.0.1 0 65535 8\n");
        return 0;
    }

    pthread_num = atoi(argv[4]);
    if (pthread_num > 100) {
        printf("You can't want to get so many pthread!\n");
        return 0;
    }
    pthreads = (pthread_t *) malloc(sizeof(pthread_t) * pthread_num);
    args_array = (scan_thread_args_ptr) malloc(sizeof(scan_thread_args) * pthread_num);

    for (i = 0; i < pthread_num; i++) {
        memset(&args_array[i], 0, sizeof(args_array[i]));
        args_array[i].pthread_num = pthread_num;
        args_array[i].port = atoi(argv[2]) + i;
        args_array[i].ip = argv[1];
        args_array[i].end = atoi(argv[3]);

        if (pthread_create(&pthreads[i], NULL, scan_thread, (void *) &args_array[i]) == -1) {
            printf("Can't create pthread! Please try again!\n");
            return 0;
        }
    }

    // 睡一会，让子线程先运行
    sleep(1);

    // 等待线程释放
    for (i = 0; i < pthread_num; i++) {
        pthread_join(pthreads[i], NULL);
    }

    free(pthreads);
    free(args_array);

    return 0;
}

void *scan_thread(void *args) {
    scan_thread_args_ptr temp;
    temp = (scan_thread_args_ptr) args;

    while (temp->port <= temp->end) {
        if (tcp_connect_scan(temp->ip, temp->port)) {
            printf("Port %d - Open\n", temp->port);
        }

        temp->port += temp->pthread_num;
    }
}
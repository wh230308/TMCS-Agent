#include <hzchangrong-tmcs-mib/net/server_api.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <WinSock2.h>
#include <process.h>
#else
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#endif // WIN32
#include <hzchangrong-tmcs-mib/common.h>
#include <hzchangrong-tmcs-mib/net/io_handler.h>

#ifdef WIN32
#pragma warning(disable: 4996)

SOCKET sock_listen;
HANDLE h_thread;
unsigned int __stdcall network_routine(void *);
#else
int sock_listen;
pthread_t network_tid;
void *network_routine(void *arg);
#endif


void init_server_api(void)
{
    start("0.0.0.0", 3000);
}

int start(const char *serv_ip, unsigned short port)
{
    int ret, optval;
    struct sockaddr_in serv_addr;

    sock_listen = socket(AF_INET, SOCK_STREAM, 0);
#ifdef WIN32
    if (INVALID_SOCKET == sock_listen) {
#else
    if (sock_listen < 0) {
#endif
        printf("Failed to create socket, errno:%d.\n", errno);
        return TMCS_ERR_CREATE_SOCK;
    }

    optval = 1;
    ret = setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(optval));
#ifdef WIN32
    if (SOCKET_ERROR == ret) {
#else
    if (ret < 0) {
#endif
        printf("Failed to set socket SO_REUSEADDR option, errno:%d.\n", errno);
        return TMCS_ERR_SET_SOCK_OPT;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(serv_ip);

    do {
        ret = bind(sock_listen, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
#ifdef WIN32
        if (SOCKET_ERROR == ret) {
#else
        if (ret < 0) {
#endif
            printf("Failed to bind socket, errno:%d.\n", errno);
            ret = TMCS_ERR_BIND_SOCK;
            break;
        }

        ret = listen(sock_listen, 5);
#ifdef WIN32
        if (SOCKET_ERROR == ret) {
#else
        if (ret < 0) {
#endif
            printf("Failed to listen for socket, errno:%d.\n", errno);
            ret = TMCS_ERR_LISTEN_SOCK;
            break;
        }


#ifdef WIN32
        uintptr_t handle = _beginthreadex(NULL, 0, network_routine, NULL, CREATE_SUSPENDED, NULL);
        if (-1 == handle) {
#else
        ret = pthread_create(&network_tid, NULL, network_routine, NULL);
        if (ret != 0) {
#endif
            printf("Failed to create network thread, errno:%d.\n", errno);
            ret = TMCS_ERR_CREATE_THREAD;
            break;
        }

#ifdef WIN32
        h_thread = (HANDLE)handle;
        ResumeThread(h_thread);
#endif // WIN32
        return TMCS_NO_ERROR;
    } while (0);

#ifdef WIN32
    closesocket(sock_listen);
#else
    close(sock_listen);
#endif
    return ret;
}

void stop()
{
#ifdef WIN32
#else
    pthread_cancel(network_tid);
    close(sock_listen);
#endif
}

int send_packet(int fd, const char *data, int size)
{
    return send(fd, data, size, 0);
}

#ifdef WIN32
unsigned int __stdcall network_routine(void * arg)
#else
void *network_routine(void *arg)
#endif
{
    int i, ret, max_fd, conn_fd, sock_fd;
    int max_idx, client[FD_SETSIZE];
    fd_set rd_set, all_set;
    struct sockaddr_in cli_addr;
    char recv_buf[RECV_BUF_SIZE];
#ifdef WIN32
    int cli_len, bytes_recv;
#else
    socklen_t cli_len;
    ssize_t bytes_recv;
#endif

    printf("network_routine...\n");

    max_fd = sock_listen;
    max_idx = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;
    FD_ZERO(&all_set);
    FD_SET(sock_listen, &all_set);

    for (;;) {
        rd_set = all_set;
        ret = select(max_fd + 1, &rd_set, NULL, NULL, NULL);
        if (ret > 0) {
            if (FD_ISSET(sock_listen, &rd_set)) {
                cli_len = sizeof(cli_addr);
                conn_fd = accept(sock_listen, (struct sockaddr *)&cli_addr, &cli_len);

                for (i = 0; i < FD_SETSIZE; i++) {
                    if (client[i] < 0) {
                        client[i] = conn_fd;
                        break;
                    }
                }

                if (i == FD_SETSIZE) {
                    printf("too much clients, errno:%d.\n", errno);
                    continue;
                }

                FD_SET(conn_fd, &all_set);
                on_connected(conn_fd);
                if (conn_fd > max_fd)
                    max_fd = conn_fd;

                if (i > max_idx)
                    max_idx = i;

                if (--ret <= 0)
                    continue;
            }

            for (i = 0; i <= max_idx; i++) {
                if ((sock_fd = client[i]) < 0)
                    continue;

                if (FD_ISSET(sock_fd, &rd_set)) {
                    if ((bytes_recv = recv(sock_fd, (void *)recv_buf, sizeof(recv_buf), 0)) == 0) {
                        FD_CLR(sock_fd, &all_set);
                        on_closed(sock_fd);
                    } else {
                        on_recv(sock_fd, recv_buf, bytes_recv);
                    }

                    if (--ret <= 0)
                        break;
                }
            }
        } else {
            printf("select, errno:%d.\n", errno);
            break;
        }
    }

    return 0;
}

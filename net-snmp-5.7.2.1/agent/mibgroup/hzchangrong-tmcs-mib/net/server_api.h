#ifndef SERVER_API_H
#define SERVER_API_H

#define TMCS_NO_ERROR                   (0)
#define TMCS_ERR_CREATE_SOCK            (1)
#define TMCS_ERR_BIND_SOCK              (2)
#define TMCS_ERR_LISTEN_SOCK            (3)
#define TMCS_ERR_SET_SOCK_OPT           (4)
#define TMCS_ERR_CREATE_THREAD          (100)
#define TMCS_ERR_PKT_COMPLETE           (200)
#define TMCS_ERR_HEAD_INVALID           (201)
#define TMCS_ERR_HEAD_INCOMPLETE        (202)
#define TMCS_ERR_PACKET_INCOMPLETE      (203)

#define RECV_BUF_SIZE (1024 * 256)
#define PKT_BUF_SIZE (1024 * 128)

void init_server_api(void);
int start(const char *serv_ip, unsigned short port);
void stop();
int send_packet(int fd, const char *data, int size);

#endif // SERVER_API_H

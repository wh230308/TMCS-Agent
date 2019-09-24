#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <time.h>
#ifndef WIN32
#include <sys/types.h>
#endif // WIN32

typedef struct _ClientIoData
{
    int fd;                  // socket
    char *packet_buf;        // 业务包缓冲区
    size_t packet_size;      // 业务包缓冲区当前有效字节数
    time_t last_active_time; // 上次活动时间，用于检查心跳超时
    struct _ClientIoData *next;
} ClientIoData, *PClientIoData;

extern PClientIoData cli_io_data_head;

void on_connected(int fd);
void on_recv(int fd, const char *data, size_t size);
void on_closed(int fd);
void on_error(int fd);
PClientIoData add_ClientIoData(int fd);
void remove_ClientIoData(int fd);
PClientIoData find_ClientIoData(int fd);
void clear_ClientIoData();

#endif // IO_HANDLER_H
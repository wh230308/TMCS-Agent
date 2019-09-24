#include <hzchangrong-tmcs-mib/net/io_handler.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hzchangrong-tmcs-mib/common.h>
#include <hzchangrong-tmcs-mib/net/proto_def.h>
#include <hzchangrong-tmcs-mib/net/server_api.h>
#include <hzchangrong-tmcs-mib/net/packet_handler.h>

PClientIoData cli_io_data_head;
int parse_packet(PClientIoData, const char *, size_t);

void on_connected(int fd)
{
    printf("[%d]|%s\n", fd, __FUNCTION__);
    add_ClientIoData(fd);
    get_dev_info(fd);
    get_mpu_info(fd);
    get_riu_info(fd);
    get_cwp_info(fd);
}

void on_recv(int fd, const char *data, size_t size)
{
    printf("[%d]|%s\n", fd, __FUNCTION__);
    PClientIoData cli_io_data = find_ClientIoData(fd);
    if (!cli_io_data)
        return;

    parse_packet(cli_io_data, data, size);
}

void on_closed(int fd)
{
    printf("[%d]|%s\n", fd, __FUNCTION__);
    remove_ClientIoData(fd);
}

void on_error(int fd)
{
    printf("[%d]|%s\n", fd, __FUNCTION__);
}

PClientIoData add_ClientIoData(int fd)
{
    PClientIoData ptr;

    ptr = (PClientIoData)malloc(sizeof(ClientIoData));
    if (!ptr) {
        printf("%d:malloc error\n", __LINE__);
        return NULL;
    }

    ptr->fd = fd;
    ptr->packet_buf = (char *)malloc(sizeof(char) * PKT_BUF_SIZE);
    if (!ptr->packet_buf) {
        printf("%d:malloc error\n", __LINE__);
        return NULL;
    }

    ptr->packet_size = 0;
    ptr->last_active_time = time(NULL);
    ptr->next = cli_io_data_head;
    cli_io_data_head = ptr;
    return ptr;
}

void remove_ClientIoData(int fd)
{
    PClientIoData ptr, prev;

    for (ptr = cli_io_data_head, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
        if (ptr->fd == fd)
            break;
    }

    if (!ptr) {
        printf("Can't find the ClientIoData.\n");
        return;
    }

    if (!prev)
        cli_io_data_head = ptr->next;
    else
        prev->next = ptr->next;

#ifdef WIN32
    closesocket(fd);
#else
    close(fd);
#endif // WIN32

    free(ptr->packet_buf);
    free(ptr);
}

PClientIoData find_ClientIoData(int fd)
{
    PClientIoData ptr;

    for (ptr = cli_io_data_head; ptr != NULL; ptr = ptr->next) {
        if (ptr->fd == fd)
            break;
    }

    if (!ptr)
        printf("Can't find the ClientIoData.\n");

    return ptr;
}

void clear_ClientIoData()
{
    PClientIoData ptr;

    for (ptr = cli_io_data_head; ptr != NULL; ptr = ptr->next) {
        close(ptr->fd);
        free(ptr->packet_buf);
        free(ptr);
    }
}

int parse_packet(PClientIoData cli_io_data, const char *data, size_t size)
{
    size_t offset, cp_size, left_size;
    int ret;

    offset = 0;
    left_size = size;

    printf("[%d]|recv data size: %d， last packet size: %d\n", cli_io_data->fd, left_size, cli_io_data->packet_size);

    if (cli_io_data->packet_size > 0) {
        // 4.packet_size小于业务包头长度，继续接收网络包，填满业务包头
        if (cli_io_data->packet_size < sizeof(PacketHead)) {
            printf("4.packet_size小于业务包头长度，继续接收网络包，填满业务包头\n");
            cp_size = MIN(sizeof(PacketHead) - cli_io_data->packet_size, left_size);
            memcpy(cli_io_data->packet_buf + cli_io_data->packet_size, data, cp_size);
            cli_io_data->packet_size += cp_size;
            left_size -= cp_size;

            if (cli_io_data->packet_size < sizeof(PacketHead))
                return TMCS_ERR_HEAD_INCOMPLETE;
        }


        PacketHead *head = (PacketHead *)cli_io_data->packet_buf;
        // 5.1.剩余的网络包包头size字段非法(size <= 0)，packet_size置0
        if (head->size <= 0) {
            cli_io_data->packet_size = 0;
            return TMCS_ERR_HEAD_INVALID;
        }

        // 5.2.packet_size + left_size小于一个完整的业务包长度时，继续接收网络包，填满一个完整的业务包
        if (cli_io_data->packet_size + left_size < head->size) {
            printf("5.packet_size + left_size小于一个完整的业务包长度时，继续接收网络包，填满一个完整的业务包\n");
            memcpy(cli_io_data->packet_buf + cli_io_data->packet_size, data, left_size);
            cli_io_data->packet_size += left_size;
            return TMCS_ERR_PACKET_INCOMPLETE;
        }

        // 6.packet_size + left_size大于或等于一个完整的业务包长度时，填满一个完整的业务包，从packet_buf中处理
        // 剩余部分从data处理
        cp_size = head->size - cli_io_data->packet_size;
        memcpy(cli_io_data->packet_buf + cli_io_data->packet_size, data, cp_size);
        process_packet(cli_io_data->fd, cli_io_data->packet_buf, head->size);
        if (cli_io_data->packet_size + left_size == head->size) {
            printf("6.packet_size + left_size等于一个完整的业务包长度\n");
            cli_io_data->packet_size = 0;
            return TMCS_ERR_PKT_COMPLETE;
        }

        printf("6.packet_size + left_size大于一个完整的业务包长度，，填满一个完整的业务包，从packet_buf中处理，剩余部分从data处理\n");
        offset = cp_size;
        left_size -= cp_size;
    }

    // 当收到的网络包大于一个完整的业务包长度时，需要循环处理
    while (1) {
        // 1.剩余的网络包小于业务包头长度，存放到packet_buf中
        if (left_size < sizeof(PacketHead)) {
            printf("1.剩余的网络包小于业务包头长度，存放到packet_buf中\n");
            memcpy(cli_io_data->packet_buf, data + offset, left_size);
            cli_io_data->packet_size = left_size;
            ret = TMCS_ERR_HEAD_INCOMPLETE;
            break;
        }


        PacketHead *head = (PacketHead *)(data + offset);
        // 2.1.剩余的网络包包头size字段非法(size <= 0)，packet_size置0
        if (head->size <= 0) {
            cli_io_data->packet_size = 0;
            ret = TMCS_ERR_HEAD_INVALID;
            break;
        }

        // 2.2.剩余的网络包小于一个完整的业务包长度时，存放到packet_buf中
        if (left_size < head->size) {
            printf("2.剩余的网络包小于一个完整的业务包长度时，存放到packet_buf中\n");
            memcpy(cli_io_data->packet_buf, data + offset, left_size);
            cli_io_data->packet_size = left_size;
            ret = TMCS_ERR_PACKET_INCOMPLETE;
            break;
        }

        // 3.剩余的网络包大于或等于一个完整的业务包长度时，直接从data处理
        process_packet(cli_io_data->fd, data, head->size);
        if (left_size == head->size) {
            printf("3.剩余的网络包等于一个完整的业务包长度\n");
            cli_io_data->packet_size = 0;
            ret = TMCS_ERR_PKT_COMPLETE;
            break;
        } else {
            printf("3.剩余的网络包大于一个完整的业务包长度\n");
            offset += head->size;
            left_size -= head->size;
        }
    }

    return ret;
}

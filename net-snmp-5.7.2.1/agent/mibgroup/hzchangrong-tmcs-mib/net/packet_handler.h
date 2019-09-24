#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#ifndef WIN32
#include <sys/types.h>
#endif // WIN32

void init_packet_handler(void);
void process_packet(int fd, const char *data, size_t size);
int get_dev_info(int fd);
int get_mpu_info(int fd);
int get_riu_info(int fd);
int get_cwp_info(int fd);

#endif // PACKET_HANDLER_H
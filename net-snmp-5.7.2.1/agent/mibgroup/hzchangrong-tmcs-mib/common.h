#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#ifdef WIN32
#include <Winsock2.h>
#else
#include <errno.h>
#endif // WIN32

#define MIN(x, y)                   (((x) < (y)) ? (x) : (y))
#define DEV_NAME_LEN                (16)
#define CWP_USER_NAME_LEN           (32)
#define CWP_PHONE_LEN               (32)
#define CWP_ROLES_LEN               (96)

#define COPY_LEN(buf, size)         (('\0' == buf[size - 1]) ? strlen(buf) : sizeof(buf))
#ifdef WIN32
#define sys_errno WSAGetLastError();
#else
#define sys_errno errno;
#endif // WIN32



#endif // COMMON_H
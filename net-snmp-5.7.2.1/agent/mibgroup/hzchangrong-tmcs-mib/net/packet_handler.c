#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <hzchangrong-tmcs-mib/net/packet_handler.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/time.h>
#endif // WIN32
#include <hzchangrong-tmcs-mib/net/proto_def.h>
#include <hzchangrong-tmcs-mib/net/server_api.h>
#include <hzchangrong-tmcs-mib/net/io_handler.h>
#include <hzchangrong-tmcs-mib/management/devInfoTable.h>
#include <hzchangrong-tmcs-mib/management/mpuInfoTable.h>
#include <hzchangrong-tmcs-mib/management/riuInfoTable.h>
#include <hzchangrong-tmcs-mib/management/cwpInfoTable.h>
#include <hzchangrong-tmcs-mib/management/devInfoChange.h>
#include <hzchangrong-tmcs-mib/management/mpuInfoChange.h>
#include <hzchangrong-tmcs-mib/management/riuInfoChange.h>
#include <hzchangrong-tmcs-mib/management/cwpInfoChange.h>
#include <hzchangrong-tmcs-mib/management/riuPortsStatus.h>
#include <hzchangrong-tmcs-mib/management/phoneBtnInfos.h>
#include <hzchangrong-tmcs-mib/management/radioBtnInfos.h>
#include <hzchangrong-tmcs-mib/management/funcBtnInfos.h>
#include <hzchangrong-tmcs-mib/management/callRecords.h>
#include <hzchangrong-tmcs-mib/management/liuEthStatus.h>
#include <hzchangrong-tmcs-mib/management/cwpEthStatus.h>
#include <hzchangrong-tmcs-mib/management/cwpPowerStatus.h>

#define KEEPALIVE_INTERVAL (5)

#ifdef WIN32
#else
pthread_t keepalive_tid;
#endif // WIN32

int dev_info_changed = 0;
int mpu_info_changed = 0;
int riu_info_changed = 0;
int cwp_info_changed = 0;

void *keepalive_routine(void *);
void on_keepalive(int);
void on_get_dev_info_ack(int, const char *, size_t);
void on_get_mpu_info_ack(int, const char *, size_t);
void on_get_riu_info_ack(int, const char *, size_t);
void on_get_cwp_info_ack(int, const char *, size_t);
void on_report_dev_info_change(int, const char *, size_t);
void on_report_mpu_info_change(int, const char *, size_t);
void on_report_riu_info_change(int, const char *, size_t);
void on_report_cwp_info_change(int, const char *, size_t);
void on_report_riu_port_status(int, const char *, size_t);
void on_report_button_info(int, const char *, size_t);
void on_report_call_records(int, const char *, size_t);
void on_report_liu_eth_status(int, const char *, size_t);
void on_report_cwp_eth_status(int, const char *, size_t);
void on_report_power_eth_status(int, const char *, size_t);
void on_report_network_capability(int, const char *, size_t);
void on_report_network_traffic(int, const char *, size_t);
void on_report_hardware_status(int, const char *, size_t);
void on_report_application_status(int, const char *, size_t);
void on_report_user_operation(int, const char *, size_t);
void on_report_telephone_traffic(int, const char *, size_t);
void on_report_cwp_func_btn_status(int, const char *, size_t);

void init_packet_handler(void)
{
    // int ret = pthread_create(&keepalive_tid, NULL, keepalive_routine, NULL);
    // if (ret != 0)
    //     printf("Failed to create keepalive thread, errno:%d.\n", errno);
}

void process_packet(int fd, const char *data, size_t size)
{
    PacketHead *head = (PacketHead *)data;
    if (head->type == kKeepalive) {
        on_keepalive(fd);
    } else if (head->type == kGetDevInfoAck) {
        on_get_dev_info_ack(fd, data, size);
    } else if (head->type == kGetMpuInfoAck) {
        on_get_mpu_info_ack(fd, data, size);
    } else if (head->type == kGetRiuInfoAck) {
        on_get_riu_info_ack(fd, data, size);
    } else if (head->type == kGetCwpInfoAck) {
        on_get_cwp_info_ack(fd, data, size);
    } else if (head->type == kReportDevInfoChange) {
        on_report_dev_info_change(fd, data, size);
    } else if (head->type == kReportMpuInfoChange) {
        on_report_mpu_info_change(fd, data, size);
    } else if (head->type == kReportRiuInfoChange) {
        on_report_riu_info_change(fd, data, size);
    } else if (head->type == kReportCwpInfoChange) {
        on_report_cwp_info_change(fd, data, size);
    } else if (head->type == kReportRiuPortStatus) {
        on_report_riu_port_status(fd, data, size);
    } else if (head->type == kReportButtonInfo) {
        on_report_button_info(fd, data, size);
    } else if (head->type == kReportCallRecords) {
        on_report_call_records(fd, data, size);
    } else if (head->type == kReportLiuEthStatus) {
        on_report_liu_eth_status(fd, data, size);
    } else if (head->type == kReportCwpEthStatus) {
        on_report_cwp_eth_status(fd, data, size);
    } else if (head->type == kReportCwpPowerStatus) {
        on_report_power_eth_status(fd, data, size);
    } else if (head->type == kReportNetworkCapability) {
        on_report_network_capability(fd, data, size);
    } else if (head->type == kReportNetworkTraffic) {
        on_report_network_traffic(fd, data, size);
    } else if (head->type == kReportHardwareStatus) {
        on_report_hardware_status(fd, data, size);
    } else if (head->type == kReportApplicationStatus) {
        on_report_application_status(fd, data, size);
    } else if (head->type == kReportUserOperation) {
        on_report_user_operation(fd, data, size);
    } else if (head->type == kReportTelephoneTraffic) {
        on_report_telephone_traffic(fd, data, size);
    } else if (head->type == kReportCwpFuncBtnStatus) {
        on_report_cwp_func_btn_status(fd, data, size);
    } else {
        printf("Unknown packet type.\n");
    }
}

void *keepalive_routine(void *arg)
{
    struct timeval tval;
    PClientIoData ptr;

    while (1) {
        tval.tv_sec = 5;
        tval.tv_usec = 0;
        int ret = select(0, NULL, NULL, NULL, &tval);
        if (ret < 0) {
            printf("select error.\n");
            return NULL;
        }

        for (ptr = cli_io_data_head; ptr != NULL; ptr = ptr->next) {
            time_t cur_time = time(NULL);
            if (cur_time - ptr->last_active_time > KEEPALIVE_INTERVAL * 3) {
                printf("Client timeout.\n");
                remove_ClientIoData(ptr->fd);
            }
        }
    }
}

void on_keepalive(int fd)
{
    printf("on_keepalive\n");
    PClientIoData ptr;

    for (ptr = cli_io_data_head; ptr != NULL; ptr = ptr->next) {
        if (ptr->fd == fd) {
            ptr->last_active_time = time(NULL);
            break;
        }
    }
}

int get_dev_info(int fd)
{
    PacketGetDevInfo src_pkt;
    src_pkt.head.id = 0;
    src_pkt.head.type = kGetDevInfo;
    src_pkt.head.size = sizeof(PacketGetDevInfo);
    src_pkt.head.token = 0;
    return send_packet(fd, (const char *)&src_pkt, src_pkt.head.size);
}

void on_get_dev_info_ack(int fd, const char *data, size_t size)
{
    const PacketGetDevInfoAck *recv_pkt = (const PacketGetDevInfoAck *)data;
    devInfoTable_createEntry(recv_pkt);
    if (dev_info_changed) {
        dev_info_changed = 0;
        send_devInfoChange_trap();
    }
}

int get_mpu_info(int fd)
{
    PacketGetMpuInfo src_pkt;
    src_pkt.head.id = 0;
    src_pkt.head.type = kGetMpuInfo;
    src_pkt.head.size = sizeof(PacketGetMpuInfo);
    src_pkt.head.token = 0;
    return send_packet(fd, (const char *)&src_pkt, src_pkt.head.size);
}

void on_get_mpu_info_ack(int fd, const char *data, size_t size)
{
    const PacketGetMpuInfoAck *recv_pkt = (const PacketGetMpuInfoAck *)data;
    mpuInfoTable_createEntry(recv_pkt);
    if (mpu_info_changed) {
        mpu_info_changed = 0;
        send_mpuInfoChange_trap();
    }
}

int get_riu_info(int fd)
{
    PacketGetRiuInfo src_pkt;
    src_pkt.head.id = 0;
    src_pkt.head.type = kGetRiuInfo;
    src_pkt.head.size = sizeof(PacketGetRiuInfo);
    src_pkt.head.token = 0;
    return send_packet(fd, (const char *)&src_pkt, src_pkt.head.size);
}

void on_get_riu_info_ack(int fd, const char *data, size_t size)
{
    const PacketGetRiuInfoAck *recv_pkt = (const PacketGetRiuInfoAck *)data;
    riuInfoTable_createEntry(recv_pkt);
    if (riu_info_changed) {
        riu_info_changed = 0;
        send_riuInfoChange_trap();
    }
}

int get_cwp_info(int fd)
{
    PacketGetCwpInfo src_pkt;
    src_pkt.head.id = 0;
    src_pkt.head.type = kGetCwpInfo;
    src_pkt.head.size = sizeof(PacketGetCwpInfo);
    src_pkt.head.token = 0;
    return send_packet(fd, (const char *)&src_pkt, src_pkt.head.size);
}

void on_get_cwp_info_ack(int fd, const char *data, size_t size)
{
    const PacketGetCwpInfoAck *recv_pkt = (const PacketGetCwpInfoAck *)data;
    cwpInfoTable_createEntry(recv_pkt);
    if (cwp_info_changed) {
        cwp_info_changed = 0;
        send_cwpInfoChange_trap();
    }
}

void on_report_dev_info_change(int fd, const char *data, size_t size)
{
    const PacketReportDevInfoChange *recv_pkt = (const PacketReportDevInfoChange *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    if (get_dev_info(fd))
        dev_info_changed = 1;

    // printf("send buttton info\n");
    // PhoneButtonInfo phone_btn_info[2];
    // phone_btn_info[0].btn_num = 1;
    // strncpy(phone_btn_info[0].name, "phone1", strlen("phone1") + 1);
    // strncpy(phone_btn_info[0].phone_num, "10086", strlen("10086") + 1);
    // phone_btn_info[0].is_dialog = 0;
    // phone_btn_info[0].can_use = 1;
    // phone_btn_info[0].type = 7;
    // phone_btn_info[1].btn_num = 2;
    // strncpy(phone_btn_info[1].name, "phone2", strlen("phone2") + 1);
    // strncpy(phone_btn_info[1].phone_num, "10010", strlen("10010") + 1);
    // phone_btn_info[1].is_dialog = 0;
    // phone_btn_info[1].can_use = 1;
    // phone_btn_info[1].type = 2;

    // RadioButtonInfo radio_btn_info[3];
    // radio_btn_info[0].btn_num = 1;
    // strncpy(radio_btn_info[0].name, "radio1", strlen("radio1") + 1);
    // strncpy(radio_btn_info[0].frequency, "fm1019", strlen("fm1019") + 1);
    // radio_btn_info[0].lifesaving = 1;
    // radio_btn_info[0].can_use = 1;
    // radio_btn_info[1].btn_num = 2;
    // strncpy(radio_btn_info[1].name, "radio2", strlen("radio2") + 1);
    // strncpy(radio_btn_info[1].frequency, "fm1020", strlen("fm1020") + 1);
    // radio_btn_info[1].lifesaving = 0;
    // radio_btn_info[1].can_use = 0;
    // radio_btn_info[2].btn_num = 3;
    // strncpy(radio_btn_info[2].name, "radio3", strlen("radio3") + 1);
    // strncpy(radio_btn_info[2].frequency, "fm1021", strlen("fm1021") + 1);
    // radio_btn_info[2].lifesaving = 0;
    // radio_btn_info[2].can_use = 1;

    // FuncButtonInfo func_btn_info[1];
    // func_btn_info[0].btn_num = 1;
    // strncpy(func_btn_info[0].name, "func1", strlen("func1") + 1);
    // func_btn_info[0].type = 0;

    // PacketReportButtonInfo src_pkt;
    // printf("PacketReportButtonInfo size:%d", sizeof(PacketReportButtonInfo));
    // src_pkt.head.id = 0;
    // src_pkt.head.type = kReportButtonInfo;
    // src_pkt.head.size = 16 + 4 + 4 + sizeof(PhoneButtonInfo) * 2 + 4 + sizeof(RadioButtonInfo) * 3 + 4 + sizeof(FuncButtonInfo);
    // printf("[%d:%s]|packet size: %d\n", fd, __FUNCTION__, src_pkt.head.size);
    // src_pkt.head.token = 0;
    // src_pkt.cwp_num = 1;
    // src_pkt.phone_btn_counts = 2;
    // src_pkt.phone_btn_info = phone_btn_info;
    // src_pkt.radio_btn_counts = 3;
    // src_pkt.radio_btn_info = radio_btn_info;
    // src_pkt.func_btn_counts = 1;
    // src_pkt.func_btn_info = func_btn_info;

    // char buf[1024 * 128];
    // size_t offset, len;

    // offset = 0;
    // len = sizeof(src_pkt.head);
    // memcpy(buf + offset, &src_pkt.head, len);

    // offset += len;
    // len = sizeof(src_pkt.cwp_num);
    // memcpy(buf + offset, &src_pkt.cwp_num, len);

    // offset += len;
    // len = sizeof(src_pkt.phone_btn_counts);
    // memcpy(buf + offset, &src_pkt.phone_btn_counts, len);

    // offset += sizeof(src_pkt.phone_btn_counts);
    // len = sizeof(PhoneButtonInfo) * src_pkt.phone_btn_counts;
    // memcpy(buf + offset, src_pkt.phone_btn_info, len);

    // offset += len;
    // len = sizeof(src_pkt.radio_btn_counts);
    // memcpy(buf + offset, &src_pkt.radio_btn_counts, len);

    // offset += len;
    // len = sizeof(RadioButtonInfo) * src_pkt.radio_btn_counts;
    // memcpy(buf + offset, src_pkt.radio_btn_info, len);

    // offset += len;
    // len = sizeof(src_pkt.func_btn_counts);
    // memcpy(buf + offset, &src_pkt.func_btn_counts, len);

    // offset += len;
    // len = sizeof(FuncButtonInfo) * src_pkt.func_btn_counts;
    // memcpy(buf + offset, src_pkt.func_btn_info, len);

    // send_packet(fd, (const char *)&buf, src_pkt.head.size);
}

void on_report_mpu_info_change(int fd, const char *data, size_t size)
{
    const PacketReportMpuInfoChange *recv_pkt = (const PacketReportMpuInfoChange *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    if (get_mpu_info(fd))
        mpu_info_changed = 1;
}

void on_report_riu_info_change(int fd, const char *data, size_t size)
{
    const PacketReportRiuInfoChange *recv_pkt = (const PacketReportRiuInfoChange *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    if (get_riu_info(fd))
        riu_info_changed = 1;
}
void on_report_cwp_info_change(int fd, const char *data, size_t size)
{
    const PacketReportCwpInfoChange *recv_pkt = (const PacketReportCwpInfoChange *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    if (get_cwp_info(fd))
        cwp_info_changed = 1;
}

void on_report_riu_port_status(int fd, const char *data, size_t size)
{
    const PacketReportRiuPortStatus *recv_pkt = (const PacketReportRiuPortStatus *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    send_riuPortsStatus_trap((const PacketReportRiuPortStatus *)data);
}

void on_report_button_info(int fd, const char *data, size_t size)
{
    const PacketHead *head = (const PacketHead *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, head->type);

    size_t offset = 0;
    int i, cwp_num, phone_btn_counts, radio_btn_counts, func_btn_counts;

    offset += sizeof(PacketHead);
    cwp_num = *(int *)(data + offset);
    printf("cwp_num: %d\n", cwp_num);

    offset += sizeof(cwp_num);
    phone_btn_counts = *(int *)(data + offset);
    printf("phone_btn_counts: %d\n", phone_btn_counts);

    offset += sizeof(phone_btn_counts);
    for (i = 0; i < phone_btn_counts; i++) {
        PhoneButtonInfo *phone_btn_info = (PhoneButtonInfo *)(data + offset);
        printf("btn_num:%d, name:%s, phone_num:%s, is_dialog:%d, can_use:%d, type:%d\n",
            phone_btn_info->btn_num, phone_btn_info->name, phone_btn_info->phone_num,
            phone_btn_info->is_dialog, phone_btn_info->can_use, phone_btn_info->type);
        send_phoneBtnInfos_trap(cwp_num, phone_btn_info);
        offset += sizeof(PhoneButtonInfo);
    }

    radio_btn_counts = *(int *)(data + offset);
    printf("radio_btn_counts: %d\n", radio_btn_counts);

    offset += sizeof(radio_btn_counts);
    for (i = 0; i < radio_btn_counts; i++) {
        RadioButtonInfo *radio_btn_info = (RadioButtonInfo *)(data + offset);
        printf("btn_num:%d, name:%s, frequency:%s, lifesaving:%d, can_use:%d\n",
            radio_btn_info->btn_num, radio_btn_info->name, radio_btn_info->frequency,
            radio_btn_info->lifesaving, radio_btn_info->can_use);

        send_radioBtnInfos_trap(cwp_num, radio_btn_info);
        offset += sizeof(RadioButtonInfo);
    }

    func_btn_counts = *(int *)(data + offset);
    printf("func_btn_counts: %d\n", func_btn_counts);

    offset += sizeof(func_btn_counts);
    for (i = 0; i < func_btn_counts; i++) {
        FuncButtonInfo *func_btn_info = (FuncButtonInfo *)(data + offset);
        printf("btn_num:%d, name:%s, type:%d\n",
            func_btn_info->btn_num, func_btn_info->name, func_btn_info->type);

        send_funcBtnInfos_trap(cwp_num, func_btn_info);
        offset += sizeof(FuncButtonInfo);
    }
}

void on_report_call_records(int fd, const char *data, size_t size)
{
    const PacketReportCallRecords *recv_pkt = (const PacketReportCallRecords *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    // send_callRecords_trap((const PacketReportCallRecords *)data);
    printf("is_connected:%d, business_type:%d, business_id:%s, cause_of_release:%d, "
        "calling_num:%s, called_num:%s, thirdparty_num:%s, incoming_time:%lld, start_time:%lld, end_time:%lld\n",
        recv_pkt->is_connected, recv_pkt->business_type, recv_pkt->business_id, recv_pkt->cause_of_release,
        recv_pkt->calling_num, recv_pkt->called_num, recv_pkt->thirdparty_num, recv_pkt->incoming_time,
        recv_pkt->start_time, recv_pkt->end_time);
    send_callRecords_trap((const PacketReportCallRecords *)data);
}

void on_report_liu_eth_status(int fd, const char *data, size_t size)
{
    const PacketReportLiuEthStatus *recv_pkt = (const PacketReportLiuEthStatus *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    send_liuEthStatus_trap((const PacketReportLiuEthStatus *)data);
}

void on_report_cwp_eth_status(int fd, const char *data, size_t size)
{
    const PacketReportCwpEthStatus *recv_pkt = (const PacketReportCwpEthStatus *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    send_cwpEthStatus_trap((const PacketReportCwpEthStatus *)data);
}

void on_report_power_eth_status(int fd, const char *data, size_t size)
{
    const PacketReportCwpPowerStatus *recv_pkt = (const PacketReportCwpPowerStatus *)data;
    printf("[%d:%s]|packet_type: %08x\n", fd, __FUNCTION__, recv_pkt->head.type);
    send_cwpPowerStatus_trap((const PacketReportCwpPowerStatus *)data);
}

void on_report_network_capability(int fd, const char *data, size_t size)
{
}

void on_report_network_traffic(int fd, const char *data, size_t size)
{
}

void on_report_hardware_status(int fd, const char *data, size_t size)
{
}

void on_report_application_status(int fd, const char *data, size_t size)
{
}

void on_report_user_operation(int fd, const char *data, size_t size)
{
}

void on_report_telephone_traffic(int fd, const char *data, size_t size)
{
}

void on_report_cwp_func_btn_status(int fd, const char *data, size_t size)
{
}

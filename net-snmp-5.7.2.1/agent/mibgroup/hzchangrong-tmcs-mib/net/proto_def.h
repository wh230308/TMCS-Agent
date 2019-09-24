#ifndef PROTO_DEF_H
#define PROTO_DEF_H

#define SERVER_PORT (3000)

#pragma pack(push, 4)

/* 心跳包 */
#define kKeepalive 0x00100000
#define kKeepaliveAck 0x80100000

/* 获取设备信息 */
#define kGetDevInfo 0x00100001
#define kGetDevInfoAck 0x80100001

/* 获取主控板信息 */
#define kGetMpuInfo 0x00100003
#define kGetMpuInfoAck 0x80100003

/* 获取用户板信息 */
#define kGetRiuInfo 0x00100005
#define kGetRiuInfoAck 0x80100005

/* 获取席位信息 */
#define kGetCwpInfo 0x00100007
#define kGetCwpInfoAck 0x80100007

/* 上报设备信息变更 */
#define kReportDevInfoChange 0x00100100
#define kReportDevInfoChangeAck 0x80100100

/* 上报主控板信息变更 */
#define kReportMpuInfoChange 0x00100101
#define kReportMpuInfoChangeAck 0x80100101

/* 上报用户板信息变更 */
#define kReportRiuInfoChange 0x00100102
#define kReportRiuInfoChangeAck 0x80100102

/* 上报席位信息变更 */
#define kReportCwpInfoChange 0x00100103
#define kReportCwpInfoChangeAck 0x80100103

/* 上报用户板端口状态 */
#define kReportRiuPortStatus 0x00100104
#define kReportRiuPortStatusAck 0x80100104

/* 上报席位按键信息 */
#define kReportButtonInfo 0x00100105
#define kReportButtonInfoAck 0x80100105

/* 上报通话记录 */
#define kReportCallRecords 0x00100106
#define kReportCallRecordsAck 0x80100106

/* 上报LIU网络状态 */
#define kReportLiuEthStatus 0x00100107
#define kReportLiuEthStatusAck 0x80100107

/* 上报席位网络状态 */
#define kReportCwpEthStatus 0x00100108
#define kReportCwpEthStatusAck 0x80100108

/* 上报席位电源状态 */
#define kReportCwpPowerStatus 0x00100109
#define kReportCwpPowerStatusAck 0x80100109

/* 上报网络性能参数 */
#define kReportNetworkCapability 0x00100110
#define kReportNetworkCapabilityAck 0x80100110

/* 上报网络流量信息 */
#define kReportNetworkTraffic 0x00100111
#define kReportNetworkTrafficAck 0x80100111

/* 上报硬件状态信息 */
#define kReportHardwareStatus 0x00100112
#define kReportHardwareStatusAck 0x80100112

/* 上报软件状态信息 */
#define kReportApplicationStatus 0x00100113
#define kReportApplicationStatusAck 0x80100113

/* 用户行为告警 */
#define kReportUserOperation 0x00100114
#define kReportUserOperationAck 0x80100114

/* 上报话务信息 */
#define kReportTelephoneTraffic 0x00100115
#define kReportTelephoneTrafficAck 0x80100115

/* 上报席位功能键状态信息 */
#define kReportCwpFuncBtnStatus 0x00100116
#define kReportCwpFuncBtnStatusAck 0x80100116

typedef struct _PacketHead
{
    int id;
    int type;
    int size;
    int token;
} PacketHead;

typedef struct _PacketKeepalive
{
    PacketHead head;
} PacketKeepalive;

typedef struct _PacketKeepaliveAck
{
    PacketHead head;
} PacketKeepaliveAck;

/* 设备信息 */
typedef struct _PacketGetDevInfo
{
    PacketHead head;
} PacketGetDevInfo;

typedef struct _PacketGetDevInfoAck
{
    PacketHead head;
    /* 设备号 */
    unsigned int dev_num;

    /* 设备类型：0表示server；1表示LIU */
    int dev_type;

    /* 设备名 */
    char dev_name[16];
} PacketGetDevInfoAck;

/* 主控板信息 */
typedef struct _PacketGetMpuInfo
{
    PacketHead head;
} PacketGetMpuInfo;

typedef struct _PacketGetMpuInfoAck
{
    PacketHead head;
    /* 槽位号 */
    unsigned int slot_num;

    /* 设备号 */
    unsigned int dev_num;

    /* 状态：0表示故障；1表示正常 */
    int status;
} PacketGetMpuInfoAck;

/* 用户板信息 */
typedef struct _PacketGetRiuInfo
{
    PacketHead head;
} PacketGetRiuInfo;

typedef struct _PacketGetRiuInfoAck
{
    PacketHead head;
    /* 框号 */
    unsigned int frame_num;

    /* 槽位号 */
    unsigned int slot_num;

    /* 状态：0表示故障；1表示正常 */
    int status;

    /* 用户板类型：
       0x00：ASL
       0x01：ALT
       0x02：EM
       0x03：MTK
       0x04：ISDN
       0x05：DTK
       0x06：DSL
       0x07：DIU
       0x10：RIU
       */
    int type;

    /* 主备：0表示备；1表示主 */
    int active_standby;

    /* 组号 */
    unsigned int group_num;
} PacketGetRiuInfoAck;

/* 席位信息 */
typedef struct _PacketGetCwpInfo
{
    PacketHead head;
} PacketGetCwpInfo;

typedef struct _PacketGetCwpInfoAck
{
    PacketHead head;
    /* 组号 */
    unsigned int group_num;

    /* 席位号 */
    unsigned int cwp_num;

    /* 状态：0表示故障；1表示正常 */
    int status;

    /* 用户登录名 */
    char user_name[32];

    /* 左话机 */
    char left_phone[32];

    /* 右话机 */
    char right_phone[32];

    /* 用户所选角色 */
    char roles[96];
} PacketGetCwpInfoAck;

/* 上报设备信息变更 */
typedef struct _PacketReportDevInfoChange
{
    PacketHead head;
} PacketReportDevInfoChange;

/* 上报主控板信息变更 */
typedef struct _PacketReportMpuInfoChange
{
    PacketHead head;
} PacketReportMpuInfoChange;

/* 上报用户板信息变更 */
typedef struct _PacketReportRiuInfoChange
{
    PacketHead head;
} PacketReportRiuInfoChange;

/* 上报席位信息变更 */
typedef struct _PacketReportCwpInfoChange
{
    PacketHead head;
} PacketReportCwpInfoChange;

/* 上报用户板端口状态 */
typedef struct _PacketReportRiuPortStatus
{
    PacketHead head;

    /* 端口号：0~255 */
    unsigned int port_num;

    /* 框号 */
    unsigned int frame_num;

    /* 槽位号 */
    unsigned int slot_num;

    /* 状态：0表示故障；1表示正常 */
    int status;

    /* 端口类型：
       0x00：ASL
       0x01：ALT
       0x02：EM
       0x03：MTK
       0x04：ISDN
       0x05：DTK
       0x06：DSL
       0x07：DIU
       0x08：RIU
       0x09：YCK
       0x10：EM4
       */
    int type;
} PacketReportRiuPortStatus;

/* 电话按钮信息 */
typedef struct _PhoneButtonInfo
{
    /* 所在按钮位置 */
    unsigned int btn_num;

    /* 按钮对应名称 */
    char name[32];

    /* 按钮对应的电话号码 */
    char phone_num[32];

    /* 是否弹出拨号盘，0否；1是 */
    unsigned int is_dialog;

    /* 是否使能，0否；1是 */
    unsigned int can_use;

    /* 按钮类型
       1：模拟电话
       2：中继
       3：速拨
       4：组拨号
       5：ip电话
       6：磁石电话
       7：席位电话
       8：中继线路号
       */
    int type;
} PhoneButtonInfo;

/* 电台按钮信息 */
typedef struct _RadioButtonInfo
{
    /* 所在按钮位置 */
    unsigned int btn_num;

    /* 按钮对应名称 */
    char name[32];

    /* 电台频率 */
    char frequency[32];

    /* 是否是救生频率，0表示普通；1表示救生 */
    int lifesaving;

    /* 是否使能，0否；1是 */
    int can_use;
} RadioButtonInfo;

/* 功能按钮信息 */
typedef struct _FuncButtonInfo
{
    /* 所在按钮位置 */
    unsigned int btn_num;

    /* 按钮对应名称 */
    char name[32];

    /* 功能键种类 */
    int type;
} FuncButtonInfo;

/* 上报席位按键信息 */
typedef struct _PacketReportButtonInfo
{
    PacketHead head;
    /* 席位号 */
    unsigned int cwp_num;

    /* 电话按钮个数 */
    unsigned int phone_btn_counts;

    /* 电话按钮信息 */
    PhoneButtonInfo *phone_btn_info;

    /* 电台按钮个数 */
    unsigned int radio_btn_counts;

    /* 电台按钮信息 */
    RadioButtonInfo *radio_btn_info;

    /* 功能按钮个数 */
    unsigned int func_btn_counts;

    /* 功能按钮信息 */
    FuncButtonInfo *func_btn_info;
} PacketReportButtonInfo;

/* 上报通话记录 */
typedef struct _PacketReportCallRecords
{
    PacketHead head;
    /* 应答类型
        0x00表示未接通；1表示接通
        */
    int is_connected;

    /* 业务类型
       0：普通呼叫
       1：席位参与的双方通话
       2：保持
       3：取消保持
       4：监听
       5：强插
       6：强拆
       7：转接
       8：转接失败返回
       9：代答
       10：会议
       11：临时会议
       12：组呼会议
       13：呼入组呼
       14：呼入调度组组呼
       15：紧急呼叫
       16：查号
       */
    int business_type;

    /* 业务标识号 */
    char business_id[4];

    /* 释放原因 */
    int cause_of_release;

    /* 主叫号码 */
    char calling_num[16];

    /* 被叫号码 */
    char called_num[16];

    /* 第三方号码 */
    char thirdparty_num[16];

    /* 发起呼叫时间 */
    long long incoming_time;

    /* 呼叫接通时间 */
    long long start_time;

    /* 结束时间 */
    long long end_time;
} PacketReportCallRecords;

/* 上报LIU网络状态 */
typedef struct _PacketReportLiuEthStatus
{
    PacketHead head;
    /* 左右标记 */
    int lr_flag;

    /* 设备号 */
    unsigned int dev_num;

    /* 网口1状态，0表示断开；1表示连接 */
    int eth1_status;

    /* 网口2状态，0表示断开；1表示连接 */
    int eth2_status;
} PacketReportLiuEthStatus;

/* 上报席位网络状态 */
typedef struct _PacketReportCwpEthStatus
{
    PacketHead head;
    /* 席位号 */
    unsigned int cwp_num;

    /* 网络状态，0表示断开；1表示连接 */
    int eth_status;
} PacketReportCwpEthStatus;

/* 上报席位电源状态 */
typedef struct _PacketReportCwpPowerStatus
{
    PacketHead head;
    /* 席位号 */
    unsigned int cwp_num;

    /* 电源状态，0表示故障；1表示正常 */
    int power_status;
} PacketReportCwpPowerStatus;

/* 上报网络性能参数 */
typedef struct _PacketReportNetworkCapability
{
    PacketHead head;
    /* 带宽（抖动，延迟) */
    unsigned int if_speed;

    /* 带宽利用率 */
    unsigned int if_load;

    /* 每秒数据包 */
    unsigned int if_pkts_per_sec;

    /* 数据包数 */
    unsigned int if_pkts;

    /* 错误数据包数 */
    unsigned int if_errors;
} PacketReportNetworkCapability;

/* 上报网络流量信息 */
typedef struct _PacketReportNetworkTraffic
{
    PacketHead head;
} PacketReportNetworkTraffic;

/* 上报硬件状态信息 */
typedef struct _PacketReportHardwareStatus
{
    PacketHead head;
    /* cpu使用率 */
    unsigned int cpu_usage;

    /* 总内存 */
    unsigned long long total_mem;

    /* 已使用内存 */
    unsigned long long used_mem;

    /* 网卡ip */
    int eth1_ip;
    /* 状态
       0：断开
       1：连接
       */
    int eth1_conn;
    int eth2_ip;
    int eth2_conn;

} PacketReportHardwareStatus;

/* 上报软件状态信息 */
typedef struct _PacketReportApplicationStatus
{
    PacketHead head;
    /* 软件版本号 */
    char version[32];

    /* server ip */
    int server1_ip;
    /* 席位与server连接状态
       0：断开
       1：连接
       */
    int server1_conn;
    int server2_ip;
    int server2_conn;

    /* 运行时长 */
    long long running_time;
} PacketReportApplicationStatus;

/* 用户行为告警 */
typedef struct _PacketReportUserOperation
{
    PacketHead head;
    /* 用户行为类型：
       0：登录
       1：加载角色
       2：注销
       3：重启
       4：关机
       */
    int operation;

    /* 操作日期时间 */
    long long datetime;
} PacketReportUserOperation;

/* 上报话务信息 */
typedef struct _PacketReportTelephoneTraffic
{
    PacketHead head;
} PacketReportTelephoneTraffic;

/* 上报席位功能键状态信息 */
typedef struct _PacketReportCwpFuncBtnStatus
{
    PacketHead head;
    /* 席位功能键按下/弹起 */
    int is_func_btn_down;

    /* 席位配置面板功能键选择 */
    int is_func_btn_checked;
} PacketReportCwpFuncBtnStatus;

#pragma pack(pop)

#endif // PROTO_DEF_H
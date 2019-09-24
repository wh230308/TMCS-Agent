/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <hzchangrong-tmcs-mib/management/phoneBtnInfos.h>
#include <hzchangrong-tmcs-mib/common.h>

extern const oid snmptrap_oid[];
extern const size_t snmptrap_oid_len;

int send_phoneBtnInfos_trap(int cwp_num, const PhoneButtonInfo *btn_info)
{
    netsnmp_variable_list *var_list = NULL;
    const oid phoneBtnInfos_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 0, 6};
    const oid cwpNumForPhone_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 1, 0};
    const oid phoneBtnNum_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 2, 0};
    const oid phoneBtnName_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 3, 0};
    const oid phoneNum_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 4, 0};
    const oid isDialog_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 5, 0};
    const oid isPhoneBtnEnable_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 6, 0};
    const oid phoneBtnType_oid[] = {1, 3, 6, 1, 4, 1, 826318, 2, 2, 2, 3, 7, 0};
    u_int cwp_number;
    u_int btn_num;
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
                              snmptrap_oid, snmptrap_oid_len,
                              ASN_OBJECT_ID,
                              phoneBtnInfos_oid, sizeof(phoneBtnInfos_oid));

    cwp_number = cwp_num + 1;
    btn_num = btn_info->btn_num + 1;
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
                              cwpNumForPhone_oid, OID_LENGTH(cwpNumForPhone_oid),
                              ASN_UNSIGNED,
                              /* Set an appropriate value for cwpNumForPhone */
                              (const void *)&cwp_number, sizeof(cwp_number));
    snmp_varlist_add_variable(&var_list,
                              phoneBtnNum_oid, OID_LENGTH(phoneBtnNum_oid),
                              ASN_UNSIGNED,
                              /* Set an appropriate value for phoneBtnNum */
                              (const void *)&btn_num, sizeof(btn_num));
    snmp_varlist_add_variable(&var_list,
                              phoneBtnName_oid, OID_LENGTH(phoneBtnName_oid),
                              ASN_OCTET_STR,
                              /* Set an appropriate value for phoneBtnName */
                              (const void *)btn_info->name, COPY_LEN(btn_info->name, sizeof(btn_info->name)));
    snmp_varlist_add_variable(&var_list,
                              phoneNum_oid, OID_LENGTH(phoneNum_oid),
                              ASN_OCTET_STR,
                              /* Set an appropriate value for phoneNum */
                              (const void *)btn_info->phone_num, COPY_LEN(btn_info->phone_num, sizeof(btn_info->phone_num)));
    snmp_varlist_add_variable(&var_list,
                              isDialog_oid, OID_LENGTH(isDialog_oid),
                              ASN_INTEGER,
                              /* Set an appropriate value for isDialog */
                              (const void *)&btn_info->is_dialog, sizeof(btn_info->is_dialog));
    snmp_varlist_add_variable(&var_list,
                              isPhoneBtnEnable_oid, OID_LENGTH(isPhoneBtnEnable_oid),
                              ASN_INTEGER,
                              /* Set an appropriate value for isPhoneBtnEnable */
                              (const void *)&btn_info->can_use, sizeof(btn_info->can_use));
    snmp_varlist_add_variable(&var_list,
                              phoneBtnType_oid, OID_LENGTH(phoneBtnType_oid),
                              ASN_INTEGER,
                              /* Set an appropriate value for phoneBtnType */
                              (const void *)&btn_info->type, sizeof(btn_info->type));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap(var_list);
    snmp_free_varbind(var_list);

    return SNMP_ERR_NOERROR;
}
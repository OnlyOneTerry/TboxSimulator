// 
// Create by kong on 2024/2/26
// Copyright 2024 Beijing Xinchangcheng Technology Development Co., Ltd.
//
#ifndef SVKD_BUILD_IWALL_TLS_H
#define SVKD_BUILD_IWALL_TLS_H

#ifdef __cpulsplus
extern "C" {
#endif

/**
 * @brief 获取 Openssl Context
 *
 * @param hAppHandle                 [IN] 应用接口句柄
 * @param pucContainerName           [IN] 容器名称
 * @param uiContainerNameLen         [IN] 容器名称长度
 * @param pucPin                     [IN] 设备口令
 * @param uiPinLen                   [IN] 设备口令长度
 * @param ctx                        [OUT] SSL_CTX
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_GetSSLContext(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        void **ctx);

/**
 * @brief 设置 Curl tls 参数
 *
 * @param curl                       [IN] CURL 上下文
 * @param hAppHandle                 [IN] 应用接口句柄
 * @param pucContainerName           [IN] 容器名称
 * @param uiContainerNameLen         [IN] 容器名称长度
 * @param pucPin                     [IN] 设备口令
 * @param uiPinLen                   [IN] 设备口令长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int curl_easy_setopt_cert_and_privatekey(
        void *curl,
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen);

/**
 * @brief 设置 mosquitto 参数
 *
 * @param mosquitto                  [IN] Mosquitto 上下文
 * @param hAppHandle                 [IN] 应用接口句柄
 * @param pucContainerName           [IN] 容器名称
 * @param uiContainerNameLen         [IN] 容器名称长度
 * @param pucPin                     [IN] 设备口令
 * @param uiPinLen                   [IN] 设备口令长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int mosquitto_tls_opts_set_cert_and_privatekey(
        void *mosquitto,
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen);

#ifdef __cpulsplus
}
#endif

#endif //SVKD_BUILD_IWALL_TLS_H

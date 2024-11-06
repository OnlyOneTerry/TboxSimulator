//
// Create by kong on 2023/11/3
// Copyright 2023 Beijing Xinchangcheng Technology Development Co., Ltd.
//

#ifndef SCM_IWALL_PKI_H
#define SCM_IWALL_PKI_H

#include <stdint.h>
#include "iwall_define.h"

#ifdef _WIN32
#define IW_EXPORT __declspec(dllexport)
#else
#define IW_EXPORT __attribute__ ((visibility ("default")))
#endif

#ifdef __cpulsplus
extern "C" {
#endif

/* ******************************************
           Environment interface
****************************************** */

/**
 * @brief 初始化密码服务
 *
 * @param phAppHandle     [IN/OUT] 输入并返回应用接口句柄
 * @param pcAppFilePath   [IN]     应用存储路径
 * @param pcBaseUrl       [IN]     接口请求路径，若切换路径需先清空 pcAppFilePath 文件夹
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_InitService(
        void **phAppHandle,
        const char *pcAppFilePath,
        const char *pcBaseUrl,
        uint32_t uiCertificateChainFlag);

/**
 * @brief 清除密码服务
 *
 * @param phAppHandle     [IN] 应用接口句柄
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_Finalize(void *hAppHandle);

/**
 * @brief 获取 lib 版本信息
 *
 * @param pcVersion       [OUT] 版本号
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetVersion(char *pcVersion);

/* ******************************************
           Certificate interface
 ****************************************** */

/**
 * @brief 请求服务器上的证书链
 *
 * @param hAppHandle              [IN]  应用接口句柄
 * @param pcRequestUrl            [IN]  证书链请求地址
 * @param uiCertificateChainFlag  [IN]  证书链标识
 * @param pucCertificates         [OUT] PEM 编码的证书链
 * @param uiCertificatesLen       [OUT] PEM 证书链长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetTrustCertificateChainFromServer(
        void *hAppHandle,
        const char   *pcRequestUrl,
        uint32_t uiCertificateChainFlag,
        unsigned char *pucCertificates,
        unsigned int  *uiCertificatesLen);

/**
 * @brief 导入信任的证书链
 *
 * @param hAppHandle              [IN] 应用接口句柄
 * @param pucCertificates         [IN] PEM 编码的证书链
 * @param uiCertificatesLen       [IN] PEM 证书链长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_ImportTrustedCertificateChain(
        void *hAppHandle,
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen);

/**
 * @brief 获取信任的证书链
 *
 * @param hAppHandle              [IN]  应用接口句柄
 * @param pucCertificates         [OUT] PEM 格式的证书
 * @param puiCertificatesLen      [OUT] PEM 证书长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetTrustedCertificateChain(
        void *hAppHandle,
        unsigned char *pucCertificates,
        unsigned int *puiCertificatesLen);

/**
 * @brief 删除信任的证书链
 *
 * @param hAppHandle              [IN] 应用接口句柄
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RemoveTrustedCertificateChain(void *hAppHandle);

/**
 * @brief 生成证书请求文件
 *
 * @param hAppHandle               [IN]  应用接口句柄
 * @param pucContainerName         [IN]  容器名称，需要传入已有密钥容器。
 * @param uiContainerNameLen       [IN]  容器名称长度
 * @param pucPin                   [IN]  设备口令
 * @param uiPinLen                 [IN]  设备口令长度
 * @param pstNameInfo              [IN]  请求信息
 * @param pucCertificateRequest    [OUT] Der 格式证书请求文件
 * @param puiCertificateRequestLen [OUT] Der 格式证书请求文件长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GenerateCertificateSigningRequest(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        SGD_NAME_INFO *pstNameInfo,
        unsigned char *pucCertificateRequest,
        unsigned int *puiCertificateRequestLen);

/**
 * @brief 通过证书请求文件获取证书
 *
 * @param hAppHandle                 [IN]  应用接口句柄
 * @param pcRequestUrl               [IN]  证书请求地址
 * @param pucCertificateRequest      [IN]  Der 格式证书请求文件
 * @param uiCertificateRequestLen    [IN]  Der 格式证书请求文件长度
 * @param pucContainerName           [IN]  容器名称
 * @param uiContainerNameLen         [IN]  容器名称长度
 * @param pucCertificate             [OUT] 证书
 * @param puiCertificateLen          [OUT] 证书长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetUserCertificateFromServerByCsr(
        void          * hAppHandle,
        char          * pcBaseUrl,
        unsigned char * pucCertificateRequest,
        unsigned int    uiCertificateRequestLen,
        unsigned char * pucContainerName,
        unsigned int    uiContainerNameLen,
        unsigned char * pucCertificate,
        unsigned int  * puiCertificateLen);

/**
 * @brief 通过证书请求文件获取证书
 *
 * @param hAppHandle               [IN]  应用接口句柄
 * @param pucContainerName         [IN]  容器名称，需要传入已有密钥容器。
 * @param uiContainerNameLen       [IN]  容器名称长度
 * @param pucPin                   [IN]  设备口令
 * @param uiPinLen                 [IN]  设备口令长度
 * @param pstNameInfo              [IN]  请求信息
 * @param pucCertificateRequest    [OUT] Der 格式证书请求文件
 * @param puiCertificateRequestLen [OUT] Der 格式证书请求文件长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetUserCertificateFromServerByCsrInfo(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        SGD_NAME_INFO *pstNameInfo,
        unsigned char *pucCertificateRequest,
        unsigned int *puiCertificateRequestLen);

/**
 * @brief 通过证书别名获取证书
 *
 * @param hAppHandle                 [IN] 应用接口句柄
 * @param pcRequestUrl               [IN] 证书请求地址
 * @param pcAlias                    [IN] 别名
 * @param pucContainerName           [IN] 容器名称
 * @param uiContainerNameLen         [IN] 容器名称长度
 * @param pucCertificate             [OUT] PEM 格式证书
 * @param uiCertificateLen           [OUT] PEM 格式证书长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetUserCertificateFromServerByAlias(
        void *hAppHandle,
        const char *pcRequestUrl,
        const char *pcAlias,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucCertificate,
        unsigned int  *uiCertificateLen);

/**
 * @brief 检查本地证书是否可用并校验证书与本地密钥是否匹配
 *
 * @param hAppHandle          [IN]  应用接口句柄
 * @param pucContainerName    [IN]  容器名称
 * @param uiContainerNameLen  [IN]  容器名称长度
 * @param pucPin              [IN]  设备口令
 * @param uiPinLen            [IN]  设备口令长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_CheckCertificateKeyMatcher(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int   uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int   uiPinLen);

/**
 * @brief 导入用户证书
 *
 * @param hAppHandle          [IN] 应用接口句柄
 * @param pucContainerName    [IN] 容器名称
 * @param uiContainerNameLen  [IN] 容器名称长度
 * @param iSignFlag           [IN] 1 表示签名证书，0 表示加密证书
 * @param pucCertificate      [IN] 证书内容缓冲区
 * @param uiCertificate       [IN] 证书长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_ImportCertificate(
        void  *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int   uiContainerNameLen,
        unsigned int   uiSignFlag,
        unsigned char *pucCertificate,
        unsigned int   uiCertificateLen);

/**
 * @brief 导出用户证书
 *
 * @param hAppHandle          [IN]  应用接口句柄
 * @param pucContainerName    [IN]  容器名称
 * @param uiContainerNameLen  [IN]  容器名称长度
 * @param iSignFlag           [IN]  1 表示签名证书，0 表示加密证书
 * @param pucCertificate      [OUT] 指向证书内容缓冲区
 * @param puiCertificate      [IN/OUT] 输入时候表示证书缓冲区长度，输出表示证书内容长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_ExportCertificate(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int   uiContainerNameLen,
        unsigned int   iSignFlag,
        unsigned char *pucCertificate,
        unsigned int  *puiCertificateLen);

/**
 * @brief 删除用户证书
 *
 * @param hAppHandle          [IN] 应用接口句柄
 * @param pucContainerName    [IN] 容器名称
 * @param uiContainerNameLen  [IN] 容器名称长度
 * @param iSignFlag           [IN] 1 表示签名证书，0 表示加密证书
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_RemoveCertificate(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int   uiContainerNameLen,
        int iSignFlag);

/**
 * @brief 验证用户证书的有效性，包括验证有效期，证书信任列表，不包含吊销状态。
 *
 * @param hAppHandle          [IN] 应用接口句柄
 * @param pucUsrCertificate   [IN] PEM 编码的证书
 * @param uiUsrCertificateLen [IN] 证书长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_VerifyCertificate(
        void *hAppHandle,
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen);

/**
 * @brief 验证用户证书的有效性，包括验证有效期，证书信任列表，包含吊销状态。
 *
 * @param hAppHandle          [IN] 应用接口句柄
 * @param pucUsrCertificate   [IN] PEM 编码证书
 * @param uiUsrCertificateLen [IN] 证书长度
 * @param pucPemCrl           [IN] PEM 编码的 CRL，若为 NULL 则根据证书中的 CRL 地址下载。
 * @param uiDerPemLen         [IN] CRL 长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_VerifyCertificateByCrl(
        void *hAppHandle,
        unsigned char *pucUsrCertificate,
        unsigned int uiUsrCertificateLen,
        unsigned char *pucPemCrl,
        unsigned int uiDerPemLen);

/**
 * @brief 通过 OCSP 获取证书状态
 *
 * @param hAppHandle          [IN] 应用接口句柄
 * @param pcOcspHostURL       [IN] OCSP 服务的 URL
 * @param uiOcspHostURLLen    [IN] URL 长度
 * @param pucUsrCertificate   [IN] PEM 编码证书
 * @param uiUsrCertificateLen [IN] 证书长度
 * @param pucCACertificate    [IN] PEM 编码颁发者证书
 * @param uiCACertificateLen  [IN] 颁发者证书长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_GetCertificateStateByOCSP(
        void *hAppHandle,
        unsigned char *pcOcspHostURL,
        unsigned int uiOcspHostURLLen,
        unsigned char *pucUsrCertificate,
        unsigned int uiUsrCertificateLen,
        unsigned char *pucCACertificate,
        unsigned int uiCACertificateLen);

/**
 * @brief 解析证书，获取证书中的信息
 *
 * @param pucCertificate      [IN] PEM 编码的证书
 * @param uiCertificateLen    [IN] 证书长度
 * @param uiInfoType          [IN] 制定的证书解析标识，见: 证书解析项标识
 * @param pucInfo             [OUT] 获取的证书信息
 * @param puiInfoLen          [OUT] 获取的证书信息长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_GetCertificateInfo(
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen,
        unsigned int uiInfoType,
        unsigned char *pucInfo,
        unsigned int *puiInfoLen);

/* ******************************************
      Cryptographic algorithm interface
 ****************************************** */

/**
 * @brief Base 64 编码
 *
 * @param pucInData       [IN]  编码前的数据
 * @param puiInDataLen    [IN]  编码前的数据长度
 * @param pucOutData      [OUT] 编码后的数据
 * @param puiOutDataLen   [IN/OUT] 输入时表示编码结果的缓冲区大小，输出时表示编码结果长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_Base64_Encode(
        unsigned char *pucInData,
        unsigned int puiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * @brief Base 64 解码
 *
 * @param pucInData       [IN]  解码前的数据
 * @param puiInDataLen    [IN]  解码前的数据长度
 * @param pucOutData      [OUT] 解码后的数据
 * @param puiOutDataLen   [IN/OUT] 输入时表示解码结果的缓冲区大小，输出时表示解码结果长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_Base64_Decode(
        unsigned char *pucInData,
        unsigned int puiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * 生成随机数
 *
 * @param uiRandLen       [IN]  随机数长度
 * @param pucRand         [OUT] 随机数
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GenRandom(
        unsigned int uiRandLen,
        unsigned char *pucRand);

/**
 * @brief 生成随机数 使用安全芯片
 *
 * @param hAppHandle          [IN] 应用接口句柄
 * @param uiRandLen           [IN]  随机数长度
 * @param pucRand             [OUT] 随机数
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GenRandomInner(
        void *hAppHandle,
        unsigned int uiRandLen,
        unsigned char *pucRand);

/**
 * @brief HASH 运算
 *
 * @param uiHashAlgoType   [IN]  HASH 算法，见：哈希算法标识
 * @param pucInData        [IN]  输入数据
 * @param uiInDataLen      [IN]  输入数据长度
 * @param pucOutData       [OUT]    HASH
 * @param puiOutDataLen    [IN/OUT] 输入时候表示哈希缓冲区长度，输出表示哈希内容长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_Hash(
        unsigned int uiHashAlgoType,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * @brief 创建 Hash 对象
 *
 * @param phHashObj     [IN/OUT] 哈希对象
 * @param uiAlgoType    [IN]     哈希算法，见 哈希算法标识
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_CreateHashObj(
        void **phHashObj,
        unsigned int uiHashAlgoType);

/**
 * @brief 销毁 Hash 对象
 *
 * @param hHashObj      [IN] Hash 对象
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_DestroyHashObj(
        void *hHashObj);

/**
 * @brief 多块 Hash 运算
 *
 * @param hHashObj      [IN]  Hash 对象
 * @param pucInData     [IN]  输入数据
 * @param uiInDataLen   [IN]  输入数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_HashUpdate(
        void *hHashObj,
        unsigned char *pucInData,
        unsigned int uiInDataLen);

/**
 * 结束 Hash 运算
 *
 * @param hHashObj      [IN]  Hash 对象
 * @param pucOutData    [OUT] 输出的 Hash 值
 * @param uiOutDataLen  [IN/OUT] 输入时候表示哈希值缓冲区长度，输出表示哈希值长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_HashFinal(
        void *hHashObj,
        unsigned char *pucOutData,
        unsigned int *uiOutDataLen);

/**
 * @brief 生成 RSA 密钥对
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param uiKeyBits          [IN] 密钥长度 支持 2048, 3072, 4096
 * @param uiKeyUsage         [IN] 密钥用途 SGD_KEYUSAGE_SIGN（签名）SGD_KEYUSAGE_ENC（加密）
 * @param uiExportFlag       [IN] 是否可导出密钥（仅对私钥有效）, 0 不可导出，1 可导出，若使用安全芯片则需传入 0 不可导出。
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GenRsaKeyPair(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned int uiKeyBits,
        unsigned int uiKeyUsage,
        unsigned int uiExportFlag);

/**
 * @brief 获取 RSA 公钥
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param uiKeyUsage         [IN] 密钥用途 SGD_KEYUSAGE_SIGN（签名）SGD_KEYUSAGE_ENC（加密）
 * @param pucPublicKey       [OUT] DER 格式公钥
 * @param puiPublicKeyLen    [OUT] DER 格式公钥长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetRsaPublicKey(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned int uiKeyUsage,
        unsigned char *pucPublicKey,
        unsigned int *puiPublicKeyLen);

/**
 * @brief 私钥签名
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucInData          [IN] 原始数据
 * @param uiInDataLen        [IN] 原始数据的长度
 * @param pucSignature       [OUT] 输出的 DER 格式的签名结果
 * @param puiSignatureLen    [IN/OUT] 输入时候表示签名缓冲区长度，输出表示签名内容长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaSign(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned int uiHashAlgoType,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucSignature,
        unsigned int *puiSignatureLen);

/**
 * @brief 对文件进行 RSA 签名运算
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 密钥的容器名
 * @param uiContainerNameLen [IN] 密钥容器名长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucFileName        [IN] 要签名的全路径文件名
 * @param pucSignature       [OUT] 输出的 DER 格式的签名结果
 * @param puiSignatureLen    [IN/OUT] 输入时候表示签名缓冲区长度，输出表示签名内容长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaSignFile(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned int uiHashAlgoType,
        const char *pcFileName,
        unsigned char *pucSignature,
        unsigned int *puiSignatureLen);

/**
 * @brief RSA 验证签名运算
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucPublicKey       [IN] DER 编码的公钥
 * @param uiPublicKeyLen     [IN] DER 编码的公钥长度
 * @param pucInData          [IN] 原始数据
 * @param uiInDataLen        [IN] 原始数据长度
 * @param pucSignData        [IN] DER 编码的签名数据
 * @param uiSignDataLen      [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaVerifySign(
        unsigned int uiHashAlgoType,
        unsigned char *pucPublicKey,
        unsigned int uiPublicKeyLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucSignData,
        unsigned int uiSignDataLen);

/**
 * @brief 对文件进行 RSA 验签
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucPublicKey       [IN] DER 编码的公钥
 * @param uiPublicKeyLen     [IN] DER 编码的公钥长度
 * @param pucFileName        [IN] 要验证签名的全路径文件名
 * @param pucSignData        [IN] DER 编码的签名数据
 * @param uiSignDataLen      [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaVerifySignFile(
        unsigned int uiHashAlgoType,
        unsigned char *pucPublicKey,
        unsigned int uiPublicKeyLen,
        const char *pucFileName,
        unsigned char *pucSignData,
        unsigned int uiSignDataLen);

/**
 * @brief 使用数字证书对签名值进行验证
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucCertificate     [IN] DER 编码的数字证书
 * @param uiCertificateLen   [IN] DER 编码的数字证书长度
 * @param pucInData          [IN] 原始数据
 * @param uiInDataLen        [IN] 原始数据的长度
 * @param pucSignData        [IN] 签名数据
 * @param uiSignDataLen      [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaVerifySignByCert(
        unsigned int uiHashAlgoType,
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucSignData,
        unsigned int uiSignDataLen);

/**
 * @brief 使用数字证书对文件签名值进行验证
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucCertificate     [IN] DER 编码的数字证书
 * @param uiCertificateLen   [IN] DER 编码的数字证书长度
 * @param pucFileName        [IN] 要验证签名的全路径文件名
 * @param pucSignature       [IN] DER 编码的签名数据
 * @param uiSignatureLen     [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaVerifySignFileByCert(
        unsigned int uiHashAlgoType,
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen,
        const char *pcFileName,
        unsigned char *pucSignature,
        unsigned int uiSignatureLen);

/**
 * @brief RSA 加密
 *
 * @param pucPublicKey       [IN] DER 编码的公钥
 * @param uiPublicKeyLen     [IN] DER 编码的公钥长度
 * @param pucInData          [IN] 待加密数据，长度需小于 RSA bits / 8 - 11
 * @param uiInDataLen        [IN] 要验证签名的全路径文件名
 * @param pucData            [OUT] 密文数据 采用 RSA_PKCS1_PADDING 填充方式
 * @param puiDataLen         [OUT] 密文数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaEncrypt(
        unsigned char *pucPublicKey,
        unsigned int uiPublicKeyLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucData,
        unsigned int  *puiDataLen);

/**
 * @brief 通过证书 RSA 加密
 *
 * @param pucCertificate     [IN] DER 编码的数字证书
 * @param uiCertificateLen   [IN] DER 编码的数字证书长度
 * @param pucInData          [IN] 待加密数据，长度需小于 RSA bits / 8 - 11
 * @param uiInDataLen        [IN] 要验证签名的全路径文件名
 * @param pucData            [OUT] 密文数据 采用 RSA_PKCS1_PADDING 填充方式
 * @param puiDataLen         [OUT] 密文数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaEncryptByCert(
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucData,
        unsigned int *uiDataLen);

/**
 * @brief RSA 解密
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param pucInData          [IN] 待解密数据
 * @param uiInDataLen        [IN] 待解密数据长度
 * @param pucData            [OUT] 明文数据
 * @param puiDataLen         [OUT] 明文数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_RsaDecrypt(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucData,
        unsigned int *puiDataLen);

/**
 * @brief 生成 ECC 密钥对
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param uiAlgorithmID      [IN] 密钥标识 SGD_SM2, SGD_ECC, SGD_ED25519
 * @param uiKeyUsage         [IN] 密钥用途 SGD_KEYUSAGE_SIGN（签名）SGD_KEYUSAGE_ENC（加密）
 * @param uiExportFlag       [IN] 是否可导出密钥, 0 不可导出，1 可导出。
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GenEccKeyPair(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned int uiAlgorithmID,
        unsigned int uiKeyUsage,
        unsigned int uiExportFlag);

/**
 * @brief 获取 ECC 公钥
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param uiKeyUsage         [IN] 密钥用途 SGD_KEYUSAGE_SIGN（签名）SGD_KEYUSAGE_ENC（加密）
 * @param pucPublicKey       [OUT] 公钥
 * @param puiPublicKeyLen    [OUT] 公钥长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_GetEccPublicKey(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned int uiKeyUsage,
        unsigned char *pucPublicKey,
        unsigned int *puiPublicKeyLen);

/**
 * @brief ECC 私钥签名
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 容器名称
 * @param uiContainerNameLen [IN] 容器名称长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucInData          [IN] 原始数据
 * @param uiInDataLen        [IN] 原始数据的长度
 * @param pucSignature       [OUT] 输出的 DER 格式的签名结果
 * @param puiSignatureLen    [IN/OUT] 输入时候表示签名缓冲区长度，输出表示签名内容长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_EccSign(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned int uiHashAlgoType,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucSignature,
        unsigned int *puiSignatureLen);

/**
 * @brief 对文件进行 ECC 签名运算
 *
 * @param hAppHandle         [IN] 应用接口句柄
 * @param pucContainerName   [IN] 密钥的容器名
 * @param uiContainerNameLen [IN] 密钥容器名长度
 * @param pucPin             [IN] 设备口令
 * @param uiPinLen           [IN] 设备口令长度
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucFileName        [IN] 要签名的全路径文件名
 * @param pucSignature       [OUT] 输出的 DER 格式的签名结果
 * @param puiSignatureLen    [IN/OUT] 输入时候表示签名缓冲区长度，输出表示签名内容长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
IW_EXPORT int
IW_EccSignFile(
        void *hAppHandle,
        unsigned char *pucContainerName,
        unsigned int uiContainerNameLen,
        unsigned char *pucPin,
        unsigned int uiPinLen,
        unsigned int uiHashAlgoType,
        const char *pcFileName,
        unsigned char *pucSignature,
        unsigned int *puiSignatureLen);

/**
 * @brief Ecc 验证签名运算
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucPublicKey       [IN] DER 编码的公钥
 * @param uiPublicKeyLen     [IN] DER 编码的公钥长度
 * @param pucInData          [IN] 原始数据
 * @param uiInDataLen        [IN] 原始数据长度
 * @param pucSignData        [IN] DER 编码的签名数据
 * @param uiSignDataLen      [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_EccVerifySign(
        unsigned int uiHashAlgoType,
        unsigned char *pucPublicKey,
        unsigned int uiPublicKeyLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucSignData,
        unsigned int uiSignDataLen);

/**
 * @brief 对文件进行 ECC 验签
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucPublicKey       [IN] DER 编码的公钥
 * @param uiPublicKeyLen     [IN] DER 编码的公钥长度
 * @param pucFileName        [IN] 要验证签名的全路径文件名
 * @param pucSignData        [IN] DER 编码的签名数据
 * @param uiSignDataLen      [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_EccVerifySignFile(
        unsigned int uiHashAlgoType,
        unsigned char *pucPublicKey,
        unsigned int uiPublicKeyLen,
        const char *pucFileName,
        unsigned char *pucSignData,
        unsigned int uiSignDataLen);

/**
 * @brief 使用 Ecc 数字证书对签名值进行验证
 *
 * @param uiHashAlgoType     [IN] 密码杂凑算法标识
 * @param pucCertificate     [IN] DER 编码的数字证书
 * @param uiCertificateLen   [IN] DER 编码的数字证书长度
 * @param pucInData          [IN] 原始数据
 * @param uiInDataLen        [IN] 原始数据的长度
 * @param pucSignData        [IN] 签名数据
 * @param uiSignDataLen      [IN] 签名数据长度
 * @return 0 成功 / 非 0 失败，返回错误码
 */
int IW_EccVerifySignByCert(
        unsigned int uiHashAlgoType,
        unsigned char *pucCertificate,
        unsigned int uiCertificateLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucSignData,
        unsigned int uiSignDataLen);

/**
 * 创建对称算法对象
 *
 * @param phSymmKeyObj      [OUT] 对称算法对象
 * @param pucKey            [IN]  对称密钥
 * @param uiKeyLen          [IN]  对称密钥长度
 * @param pucIV             [IN]  初始向量
 * @param uiIVLen           [IN]  初始向量长度
 * @param uiEncOrDec        [IN]  1 加密，0 解密
 * @param uiCryptoAlgoType  [IN]  分组密码标识
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_CreateSymmKeyObj(
        void **phSymmKeyObj,
        unsigned char *pucKey,
        unsigned int uiKeyLen,
        unsigned char *pucIV,
        unsigned int uiIVLen,
        unsigned int uiEncOrDec,
        unsigned int uiCryptoAlgoType);

/**
 * 销毁对称算法对象
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @return 0 成功，非 0 失败。
 */
IW_EXPORT int
IW_DestroySymmKeyObj(
        void *hSymmKeyObj);

/**
 * 单块加密运算
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @param pucInData     [IN]  输入数据
 * @param uiInDataLen   [IN]  输入数据长度
 * @param pucOutData    [OUT] 输出数据
 * @param puiOutDataLen [OUT] 输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_SymmEncrypt(
        void *hSymmKeyObj,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * 多块加密运算
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @param pucInData     [IN]  输入数据
 * @param uiInDataLen   [IN]  输入数据长度
 * @param pucOutData    [OUT] 输出数据
 * @param puiOutDataLen [OUT] 输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_SymmEncryptUpdate(
        void *hSymmKeyObj,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * 结束加密运算
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @param pucOutData    [OUT] 输出数据
 * @param puiOutDataLen [OUT] 输出数据长度
 * @return 0 成功，非 0 失败。
 */
IW_EXPORT int
IW_SymmEncryptFinal(
        void *hSymmKeyObj,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * 单块解密运算
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @param pucInData     [IN]  输入数据
 * @param uiInDataLen   [IN]  输入数据长度
 * @param pucOutData    [OUT] 输出数据
 * @param puiOutDataLen [OUT] 输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_SymmDecrypt(
        void *hSymmKeyObj,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * 多块解密运算
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @param pucInData     [IN]  输入数据
 * @param uiInDataLen   [IN]  输入数据长度
 * @param pucOutData    [OUT] 输出数据
 * @param puiOutDataLen [OUT] 输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_SymmDecryptUpdate(
        void *hSymmKeyObj,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * 结束解密运算
 *
 * @param hSymmKeyObj   [IN]  对称算法对象
 * @param pucOutData    [OUT] 输出数据
 * @param puiOutDataLen [OUT] 输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_SymmDecryptFinal(
        void *hSymmKeyObj,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * @brief Hmac 计算
 * @param uiHashAlgoType [IN]  哈希算法标识
 * @param keyData        [IN]  密钥
 * @param keyDataLen     [IN]  密钥长度
 * @param pucInData      [IN]  输入数据
 * @param uiInDataLen    [IN]  输入数据长度
 * @param pucOutData     [OUT] 输出数据
 * @param puiOutDataLen  [OUT] 输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_Hmac(unsigned int uiHashAlgoType,
        unsigned char *pucKey,
        unsigned int uiKeyLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int *puiOutDataLen);

/**
 * @brief HKdf 计算
 *
 * @param uiHashAlgoType [IN]  哈希算法标识
 * @param pucIKM         [IN]  原始密钥
 * @param uiIKMLen       [IN]  原始密钥长度
 * @param pucSaltData    [IN]  如为空则为初始化为 0 的字符串，长度为哈希函数的散列值长度。
 * @param uiSaltDataLen  [IN]  随机源长度
 * @param pucInData      [IN]  输入数据
 * @param uiInDataLen    [IN]  输入数据长度
 * @param pucOutData     [OUT] 输出数据
 * @param puiOutDataLen  [IN]  输出数据长度
 * @return 0 成功 / 非 0 失败，返回错误码。
 */
IW_EXPORT int
IW_Hkdf(unsigned int uiHashAlgoType,
        unsigned char *pucIkm,
        unsigned int uiIkmLen,
        unsigned char *pucSaltData,
        unsigned int uiSaltDataLen,
        unsigned char *pucInData,
        unsigned int uiInDataLen,
        unsigned char *pucOutData,
        unsigned int puiOutDataLen);

#ifdef __cpulsplus
}
#endif


#endif //SCM_IWALL_PKI_H

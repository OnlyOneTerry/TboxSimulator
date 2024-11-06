// 
// Create by kong on 2023/12/21
// Copyright 2023 Beijing Xinchangcheng Technology Development Co., Ltd.
//
#ifndef SVKD_BUILD_IWALL_DEFINE_H
#define SVKD_BUILD_IWALL_DEFINE_H

// 常量定义
#define SGD_MAX_COUNT                    64    // 枚举出的对象数量最大值
#define SGD_MAX_NAME_SIZE               256    // 证书中某项信息的字符串长度最大值
#define SGD_MAX_SIZE                    256

// 分组密码算法标识
#define SGD_SM4_ECB              0x00000401    // SM4 算法 ECB 加密模式
#define SGD_SM4_CBC              0x00000402    // SM4 算法 CBC 加密模式
#define SGD_SM4_CFB              0x00000404    // SM4 算法 CFB 加密模式
#define SGD_SM4_OFB              0x00000408    // SM4 算法 OFB 加密模式
#define SGD_SM4_MAC              0x00000410    // SM4 算法 MAC 运算

#define SGD_AES_ECB              0x00000501    // AES 算法 ECB 加密模式
#define SGD_AES_CBC              0x00000502    // AES 算法 CBC 加密模式
#define SGD_AES_CFB              0x00000504    // AES 算法 CFB 加密模式
#define SGD_AES_OFB              0x00000508    // AES 算法 OFB 加密模式
#define SGD_AES_MAC              0x00000510    // AES 算法 MAC 运算


// 非对称密码算法标识
#define SGD_RSA                  0x00010000    // RSA 算法
#define SGD_SM2                  0x00020100    // SM2 椭圆曲线密码算法
#define SGD_ECC                  0x00080000    // ECC 椭圆曲线密码算法
#define SGD_ED25519              0x00081000    // ED25519 椭圆曲线密码算法

// 密码杂凑算法标识
#define SGD_SM3                  0x00000001    // SM3 杂凑算法
#define SGD_SHA1                 0x00000002    // SHA_1 杂凑算法
#define SGD_SHA256               0x00000004    // SHA_256 杂凑算法
#define SGD_SHA512               0x00000006    // SHA_512 杂凑算法

// 密钥用途标识
#define SGD_KEYUSAGE_SIGN        0x00000001    // 签名
#define SGD_KEYUSAGE_ENC         0x00000002    // 加密

// 证书解析项标识
#define SGD_CERT_VERSION         0x00000001    // 证书版本
#define SGD_CERT_SERIAL          0x00000002    // 证书序列号
#define SGD_CERT_ISSUER          0x00000005    // 证书颁发者信息
#define SGD_CERT_VALID_TIME      0x00000006    // 证书有效期
#define SGD_CERT_SUBJECT         0x00000007    // 证书拥有者信息
#define SGD_CERT_DER_PUBLIC_KEY  0x00000008    // 证书公钥信息
#define SGD_CERT_ALGORITHM       0x0000000A    // 证书算法信息
#define SGD_EXT_AUTHORITYKEYIDENTIFIER_INFO  0x00000011      // 颁发者密钥标识符
#define SGD_EXT_SUBJECTKEYIDENTIFIER_INFO    0x00000012      // 证书持有者密钥标识符
#define SGD_EXT_KEYUSAGE_INFO                0x00000013      // 密钥用途
#define SGD_EXT_CRLDISTRIBUTIONPOINTS_INFO   0x0000001A      // CRL 发布点

typedef struct {
    char dn_c[SGD_MAX_COUNT];
    char dn_s[SGD_MAX_COUNT];
    char dn_l[SGD_MAX_COUNT];
    char dn_o[SGD_MAX_COUNT];
    char dn_ou[SGD_MAX_COUNT];
    char dn_sn[SGD_MAX_COUNT + 1];
    char dn_cn[SGD_MAX_COUNT + 1];
    char dn_dc1[SGD_MAX_COUNT + 1];
    char dn_dc2[SGD_MAX_COUNT + 1];
    char dn_dc3[SGD_MAX_COUNT + 1];
    char dn_challengePassword[SGD_MAX_COUNT];
    char dn_subjectAltName[SGD_MAX_COUNT];
} SGD_NAME_INFO;

#endif //SVKD_BUILD_IWALL_DEFINE_H
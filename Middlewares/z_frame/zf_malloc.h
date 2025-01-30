/**
  *****************************************************************************
  * @file    zf_malloc.h
  * @author  Zorb
  * @version V1.0.0
  * @date    2018-06-28
  * @brief   �ڴ�����ͷ�ļ�
  *****************************************************************************
  * @history
  *
  * 1. Date:2018-06-28
  *    Author:Zorb
  *    Modification:�����ļ�
  *
  *****************************************************************************
  */

#ifndef __ZF_MALLOC_H__
#define __ZF_MALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdlib.h"
#include "string.h"
#include "./TLSF/tlsf.h"

extern tlsf_t ccm_pool_manager;

#define _ZF_MALLOC             /* �����ڴ������ */

#ifdef _ZF_MALLOC
    /* ���亯�� */
    #define ZF_MALLOC(size_) tlsf_malloc(ccm_pool_manager, size_)
    /* �ͷź��� */
    #define ZF_FREE(ptr_) tlsf_free(ccm_pool_manager, ptr_)
    /* �������� */
    #define ZF_MEMCPY(des_, src_, len_) memcpy(des_, src_, len_)
#endif /* _ZF_MALLOC */

#ifdef __cplusplus
}
#endif

#endif /* __ZF_MALLOC_H__ */

/******************************** END OF FILE ********************************/

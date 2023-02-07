/**
* @file memory_type_define.h
* @brief memory_type_defineの型定義を行います。
*/

#pragma once

#include "type_define.h"

/** 
 * 物理アドレス-8byte
 */
typedef UINT64 EFI_PHYSICAL_ADDRESS;

/** 
 * 仮想アドレス-8byte
 */
typedef UINT64 EFI_VIRTUAL_ADDRESS;

/** 
 * MEMORY_DESCRIPTORの前方宣言です
 */
struct _EFI_MEMORY_DESCRIPTOR;

/** 
 * MEMORY_DESCRIPTORの定義です
 */
struct _EFI_MEMORY_DESCRIPTOR {
    /** メモリの種類 */
    UINT32                     Type;

    /** 初めの物理アドレス */
    EFI_PHYSICAL_ADDRESS       PhysicalStart;

    /** 初めの仮想アドレス */
    EFI_VIRTUAL_ADDRESS        VirtualStart;

    /** ページ数(4KiB) */
    UINT64                     NumberOfPages;

    /** 各種属性 */
    UINT64                     Attribute;
}; 

/** 
 * MEMORY_DESCRIPTORです
 */
typedef struct _EFI_MEMORY_DESCRIPTOR EFI_MEMORY_DESCRIPTOR;
/**
* @file configuration_table.h
* @brief configuration_tableの型定義を行います。
*/

#pragma once

#include "type_define.h"

/** 
 * 構成テーブルの前方宣言です
 */
struct _EFI_CONFIGURATION_TABLE;

/** 
 * 構成テーブルの定義です
 */
struct _EFI_CONFIGURATION_TABLE {
  /** 構成テーブルの識別子です */
  EFI_GUID           VendorGuid;

  /** 構成テーブルへのポインタです　仕様は策定者に依存します　GUIDから判断してください */
  VOID               *VendorTable;
};

/** 
 * 構成テーブルです
 */
typedef struct _EFI_CONFIGURATION_TABLE EFI_CONFIGURATION_TABLE;
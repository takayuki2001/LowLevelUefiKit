/**
* @file system_table.h
* @brief system_tableの型定義を行います。
*/

#pragma once

#include "type_define.h"

#include "table_header.h"
#include "configuration_table.h"
#include "system_table/simple_text_output_protocol.h"
#include "system_table/simple_text_input_protocol.h"
#include "system_table/runtime_services.h"
#include "system_table/runtime_services.h"
#include "system_table/boot_services.h"

/** 
 * EFIのシステムテーブルの前方宣言です
 */
struct _EFI_SYSTEM_TABLE;

/** 
 * EFIのシステムテーブルの定義です
 */
struct _EFI_SYSTEM_TABLE{
    /** EFIテーブルヘッダー */
    EFI_TABLE_HEADER                 Hdr;

    /** システムファームウェアベンダ識別文字列へのポインタ */
    CHAR16                           *FirmwareVendor;

    /** システムファームウェアベンダ固有のバージョン */
    UINT32                           FirmwareRevision;

    /** ConsoleInへのハンドル */
    EFI_HANDLE                       ConsoleInHandle;

    /** EFI_SIMPLE_TEXT_INPUT_PROTOCOLインターフェイスへのポインタ */
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *ConIn;

    /** ConsoleOutへのハンドル */
    EFI_HANDLE                       ConsoleOutHandle;

    /** EFI_SIMPLE_TEXT_OUTPUT_PROTOCOLインターフェイスへのポインタ */
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;

    /** 標準エラーデバイスへのハンドル */
    EFI_HANDLE                       StandardErrorHandle;

    /** 標準エラーデバイスに対するEFI_SIMPLE_TEXT_OUTPUT_PROTOCOLインターフェイスへのポインタ */
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *StdErr;

    /** EFI_RUNTIME_SERVICESへのポインタ */
    EFI_RUNTIME_SERVICES             *RuntimeServices;
    
    /** EFI_BOOT_SERVICESへのポインタ */
    EFI_BOOT_SERVICES                *BootServices;

    /** システム構成テーブル内に存在する構成テーブルの数 */
    UINTN                            NumberOfTableEntries;

    /** システム構成テーブルへのポインタ */
    EFI_CONFIGURATION_TABLE          *ConfigurationTable;
};

/** 
 * EFIのシステムテーブルです
 */
typedef struct _EFI_SYSTEM_TABLE EFI_SYSTEM_TABLE;

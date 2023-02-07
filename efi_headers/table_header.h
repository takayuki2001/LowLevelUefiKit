/**
* @file table_header.h
* @brief EFI_TABLE_HEADERの型定義を行います。
*/

/*
    インクルードガード
*/
#ifndef __LLUK_TABLE_HEADER_INCLUDED__
#define __LLUK_TABLE_HEADER_INCLUDED__

#include "type_define.h"

/** 
 * 各種テーブルヘッダの前方宣言です
 */
struct _EFI_TABLE_HEADER;

/** 
 * 各種テーブルヘッダの定義です
 */
struct _EFI_TABLE_HEADER{
    /** このテーブルの種類を示すシグネイチャ */
    UINT64      Signature;

    /** このテーブルが対応するEFI 仕様のリビジョン */
    UINT32      Revision;

    /** このテーブルヘッダを含む”テーブル全体”のサイズ */
    UINT32      HeaderSize;

    /** このテーブルヘッダを含むテーブル全体のCRC32 */
    UINT32      CRC32;

    /** 予約領域であり０である必要があります */
    UINT32      Reserved;
}; 

/** 
 * 各種のテーブルヘッダです
 */
typedef struct _EFI_TABLE_HEADER EFI_TABLE_HEADER;

/*
    インクルードガード終わり
*/
#endif

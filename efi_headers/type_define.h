/**
* @file typedefine.h
* @brief EFIの型定義を行います。
*/

/*
    インクルードガード
*/
#ifndef __LLUK_TYPE_DEFINE_INCLUDED__
#define __LLUK_TYPE_DEFINE_INCLUDED__

/*
    アーキテクチャ定義
*/
#ifdef __X86
    #define __LLUK_ARCHITECTURE_32
#elif defined(__X64)
    #define __LLUK_ARCHITECTURE_64
#else
    #error Unknown Architecture
    
    // 補完有効化の為のダミー定義
    // 通常であれば上記マクロでコンパイル出来ない為問題なし
    #define __LLUK_ARCHITECTURE_64
#endif

//////////////////////////////////////////////////////////////////////////////////////
//
//                                      型定義
//
//////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////
//
//              Native型
//
///////////////////////////////////////////

#ifdef __LLUK_ARCHITECTURE_32

    /** 
     * unsigned int native-(CPUのBit数/4) byte
     */
    typedef unsigned int UINTN;

    /** 
     * int native-(CPUのBit数/4) byte
     */
    typedef int INTN;

#elif  defined(__LLUK_ARCHITECTURE_64)

    /** 
     * unsigned int native-(CPUのBit数/4) byte
     */
    typedef unsigned long long UINTN;

    /** 
     * int native-(CPUのBit数/4) byte
     */
    typedef long long INTN;

#endif

///////////////////////////////////////////
//
//              Native型以外
//
///////////////////////////////////////////

/** 
 * ブーリアン-1byte
 * @details 0がFalse　1がTrue それ以外は未定義
 */
typedef unsigned char BOOLEAN;
#define FALSE 0
#define TRUE  1


/** 
 * INT8-1byte
 */
typedef char INT8;

/** 
 * INT16-2byte
 */
typedef short INT16;

/** 
 * INT32-4byte
 */
typedef int INT32;

/** 
 * INT64-8byte
 */
typedef long long INT64;

/** 
 * INT128-16byte
 * @warning 未サポート
 */
typedef void INT128;

/** 
 * UINT8-1byte
 */
typedef unsigned char UINT8;


/** 
 * UINT16-2byte
 */
typedef unsigned short UINT16;

/** 
 * UINT32-4byte
 */
typedef unsigned int UINT32;

/** 
 * UINT64-8byte
 */
typedef unsigned long long UINT64;

/** 
 * UINT128-16byte
 * @warning 未サポート
 */
typedef void UINT128;

/** 
 * CHAR8-1byte
 * @details ASCII エンコード
 */
typedef unsigned short CHAR8;

/** 
 * CHAR16-2byte
 * @details UCS-2を扱うので2バイト
 */
typedef unsigned short CHAR16;

/** 
 * VOID-undefined
 */
typedef void VOID;

/** 
 * EFI_GUID-16byte
 * @details 指定がない場合8バイト＊２で16バイト
 */
typedef struct {
    UINT32      Data1;
    UINT16      Data2;
    UINT16      Data3;
    UINT8       Data4[8];
} EFI_GUID;

/** 
 * EFI_STATUS-(CPUのBit数/4) byte
 */
typedef UINTN EFI_STATUS;

/** 
 * EFI_HANDLE-(CPUのBit数/4) byte
 */
typedef VOID* EFI_HANDLE;

/** 
 * EFI_EVENT-(CPUのBit数/4) byte
 */
typedef VOID* EFI_EVENT;

/** 
 * EFI_LBA-8byte
 */
typedef UINT64 EFI_LBA;

/** 
 * EFI_TPL-(CPUのBit数/4) byte
 */
typedef UINTN EFI_TPL;

/** 
 * EFI_MAC_ADDRESS-32byte
 */
typedef CHAR8 EFI_MAC_ADDRESS[32];

/** 
 * EFI_IPv4_ADDRESS-32byte
 */
typedef CHAR8 EFI_IPv4_ADDRESS[4];

/** 
 * EFI_IPv6_ADDRESS-16byte
 */
typedef CHAR8 EFI_IPv6_ADDRESS[4];

/** 
 * EFI_IP_ADDRESS-16byte
 * @details 4バイト*4で16byte
 */
typedef UINT32 EFI_IP_ADDRESS[4];

///////////////////////////////////////////
//
//          UEFI データ型の修飾子
//
///////////////////////////////////////////

/** 
 * Datumを渡す
 */
#define IN

/** 
 * Datumが返される
 */
#define OUT

/** 
 * オプションでありNULLが入ってもOK
 */
#define OPTIONAL

/** 
 * 読み取り専用
 */
#define CONST const

/**
 * UEFI インターフェイスの呼び出し規約
*/
#define EFIAPI


//////////////////////////////////////////////////////////////////////////////////////
//
//                                終了ステータスコード
//
//////////////////////////////////////////////////////////////////////////////////////
#ifdef  __LLUK_ARCHITECTURE_32
    #define __EFI_ERROR (1 << 31)
#elif defined(__LLUK_ARCHITECTURE_64)
    #define __EFI_ERROR (1UL << 63)
#endif

///////////////////////////////////////////
//
//         正常終了ステータスコード
//
///////////////////////////////////////////

/**
 * 正常終了
*/
#define EFI_SUCCESS 0

///////////////////////////////////////////
//
//         警告終了ステータスコード
//
///////////////////////////////////////////

/**
 * 表示されない文字がありました
*/
#define EFI_WARN_UNKNOWN_GLYPH 1 

/**
 * ハンドルは閉じられましたがファイルの削除はされていません
*/
#define EFI_WARN_DELETE_FAILURE 2

/**
 * ハンドルは閉じられましたがファイルの書き込みが出来ませんでした
*/
#define EFI_WARN_WRITE_FAILURE 3

/**
 * バッファーサイズが小さかった為切り捨てが行われました
*/
#define EFI_WARN_BUFFER_TOO_SMALL 4

/**
 * ポリシーで指定された期間内に更新されていません
*/
#define EFI_WARN_STALE_DATA 5

/**
 * 結果にはUEFI準拠のファイルシステムが含まれます
*/
#define EFI_WARN_FILE_SYSTEM 6

/**
 * 操作はシステムのリセット後に処理されます
*/
#define EFI_WARN_RESET_REQUIRED 7


///////////////////////////////////////////
//
//         異常終了ステータスコード
//
///////////////////////////////////////////

/**
 * イメージロード失敗
*/
#define EFI_LOAD_ERROR 1 | __EFI_ERROR

/**
 * パラメーター間違い
*/
#define EFI_INVALID_PARAMETER 2 | __EFI_ERROR

/**
 * サポートされていない操作
*/
#define EFI_UNSUPPORTED 3 | __EFI_ERROR

/**
 * バッファーのサイズがおかしい
*/
#define EFI_BAD_BUFFER_SIZE 4 | __EFI_ERROR

/**
 * バッファーが小さいです
 * @details このエラーが発生すると要求するバッファーサイズが適当に返されます
*/
#define EFI_BUFFER_TOO_SMALL 5 | __EFI_ERROR

/**
 * この時点で返す値はありません
*/
#define EFI_NOT_READY 6 | __EFI_ERROR

/**
 * 物理デバイスがエラーを吐きました
*/
#define EFI_DEVICE_ERROR 7 | __EFI_ERROR

/**
 * 書き込めませんでした
*/
#define EFI_WRITE_PROTECTED 8 | __EFI_ERROR

/**
 * リソース不足です
*/
#define EFI_OUT_OF_RESOURCES 9 | __EFI_ERROR

/**
 * ファイルシステムの不整合が発生
*/
#define EFI_VOLUME_CORRUPTED 10 | __EFI_ERROR

/**
 * ファイルシステムが満杯です
*/
#define EFI_VOLUME_FULL 11 | __EFI_ERROR

/**
 * メディアが挿入されていません
*/
#define EFI_NO_MEDIA 12 | __EFI_ERROR

/**
 * 知らないうちにメディアに変更がありました
*/
#define EFI_MEDIA_CHANGED 13 | __EFI_ERROR

/**
 * アイテムが見つかりませんでした
*/
#define EFI_NOT_FOUND 14 | __EFI_ERROR

/**
 * アクセス拒否
*/
#define EFI_ACCESS_DENIED 15 | __EFI_ERROR

/**
 * 応答がありません
*/
#define EFI_NO_RESPONSE 16 | __EFI_ERROR

/**
 * デバイスへのマッピングがありません
*/
#define EFI_NO_MAPPING 17 | __EFI_ERROR

/**
 * タイムアウトしました
*/
#define EFI_TIMEOUT 18 | __EFI_ERROR

/**
 * プロトコルがまだ動いていません
*/
#define EFI_NOT_STARTED 19 | __EFI_ERROR

/**
 * プロトコルがすでに動いています
*/
#define EFI_ALREADY_STARTED 20 | __EFI_ERROR

/**
 * 操作が中断されました
*/
#define EFI_ABORTED 21 | __EFI_ERROR

/**
 * ICMPエラー
*/
#define EFI_ICMP_ERROR 22 | __EFI_ERROR

/**
 * TFTPエラー
*/
#define EFI_TFTP_ERROR 23 | __EFI_ERROR

/**
 * プロトコルエラー
*/
#define EFI_PROTOCOL_ERROR 24 | __EFI_ERROR

/**
 * 要求されたバージョンと互換性がありません
*/
#define EFI_INCOMPATIBLE_VERSION 25 | __EFI_ERROR

/**
 * セキュリティ違反が発生しました
*/
#define EFI_SECURITY_VIOLATION 26 | __EFI_ERROR

/**
 * CRCエラー
*/
#define EEFI_CRC_ERROR 27 | __EFI_ERROR

/**
 * メディアの終端に到達しました
*/
#define EFI_END_OF_MEDIA 28 | __EFI_ERROR

/**
 * ファイルの終端に到達しました
*/
#define EFI_END_OF_FILE 31 | __EFI_ERROR

/**
 * 無効な言語です
*/
#define EFI_INVALID_LANGUAGE 32 | __EFI_ERROR

/**
 * セキュリティ上の事由によりデータを更新してください
*/
#define EFI_COMPROMISED_DATA 33 | __EFI_ERROR

/**
 * IPアドレス競合が発生しました
*/
#define EFI_IP_ADDRESS_CONFLICT 34 | __EFI_ERROR

/**
 * HTTPエラーが発生しました
*/
#define EFI_HTTP_ERROR 35 | __EFI_ERROR

/*
    インクルードガード終わり
*/
#endif
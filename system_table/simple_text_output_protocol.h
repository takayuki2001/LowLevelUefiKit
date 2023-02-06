/**
* @file Simple_Text_Output_Protocol.h
* @brief Simple_Text_Output_Protocolの定義を行います。
*/

#pragma once

#include "../type_define.h"

//SIMPLE_TEXT_OUTPUT_PROTOCOLの前方宣言です。
struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

/** 
 * 出力デバイスをリセットします。
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] ExtendedVerification  動作確認を行うかどうか
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN BOOLEAN                                  ExtendedVerification
);

/** 
 * 文字列を出力
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] *String               CHAR16文字列へのアドレス
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR・EFI_UNSUPPORTED・EFI_WARN_UNKNOWN_GLYPH
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN CHAR16                                   *String
);

/** 
 * 文字列の中に出力不可能な文字が存在しないことを確認
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] *String               CHAR16文字列へのアドレス
 * @return EFI_SUCCESS・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_TEST_STRING) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *This,
    IN CHAR16                                        *String
);

/** 
 * 使用したいテキストモードが使用できるか調査します ダメならEFI_UNSUPPORTED
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] ModeNumber            調査するテキストモード          
 * @param[out] *Columns             指定テキストモードの列数
 * @param[out] *Rows                指定テキストモードの行数
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_QUERY_MODE) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN UINTN                                    ModeNumber,
    OUT UINTN                                   *Columns,
    OUT UINTN                                   *Rows
);

/** 
 * 指定したテキストモードに移行します
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] ModeNumber            移行するテキストモード         
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_MODE) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,
    IN UINTN                                    ModeNumber
);

/** 
 * 文字の色と背景色を指定します　0~3bitが文字色で4~6bitが背景色です
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] Attribute             色設定
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL      *This,
    IN UINTN                                        Attribute
);

/** 
 * 画面を設定されている背景色でクリアします
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL             *This
);

/** 
 * カーソルを指定位置に移動します
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] Column                列
 * @param[in] Row                   行
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL     *This,
    IN UINTN                                       Column,
    IN UINTN                                       Row
);

/** 
 * カーソルの表示状態を変更します　TRUEは表示
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL自身
 * @param[in] Visible               カーソルの状態
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL     *This,
    IN BOOLEAN                                     Visible
);

/** 
 * SIMPLE_TEXT_OUTPUT_MODEの前方宣言です
 */
struct _SIMPLE_TEXT_OUTPUT_MODE;

/** 
 * SIMPLE_TEXT_OUTPUT_MODEの定義です
 */
struct _SIMPLE_TEXT_OUTPUT_MODE {
    /** サポートされているモード数 */
    INT32                              MaxMode;

    /** 現在のモード */
    INT32                              Mode;

    /** 現在の文字色と背景色 */
    INT32                              Attribute;

    /** 現在のカーソル列 */
    INT32                              CursorColumn;

    /** 現在のカーソル行 */
    INT32                              CursorRow;

    /** 現在のカーソル表示状態 */
    BOOLEAN                            CursorVisible;
} ;

/** 
 * SIMPLE_TEXT_OUTPUT_MODEです
 */
typedef _SIMPLE_TEXT_OUTPUT_MODE SIMPLE_TEXT_OUTPUT_MODE;

/** 
 * SIMPLE_TEXT_OUTPUTのプロトタイプ
 */
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET                           Reset;
    EFI_TEXT_STRING                          OutputString;
    EFI_TEXT_TEST_STRING                     TestString;
    EFI_TEXT_QUERY_MODE                      QueryMode;
    EFI_TEXT_SET_MODE                        SetMode;
    EFI_TEXT_SET_ATTRIBUTE                   SetAttribute;
    EFI_TEXT_CLEAR_SCREEN                    ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION             SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR                   EnableCursor;
    SIMPLE_TEXT_OUTPUT_MODE                  *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
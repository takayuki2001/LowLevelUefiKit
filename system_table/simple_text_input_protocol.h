/**
* @file Simple_Text_Input_Protocol.h
* @brief Simple_Text_Input_Protocolの定義を行います。
*/
#pragma once

#include "../type_define.h"

/** 
 * EFI_INPUT_KEY
 * @details スキャンコードとUCS-2を入れられます。
 */
typedef struct _EFI_INPUT_KEY {
    UINT16  ScanCode;
    CHAR16  UnicodeChar;
} EFI_INPUT_KEY;

//仮定義しないと後方から参照がないと怒られる
struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

/** 
 * 入力デバイスをリセットします。
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_INPUT_PROTOCOL自身
 * @param[in] ExtendedVerification  動作確認を行うかどうか
 * @return EFI_SUCCESS・EFI_DEVICE_ERROR
 */
typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    IN BOOLEAN                                  ExtendedVerification
);

/** 
 * 入力を読み取る
 * 
 * @param[in] *This                 EFI_SIMPLE_TEXT_INPUT_PROTOCOL自身
 * @param[out] *Key                  格納したいEFI_INPUT_KEYへのアドレス
 * @return EFI_SUCCESS・EFI_NOT_READY・EFI_DEVICE_ERROR・EFI_UNSUPPORTED
 */
typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    OUT EFI_INPUT_KEY                           *Key
);

/** 
 * SIMPLE_TEXT_INPUTのプロトタイプ
 */
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_INPUT_RESET                       Reset;
    EFI_INPUT_READ_KEY                    ReadKeyStroke;
    EFI_EVENT                             WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

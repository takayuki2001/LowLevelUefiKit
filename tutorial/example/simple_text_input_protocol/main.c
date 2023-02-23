#include <efi_headers/type_define.h>
#include <efi_headers/system_table.h>
#include <efi_headers/system_table/simple_text_output_protocol.h>
#include <efi_headers/system_table/simple_text_input_protocol.h>

//-------------------------
//
//      GlobalVariable
//
//-------------------------
EFI_SYSTEM_TABLE *gSystemTable;

//-------------------------
//
//      　 Function
//
//-------------------------

/**
 * 何か入力があるまで待機をする。
*/
void Wait4Anykey(){
    //キー情報を格納する構造体　simple_text_input_protocol.hで定義
    EFI_INPUT_KEY inputkey;

    //メッセージを表示
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Waiting for any key...\r\n");

    //EFI_SUCCESSが帰るときキーコードが格納される。
    while (gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &inputkey) != EFI_SUCCESS);
}

/**
 * 一行入力を受ける。
*/
void getLine(CHAR16 str[]){
    //キー情報を格納する構造体　simple_text_input_protocol.hで定義
    EFI_INPUT_KEY inputkey;

    //戻り値格納用にresを定義
    EFI_STATUS res;

    //単文字列
    CHAR16 schar[] = {L'\0', L'\0'};

    //入力カーソル
    gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);

    //文字配列用index
    UINTN i = 0;

    while (1){
        //キーを取得する
        res = gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &inputkey);

        //EFI_SUCCESSが帰るときキーコードが格納される。
        if(res == EFI_SUCCESS){

            //短文字列の先頭に文字を挿入。
            schar[0] = inputkey.UnicodeChar;

            //文字を表示
            gSystemTable->ConOut->OutputString(gSystemTable->ConOut, schar);

            //Enterキーが押された場合
            if(inputkey.UnicodeChar == L'\r'){
                //短文字列の先頭に文字を挿入。
                schar[0] = L'\n';

                //文字を表示
                gSystemTable->ConOut->OutputString(gSystemTable->ConOut, schar);

                //null文字を最後に入れておわり
                str[i] = L'\0';
                return;
            }

            //文字を配列に積む
            str[i++] = inputkey.UnicodeChar;
        }
    }
}



//-------------------------
//
//          EFI
//
//-------------------------
EFI_STATUS EFIAPI EfiMain (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    //受け取ったSystemTableをグループにコピー
    gSystemTable = SystemTable;

    //戻り値格納用にresを定義
    EFI_STATUS res;

    //画面をリセット
    gSystemTable->ConOut->Reset(gSystemTable->ConOut, FALSE);

    //文字列を表示できるか確認
    res = gSystemTable->ConOut->TestString(gSystemTable->ConOut, L"ようこそ！ LowLevelUefiKit\r\n");
    if(res == EFI_SUCCESS){
        //文字列を表示！(日本語OKな環境)
        gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"ようこそ！ LowLevelUefiKit\r\n");        
    }else{
        //文字列を表示！(日本語NGの環境)
        gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Hello LowLevelUefiKit\r\n"); 
    }

    //指定したモードに対応しているかを確認する。
    //Mode 0は80x25　Mode 1は80x50　Mode 2以降は独自定義
    //Mode　2以降ではcolとrowの値を参考にしよう！
    UINTN mode = 0;
    UINTN col = 0;
    UINTN row = 0;
    res = gSystemTable->ConOut->QueryMode(gSystemTable->ConOut, mode, &col, &row);
    if(res == EFI_SUCCESS){
        //Mode 0に対応してた！
        gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"OK. Nice Device.\r\n");

        //入力待ちのカーソル
        gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);
        //Key入力待ち
        Wait4Anykey();
        //入力待ちのカーソル
        gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, FALSE);

        //Modeチェンジ！
        gSystemTable->ConOut->SetMode(gSystemTable->ConOut, mode);
        gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Mode changed!!!\r\n");

    }else{
        //Mode 0に対応したデバイス買って！！
        gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Buy compatible devices\r\n");
    }
    
    //入力待ちのカーソル
    gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);
    //Key入力待ち
    Wait4Anykey();
    //入力待ちのカーソル
    gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, FALSE);

    //文字の色属性
    UINTN Attribute;
    //文字色ルール
    //文字色　0000->黒 0001->青　0010->緑　0100->赤　0111->白 1000->明るい黒　明るさRGBで定義されます。
    //背景色　 000->黒　001->青　 010->緑 　100->赤 　111->白                RGBで定義
    //文字色と背景色のルール 背景色　0b000----　文字色　0b---0000
    //          文字色 背景色
    Attribute = 0b1111 | (0b001 << 4);

    //文字色と背景色設定を適応
    gSystemTable->ConOut->SetAttribute(gSystemTable->ConOut, Attribute);
    
    //画面クリア
    gSystemTable->ConOut->ClearScreen(gSystemTable->ConOut);

    //カーソルを雰囲気中央に移動
    gSystemTable->ConOut->SetCursorPosition(gSystemTable->ConOut, 30, 10);

    //文字を表示
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"BlueScreen!\r\n");


    ////////////////////////////////////
    //
    //
    //              追加分
    //
    //
    ////////////////////////////////////


    //文字列
    CHAR16 str[255];

    //文字列を取得
    getLine(str);

    //文字を表示
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str);
    
    //待機
    Wait4Anykey();

    return EFI_SUCCESS;
}


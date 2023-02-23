#include <efi_headers/type_define.h>
#include <efi_headers/system_table.h>
#include <efi_headers/system_table/simple_text_output_protocol.h>
#include <efi_headers/system_table/simple_text_input_protocol.h>

#define NULL 0

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
 * 1文字出力
*/
VOID putch(CHAR16 ch){
    //1文字表示するための文字列を用意
    CHAR16 str[2] = {'\0', '\0'};
    str[0] = ch;
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str);
}

/**
 * 文字列出力
*/
VOID puts(CHAR16 str[]){
    //文字列を表示
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str);
}

UINTN strlen(CHAR16 str[]){
    UINTN i = 0;
    while(str[i] != L'\0'){
        i++;
    }
    return i;
}

BOOLEAN strcmp(CHAR16 str[], CHAR16 str2[]){

    if(strlen(str) - strlen(str2) == 0){
        UINTN i = 0;
        while (str[i] != L'\0')
        {
            if(str[i] != str2[i]){
                return FALSE;
            }

            i++;
        }

        return TRUE;   
    }

    return FALSE;
}

/**
 * 文字列をリバースする
*/
VOID strswap(CHAR16 str[], UINTN length){
    length--;
    length--;
    
    for(UINTN i = 0; i <= length / 2; i++){
        CHAR16 old = str[i];
        str[i] = str[length - i];
        str[length - i] = old;
    }
}

/**
 * a^nを計算する
*/
INTN pow(INTN a, INTN n){
    if(n == 1){
        return a;
    }

    if(n == 0){
        return 1;
    }

    INTN ret = 1;
    while(n){
        if (n & 1) {
            ret *= a;
        }

        a *= a;

        n >>= 1;
    }

    return ret;
}

INTN atoi(CHAR16 str[]){
    INTN ret = 0;
    UINTN nonNullLen = strlen(str);

    for(UINTN i = 0; i < nonNullLen; i++){
        ret += (str[nonNullLen - 1 - i] - '0') * pow(10, i);
    }

    return ret;
}

VOID itoa(CHAR16 str[], INTN i){
    INTN c = 0;
    INTN mod = 0;
    do{
        mod = i % 10;
        str[c++] = mod + '0';
        i = i / 10;
    }while(i);

     str[c++] = '\0';

     strswap(str, c);
}

/**
 * 一文字を受ける。
*/
CHAR16 getch(){
    //キー情報を格納する構造体　simple_text_input_protocol.hで定義
    EFI_INPUT_KEY inputkey;

    //戻り値格納用にresを定義
    EFI_STATUS res;

    while (1){
        //キーを取得する
        res = gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &inputkey);

        //EFI_SUCCESSが帰るときキーコードが格納される。
        if(res == EFI_SUCCESS){

            //文字を表示
            puts(schar);
            return inputkey.UnicodeChar;
        }
    }
}

/**
 * 一行入力を受ける。
*/
VOID getLine(CHAR16 str[]){

    //入力カーソル
    gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);

    //文字配列用index
    UINTN i = 0;

    //文字
    CHAR16 c;

    while (1){
        //キーを取得する
        c = getch();

        //BSキーが押された場合
        if(c == '\b'){
            i--;
            continue;
        }

        //Enterキーが押された場合
        if(c == L'\r'){
                puts(L"\n");
                //null文字を最後に入れておわり  
                str[i] = L'\0';
                return;
        }

        //文字を配列に積む
        str[i++] = c;
        
    }
}

/**
 * 文字列配列を空白区切りで表示する
*/
VOID putsStrArray(CHAR16* sugs[], UINTN size){
    for(UINTN i = 0; i < size; i++){
        puts(sugs[i]);
        puts(L"  ");
    }

    puts(L"\r\n");
}

/**
 * タブキーを入力途中に押されると文字列配列を表示するgetLine
 * タブキーが押されたら-1で異常終了。
*/
INTN suggestLine(CHAR16 str[], CHAR16* sugs[], int size){

    //入力カーソル
    gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);

    //文字配列用index
    UINTN i = 0;

    //文字
    CHAR16 c;

    //単文字列
    CHAR16 schar[] = {'\0','\0'};

    while (1){
        //キーを取得する
        c = getch();

        if(c == L'\t'){
            puts(L"\r\n");
            printStrArray(sugs, size);
            return -1;
        }

        //BSキーが押された場合
        if(c == L'\b'){
            i--;
            continue;
        }

        //Enterキーが押された場合
        if(c == L'\r'){
                puts(L"\n");
                //null文字を最後に入れておわり  
                str[i] = '\0';
                return 0;
        }

        //文字を配列に積む
        str[i++] = c;
        
    }
}

/**
 * スペース区切り文字列を文字列配列に変換する
*/
INTN strSplit(CHAR16 str[], CHAR16 *args[]){

    CHAR16 *start = str;
    UINTN point_count = 0;

    args[point_count++] = start;

    for(UINTN i = 0;; i++){
        if(str[i] == '\0'){
            return point_count;
        }
        
        if(str[i] == ' '){
            str[i] = '\0';
            args[point_count++] = &(str[i + 1]);
        }
    }
}

/**
 * 何か入力があるまで待機をする。
*/
VOID Wait4Anykey(){
    //キー情報を格納する構造体　simple_text_input_protocol.hで定義
    EFI_INPUT_KEY inputkey;

    //メッセージを表示
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Waiting for any key...\r\n");

    //EFI_SUCCESSが帰るときキーコードが格納される。
    while (gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &inputkey) != EFI_SUCCESS);
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
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"BlueScreenOS!\r\n");


    ////////////////////////////////////
    //
    //
    //              追加分
    //
    //
    ////////////////////////////////////



    //コマンドラインでタブを押したときに出る候補のコマンド一覧
    CHAR16* sugs[] = {
        L"echo_str...",
        L"bc_a_op_b",
        L"ping_args...",
        L"exit"
    };

    //文字列
    CHAR16 str[255];

    //コマンド引数格納用配列
    CHAR16 *args[255];

    //コマンド受付のメインループ
    while(1){

        //入力を促すメッセージ
        puts(L"user@local>");

        //入力を求める　入力バッファ、コマンド候補一覧、コマンド候補の数
        suggestLine(str, sugs, 4);

        //入力されたコマンドを分割して引数一覧に格納する
        UINTN args_count = strSplit(str, args);

        //引数の0番目がechoならば
        if(strcmp(args[0], L"echo")){
            //＞を出力する
            puts(L">");

            //引数１以降をスペース区切りで表示
            for(UINTN i = 1; i < args_count; i++){
                puts(args[i]);
                puts(L" ");
            }

            //改行をする
            puts(L"\r\n");

        //引数の0番目がbcならば
        } else if(strcmp(args[0], L"bc")){

            //引数の数が4個であるとき
            if(args_count == 4){

                //引数1をaに代入
                INTN a = atoi(args[1]);

                //オペレーターとして引数2のポインタを代入
                CHAR16* operator = args[2];

                //引数2をbに代入
                INTN b = atoi(args[3]);
                
                //計算後の結果を格納するretを用意
                INTN ret = 0;

                //オペレータの1文字目で分岐
                switch (operator[0]) {
                case L'+':
                    // 加算の処理
                    ret = a + b;
                    break;
                case L'-':
                    // 減算の処理
                    ret = a - b;
                    break;
                case L'*':
                    // 乗算の処理
                    ret = a * b;
                    break;
                case L'/':
                    // 除算の処理
                    ret = a / b;
                    break;
                case L'%':
                    // modの処理
                    ret = a % b;
                    break;
                default:
                    // 想定外の演算子が与えられた場合の処理
                    puts(L"Operator error[");
                    puts(args[2]);
                    puts(L"]");
                    goto bc_end;
                    break;
                }

                //int からcharに変換後に代入されるバッファ
                CHAR16 xstr[255];

                //intからcharに変換　バッファ　int
                itoa(xstr, ret);

                //計算結果を表示
                puts(xstr);
            }else{
                //引数の数が違う場合
                puts(L"The number of arguments seems a bit wonky. Please check and try again.");
            }

            bc_end:
            puts(L"\r\n");
        }

        //pingコマンドであれば
        if(strcmp(args[0], L"ping")){
            puts(L"                    _    Ping says.\r\n");
            puts(L"   __------__     (  \\    Open cmd on Windows and type 'ping'.\r\n");
            puts(L"  /          \\    |  |    Are you sure?\r\n");
            puts(L" ( ( .)   ( .) )  |  | \r\n");
            puts(L"  >    []     <   /  / \r\n");
            puts(L" /             \\/  /  \r\n");
        }

        
        //pingコマンドであれば
        if(strcmp(args[0], L"exit")){
            puts(L"Bye.\r\n");
            break;
        }

    //メインループのためここでループ先頭に戻り次の入力を待機する。
    }

    //待機
    Wait4Anykey();

    return EFI_SUCCESS;
}
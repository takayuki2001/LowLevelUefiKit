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

void putch(CHAR16 ch){
    //文字を表示
    CHAR16 str[2] = {'\0', '\0'};
    str[0] = ch;
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str);
}

void print(CHAR16 str[]){
    //文字を表示
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

//836\ 5 -> i < 4
void strswap(CHAR16 str[], int length){
    length--;
    length--;
    
    for(int i = 0; i <= length / 2; i++){
        CHAR16 old = str[i];
        str[i] = str[length - i];
        str[length - i] = old;
    }
}

int pow(int a, int n){
    if(n == 1){
        return a;
    }

    if(n == 0){
        return 1;
    }

    int ret = 1;
    while(n){
        if (n & 1) {
            ret *= a;
        }

        a *= a;

        n >>= 1;
    }

    return ret;
}

int atoi(CHAR16 str[]){
    int ret = 0;
    int nonNullLen = strlen(str);

    for(int i = 0; i < nonNullLen; i++){
        ret += (str[nonNullLen - 1 - i] - '0') * pow(10, i);
    }

    return ret;
}

void itoa(CHAR16 str[], int i){
    int c = 0;
    int mod = 0;
    do{
        mod = i % 10;
        str[c++] = mod + '0';
        i = i / 10;
    }while(i);

     str[c++] = '\0';

     strswap(str, c);
}

/**
 * 一行入力を受ける。
*/
CHAR16 getch(){
    //キー情報を格納する構造体　simple_text_input_protocol.hで定義
    EFI_INPUT_KEY inputkey;

    //戻り値格納用にresを定義
    EFI_STATUS res;

    //単文字列
    CHAR16 schar[] = {'\0','\0'};

    while (1){
        //キーを取得する
        res = gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &inputkey);

        //EFI_SUCCESSが帰るときキーコードが格納される。
        if(res == EFI_SUCCESS){

            //短文字列の先頭に文字を挿入。
            schar[0] = inputkey.UnicodeChar;

            //文字を表示
            print(schar);

            return inputkey.UnicodeChar;
        }
    }
}

/**
 * 一行入力を受ける。
*/
void getLine(CHAR16 str[]){

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

        //BSキーが押された場合
        if(c == '\b'){
            i--;
            continue;
        }

        //Enterキーが押された場合
        if(c == L'\r'){
                print(L"\n");
                //null文字を最後に入れておわり  
                str[i] = L'\0';
                return;
        }

        //文字を配列に積む
        str[i++] = c;
        
    }
}

void printStrArray(CHAR16* sugs[], int size){
    for(int i = 0; i < size; i++){
        print(sugs[i]);
        print(L"  ");
    }

    print(L"\r\n");
}

int suggestLine(CHAR16 str[], CHAR16* sugs[], int size){

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
            print(L"\r\n");
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
                print(L"\n");
                //null文字を最後に入れておわり  
                str[i] = '\0';
                return 0;
        }

        //文字を配列に積む
        str[i++] = c;
        
    }
}

int strSplit(CHAR16 str[], CHAR16 *args[]){

    CHAR16 *start = str;
    int point_count = 0;

    args[point_count++] = start;

    for(int i = 0;; i++){
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
void Wait4Anykey(){
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


    //文字列
    CHAR16 str[255];

    //文字列を取得
    //getLine(str);A
    CHAR16* sugs[] = {
        L"echo_str...",
        L"bc_a_op_b",
        L"ping_args..."
    };
    
    while(1){
        print(L"user@local>");
        suggestLine(str, sugs, 3);

        CHAR16 *args[255];
        int args_count = strSplit(str, args);
 
        if(strcmp(args[0], L"echo")){
            print(L">");
            for(int i = 1; i < args_count; i++){
                print(args[i]);
                print(L" ");
            }
            print(L"\r\n");
        } 

        if(strcmp(args[0], L"bc")){
            if(args_count == 4){
                int a = atoi(args[1]);
                CHAR16* operator = args[2];
                int b = atoi(args[3]);
                int ret = 0;

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
                    print(L"Operator error[");
                    print(args[2]);
                    print(L"]");
                    goto bc_end;
                    break;
                }

                CHAR16 xstr[255];
                itoa(xstr, ret);
                print(xstr);
            }else{
                print(L"The number of arguments seems a bit wonky. Please check and try again.");
            }

            bc_end:
            print(L"\r\n");
        }

        if(strcmp(args[0], L"ping")){
            print(L"                    _    Ping says.\r\n");
            print(L"   __------__     (  \\    Open cmd on Windows and type 'ping'.\r\n");
            print(L"  /          \\    |  |    Are you sure?\r\n");
            print(L" ( ( .)   ( .) )  |  | \r\n");
            print(L"  >    []     <   /  / \r\n");
            print(L" /             \\/  /  \r\n");
        }
    }

    print(str);
    print(L"\r\n");


    
    //待機
    Wait4Anykey();

    return EFI_SUCCESS;
}


# UEFIチュートリアル
## 必要な物
1. WindowsPC
1. PC操作の基本
1. C言語の簡単な知識
2. 新品のUSBメモリ（データの内容は消えます）
3. セキュアブートが無効化できるPC
1. Visual Studio Code（以下VS Code）
1. 知らない単語・分からない箇所が出てきたら　○○とは、○○のやり方、などで検索が行える能力

### あると便利な物
1. サブのPC
1. 拡張子が表示状態のエクスプローラー

### 注意事項
本文書に対しての何らかの保証はなく、内容に基づくいかなる結果に対しても一切の責任を負いません。

## ソフトウェアが動くまで

### OSとは
皆さんは普段Windowsを使っていると思います。そしてインターネットで調べ物をしたければWindowsを起動してからブラウザを起動すると思います。
私はこれを不思議だと思います。それはなぜでしょうか？
考えてみてください。私は調べ物をするためにブラウザを起動したいわけです。別にWindowsを起動したいわけではありません。なぜブラウザを起動するためにWindowsを起動しなければいけないのでしょうか？邪魔ですね！

そんな不思議なWindowsの存在意義を説明したいと思います。Windwosはブラウザ以外のソフトウェアを同時に起動できるようにしたりセキュリティを守る役割を担っています。例えば音楽を聞きながらゲームをするといった事はよくある事があると思います。この時ゲームとブラウザを同時起動できるように二つのソフトウェアを管理してくれているのがWindowsです。

ちなみにWindowsというのはMicrosoftが開発・販売している物ですが競合他社製品としてUbuntuやAndroidなどの製品があります。これらの事をOSと呼びます。これはプリウスやフェアレディZに対する車のような物です。

### UEFIとは
OSがソフトウェア管理などを行ってくれることが分かりました。つまりはソフトウェアの起動はOSが行っています。ですがOSは誰が起動するのでしょうか？それはUEFIです。それでは何故UEFIがOSを起動しているのでしょうか？それはUEFIが管理する対象にあります。OSはソフトウェアの管理をメインとしますがUEFIはハードウェアの管理をメインとします。例えば電圧を下げたりファンのスピードを変えたりです。この様にハードウェアとOSを分割することにより多様性を高めています。

![ComputerLineUEFI_OS_SOFTWARE](./img/ComputerLineUEFI_OS_SOFTWARE.png "ComputerLineUEFI_OS_SOFTWARE")

## UEFIでアプリケーションを動かそう。

### なぜUEFIなのか？
UEFIは上記の通りOSよりも下にあり、情報が少ない分野です。ですがUEFIはOS起動までの仕事を担っておりその役割は単純ですが重要です。そんなUEFIアプリケーションを作ることを通じてセキュリティやプログラム実行の仕組み・C言語について深く学べる数少ない教材であり、各ソフトウェアの国産化を目指すのであれば決して無視できない領域です。

### WSLのセットアップ
Windows Subsystem for Linux 通称WSLという機能があります。今回はこれを用いて作業をしていきます。そこでまずWSLのセットアップを行う必要があります。

#### Windows11の場合
2023年1月現在では　__Microsoft Store__　の検索からWSLを検索し　__Windows Subsystem for Linux__　をインストール後に __Ubuntu__ と検索をし　__Ubuntu__　もインストールします。更に　__Windows の機能の有効化または無効化__　から　__仮想マシンプラットフォーム__　を有効化しましょう。この３つのインストールが終わったら再起動をして完了です。

#### Windows10の場合
コマンドプロンプトを __管理者権限__ で起動し`wsl --install`コマンドを実行してください。

### Ubuntuの起動
WSLとUbuntuのインストールと仮想マシンプラットフォームを有効化が __終わったら__ Ubuntuを起動していきます。　__初回起動時にユーザー名とパスワードの設定を求められるのでこのパスワードを忘れずに覚えておいてください__　__（パスワード入力中は＊＊＊など入力のサインはありません）。__

補足：一部環境でエラーが発生するそうです。対処法へのリンクを張るのでエラーになった際には確認してみてください。(AppDataフォルダは隠しフォルダであるため表示設定をしないと表示されません)
https://qiita.com/kuryus/items/27a7206c64eca7ba710b

### 各種環境設定
セットアップが終了したら

``` bash
git clone https://github.com/takayuki2001/LowLevelUefiKit.git
cd LowLevelUefiKit/tutorial/
```
を実行します。

次に
``` bash
sudo ./setup.sh
make setup
```
を実行します。もしもパスワード入力が求められた場合は初回起動時に設定したパスワードを入力してください。

それが終わったら
``` bash
make hello_world
```
を実行しUEFIアプリケーションを起動できます。
その後は立ち上がったUEFIアプリケーションではなくWSLの画面で __q__ を入力し終了させましょう。

### UEFIアプリケーションにおける文字表示のプロセスを確認しよう。
`\\wsl$\Ubuntu\home\user_name\LowLevelUefiKit`
をExplorerのアドレスバーに入力するとWindows上でフォルダを開く事が出来ます。
**Warning**
ディレクトリアドレスにある`user_name`は適宜設定したユーザー名に置き換えてください。

そして __LowLevelUefiKit.code-workspace__ をVS Codeで開きましょう。

`LowLevelUefiKit/tutorial/example/hello_world/main.c`を開いてみましょう。

まずIncludeから確認をしていきます。
``` C
#include <efi_headers/type_define.h>
#include <efi_headers/system_table.h>
```
この二つのみがインクルードされています。
まず上部の __type_define.h__ (場所: __LowLevelUefiKit/efi_headers/table_header.h__ )では型のtypedefが大量に並んでいます。
又、INやOUTといった修飾子マクロも定義されています。

__system_table.h__ (場所: __LowLevelUefiKit/efi_headers/system_table.h__ )では構造体が定義されています。詳細は後述します。
ここで注目したいのは __stdio.h__ 等の標準ライブラリは一切使用されていない事です。

次に来るのはグローバル変数
``` C
EFI_SYSTEM_TABLE *gSystemTable;
```
です。

これはsystem_table.hで定義されている構造体 __EFI_SYSTEM_TABLE__ のポインタ格納用変数です。UEFIではEFI_SYSTEM_TABLE構造体を大変よく使います。そこでグローバル変数としてソースコード全体で使えるように定義しています。

次は __EfiMain__ 関数です。これは通常のmain関数に相当します。
``` C
EFI_STATUS EFIAPI EfiMain (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
```
main関数の引数に対し通常であれば引数へのポインタが渡されますがUEFIアプリケーションでは __EFI_HANDLE__ と __EFI_SYSTEM_TABLE__ へのポインタがマザーボードより渡されます。EFI_HANDLEは本書で使用しないため解説をしません。

次は
``` C
gSystemTable = SystemTable;
```
です。これは単純に受け取った引数をグローバルポインタとして保存しています。

次にここで文字列を表示しています。
``` C
gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Hello LowLevelUefiKit");
```
EFI_SYSTEM_TABLE構造体に定義されている構造体 __ConOut__(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL型)で定義されている関数 __OutputString__ 関数を呼び出しています。

第一引数には __ConOut自身を渡し__ 第二引数には __L"文字列"__　の形で文字配列を渡しています。

ここで使ったことがない人が多いであろう __L__ について解説します。これはUnicode文字を表す記号です。Lをつけることで一文字2バイトとして取り扱われ日本語などの表示も可能になります。UEFIでは文字は常に2バイトで定義されておりLなしで定義すると1バイト扱いとなりバグります。

そのため __今後文字や文字列を扱う際には必ずLをつけること__ を意識してください。また、 __文字、文字配列を宣言する際には必ずCHAR16を用いて2バイトで文字、文字列を使うようにしてください。__

その後は終了防止のwhile無限ループと実行されることのない成功を返すreturnがたたずんでいます。
``` C
while (1){}
return EFI_SUCCESS;
```

これでUEFIアプリケーションの完成です！おめでとうございます。

## UEFIでアプリケーションを実機で動かそう

### USBメモリのセットアップ
まずUSBメモリをFAT32でフォーマットする必要があります。
1. __ディスクの管理__ を起動します。
1. 上部に表示されている __ボリューム一覧__ を確認します。 
2. USBメモリをPCに差します。
3. 上部に表示されているボリューム一覧に指したUSBメモリが追加されます。
4. 追加された名前を参考に __下部のディスク一覧__ からUSBメモリを探します。
5. 青色のボリューム __がある場合は__ 右クリックでボリューム一を削除し続けます。（ __削除できないボリュームは無視で構いません。__）
6. 黒色になった部分を選択し右クリックから新しくシンプルボリュームを作成をクリック
7. 次へを __３回__ 押し __ファイルシステムをFAT32にします。__
8. 次へを押して完了を押します。
9. エクスプローラーにさっき作ったボリュームが出現するのでそのボリュームを開きます。
10. その中にEFIフォルダを作成。その中にBOOTフォルダを作成します。(例:USB:\\\\EFI\BOOT\\)
11. そのBOOTフォルダの中に`\\wsl$\Ubuntu\home\user_name\LowLevelUefiKit\tutorial\BOOTX64.EFI`を移動します。

これで準備が出来ました！
USBをPCに差して起動してみましょう。

起動の仕方はWindowsの __設定__ から __WindowsUpdate__ を開き __詳細オプション__ を開き __回復__ を開き __PCの起動をカスタマイズ__ を押します。

再起動したら __デバイスの使用__ を選択し __EFI USB Device__ を選択します。
Hello LowLevelUefiKitが表示されたら成功です。

もし表示されなければセキュアブートを無効にしましょう！
（セキュアブートの無効化方法は機種によってかなり違います。その為 __調べるか__ PCを購入したお店やメーカーに問い合わせをしてください。）
https://www.google.com/search?q=%E3%82%BB%E3%82%AD%E3%83%A5%E3%82%A2%E3%83%96%E3%83%BC%E3%83%88%E7%84%A1%E5%8A%B9%E5%8C%96

### 何故セキュアブートの無効化が必要か？
まずセキュアブートとは信頼された企業や団体以外のUEFIアプリケーション実行を拒否するものです。

拒否する必要性はWindowsを暗号化して金銭要求するようなUEFIアプリケーションがあったとします。通常であればOSのセキュリティ機能などで検出がなされます。ですがUEFIアプリケーションはOSのセキュリティ機能の影響を受けません。その為UEFIアプリケーション悪さし放題なのです。これでは問題なので特定の企業や団体以外が作ったUEFIアプリケーションの実行はデフォルトで拒否されています。

### セキュアブートの問題点と使い方
世の中にはWindwos以外のOSが複数あります。その中で特に無料のものなどはセキュアブートに対応していない事があります。その為必然的にセキュアブートを無効化して使うことになりますが、セキュアブートが無効だと悪いUEFIアプリケーションが動く可能性があります。そこでUEFIには信頼する特定の企業や団体を自分で追加できる機能が用意されています。そのような機能を駆使すれば安心してWindwos以外のOSを使うことが出来ます。

## UEFIで他の機能を呼び出してみよう

### 遂に内製化!!
ここからはUEFIの他の機能をいつくか紹介していきます。
一般的なOSでは起動時のみUEFIを活用し、起動が始まったらOS自身がUEFIを頼らずにキーボードやマウスを管理します。つまりUEFIの機能を多く使いません。ですがこれはOSだから自前管理が必要なのであり特定用途に向けたUEFIアプリケーションではこれらの機能を上手く使うことによって国産化をすることが出来ます。しかも簡単に！！その為に代表的なUEIF機能をいくつか紹介してみようと思います。

（本当に一部なので詳細は仕様書を見てみてください）

### OUTPUT
__Simple Text Output Protocol__ というものを使うとテキストを出力することが出来ます。(正確にはテキスト出力関係全般が使えます)
これは __LowLevelUefiKit/efi_headers/system_table/simple_text_output_protocol.h__ に定義されています。

``` C
/** 
 * SIMPLE_TEXT_OUTPUTのプロトタイプ
 */
struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET                           Reset;         //関数
    EFI_TEXT_STRING                          OutputString;  //関数
    EFI_TEXT_TEST_STRING                     TestString;    //関数
    EFI_TEXT_QUERY_MODE                      QueryMode;     //関数
    EFI_TEXT_SET_MODE                        SetMode;       //関数
    EFI_TEXT_SET_ATTRIBUTE                   SetAttribute;  //関数
    EFI_TEXT_CLEAR_SCREEN                    ClearScreen;   //関数
    EFI_TEXT_SET_CURSOR_POSITION             SetCursorPosition;//関数
    EFI_TEXT_ENABLE_CURSOR                   EnableCursor;  //関数
    SIMPLE_TEXT_OUTPUT_MODE                  *Mode;         //構造体
};
```
重要個所を抜粋してみました。EFI_TEXT_RESET～EFI_TEXT_ENABLE_CURSORまでの９個の関数とSIMPLE_TEXT_OUTPUT_MODEという一つの構造体が定義されています。

UEFIにおいてはこのような __構造体を活用してプログラムを作成していく__ ことになります。

このSimple Text Output Protocolをフル活用したサンプルプログラムを       __LowLevelUefiKit/tutorial/example/simple_text_output_protocol/main.c__ として用意しました。
ここからはこれをベースに解説をしていきます。

早速ですがおまじないがあります。それはWait4Anykey関数です。これは次で解説をするsimple_text_input_protocolを活用しているので解説は少々お待ちください。動作としては何かキーが押されるまで待機するというメッセージ出力とそのメッセージ通り何かキーが押されるまで待機するだけです。

``` C
    //画面をリセット
    gSystemTable->ConOut->Reset(gSystemTable->ConOut, FALSE);
```
を用いてコンソール画面を初期化しています。

``` C
    //戻り値格納用にresを定義
    EFI_STATUS res;

    //文字列を表示できるか確認
    res = gSystemTable->ConOut->TestString(gSystemTable->ConOut, L"ようこそ！ LowLevelUefiKit\r\n");
``` 
EFI_STATUS res;は戻り値を格納するための変数です。例えばEFI_SUCCESSなどが入ります。
TestString関数は引数で与えられた文字列が表示可能か（フォントが存在しているか）を確認します。
つまりその次の `if(res == EFI_SUCCESS){` では日本語フォントが存在しているかを判定した結果が判定成功であれば日本語文メッセージを表示しています。（英字フォントは当然として存在しているものとしています。）

``` C
    //指定したモードに対応しているかを確認する。
    //Mode 0は80x25　Mode 1は80x50　Mode 2以降は独自定義
    //Mode　2以降ではcolとrowの値を参考にしよう！
    UINTN mode = 0;
    UINTN col = 0;
    UINTN row = 0;
    res = gSystemTable->ConOut->QueryMode(gSystemTable->ConOut, mode, &col, &row);
    if(res == EFI_SUCCESS){
```
QueryModeは指定したクエリモードに対応しているかを調べる関数になります。ここでいうクエリモードとは80x25の文字表示コンソールや80x50コンソールなどコンソールの行列のことを指します。ここではモード0である80x25の文字表示に対応をしているか調べています。もし80x50以上の行列に対応している場合はベンダー独自で2番以降が割り当てられそのモードの行列は引数で返されます。

``` C
        //入力待ちのカーソル
        gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);
        //Key入力待ち
        Wait4Anykey();
        //入力待ちのカーソル
        gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, FALSE);
        
         //Modeチェンジ！
        gSystemTable->ConOut->SetMode(gSystemTable->ConOut, mode);
```
ではEnableCursorを用いてコンソールカーソルをONにしてキー入力を待ちます。そしてカーソルをOFFを切り替えています。その後SetMode関数を用いてコンソールをモード0に設定しています。この際明確な規定はありませんがコンソールはリセットされます。

``` C
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
```
ではコンソールの色を設定しています。色オプションは計7bitで表します。下位4bitは文字色を表し上位3bitで背景色を表します。文字色の表し方は（明暗）（R）（G）（B）となり、背景色では明暗が消え、（R）（G）（B）となります。尚、光の三原色です。このルールで定めたオプションをSetAttribute関数で適応しています。

``` C
    //画面クリア
    gSystemTable->ConOut->ClearScreen(gSystemTable->ConOut);
```
では現在のコンソールをクリアします。色を設定後にクリアすることで背景色と文字色を適応しつつ画面をクリアしています。

``` C
    //カーソルを雰囲気中央に移動
    gSystemTable->ConOut->SetCursorPosition(gSystemTable->ConOut, 30, 10);

    //文字を表示
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"BlueScreen!\r\n");
```
ではコンソールのカーソルを雰囲気真ん中に移動させます（Mode 0は80x25であるため）。そして雰囲気真ん中にL"BlueScreen!\r\n"を表示しています。

SIMPLE_TEXT_OUTPUT構造体の中で解説していないものはSIMPLE_TEXT_OUTPUT_MODE　*Mode;のみとなりましたが、これは現在のモードの情報が格納されています。

以上でOUTPUTの解説は以上となります。

### INPUT
Simple Text Input Protocolというものを使うとテキストを出力することが出来ます。プロトコルを実行することが出来ます。
これは efi_headers/system_table/simple_text_input_protocol.hに定義されています。

``` C
/** 
 * SIMPLE_TEXT_INPUTのプロトタイプ
 */
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_INPUT_RESET                       Reset;
    EFI_INPUT_READ_KEY                    ReadKeyStroke;
    EFI_EVENT                             WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
```
重要個所を抜粋してみました。今回は２個の関数と1つのイベントを持つ構造体が定義されています。
Reset関数は入力デバイスをリセットします。ReadKeyStrokey関数では今この瞬間に押されているキーを取得します。
EFI_EVENT WaitForKeyは別で定義されているイベントシステムに渡すための引数です。

このsimple_text_input_protocolを活用したサンプルプログラムをsimple_text_input_protocolの下にmain.cとして用意しました。
ここからはこれをベースに解説をしていきます。

getLine関数を見てみましょう！

``` C
    //キー情報を格納する構造体　simple_text_input_protocol.hで定義
    EFI_INPUT_KEY inputkey;

    //戻り値格納用にresを定義
    EFI_STATUS res;

    //単文字列
    CHAR16 schar[] = {'\0','\0'};

    //入力カーソル
    gSystemTable->ConOut->EnableCursor(gSystemTable->ConOut, TRUE);
```
EFI_INPUT_KEY inputkey;ではキー情報を格納する構造体を作っています。

``` C
/** 
 * EFI_INPUT_KEY
 * @details スキャンコードとUCS-2を入れられます。
 */
struct _EFI_INPUT_KEY {
    UINT16  ScanCode;
    CHAR16  UnicodeChar;
};
```
EFI_INPUT_KEYは上記のように定義され、スキャンコードとユニコードが格納されています。
CHAR16 schar[] = {'\0','\0'};では一文字のみ格納するような文字列を作成しています。
そのほかは説明済みなので省略します。

``` C
        //キーを取得する
        res = gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &inputkey);

        //EFI_SUCCESSが帰るときキーコードが格納される。
        if(res == EFI_SUCCESS){
```
ではReadKeyStrokeを用いてこの関数が実行された瞬間のキー情報を取得します。ですがこの関数の実行時、何もキーが押されていない場合はエラーとして戻ります。そこでEFI_SUCCESSか比較することでキーが押されたかを判定します。ただし、一度読み込まれたキーは離されて再度押されるまでEFI_SUCCESSを返すことはないため一瞬のキープッシュで大量の文字が打たれることはありません。

``` C
            //短文字列の先頭に文字を挿入。
            schar[0] = inputkey.UnicodeChar;

            //文字を表示
            gSystemTable->ConOut->OutputString(gSystemTable->ConOut, schar);
```
構造体に入っているUnicodeを文字列として扱うためにschar[0]に代入をしそれを表示しています。
これは入力されたキーを表示しユーザーにフィードバックを与えています。

``` C
            //文字を配列に積む
            str[i++] = inputkey.UnicodeChar;
```
そして文字列を受け取るバッファに対して受け取った文字を挿入しています。

``` C
            //Enterキーが押された場合
            if(inputkey.UnicodeChar == '\r'){
                //短文字列の先頭に文字を挿入。
                schar[0] = '\n';

                //文字を表示
                gSystemTable->ConOut->OutputString(gSystemTable->ConOut, schar);

                //null文字を最後に入れておわり
                str[i] = '\0';
                return;
            }
```
もし文字入力の中でエンターキーが押された場合は\r（エンターキー）は出力されているので足りていない\nを追加で表示し、null文字をバッファの最後に入れます。

### Let's make OS!
それでは今までの知見を生かしていくつかの動作を提供するようなOSを作成してみましょう。

やはりサンプルプログラムをsimple_osの下にmain.cとして用意しました。

基本的に関数整備を行っています。Cの標準ライブラリに沿ったような関数になっていますので各自で動作を確認してみてください。

## 最後に
実際に今回得た知識が即時就職活動や業務で活きる機会はないと思います。ですがコンピューターの構造や起動プロセスを知り考えることは新しいプログラミング技法の発見や新しいプロダクトのアイデア、外注時注意したい項目の洗い出し、アルゴリズムを超えた＋αの高速化などアドバンテージを取るのに役に立つと思います！！

### 本文書について
本文書に記載されている会社名、製品名はそれぞれ各社の商標及び登録商標です。本文書では™、®、©は割愛させて頂いております。
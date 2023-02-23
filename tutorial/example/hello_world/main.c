#include <efi_headers/type_define.h>
#include <efi_headers/system_table.h>

//-------------------------
//
//      GlobalVariable
//
//-------------------------
EFI_SYSTEM_TABLE *gSystemTable;

//-------------------------
//
//          EFI
//
//-------------------------
EFI_STATUS EFIAPI EfiMain (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    //受け取ったSystemTableをグループにコピー
    gSystemTable = SystemTable;

    //文字列を出力
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"Hello LowLevelUefiKit");

    //すぐ終わらないように待つ
    while (1){}
    
    return EFI_SUCCESS;
}


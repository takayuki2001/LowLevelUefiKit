#pragma once

#include "../../type_define.h"

typedef EFI_TPL (EFIAPI   *EFI_RAISE_TPL) (
    IN EFI_TPL  NewTpl
);

typedef VOID (EFIAPI *EFI_RESTORE_TPL) (
    IN EFI_TPL  OldTpl
);
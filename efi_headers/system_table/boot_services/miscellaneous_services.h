#pragma once

#include "../../type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
    OUT UINT64                       *Count
);

typedef EFI_STATUS (EFIAPI *EFI_STALL) (
    IN UINTN                Microseconds
);

typedef EFI_STATUS (EFIAPI *EFI_SET_WATCHDOG_TIMER) (
    IN UINTN                          Timeout,
    IN UINT64                         WatchdogCode,
    IN UINTN                          DataSize,
    IN CHAR16                         *WatchdogData OPTIONAL
);
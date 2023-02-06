#pragma once

#include "../../type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD) (
    IN EFI_HANDLE           ImageHandle
);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_START) (
    IN EFI_HANDLE                             ImageHandle,
    OUT UINTN                                 *ExitDataSize,
    OUT CHAR16                                **ExitData OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_EXIT) (
    IN EFI_HANDLE                      ImageHandle,
    IN EFI_STATUS                      ExitStatus,
    IN UINTN                           ExitDataSize,
    IN CHAR16                          *ExitData OPTIONAL
); 

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD) (
    IN EFI_HANDLE           ImageHandle
);

typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES) (
    IN EFI_HANDLE                       ImageHandle,
    IN UINTN                            MapKey
);
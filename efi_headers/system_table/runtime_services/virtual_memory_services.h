#pragma once

#include "../../type_define.h"
#include "../../memory_type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
   IN UINTN                 MemoryMapSize,
   IN UINTN                 DescriptorSize,
   IN UINT32                DescriptorVersion,
   IN EFI_MEMORY_DESCRIPTOR *VirtualMap
);

typedef EFI_STATUS (EFIAPI *EFI_CONVERT_POINTER) (
   IN UINTN             DebugDisposition,
   IN VOID              **Address
);


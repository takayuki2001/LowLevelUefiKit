#pragma once

#include "../../type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE) (
    IN CHAR16           *VariableName,
    IN EFI_GUID         *VendorGuid,
    OUT UINT32          *Attributes OPTIONAL,
    IN OUT UINTN        *DataSize,
    OUT VOID            *Data OPTIONAL
);

typedef EFI_STATUS (EFIAPI * EFI_GET_NEXT_VARIABLE_NAME) (
    IN OUT UINTN           *VariableNameSize,
    IN OUT CHAR16          *VariableName,
    IN OUT EFI_GUID        *VendorGuid
);

typedef EFI_STATUS (EFIAPI *EFI_SET_VARIABLE) (
    IN CHAR16            *VariableName,
    IN EFI_GUID          *VendorGuid,
    IN UINT32            Attributes,
    IN UINTN             DataSize,
    IN VOID              *Data
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_VARIABLE_INFO) (
    IN UINT32             Attributes,
    OUT UINT64            *MaximumVariableStorageSize,
    OUT UINT64            *RemainingVariableStorageSize,
    OUT UINT64            *MaximumVariableSize
);
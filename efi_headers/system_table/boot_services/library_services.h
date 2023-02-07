#pragma once

#include "../../type_define.h"

#include "locate_type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
    IN EFI_HANDLE                             Handle,
    OUT EFI_GUID                              ***ProtocolBuffer,
    OUT UINTN                                 *ProtocolBufferCount
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
    IN EFI_LOCATE_SEARCH_TYPE                    SearchType,
    IN EFI_GUID                                  *Protocol OPTIONAL,
    IN VOID                                      *SearchKey OPTIONAL,
    OUT UINTN                                    *NoHandles,
    OUT EFI_HANDLE                               **Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL) (
    IN EFI_GUID                            *Protocol,
    IN VOID                                *Registration OPTIONAL,
    OUT VOID                               **Interface
);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN OUT EFI_HANDLE                               *Handle,
    ...
);

typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN EFI_HANDLE Handle,
    ...
);
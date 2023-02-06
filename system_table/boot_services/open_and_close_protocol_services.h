#pragma once

#include "../../type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL) (
    IN EFI_HANDLE                    Handle,
    IN EFI_GUID                      *Protocol,
    OUT VOID                         **Interface OPTIONAL,
    IN EFI_HANDLE                    AgentHandle,
    IN EFI_HANDLE                    ControllerHandle,
    IN UINT32                        Attributes
);

typedef EFI_STATUS (EFIAPI *EFI_CLOSE_PROTOCOL) (
    IN EFI_HANDLE                 Handle,
    IN EFI_GUID                   *Protocol,
    IN EFI_HANDLE                 AgentHandle,
    IN EFI_HANDLE                 ControllerHandle
);

typedef struct {
    EFI_HANDLE                          AgentHandle;
    EFI_HANDLE                          ControllerHandle;
    UINT32                              Attributes;
    UINT32                              OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
    IN EFI_HANDLE                             Handle,
    IN EFI_GUID                               *Protocol,
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   **EntryBuffer,
    OUT UINTN                                 *EntryCount
);
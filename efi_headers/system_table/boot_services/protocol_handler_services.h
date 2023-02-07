#pragma once

#include "../../type_define.h"
#include "protocols/device_path_protocol.h"
#include "locate_type_define.h"

typedef enum {
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
    IN OUT EFI_HANDLE       *Handle,
    IN EFI_GUID             *Protocol,
    IN EFI_INTERFACE_TYPE   InterfaceType,
    IN VOID                 *Interface
);

typedef EFI_STATUS (EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE           Handle,
    IN EFI_GUID             *Protocol,
    IN VOID                 *OldInterface,
    IN VOID                 *NewInterface
);

typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE        Handle,
    IN EFI_GUID          *Protocol,
    IN VOID              *Interface
);

typedef EFI_STATUS (EFIAPI *EFI_HANDLE_PROTOCOL) (
    IN  EFI_HANDLE                    Handle,
    IN  EFI_GUID                      *Protocol,
    OUT VOID                          **Interface
);

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
    IN  EFI_GUID                         *Protocol,
    IN  EFI_EVENT                        Event,
    OUT VOID                             **Registration
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE) (
    IN      EFI_LOCATE_SEARCH_TYPE                  SearchType,
    IN      EFI_GUID                                *Protocol OPTIONAL,
    IN      VOID                                    *SearchKey OPTIONAL,
    IN OUT  UINTN                                   *BufferSize,
    OUT     EFI_HANDLE                              *Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_DEVICE_PATH) (
    IN      EFI_GUID                        *Protocol,
    IN OUT  EFI_DEVICE_PATH_PROTOCOL        **DevicePath,
    OUT     EFI_HANDLE                      *Device
);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
    IN EFI_GUID                               *Guid,
    IN VOID                                   *Table
);
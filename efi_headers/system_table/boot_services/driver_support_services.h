#pragma once

#include "../../type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_CONNECT_CONTROLLER) (
    IN EFI_HANDLE                       ControllerHandle,
    IN EFI_HANDLE                       *DriverImageHandle OPTIONAL,
    IN EFI_DEVICE_PATH_PROTOCOL         *RemainingDevicePath OPTIONAL,
    IN BOOLEAN Recursive
);

typedef EFI_STATUS (EFIAPI *EFI_DISCONNECT_CONTROLLER) (
    IN EFI_HANDLE                       ControllerHandle,
    IN EFI_HANDLE                       DriverImageHandle OPTIONAL,
    IN EFI_HANDLE                       ChildHandle OPTIONAL
);
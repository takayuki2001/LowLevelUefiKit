#pragma once

#include "../../type_define.h"

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT) (
    OUT UINT32               *HighCount
);



typedef enum {
   EfiResetCold,
   EfiResetWarm,
   EfiResetShutdown,
   EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_RESET_SYSTEM) (
    IN EFI_RESET_TYPE          ResetType,
    IN EFI_STATUS              ResetStatus,
    IN UINTN                   DataSize,
    IN VOID                    *ResetData OPTIONAL
);



typedef struct {
    EFI_GUID             CapsuleGuid;
    UINT32               HeaderSize;
    UINT32               Flags;
    UINT32               CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef EFI_STATUS (EFIAPI *EFI_UPDATE_CAPSULE) (
    IN EFI_CAPSULE_HEADER      **CapsuleHeaderArray,
    IN UINTN                   CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS    ScatterGatherList OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES) (
    IN EFI_CAPSULE_HEADER         **CapsuleHeaderArray,
    IN UINTN                      CapsuleCount,
    OUT UINT64                    *MaximumCapsuleSize,
    OUT EFI_RESET_TYPE            *ResetType
);
#pragma once

#include "../../type_define.h"

typedef struct {
   UINT16    Year;              // 1900 - 9999
   UINT8     Month;             // 1 - 12
   UINT8     Day;               // 1 - 31
   UINT8     Hour;              // 0 - 23
   UINT8     Minute;            // 0 - 59
   UINT8     Second;            // 0 - 59
   UINT8     Pad1;
   UINT32    Nanosecond;        // 0 - 999,999,999
   INT16     TimeZone;          // —1440 to 1440 or 2047
   UINT8     Daylight;
   UINT8     Pad2;
} EFI_TIME;

typedef struct {
   UINT32                  Resolution;
   UINT32                  Accuracy;
   BOOLEAN                 SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS (EFIAPI *EFI_GET_TIME) (
   OUT EFI_TIME                  *Time,
   OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SET_TIME) (
    IN EFI_TIME       *Time
);

typedef EFI_STATUS (EFIAPI *EFI_GET_WAKEUP_TIME) (
    OUT BOOLEAN            *Enabled,
    OUT BOOLEAN            *Pending,
    OUT EFI_TIME           *Time
);

typedef EFI_STATUS (EFIAPI *EFI_SET_WAKEUP_TIME) (
    IN BOOLEAN         Enable,
    IN EFI_TIME        *Time OPTIONAL
);

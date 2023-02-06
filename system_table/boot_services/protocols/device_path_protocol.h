#pragma once

#include "../../../type_define.h"

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
    UINT8           Type;
    UINT8           SubType;
    UINT8           Length[2];
} EFI_DEVICE_PATH_PROTOCOL;
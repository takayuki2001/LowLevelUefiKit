#pragma once

#include "../type_define.h"

//EFI_TABLE_HEADERの為にinclude
#include "../table_header.h"

#include "runtime_services/variable_services.h"
#include "runtime_services/time_services.h"

#include "runtime_services/variable_services.h"
#include "runtime_services/time_services.h"
#include "runtime_services/virtual_memory_services.h"
#include "runtime_services/miscellaneous_runtime_services.h"

typedef struct {
  EFI_TABLE_HEADER                 Hdr;

  EFI_GET_TIME                     GetTime;
  EFI_SET_TIME                     SetTime;
  EFI_GET_WAKEUP_TIME              GetWakeupTime;
  EFI_SET_WAKEUP_TIME              SetWakeupTime;

  EFI_SET_VIRTUAL_ADDRESS_MAP      SetVirtualAddressMap;
  EFI_CONVERT_POINTER                ConvertPointer;

  EFI_GET_VARIABLE                 GetVariable;
  EFI_GET_NEXT_VARIABLE_NAME       GetNextVariableName;
  EFI_SET_VARIABLE                 SetVariable;

  EFI_GET_NEXT_HIGH_MONO_COUNT     GetNextHighMonotonicCount;
  EFI_RESET_SYSTEM                 ResetSystem;

  EFI_UPDATE_CAPSULE               UpdateCapsule;
  EFI_QUERY_CAPSULE_CAPABILITIES   QueryCapsuleCapabilities;

  EFI_QUERY_VARIABLE_INFO          QueryVariableInfo;
} EFI_RUNTIME_SERVICES;
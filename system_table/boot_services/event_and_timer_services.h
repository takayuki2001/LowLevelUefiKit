#pragma once

#include "../../type_define.h"

typedef VOID (EFIAPI *EFI_EVENT_NOTIFY) (
    IN EFI_EVENT         Event,
    IN VOID              *Context
);

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT) (
   IN UINT32                   Type,
   IN EFI_TPL                  NotifyTpl,
   IN EFI_EVENT_NOTIFY         NotifyFunction, OPTIONAL
   IN VOID                     *NotifyContext, OPTIONAL
   OUT EFI_EVENT               *Event
);

typedef enum {
   TimerCancel,
   TimerPeriodic,
   TimerRelative
} EFI_TIMER_DELAY;

typedef EFI_STATUS (EFIAPI *EFI_SET_TIMER) (
   IN EFI_EVENT               Event,
   IN EFI_TIMER_DELAY         Type,
   IN UINT64                  TriggerTime
);

typedef EFI_STATUS (EFIAPI *EFI_WAIT_FOR_EVENT) (
   IN UINTN             NumberOfEvents,
   IN EFI_EVENT         *Event,
   OUT UINTN            *Index
);

typedef EFI_STATUS (EFIAPI *EFI_SIGNAL_EVENT) (
  IN EFI_EVENT Event
);

typedef EFI_STATUS (EFIAPI *EFI_CLOSE_EVENT) (
    IN EFI_EVENT      Event
);

typedef EFI_STATUS (EFIAPI *EFI_CHECK_EVENT) (
    IN EFI_EVENT      Event
);
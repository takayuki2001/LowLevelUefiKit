#pragma once

#include "../type_define.h"

//EFI_TABLE_HEADERの為にinclude
#include "../table_header.h"

#include "boot_services/task_priority_services.h"
#include "boot_services/memory_allocation_services.h"
#include "boot_services/event_and_timer_services.h"
#include "boot_services/protocol_handler_services.h"
#include "boot_services/image_services.h"
#include "boot_services/miscellaneous_services.h"
#include "boot_services/driver_support_services.h"
#include "boot_services/open_and_close_protocol_services.h"
#include "boot_services/library_services.h"


typedef struct {
    EFI_TABLE_HEADER     Hdr;

    EFI_RAISE_TPL        RaiseTPL;
    EFI_RESTORE_TPL      RestoreTPL;

    EFI_ALLOCATE_PAGES   AllocatePages;
    EFI_FREE_PAGES       FreePages;
    EFI_GET_MEMORY_MAP   GetMemoryMap;
    EFI_ALLOCATE_POOL    AllocatePool;
    EFI_FREE_POOL        FreePool;

    EFI_CREATE_EVENT     CreateEvent;
    EFI_SET_TIMER        SetTimer;
    EFI_WAIT_FOR_EVENT   WaitForEvent;
    EFI_SIGNAL_EVENT     SignalEvent;
    EFI_CLOSE_EVENT      CloseEvent;
    EFI_CHECK_EVENT      CheckEvent;

    EFI_INSTALL_PROTOCOL_INTERFACE     InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE   ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE   UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL                HandleProtocol;
    VOID*   Reserved;
    EFI_REGISTER_PROTOCOL_NOTIFY       RegisterProtocolNotify;
    EFI_LOCATE_HANDLE                  LocateHandle;
    EFI_LOCATE_DEVICE_PATH             LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE       InstallConfigurationTable;

    EFI_IMAGE_UNLOAD               LoadImage;
    EFI_IMAGE_START                StartImage;
    EFI_EXIT                       Exit;
    EFI_IMAGE_UNLOAD               UnloadImage;
    EFI_EXIT_BOOT_SERVICES         ExitBootServices;

    EFI_GET_NEXT_MONOTONIC_COUNT   GetNextMonotonicCount;
    EFI_STALL                      Stall;
    EFI_SET_WATCHDOG_TIMER         SetWatchdogTimer;

    EFI_CONNECT_CONTROLLER         ConnectController;
    EFI_DISCONNECT_CONTROLLER      DisconnectController;

    EFI_OPEN_PROTOCOL              OpenProtocol;
    EFI_CLOSE_PROTOCOL             CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation;

    EFI_PROTOCOLS_PER_HANDLE       ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER       LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL            LocateProtocol;
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces;

    /*
    EFI_CALCULATE_CRC32    CalculateCrc32;

    EFI_COPY_MEM           CopyMem;
    EFI_SET_MEM            SetMem;
    EFI_CREATE_EVENT_EX    CreateEventEx;
    */
  } EFI_BOOT_SERVICES;
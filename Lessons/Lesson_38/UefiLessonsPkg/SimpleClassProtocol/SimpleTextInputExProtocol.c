/*
 * Copyright (c) 2021, Konstantin Aladyshev <aladyshev22@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Protocol/SimpleTextInEx.h>


EFI_HANDLE SimpleTextInputExHandle = NULL;

EFI_STATUS Status;

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *SimpleTextInputEx;

EFI_DRIVER_BINDING_PROTOCOL *This;

EFI_STATUS
EFIAPI
SimpleTextInputExProtocolDriverUnload(
    IN EFI_HANDLE ImageHandle)
{
  Print(L"Bye-bye from SimpleTextInputExProtocol driver, handle=%p\n", SimpleTextInputExHandle);

  Status = gBS->UninstallMultipleProtocolInterfaces(
      SimpleTextInputExHandle,
      &gEfiSimpleTextInputExProtocolGuid,
      &SimpleTextInputEx,
      NULL);

  return Status;
}

EFI_STATUS
EFIAPI
SimpleTextInputExProtocolDriverEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
  //Print(L"Hello from SimpleTextInputExProtocol driver\n");
  //Print(L"GUID: [%g]\n", gEfiSimpleTextInputExProtocolGuid);
  UINTN                             SimpleTextInHandleCount = 0;
  EFI_HANDLE                        *SimpleTextInHandleBuffer = NULL;
  UINTN                             SimpleTextInputExHandleCount = 0;
  EFI_HANDLE                        *SimpleTextInputExHandleBuffer = NULL;
  UINTN                             Index;

  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiSimpleTextInputExProtocolGuid, NULL, &SimpleTextInputExHandleCount, &SimpleTextInputExHandleBuffer);
  if (Status == EFI_NOT_FOUND)
  {
    Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiSimpleTextInProtocolGuid, NULL, &SimpleTextInHandleCount, &SimpleTextInHandleBuffer);
    if (EFI_ERROR (Status)) {
        DEBUG((-1, "ShowStatus: SimpleText In protocol not found\n"));
        return EFI_UNSUPPORTED;
    } else {
      for (Index = 0; Index < SimpleTextInHandleBuffer; Index++) {
        Status = gBS->InstallProtocolInterface(&SimpleTextInHandleBuffer[Index], &gEfiSimpleTextInputExProtocolGuid, EFI_NATIVE_INTERFACE, &SimpleTextInputEx);
        if (EFI_ERROR (Status)) {
            DEBUG((-1, "ShowStatus: SimpleText InputEx protocol installed failed: %r\n", Status));
            return EFI_UNSUPPORTED;
        }
      }
    }
  }
    /*
    Status = gBS->InstallProtocolInterface(&CrScreenHandle, &gCrScreenShotGuid, EFI_NATIVE_INTERFACE, NULL);

    Status = gBS->InstallMultipleProtocolInterfaces(
        &SimpleTextInputExHandle,
        &gEfiSimpleTextInputExProtocolGuid,
        &SimpleTextInputEx,
        NULL);
    if (!EFI_ERROR(Status))
      Print(L", handle=%p\n", SimpleTextInputExHandle);
    else
      Print(L"\n", SimpleTextInputExHandle);
  }
  else
  {
    Print(L"Status: %r\n", Status);
  }
    */

    return Status;
}

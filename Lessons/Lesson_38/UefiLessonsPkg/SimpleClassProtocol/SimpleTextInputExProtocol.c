/*
 * Copyright (c) 2021, Konstantin Aladyshev <aladyshev22@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

// #include <Protocol/SimpleTextInputEx.h>
#include <Protocol/SimpleTextInEx.h>

EFI_HANDLE SimpleTextInputExHandle = NULL;

UINTN mNumber = 0;

EFI_STATUS Status;

// extern EFI_NATIVE_INTERFACE SimpleTextInputEx;

// typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* SimpleTextInputEx;

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
  Print(L"Hello from SimpleTextInputExProtocol driver");
  Status = gBS->LocateProtocol(
      &gEfiSimpleTextInputExProtocolGuid,
      NULL,
      (VOID **)SimpleTextInputEx);
  if (Status == EFI_NOT_FOUND)
  {
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
    return EFI_ALREADY_STARTED;
  }

  return Status;
}

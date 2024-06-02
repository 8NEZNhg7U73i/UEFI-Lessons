/*
 * Copyright (c) 2021, Konstantin Aladyshev <aladyshev22@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

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
  Print(L"Hello from SimpleTextInputExProtocol driver\n");
  Print(L"GUID: [%g]\n", gEfiSimpleTextInputExProtocolGuid);
  Status = gBS->LocateProtocol(
      &gEfiSimpleTextInputExProtocolGuid,
      NULL,
      (VOID **)&SimpleTextInputEx);
/*
  Status = gBS->OpenProtocol(
      SimpleTextInputExHandle,
      &gEfiSimpleTextInputExProtocolGuid,
      (VOID **)SimpleTextInputEx,
      This->DriverBindingHandle,
      NULL,
      EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
*/

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
    Print(L"Status: %r\n", Status);
  }

  return Status;
}

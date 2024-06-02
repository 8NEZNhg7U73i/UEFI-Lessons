/*
 * Copyright (c) 2021, Konstantin Aladyshev <aladyshev22@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

//#include <Protocol/SimpleTextInputEx.h>
#include <Protocol/SimpleTextInEx.h>


EFI_HANDLE  SimpleTextInputExHandle = NULL;

UINTN mNumber = 0;

//extern EFI_NATIVE_INTERFACE SimpleTextInputEx;

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL SimpleTextInputEx{
  EFI_INPUT_RESET_EX              Reset;
  EFI_INPUT_READ_KEY_EX           ReadKeyStrokeEx;
  ///
  /// Event to use with WaitForEvent() to wait for a key to be available.
  ///
  EFI_EVENT                       WaitForKeyEx;
  EFI_SET_STATE                   SetState;
  EFI_REGISTER_KEYSTROKE_NOTIFY   RegisterKeyNotify;
  EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};

EFI_STATUS
EFIAPI
SimpleTextInputExProtocolDriverUnload (
  IN EFI_HANDLE        ImageHandle
  )
{
  Print(L"Bye-bye from SimpleTextInputExProtocol driver, handle=%p\n", SimpleTextInputExHandle);

  EFI_STATUS Status = gBS->UninstallMultipleProtocolInterfaces(
                             SimpleTextInputExHandle,
                             &gEfiSimpleTextInputExProtocolGuid,
                             &SimpleTextInputEx,
                             NULL
                             );

  return Status;
}

EFI_STATUS
EFIAPI
SimpleTextInputExProtocolDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print(L"Hello from SimpleTextInputExProtocol driver");

  EFI_STATUS Status = gBS->InstallMultipleProtocolInterfaces(
                             &SimpleTextInputExHandle,
                             &gEfiSimpleTextInputExProtocolGuid,
                             &SimpleTextInputEx,
                             NULL
                             );
  if (!EFI_ERROR(Status))
    Print(L", handle=%p\n", SimpleTextInputExHandle);
  else
    Print(L"\n", SimpleTextInputExHandle);

  return Status;
}

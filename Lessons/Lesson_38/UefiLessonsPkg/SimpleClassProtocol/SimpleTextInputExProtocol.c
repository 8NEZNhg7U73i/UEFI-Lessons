/*
 * Copyright (c) 2021, Konstantin Aladyshev <aladyshev22@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

//#include <Protocol/SimpleClass.h>
#include <Protocol/SimpleTextInEx.h>


EFI_HANDLE  mSimpleClassHandle = NULL;

UINTN mNumber = 0;


EFI_STATUS
EFIAPI
SimpleClassProtocolDriverUnload (
  IN EFI_HANDLE        ImageHandle
  )
{
  Print(L"Bye-bye from SimpleClassProtocol driver, handle=%p\n", mSimpleClassHandle);

  EFI_STATUS Status = gBS->UninstallMultipleProtocolInterfaces(
                             mSimpleClassHandle,
                             &gSimpleClassProtocolGuid,
                             &mSimpleClass,
                             NULL
                             );

  return Status;
}

EFI_STATUS
EFIAPI
SimpleClassProtocolDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print(L"Hello from SimpleClassProtocol driver");

  EFI_STATUS Status = gBS->InstallMultipleProtocolInterfaces(
                             &mSimpleClassHandle,
                             &gSimpleClassProtocolGuid,
                             &mSimpleClass,
                             NULL
                             );
  if (!EFI_ERROR(Status))
    Print(L", handle=%p\n", mSimpleClassHandle);
  else
    Print(L"\n", mSimpleClassHandle);

  return Status;
}

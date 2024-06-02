/*
 * Copyright (c) 2021, Konstantin Aladyshev <aladyshev22@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include "SimpleTextIn2Protocol"

EFI_HANDLE  SimpleTextIn2Handle = NULL;

EFI_STATUS Status;

UINTN mNumber = 0;

EFI_SIMPLE_TEXTIN2_PROTOCOL *SimpleTextIn2;

EFI_STATUS
EFIAPI
SimpleTextIn2ProtocolDriverUnload (
  IN EFI_HANDLE        ImageHandle
  )
{
  Print(L"Bye-bye from SimpleTextIn2Protocol driver, handle=%p\n", SimpleTextIn2Handle);

  EFI_STATUS Status = gBS->UninstallMultipleProtocolInterfaces(
                             SimpleTextIn2Handle,
                             &gSimpleTextIn2ProtocolGuid,
                             &mSimpleClass,
                             NULL
                             );

  return Status;
}

EFI_STATUS
EFIAPI
SimpleTextIn2ProtocolDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print(L"Hello from SimpleTextIn2Protocol driver");

  EFI_STATUS Status = gBS->InstallMultipleProtocolInterfaces(
                             &SimpleTextIn2Handle,
                             &gSimpleTextIn2ProtocolGuid,
                             &mSimpleClass,
                             NULL
                             );
  if (!EFI_ERROR(Status))
    Print(L", handle=%p\n", SimpleTextIn2Handle);
  else
    Print(L"\n", SimpleTextIn2Handle);

  return Status;
}

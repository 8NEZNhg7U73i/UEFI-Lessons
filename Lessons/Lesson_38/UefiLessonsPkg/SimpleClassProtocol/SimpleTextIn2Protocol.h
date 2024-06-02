#ifndef __SIMPLE_TEXTIN2_PROTOCOL_H__
#define __SIMPLE_TEXTIN2_PROTOCOL_H__

#include <Protocol/SimpleTextIn.h>

#define EFI_SIMPLE_TEXT_INPUT2_PROTOCOL_GUID                                     \
  {                                                                                \
    0x1172a0a2, 0xe451, 0x41ee, { 0xe6, 0x14, 0x48, 0x7d, 0xb7, 0x45, 0xae, 0x5b } \
  }

typedef struct _SIMPLE_TEXTIN2_PROTOCOL SIMPLE_TEXTIN2_PROTOCOL;

///
/// The function will be called when the key sequence is typed specified by KeyData.
///
typedef
EFI_STATUS
(EFIAPI *EFI_KEY_NOTIFY_FUNCTION)(
  IN EFI_INPUT_KEY *Key
);

/**
  The RegisterKeystrokeNotify() function registers a function
  which will be called when a specified keystroke will occur.

  @param This                     A pointer to the EFI_SIMPLE_TEXT_INPUT2_PROTOCOL instance.

  @param Key                      A pointer to a buffer that is filled in with
                                  the keystroke information for the key that was
                                  pressed. If Key.Key, Key.KeyState.KeyToggleState
                                  and Key.KeyState.KeyShiftState are 0, then any incomplete
                                  keystroke will trigger a notification of the KeyNotificationFunction.

  @param KeyNotificationFunction  Points to the function to be called when the key sequence
                                  is typed specified by Key. This notification function
                                  should be called at <=TPL_CALLBACK.


  @param NotifyHandle             Points to the unique handle assigned to
                                  the registered notification.

  @retval EFI_SUCCESS           Key notify was registered successfully.

  @retval EFI_OUT_OF_RESOURCES  Unable to allocate necessary
                                data structures.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY)(
  IN  EFI_SIMPLE_TEXT_INPUT2_PROTOCOL *This,
  IN  EFI_INPUT_KEY                      *Key,
  IN  EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
  OUT VOID                              **NotifyHandle
);

/**
  The UnregisterKeystrokeNotify() function removes the
  notification which was previously registered.

  @param This               A pointer to the EFI_SIMPLE_TEXT_INPUT2_PROTOCOL instance.

  @param NotificationHandle The handle of the notification
                            function being unregistered.

  @retval EFI_SUCCESS           Key notify was unregistered successfully.

  @retval EFI_INVALID_PARAMETER The NotificationHandle is
                                invalid.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
  IN EFI_SIMPLE_TEXT_INPUT2_PROTOCOL  *This,
  IN VOID                               *NotificationHandle
);


///
/// The EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL is used on the ConsoleIn
/// device. It is an extension to the Simple Text Input protocol
/// which allows a variety of extended shift state information to be
/// returned.
///
struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL{
  EFI_REGISTER_KEYSTROKE_NOTIFY   RegisterKeyNotify;
  EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};

#endif

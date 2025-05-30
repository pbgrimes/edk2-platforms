/** @file
  AMD simulator port80 serial port library functions.

  Copyright (C) 2023-2025 Advanced Micro Devices, Inc. All rights reserved.

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/SerialPortLib.h>
#include <Uefi.h>

/**
  Initialize the serial device hardware.

  If no initialization is required, then return RETURN_SUCCESS.
  If the serial device was successfully initialized, then return RETURN_SUCCESS.
  If the serial device could not be initialized, then return RETURN_DEVICE_ERROR.

  @retval RETURN_SUCCESS        The serial device was initialized.
  @retval RETURN_DEVICE_ERROR   The serial device could not be initialized.

**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
  // Chipset defaults properly decoding port 80 to eSPI
  return EFI_SUCCESS;
}

/**
  Write data from buffer to serial device.

  Writes NumberOfBytes data bytes from Buffer to the serial device.
  The number of bytes actually written to the serial device is returned.
  If the return value is less than NumberOfBytes, then the write operation failed.
  If Buffer is NULL, then ASSERT().
  If NumberOfBytes is zero, then return 0.

  @param[in]  Buffer           The pointer to the data buffer to be written.
  @param[in]  NumberOfBytes    The number of bytes to written to the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes written to the serial device.
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8  *Buffer,
  IN UINTN  NumberOfBytes
  )
{
  UINTN  ByteCount;

  if ((Buffer == NULL) || (NumberOfBytes == 0)) {
    return 0;
  }

  IoWrite32 (0x80, SIGNATURE_32 ('R', 'T', 'S', '_'));

  ByteCount = NumberOfBytes;
  for ( ; ByteCount != 0; ByteCount--, Buffer++) {
    IoWrite8 (0x80, *Buffer);
  }

  IoWrite32 (0x80, SIGNATURE_32 ('D', 'N', 'E', '_'));

  return NumberOfBytes;
}

/**
  Read data from serial device and save the data in buffer.

  Reads NumberOfBytes data bytes from a serial device into the buffer
  specified by Buffer. The number of bytes actually read is returned.
  If the return value is less than NumberOfBytes, then the rest operation failed.
  If Buffer is NULL, then ASSERT().
  If NumberOfBytes is zero, then return 0.

  @param[out]  Buffer           The pointer to the data buffer to store the data read from the serial device.
  @param[in]   NumberOfBytes    The number of bytes which will be read.

  @retval 0                Read data failed; No data is to be read.
  @retval >0               The actual number of bytes read from serial device.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8  *Buffer,
  IN  UINTN  NumberOfBytes
  )
{
  return 0;
}

/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls a serial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  return FALSE;
}

/**
  Sets the control bits on a serial device.

  @param[in] Control                Sets the bits of Control that are settable.

  @retval RETURN_SUCCESS        The new control bits were set on the serial device.
  @retval RETURN_UNSUPPORTED    The serial device does not support this operation.
  @retval RETURN_DEVICE_ERROR   The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortSetControl (
  IN UINT32  Control
  )
{
  return RETURN_UNSUPPORTED;
}

/**
  Retrieve the status of the control bits on a serial device.

  @param[out] Control                A pointer to return the current control signals from the serial device.

  @retval RETURN_SUCCESS        The control bits were read from the serial device.
  @retval RETURN_UNSUPPORTED    The serial device does not support this operation.
  @retval RETURN_DEVICE_ERROR   The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortGetControl (
  OUT UINT32  *Control
  )
{
  return RETURN_UNSUPPORTED;
}

/**
  Sets the baud rate, receive FIFO depth, transmit/receive time out, parity,
  data bits, and stop bits on a serial device.

  @param[in,out] BaudRate          The requested baud rate. A BaudRate value of 0 will use the
                                   device's default interface speed.
                                   On output, the value actually set.
  @param[in,out] ReceiveFifoDepth  The requested depth of the FIFO on the receive side of the
                                   serial interface. A ReceiveFifoDepth value of 0 will use
                                   the device's default FIFO depth.
                                   On output, the value actually set.
  @param[in,out] Timeout           The requested time out for a single character in microseconds.
                                   This timeout applies to both the transmit and receive side of the
                                   interface. A Timeout value of 0 will use the device's default time
                                   out value.
                                   On output, the value actually set.
  @param[in,out] Parity            The type of parity to use on this serial device. A Parity value of
                                   DefaultParity will use the device's default parity value.
                                   On output, the value actually set.
  @param[in,out] DataBits          The number of data bits to use on the serial device. A DataBits
                                   value of 0 will use the device's default data bit setting.
                                   On output, the value actually set.
  @param[in,out] StopBits          The number of stop bits to use on this serial device. A StopBits
                                   value of DefaultStopBits will use the device's default number of
                                   stop bits.
                                   On output, the value actually set.

  @retval RETURN_SUCCESS            The new attributes were set on the serial device.
  @retval RETURN_UNSUPPORTED        The serial device does not support this operation.
  @retval RETURN_INVALID_PARAMETER  One or more of the attributes has an unsupported value.
  @retval RETURN_DEVICE_ERROR       The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortSetAttributes (
  IN OUT UINT64              *BaudRate,
  IN OUT UINT32              *ReceiveFifoDepth,
  IN OUT UINT32              *Timeout,
  IN OUT EFI_PARITY_TYPE     *Parity,
  IN OUT UINT8               *DataBits,
  IN OUT EFI_STOP_BITS_TYPE  *StopBits
  )
{
  return RETURN_UNSUPPORTED;
}

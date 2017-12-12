/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "midi.h"

const uint8 CYCODE MIDI_IDENTITY_REPLY[] = {
  0xF0u,      /* SysEx */
  0x7Eu,      /* Non-real time */
  0x7Fu,      /* ID of target device (7F - "All Call") */
  0x06u,      /* Sub-ID#1 - General Information */
  0x02u,      /* Sub-ID#2 - Identity Reply */
  0x7Du,      /* Manufacturer's ID: 7D - Educational Use */
  0xB4u, 0x04u,               /* Family code */
  0x32u, 0xD2u,               /* Model number */
  0x01u, 0x00u, 0x00u, 0x00u, /* Version number */
  /*0xF7         End of SysEx automatically appended */
};

void c_usbmidi_is_configuration_changed(mrb_vm *vm, mrb_value *v){
  uint8 result = USBMIDI_IsConfigurationChanged();
  SET_INT_RETURN(result);
}

void c_usbmidi_get_configuration(mrb_vm *vm, mrb_value *v){
  uint8 result = USBMIDI_GetConfiguration();
  SET_INT_RETURN(result);
}
void c_usbmidi_initialize(mrb_vm *vm, mrb_value *v){
  USBMIDI_Init();
  USBMIDI_MIDI_EP_Init();
  USBMIDI_PutUsbMidiIn(sizeof(MIDI_IDENTITY_REPLY),		\
			 (uint8 *)MIDI_IDENTITY_REPLY, 0x00u);
}

void c_usbmidi_in_and_out_service(mrb_vm *vm, mrb_value *v){
#if(!USBMIDI_EP_MANAGEMENT_DMA_AUTO) 
  USBMIDI_MIDI_IN_Service();
#endif
#if(!USBMIDI_EP_MANAGEMENT_DMA_AUTO) 
  USBMIDI_MIDI_OUT_Service();
#endif    
}

uint8 USB_MIDI_InqFlags;
void c_usbmidi_put_system_message(mrb_vm *vm, mrb_value *v){
  /* Sending an Identity Reply Universal Sysex message back to the computer */
  if(0u != (USB_MIDI_InqFlags & USBMIDI_INQ_IDENTITY_REQ_FLAG))
    {
      USBMIDI_PutUsbMidiIn(sizeof(MIDI_IDENTITY_REPLY),		\
			     (uint8 *)MIDI_IDENTITY_REPLY, USBMIDI_MIDI_CABLE_00);
      USB_MIDI_InqFlags &= ~USBMIDI_INQ_IDENTITY_REQ_FLAG;
    }       
}

void USBMIDI_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg){}

void c_usbmidi_send(mrb_vm *vm, mrb_value *v){
  uint8 midiMsg[MIDI_MSG_SIZE];
  midiMsg[MIDI_MSG_TYPE] = GET_INT_ARG(1);
  midiMsg[MIDI_NOTE_NUMBER] = GET_INT_ARG(2);
  midiMsg[MIDI_NOTE_VELOCITY] = GET_INT_ARG(3);

  USBMIDI_PutUsbMidiIn(3,midiMsg,0x00u);
}

/* [] END OF FILE */

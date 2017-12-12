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
#include "project.h"
#include "src/mrubyc.h"

#define DEVICE                  (0u)
#define MIDI_MSG_SIZE           (4u)

/*MIDI Message Fields */
#define MIDI_MSG_TYPE           (0u)
#define MIDI_NOTE_NUMBER        (1u)
#define MIDI_NOTE_VELOCITY      (2u)

void c_usbmidi_is_configuration_changed(mrb_vm *vm, mrb_value *v);
void c_usbmidi_get_configuration(mrb_vm *vm, mrb_value *v);
void c_usbmidi_initialize(mrb_vm *vm, mrb_value *v);
void c_usbmidi_in_and_out_service(mrb_vm *vm, mrb_value *v);
void c_usbmidi_put_system_message(mrb_vm *vm, mrb_value *v);
void USBMIDI_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg);
void c_usbmidi_send(mrb_vm *vm, mrb_value *v);

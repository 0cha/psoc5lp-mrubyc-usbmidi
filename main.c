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
#include "midi.h"
#include "switches.h"
#include "sample1.c"

static void mrbc_define_methods(){
  mrbc_define_method(0, mrbc_class_object, "usbmidi_send", c_usbmidi_send);
  mrbc_define_method(0, mrbc_class_object, "usbmidi_put_system_message", c_usbmidi_put_system_message);
  mrbc_define_method(0, mrbc_class_object, "usbmidi_initialize", c_usbmidi_initialize);
  mrbc_define_method(0, mrbc_class_object, "usbmidi_get_configuration", c_usbmidi_get_configuration);
  mrbc_define_method(0, mrbc_class_object, "usbmidi_is_configuration_changed", c_usbmidi_is_configuration_changed);
  mrbc_define_method(0, mrbc_class_object, "usbmidi_in_and_out_service", c_usbmidi_in_and_out_service);
  mrbc_define_method(0, mrbc_class_object, "sw_up_read", c_sw_up_read);
  mrbc_define_method(0, mrbc_class_object, "sw_left_read", c_sw_left_read);
  mrbc_define_method(0, mrbc_class_object, "sw_down_read", c_sw_down_read);
  mrbc_define_method(0, mrbc_class_object, "sw_right_read", c_sw_right_read);
  mrbc_define_method(0, mrbc_class_object, "sw0_read", c_sw0_read);
  mrbc_define_method(0, mrbc_class_object, "sw1_read", c_sw1_read);
  mrbc_define_method(0, mrbc_class_object, "sw2_read", c_sw2_read);    
}
int hal_write(int fd, const void *buf, size_t nbytes){
  UART_PutArray(buf, nbytes);
  return 0;
}
int hal_flush(int fd){
  return 0;
}

#define MEMORY_SIZE (1024*20)
static uint8_t memory_pool[MEMORY_SIZE];

int main(void)
{
  CyGlobalIntEnable; /* Enable global interrupts. */
    
  /* Place your initialization/startup code here (e.g. MyInst_Start()) */
  UART_Start();
  USBMIDI_Start(0, USBMIDI_DWR_VDDD_OPERATION);

  mrbc_init(memory_pool, MEMORY_SIZE);
  mrbc_define_methods();
    
  mrbc_create_task( sample1, 0 );
  mrbc_run();   
  for(;;)
    {
      /* Place your application code here. */
    }
}

/* [] END OF FILE */

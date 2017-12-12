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
#include "switches.h"

void c_sw_up_read(mrb_vm *vm, mrb_value *v){
    int sw_up = SW_Up_Read();
    SET_INT_RETURN(sw_up);
}
void c_sw_left_read(mrb_vm *vm, mrb_value *v){
    int sw_left = SW_Left_Read();
    SET_INT_RETURN(sw_left);
}
void c_sw_down_read(mrb_vm *vm, mrb_value *v){
    int sw_down = SW_Down_Read();
    SET_INT_RETURN(sw_down);
}
void c_sw_right_read(mrb_vm *vm, mrb_value *v){
    int sw_right = SW_Right_Read();
    SET_INT_RETURN(sw_right);
}
void c_sw0_read(mrb_vm *vm, mrb_value *v){
    int sw0 = SW0_Read();
    SET_INT_RETURN(sw0);
}
void c_sw1_read(mrb_vm *vm, mrb_value *v){
    int sw1 = SW1_Read();
    SET_INT_RETURN(sw1);
}
void c_sw2_read(mrb_vm *vm, mrb_value *v){
    int sw2 = SW2_Read();
    SET_INT_RETURN(sw2);
}

/* [] END OF FILE */

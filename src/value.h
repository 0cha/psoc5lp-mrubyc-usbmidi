/*! @file
  @brief


  <pre>
  Copyright (C) 2015 Kyushu Institute of Technology.
  Copyright (C) 2015 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.


  </pre>
*/

#ifndef MRBC_SRC_VALUE_H_
#define MRBC_SRC_VALUE_H_

#include <stdint.h>
#include "vm_config.h"


#ifdef __cplusplus
extern "C" {
#endif


// mrb types
//typedef float mrb_float;
//typedef int32_t mrb_int;
typedef int16_t mrb_sym;

/* aspec access ? */
#define MRB_ASPEC_REQ(a)          (((a) >> 18) & 0x1f)
#define MRB_ASPEC_OPT(a)          (((a) >> 13) & 0x1f)
#define MRB_ASPEC_REST(a)         (((a) >> 12) & 0x1)
#define MRB_ASPEC_POST(a)         (((a) >> 7) & 0x1f)

// #define GET_TYPE(v) ((v).tt)
#define IS_FIXNUM(v) (((v).tt)==MRB_TT_FIXNUM)

#pragma pack(2)

//================================================================
/*!@brief

*/
typedef enum {
  /* internal use */
  MRB_TT_HANDLE = -1,
  /* primitive */
  MRB_TT_EMPTY = 0,
  MRB_TT_TRUE,
  MRB_TT_FALSE,
  MRB_TT_NIL,
  MRB_TT_FIXNUM,
  MRB_TT_FLOAT,
  MRB_TT_SYMBOL,
  /* non-primitive */
  MRB_TT_OBJECT = 20,
  MRB_TT_CLASS,
  MRB_TT_PROC,
  MRB_TT_ARRAY,
  MRB_TT_STRING,
  MRB_TT_RANGE,
  MRB_TT_HASH,

  MRB_TT_USERTOP,

} mrb_vtype;


//================================================================
/*!@brief

*/
typedef struct RClass {
  mrb_sym name;   // class name
  struct RClass *super;    // mrbc_class[super]
  struct RProc *procs;   // mrbc_proc[rprocs], linked list
} mrb_class;



//================================================================
/*!@brief

*/
typedef struct RInstance {
  struct RClass *cls;    // class
} mrb_instance;



//================================================================
/*!@brief

*/
typedef struct RObject {
  struct RObject *next;
  mrb_vtype tt;
  union {
    int32_t i;             // MRB_TT_FIXNUM
    struct RObject *handle;  // handle to objects 
    struct RInstance *instance;  // MRB_TT_OBJECT : link to instance 
    //    struct RObject *obj;   // MRB_TT_OBJECT : link to instance
    struct RClass *cls;    // MRB_TT_CLASS : link to class
    struct RProc *proc;    // MRB_TT_PROC : link to proc
    struct RObject *array; // MRB_TT_ARRAY : array of objects
    struct RObject *range; // MRB_TT_RANGE : link to range
    struct RObject *hash;  // MRB_TT_HASH : link to range
    double d;              // MRB_TT_FLOAT : float
    char *str;             // MRB_TT_STRING : C-string
  };
} mrb_object;
typedef struct RObject mrb_value;


struct VM;
typedef void (*mrb_func_t)(struct VM *vm, mrb_value *v);



//================================================================
/*!@brief

*/
typedef struct RProc {
  struct RProc *next;
  unsigned int c_func:1;   // 0:IREP, 1:C Func
  mrb_sym sym_id;
  union {
    struct IREP *irep;
    mrb_func_t func;
  } func;
} mrb_proc;


// alloc one object
mrb_object *mrbc_obj_alloc(struct VM *vm, mrb_vtype tt);

// alloc one class
mrb_class *mrbc_class_alloc(struct VM *vm, const char *name, mrb_class *super);


// alloc one RProc
mrb_proc *mrbc_rproc_alloc(struct VM *vm, const char *name);
mrb_proc *mrbc_rproc_alloc_to_class(struct VM *vm, const char *name, mrb_class *cls);

// EQ two objects
int mrbc_eq(mrb_value *v1, mrb_value *v2);

// Other functions
void mrbc_dup(const struct VM *vm, mrb_value *v);
void mrbc_release(const struct VM *vm, mrb_value *v);

// for C call
#define SET_INT_RETURN(n)         {v[0].tt=MRB_TT_FIXNUM;v[0].i=(n);}
#define SET_NIL_RETURN()          v[0].tt=MRB_TT_NIL
#define SET_FLOAT_RETURN(n)       {v[0].tt=MRB_TT_FLOAT;v[0].d=(n);}
#define SET_FALSE_RETURN()        v[0].tt=MRB_TT_FALSE
#define SET_TRUE_RETURN()         v[0].tt=MRB_TT_TRUE
#define SET_RETURN(n)             v[0]=n

#define GET_TT_ARG(n)             v[n].tt
#define GET_INT_ARG(n)            v[n].i
#define GET_ARY_ARG(n)            v[n]
#define GET_ARG(n)                v[n]
#define GET_FLOAT_ARG(n)          v[n].d
#define GET_STRING_ARG(n)          v[n].str

#ifdef __cplusplus
}
#endif
#endif

#ifndef __TEMPLATES__
#define __TEMPLATES__

#include "../supporter/supporter.h"
#include <math.h>

// rapid - tpp
#define tpp_define_conceal_method(name, type)\
        void name(\
          type obj,\
          char chr = PROGRAM_CONCEAL_CHAR,\
          color_tp foreground = PROGRAM_CONCEAL_FOREGROUND,\
          color_tp background = PROGRAM_CONCEAL_BACKGROUND\
        ) {\
          DrawRecShape(\
            obj->width, obj->height, chr,\
            obj->position_x, obj->position_y,\
            foreground, background\
          );\
        }

#define tpp_define_conceal_method_type_a(name, type, width, height, position_x, position_y)\
        void name(\
          type obj,\
          char chr = PROGRAM_CONCEAL_CHAR,\
          color_tp foreground = PROGRAM_CONCEAL_FOREGROUND,\
          color_tp background = PROGRAM_CONCEAL_BACKGROUND\
        ) {\
          DrawRecShape(\
            obj->width, obj->height, chr,\
            obj->position_x, obj->position_y,\
            foreground, background\
          );\
        }

#define tpp_call_conceal_method(type, var)\
        Concealtype(var)

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

#include "theme.h"
#include "frame/frame.h"
#include "button/button.h"
#include "notify/notify.h"
#include "edit_str/edit_str.h"
#include "edit_int/edit_int.h"
#include "edit_double/edit_double.h"
#include "edit_date_time/edit_date_time.h"
#include "list_view/list_view_item_context.h"
#include "list_view/list_view.h"
#include "list_view/list_view_scroll.h"

#ifdef __cplusplus
}
#endif

#endif

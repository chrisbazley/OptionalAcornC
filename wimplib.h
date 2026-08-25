/* Copyright 1997 Acorn Computers Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * wimplib.h
 * veneers onto the wimp SWIs
 */

#ifndef __wimplib_h
#define __wimplib_h

#ifndef __kernel_h
#include "kernel.h"
#endif

#ifndef __wimp_h
#include "wimp.h"
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(USE_OPTIONAL) && !defined(_Optional)
#define _Optional
#endif


_Optional _kernel_oserror *wimp_initialise        (int version,
                                                  char *name,
                                                  int *messages,
                                                  int *cversion,
                                                  int *task);

_Optional _kernel_oserror *wimp_create_window     (WimpWindow *defn, int *handle);

_Optional _kernel_oserror *wimp_create_icon       (int priority,
                                                  WimpCreateIconBlock *defn,
                                                  int *handle);

_Optional _kernel_oserror *wimp_delete_window     (WimpDeleteWindowBlock *block);

_Optional _kernel_oserror *wimp_delete_icon       (WimpDeleteIconBlock *block);

_Optional _kernel_oserror *wimp_open_window       (WimpOpenWindowBlock *show);

_Optional _kernel_oserror *wimp_close_window      (int *window_handle);

_Optional _kernel_oserror *wimp_poll              (int mask,
                                                  WimpPollBlock *block,
                                                  int *pollword,
                                                  int *event_code);

_Optional _kernel_oserror *wimp_redraw_window     (WimpRedrawWindowBlock *block, int *more);

_Optional _kernel_oserror *wimp_update_window     (WimpRedrawWindowBlock *block, int *more);

_Optional _kernel_oserror *wimp_get_rectangle     (WimpRedrawWindowBlock *block, int *more);

_Optional _kernel_oserror *wimp_get_window_state  (WimpGetWindowStateBlock *state);

_Optional _kernel_oserror *wimp_get_window_info   (WimpGetWindowInfoBlock *block);
_Optional _kernel_oserror *wimp_get_window_info_no_icon_data   (WimpGetWindowInfoBlock *block);
_Optional _kernel_oserror *wimp_set_icon_state    (WimpSetIconStateBlock *block);

_Optional _kernel_oserror *wimp_get_icon_state    (WimpGetIconStateBlock *block);

_Optional _kernel_oserror *wimp_get_pointer_info  (WimpGetPointerInfoBlock *block);

#define CancelDrag 0

_Optional _kernel_oserror *wimp_drag_box          (_Optional WimpDragBox *block);

_Optional _kernel_oserror *wimp_force_redraw      (int window_handle,
                                                  int xmin,
                                                  int ymin,
                                                  int xmax,
                                                  int ymax);

_Optional _kernel_oserror *wimp_set_caret_position (int window_handle,
                                                  int icon_handle,
                                                  int xoffset,
                                                  int yoffset,
                                                  int height,
                                                  int index);

_Optional _kernel_oserror *wimp_get_caret_position (WimpGetCaretPositionBlock *block);

#define CloseMenu ((void *) -1)
_Optional _kernel_oserror *wimp_create_menu       (void * handle,
                                                  int x,int y);

_Optional _kernel_oserror *wimp_decode_menu       (WimpMenu *data,
                                                  int *selections,
                                                  char *buffer);

_Optional _kernel_oserror *wimp_which_icon        (int window_handle,
                                                  int *icons,
                                                  unsigned int mask,
                                                  unsigned int match);

_Optional _kernel_oserror *wimp_set_extent        (int window_handle, BBox *area);

_Optional _kernel_oserror *wimp_set_pointer_shape (int shape,
                                                  void *data,
                                                  int width,
                                                  int height,
                                                  int activex,
                                                  int activey);

_Optional _kernel_oserror *wimp_open_template     (char *name);

_Optional _kernel_oserror *wimp_close_template    (void);

_Optional _kernel_oserror *wimp_load_template     (_kernel_swi_regs *regs);

_Optional _kernel_oserror *wimp_process_key       (int keycode);

_Optional _kernel_oserror *wimp_close_down        (int th);

_Optional _kernel_oserror *wimp_start_task        (char *cl, int *handle);

int             wimp_report_error       (_kernel_oserror *er,
                                        int flags,
                                        char *name, ...);

/*
 * On 3.50 onwards we can have additional parameters:
 *                                      char *sprite
 *                                      void *area
 *                                      char *buttons
 */

_Optional _kernel_oserror *wimp_get_window_outline (WimpGetWindowOutlineBlock *block);

_Optional _kernel_oserror *wimp_pollidle          (int mask,
                                                  WimpPollBlock *block,
                                                  int time,
                                                  int *pollword,
                                                  int *event_code);

_Optional _kernel_oserror *wimp_plot_icon         (WimpPlotIconBlock *block);

_Optional _kernel_oserror *wimp_set_mode          (int mode);

typedef struct {
   unsigned int colours[16];
   unsigned int border;
   unsigned int pointer1;
   unsigned int pointer2;
   unsigned int pointer3;
} Palette;

_Optional _kernel_oserror *wimp_set_palette       (Palette *palette);

_Optional _kernel_oserror *wimp_read_palette      (Palette *palette);

#define Wimp_BackgroundColour (128)
_Optional _kernel_oserror *wimp_set_colour        (int colour);

_Optional _kernel_oserror *wimp_send_message      (int code,
                                                  void *block,
                                                  int handle,
                                                  int icon,
                                                  _Optional int *th);

_Optional _kernel_oserror *wimp_create_submenu    (void * handle,
                                                  int x,int y);

typedef struct {
   intptr_t r2;         /* ignored on entry */
   intptr_t r3;
   intptr_t r4;
   intptr_t r5;
   intptr_t r6;
   intptr_t r7;
}SpriteParams;

_Optional _kernel_oserror *wimp_sprite_op         (int code,
                                                  char *name,
                                                  SpriteParams *p);

_Optional _kernel_oserror *wimp_base_of_sprites   (void **rom,
                                                  void **ram);

_Optional _kernel_oserror *wimp_block_copy        (int handle,
                                                  int sxmin,
                                                  int symin,
                                                  int sxmax,
                                                  int symax,
                                                  int dxmin,
                                                  int dymin);

_Optional _kernel_oserror *wimp_slot_size         (int current,
                                                  int next,
                                                  int *current2,
                                                  int *next2,
                                                  int *free);

/* readpixtrans and claimfreememory not supported */

_Optional _kernel_oserror *wimp_command_window    (int type);

_Optional _kernel_oserror *wimp_text_colour       (int colour);

_Optional _kernel_oserror *wimp_transfer_block    (int sh,
                                                  void *sbuf,
                                                  int dh,
                                                  void *dbuf,
                                                  int size);

typedef struct {
   intptr_t r0;
   intptr_t r1;
} WimpSysInfo;

_Optional _kernel_oserror *wimp_read_sys_info     (int reason,
                                                  WimpSysInfo *results);

_Optional _kernel_oserror *wimp_set_font_colours  (int fore,
                                                  int back);

_Optional _kernel_oserror *wimp_get_menu_state    (int report,
                                                  int *state,
                                                  int window,
                                                  int icon);

/* no filter manager interface */

/* do not use these in toolbox applications */
_Optional _kernel_oserror *wimp_add_messages      (int *list);

_Optional _kernel_oserror *wimp_remove_messages   (int *list);

_Optional _kernel_oserror *wimp_set_colour_mapping (int which_palette,
                                                  int *bpp1,
                                                  int *bpp2,
                                                  int *bpp4);

_Optional _kernel_oserror *wimp_text_op           (_kernel_swi_regs *regs);

/* no extend or set watchdog state */

_Optional _kernel_oserror *wimp_resize_icon       (int window,
                                                  int icon,
                                                  int xmin,
                                                  int ymin,
                                                  int xmax,
                                                  int ymax);


#ifdef __cplusplus
}
#endif


#endif


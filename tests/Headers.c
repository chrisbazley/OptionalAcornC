#include <limits.h>
#include "colourdbox.h"
#include "dcs.h"
#include "event.h"
#include "fileinfo.h"
#include "flex.h"
#include "fontdbox.h"
#include "gadgets.h"
#include "iconbar.h"
#include "kernel.h"
#include "menu.h"
#include "printdbox.h"
#include "proginfo.h"
#include "quit.h"
#include "saveas.h"
#include "scale.h"
#include "scrolllist.h"
#include "swis.h"
#include "textarea.h"
#include "toolbox.h"
#include "wimp.h"
#include "wimplib.h"
#include "window.h"

/* Compiling this translation unit verifies that the public headers are
 * mutually compatible and diagnostic-free. */

#if defined(USE_OPTIONAL) && defined(__clang__)
#if __has_warning("-Wnull-to-nonoptional")
#pragma clang diagnostic error "-Wnull-to-nonoptional"
#endif
#endif

/* Standard drag types need neither custom workspace nor callbacks.
 * Exercise both explicit and implicit null initialisation. */
const WimpDragBox standard_drag_box = {
    .drag_type = Wimp_DragBox_DragPoint,
    .workspace = 0,
    .draw = 0,
};

/* Entries without click-show objects, submenus or help text are valid. */
const MenuTemplateEntry plain_menu_entry = {
    .text = "Entry",
    .click_show = 0,
};

/* Compile-time interface checks; runtime semantics are audited separately. */
void null_buffer_size_queries(void)
{
  int length;
  unsigned int unsigned_length;
  const int sizes[] = {0, 1, 4096, INT_MAX, -1};
  for (unsigned int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
    int const size = sizes[i];
    (void)dcs_get_title(0, 0, 0, size, &length);
    (void)dcs_get_message(0, 0, 0, size, &length);
    (void)textarea_get_selection_text(0, 0, 0, 0, size, &unsigned_length);
    (void)textarea_get_text(0, 0, 0, 0, size, &length);
    (void)fileinfo_get_file_name(0, 0, 0, size, &length);
    (void)fileinfo_get_title(0, 0, 0, size, &length);
    (void)fontdbox_get_title(0, 0, 0, size, &length);
    (void)fontdbox_get_try_string(0, 0, 0, size, &length);
    (void)fontdbox_get_font(0, 0, 0, size, &length);
    (void)scale_get_title(0, 0, 0, size, &length);
    (void)menu_get_title(0, 0, 0, size, &length);
    (void)menu_get_help_message(0, 0, 0, size, &length);
    (void)menu_get_entry_help_message(0, 0, 0, 0, size, &length);
    (void)menu_get_entry_sprite(0, 0, 0, 0, size, &length);
    (void)menu_get_entry_text(0, 0, 0, 0, size, &length);
    (void)saveas_get_file_name(0, 0, 0, size, &length);
    (void)saveas_get_title(0, 0, 0, size, &length);
    (void)window_get_pointer(0, 0, 0, size, &length, 0, 0);
    (void)window_get_help_message(0, 0, 0, size, &length);
    (void)window_get_title(0, 0, 0, size, &length);
    (void)toolbox_get_template_name(0, 0, 0, size, &length);
    (void)quit_get_message(0, 0, 0, size, &length);
    (void)quit_get_title(0, 0, 0, size, &length);
    (void)printdbox_get_title(0, 0, 0, size, &length);
    (void)iconbar_get_help_message(0, 0, 0, size, &length);
    (void)iconbar_get_text(0, 0, 0, size, &length);
    (void)iconbar_get_sprite(0, 0, 0, size, &length);
    (void)scrolllist_get_item_text(0, 0, 0, 0, size, 0, &length);
    (void)gadget_get_icon_list(0, 0, 0, 0, size, &length);
    (void)gadget_get_help_message(0, 0, 0, 0, size, &length);
    (void)actionbutton_get_text(0, 0, 0, 0, size, &length);
    (void)optionbutton_get_label(0, 0, 0, 0, size, &length);
    (void)radiobutton_get_label(0, 0, 0, 0, size, &length);
    (void)displayfield_get_value(0, 0, 0, 0, size, &length);
    (void)writablefield_get_value(0, 0, 0, 0, size, &length);
    (void)draggable_get_sprite(0, 0, 0, 0, size, &length);
    (void)draggable_get_text(0, 0, 0, 0, size, &length);
    (void)button_get_value(0, 0, 0, 0, size, &length);
    (void)button_get_validation(0, 0, 0, 0, size, &length);
    (void)proginfo_get_uri(0, 0, 0, size, &length);
    (void)proginfo_get_title(0, 0, 0, size, &length);
    (void)proginfo_get_version(0, 0, 0, size, &length);
  }
}

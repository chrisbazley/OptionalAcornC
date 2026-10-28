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

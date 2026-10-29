# Null-buffer getter contract audit

A buffer is pointer-to-optional only where passing null does not impose a
condition on the input size: the size is ignored on the null-buffer path.
Other preconditions, such as a valid object, gadget, menu entry or list index,
still apply. A null buffer is not an absent request to perform the operation;
it requests the required output size.

## Evidence and scope

The [Toolbox User Interface Manual](https://www.riscos.com/support/developers/manual_index/toolbox.html)
describes the required-size result when the buffer register is zero. The
[Window chapter](https://www.riscos.com/support/developers/toolbox/windows.html)
covers the built-in gadgets. [TextArea documentation](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Gadgets/docs/TextArea)
and [ScrollList documentation](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Gadgets/docs/ScrollList)
cover the extension queries. The table traces each C getter through its
implementation, rather than inferring size independence from a null-plus-zero
example. It uses the fixed historical source revision linked in each row;
it does not claim to have executed current ROM modules.

The common endpoint is [Common/string32.c:85](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Common/string32.c#L85).
Its `dst_txt == NULL` branch writes the required size without reading the
caller's initial `*max_len`. Menu and FontDbox have separate explicit null
branches. TextArea, ScrollList and gadget icon-list code are checked separately.

| Getter | Implementation evidence | Why the null-buffer size is ignored |
|---|---|---|
| `actionbutton_get_text` | [Window/gadgets/actbut.c:192](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/actbut.c#L192) | Calls string_to_buffer. |
| `button_get_validation` | [Window/gadgets/button.c:222](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/button.c#L222) | Calls string_to_buffer. |
| `button_get_value` | [Window/gadgets/button.c:212](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/button.c#L212) | Calls string_to_buffer. |
| `dcs_get_message` | [DCS/miscop.c:90](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/DCS/miscop.c#L90) | Forwards pointer and size to Button_GetValue, then string_to_buffer; Quit shares the DCS implementation. |
| `dcs_get_title` | [DCS/miscop.c:104](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/DCS/miscop.c#L104) | Forwards pointer and size to Window_GetTitle, then string_to_buffer. |
| `displayfield_get_value` | [Window/gadgets/display.c:244](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/display.c#L244) | Calls string_to_buffer. |
| `draggable_get_sprite` | [Window/gadgets/draggable.c:398](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/draggable.c#L398) | Calls string_to_buffer. |
| `draggable_get_text` | [Window/gadgets/draggable.c:408](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/draggable.c#L408) | Calls string_to_buffer. |
| `fileinfo_get_file_name` | [FileInfo/miscop.c:132](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/FileInfo/miscop.c#L132) | Forwards pointer and size to the Window or DisplayField getter, then string_to_buffer. |
| `fileinfo_get_title` | [FileInfo/miscop.c:170](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/FileInfo/miscop.c#L170) | Forwards pointer and size to the Window or DisplayField getter, then string_to_buffer. |
| `fontdbox_get_font` | [FontDbox/miscop.c:144](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/FontDbox/miscop.c#L144) | Null branch returns the font-name size before reading the input size. |
| `fontdbox_get_title` | [FontDbox/miscop.c:110](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/FontDbox/miscop.c#L110) | Forwards pointer and size to the Window or WritableField getter, then string_to_buffer. |
| `fontdbox_get_try_string` | [FontDbox/miscop.c:219](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/FontDbox/miscop.c#L219) | Forwards pointer and size to the Window or WritableField getter, then string_to_buffer. |
| `gadget_get_help_message` | [Window/gadgets.c:1373](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets.c#L1373) | Calls string_to_buffer. |
| `gadget_get_icon_list` | [Window/gadgets.c:501](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets.c#L501) | The input size is read only inside if (buffer); a null buffer counts all matching icons. |
| `iconbar_get_help_message` | [IconBar/miscop.c:279](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/IconBar/miscop.c#L279) | Calls string_to_buffer (after any object-type validation). |
| `iconbar_get_sprite` | [IconBar/miscop.c:297](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/IconBar/miscop.c#L297) | Calls string_to_buffer (after any object-type validation). |
| `iconbar_get_text` | [IconBar/miscop.c:287](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/IconBar/miscop.c#L287) | Calls string_to_buffer (after any object-type validation). |
| `menu_get_entry_help_message` | [Menu/miscop.c:489](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Menu/miscop.c#L489) | Explicit null branch returns the required size before the input size is used; entry validation still applies. |
| `menu_get_entry_sprite` | [Menu/miscop.c:354](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Menu/miscop.c#L354) | Explicit null branch returns the required size before the input size is used; entry validation still applies. |
| `menu_get_entry_text` | [Menu/miscop.c:299](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Menu/miscop.c#L299) | Explicit null branch returns the required size before the input size is used; entry validation still applies. |
| `menu_get_help_message` | [Menu/miscop.c:121](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Menu/miscop.c#L121) | Explicit null branch returns the required size before the input size is used. |
| `menu_get_title` | [Menu/miscop.c:150](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Menu/miscop.c#L150) | Explicit null branch returns the required size before the input size is used. |
| `optionbutton_get_label` | [Window/gadgets/optbut.c:207](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/optbut.c#L207) | Calls string_to_buffer. |
| `printdbox_get_title` | [PrintDbox/miscop.c:104](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/PrintDbox/miscop.c#L104) | Forwards pointer and size to Window_GetTitle, then string_to_buffer. |
| `proginfo_get_title` | [ProgInfo/miscop.c:256](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/ProgInfo/miscop.c#L256) | Calls or forwards to Window_GetTitle; null handling ultimately uses string_to_buffer. |
| `proginfo_get_uri` | [ProgInfo/miscop.c:351](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/ProgInfo/miscop.c#L351) | Calls or forwards to string_to_buffer; null handling ultimately uses string_to_buffer. |
| `proginfo_get_version` | [ProgInfo/miscop.c:153](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/ProgInfo/miscop.c#L153) | Calls or forwards to DisplayField_GetValue; null handling ultimately uses string_to_buffer. |
| `quit_get_message` | [DCS/miscop.c:90](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/DCS/miscop.c#L90) | Forwards pointer and size to Button_GetValue, then string_to_buffer; Quit shares the DCS implementation. |
| `quit_get_title` | [DCS/miscop.c:104](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/DCS/miscop.c#L104) | Forwards pointer and size to Window_GetTitle, then string_to_buffer. |
| `radiobutton_get_label` | [Window/gadgets/radiobut.c:674](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/radiobut.c#L674) | Calls string_to_buffer. |
| `saveas_get_file_name` | [SaveAs/miscop.c:139](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/SaveAs/miscop.c#L139) | Forwards pointer and size to Window_GetTitle or WritableField_GetValue, then string_to_buffer. |
| `saveas_get_title` | [SaveAs/miscop.c:117](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/SaveAs/miscop.c#L117) | Forwards pointer and size to Window_GetTitle or WritableField_GetValue, then string_to_buffer. |
| `scale_get_title` | [Scale/miscop.c:130](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Scale/miscop.c#L130) | Forwards pointer and size to Window_GetTitle, then string_to_buffer. |
| `scrolllist_get_item_text` | [Gadgets/ScrollList.c:1033](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Gadgets/ScrollList.c#L1033) | After index validation, null returns strlen + 1 before buffer_size is used. |
| `textarea_get_selection_text` | [Gadgets/TextArea.c:1357](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Gadgets/TextArea.c#L1357) | The text-query null branch ignores buff_size. The C veneer forces the return-text flag. |
| `textarea_get_text` | [Gadgets/TextArea.c:1273](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Gadgets/TextArea.c#L1273) | Explicit null branch reports get_text_size + 1; buff_size is used only in the else branch. |
| `toolbox_get_template_name` | [Toolbox/object.c:1069](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Toolbox/object.c#L1069) | Calls string_to_buffer after object validation. |
| `window_get_help_message` | [Window/miscop.c:397](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/miscop.c#L397) | Calls string_to_buffer; its null branch does not read the input size. |
| `window_get_pointer` | [Window/miscop.c:385](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/miscop.c#L385) | Calls string_to_buffer; its null branch does not read the input size. |
| `window_get_title` | [Window/miscop.c:434](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/miscop.c#L434) | Calls string_to_buffer; its null branch does not read the input size. |
| `writablefield_get_value` | [Window/gadgets/writable.c:366](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/Window/gadgets/writable.c#L366) | Calls string_to_buffer. |

## Withdrawn annotations

The two ColourDbox getters remain non-optional in this change:

- `colourdbox_get_colour`
- `colourdbox_get_colour_model`

The [manual](https://www.riscos.com/support/developers/toolbox/colourdbox.html)
documents null-buffer size queries. However, [ColourDbox/miscop.c:226](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/ColourDbox/miscop.c#L226)
and [ColourDbox/miscop.c:373](https://github.com/experimentech/RISC_OS_AWH3Dev/blob/0c1a3dfa52676de2902f13723d9b45c4673f0392/RISC_OS_Dev/castle/RiscOS/Sources/Toolbox/ColourDbox/miscop.c#L373)
check a nonzero size against the required size while the dialogue is showing,
before testing the null destination. A small nonzero size can therefore produce
`ColourDbox_ShortBuffer` even with a null destination. Their hidden-dialogue
paths handle null independently of size, but that is insufficient for an
unconditional annotation. These two changes and their blanket query comments
are withdrawn pending a separately resolved contract/implementation discrepancy.
This does not claim that a null-plus-zero query is invalid.

## Validation

`Headers.c` compiles calls to the 42 retained getters with a null buffer and
sizes 0, 1, 4096, INT_MAX and -1. These are compile-time interface checks;
compilation alone does not verify SWI behaviour.

Host execution of the unmodified historical `string_to_buffer` implementation
and extracted `_get_text`, `_get_selection`, `_get_item_text` and
`gadgets__get_icon_list` function bodies returned the same required sizes for
all five inputs. Minimal host stubs supplied object state and aborted on any
unexpected text-copy call. The remaining dispatch/forwarding and explicit-null
branches in the table were inspected. Native RISC OS SWI execution was not
available, so these checks do not constitute native integration tests.

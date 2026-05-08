
#ifndef swis_h
#define swis_h

#ifndef __kernel_h
#include "kernel.h"
#endif

#if !defined(USE_OPTIONAL) && !defined(_Optional)
#define _Optional
#endif

#define OS_FSControl 0
#define OS_SetVarVal 0
#define MessageTrans_ErrorLookup 0
#define OS_Plot 0
#define ColourTrans_GenerateTable 0
#define ColourTrans_ReadPalette 0 
#define ColourTrans_SetGCOL 0
#define OS_ReadVduVariables 0
#define OS_ReadModeVariable 0
#define DragAnObject_Stop 0
#define DragAnObject_Start 0
#define MessageTrans_Lookup 0
#define MessageTrans_CloseFile 0
#define MessageTrans_OpenFile 0
#define MessageTrans_FileInfo 0
#define OS_FSControl 0
#define Hourglass_On 0
#define Hourglass_Off 0
#define Hourglass_Percentage 0
#define OS_ReadMonotonicTime 0
#define OS_SpriteOp 0
#define OS_SetColour 0
#define Wimp_AutoScroll 0 
#define Territory_ConvertDateAndTime 0
#define Wimp_Extend 0
#define OS_RemoveTickerEvent 0
#define OS_CallAfter 0 
#define OS_Claim 0
#define OS_Release 0
#define OS_CallEvery 0

#define _IN(c) 0
#define _OUT(c) 0
#define _OUTR(c,d) 0
#define _INR(c,d) 0

_Optional _kernel_oserror *_swix(int, int, ...);

#endif

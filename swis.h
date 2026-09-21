
#ifndef swis_h
#define swis_h

#ifndef __kernel_h
#include "kernel.h"
#endif

#if !defined(USE_OPTIONAL) && !defined(_Optional)
#define _Optional
#endif

#define OS_FSControl 0x000029
#define OS_SetVarVal 0x000024
#define MessageTrans_ErrorLookup 0x041506
#define OS_Plot 0x000045
#define ColourTrans_GenerateTable 0x040763
#define ColourTrans_ReadPalette 0x04075c
#define ColourTrans_SetGCOL 0x040743
#define OS_ReadVduVariables 0x000031
#define OS_ReadModeVariable 0x000035
#define DragAnObject_Stop 0x049c41
#define DragAnObject_Start 0x049c40
#define MessageTrans_Lookup 0x041502
#define MessageTrans_CloseFile 0x041504
#define MessageTrans_OpenFile 0x041501
#define MessageTrans_FileInfo 0x041500
#define Hourglass_On 0x0406c0
#define Hourglass_Off 0x0406c1
#define Hourglass_Percentage 0x0406c4
#define OS_ReadMonotonicTime 0x000042
#define OS_SpriteOp 0x00002e
#define OS_SetColour 0x000061
#define Wimp_AutoScroll 0x0400fd
#define Territory_ConvertDateAndTime 0x04304b
#define TaskManager_EnumerateTasks 0x042681
#define Wimp_Extend 0x0400fb
#define OS_RemoveTickerEvent 0x00003d
#define OS_CallAfter 0x00003b
#define OS_Claim 0x00001f
#define OS_Release 0x000020
#define OS_CallEvery 0x00003c
#define OS_ReadArgs 0x000049
#define OS_AddCallBack 0x000054
#define OS_RemoveCallBack 0x00005f
#define Font_CacheAddr 0x040080
#define Font_FindFont 0x040081
#define Font_ScanString 0x0400a1
#define Font_ReadInfo 0x040084
#define Font_Paint 0x040086
#define ColourTrans_SetFontColours 0x04074f
#define Font_LoseFont 0x040082
#define OS_Byte 0x000006

#define _IN(c) (1U << (c))
#define _OUT(c) (1U << (31 - (c)))
#define _OUTR(c,d) (~0U >> (c) ^ ~0U >> ((d) + 1))
#define _INR(c,d) (~0U << (c) ^ ~0U << ((d) + 1))

_Optional _kernel_oserror *_swix(int, int, ...);

#endif

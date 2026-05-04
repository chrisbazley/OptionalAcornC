
#ifndef kernel_h
#define kernel_h

#if !defined(USE_OPTIONAL) && !defined(_Optional)
#define _Optional
#endif

typedef struct {
   int errnum;
   char errmess[256];
} _kernel_oserror;

typedef struct {
   int r[16];
}_kernel_swi_regs;

typedef struct {
   void * dataptr;
   int nbytes;
   int fileptr;
   char *wild_fld;
   int buf_len;
}_kernel_osgbpb_block;

typedef struct {
   int load, start, end, exec;
}_kernel_osfile_block;

#define _kernel_ERROR (-1)
int _kernel_osfile(int, const char *, _kernel_osfile_block *);
int _kernel_osword(int, int *);
_Optional _kernel_oserror *_swix(int, int, ...);
_Optional _kernel_oserror *_kernel_last_oserror(void);
int _kernel_escape_seen(void);
_Optional _kernel_oserror *_kernel_swi(int, _kernel_swi_regs *, _kernel_swi_regs *);
_Optional _kernel_oserror *_kernel_swi_c(int, _kernel_swi_regs *, _kernel_swi_regs *, int *);
int _kernel_osbyte(int, int, int);
int _kernel_oscli(char *);

int _kernel_osgbpb(int, unsigned int, _kernel_osgbpb_block *);
_Optional _kernel_oserror *_kernel_setenv(const char *, const char*);
_Optional _kernel_oserror *_kernel_getenv(const char *,  char*, int);

#endif

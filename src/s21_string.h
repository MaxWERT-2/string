#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define s21_NULL 0
// #define s21_NULL ((void *)0) 

typedef unsigned int s21_size_t;
// or another integer types

typedef struct flags {
    int m_fl;
    int p_fl;
    int s_fl;
    int r_fl;
    int n_fl;
    int a_fl;
    int width;
    int acc;
    int h_len;
    int l_len;
    int L_len;
} fl;

int s21_sprintf(char *str, const char *format, ...);

void my_itoa (long num, char *str, fl cases);
void my_otoa (long unsigned num, char *str, fl cases);
void my_xtoa (long unsigned num, char *str, fl cases, int is_p);
void my_Xtoa (long unsigned num, char *str, fl cases);
void my_utoa (long unsigned num, char *str, fl cases);
char *my_ecvt(double sup, int n, int *decpnt, int *sign);
char *my_fcvt(double sup, int n, int *decpnt, int *sign);

void str_forming(const char *format, char *s, fl cases, int counter, va_list *fact, const int cur_it);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// MAC
#ifdef MAC
//  #ifdef LINUX

enum {
    EPERM = 1,            /* Operation not permitted */
    ENOENT,           /* No such file or directory */
    ESRCH,            /* No such process */
    EINTR,           /* Interrupted system call */
    EIO,              /* Input/output error */
    ENXIO,            /* Device not configured */
    E2BIG,            /* Argument list too long */
    ENOEXEC,          /* Exec format error */
    EBADF,            /* Bad file descriptor */
    ECHILD,         /* No child processes */

    EDEADLK,         /* Resource deadlock avoided */
    ENOMEM,         /* Cannot allocate memory */
    EACCES,         /* Permission denied */
    EFAULT,          /* Bad address */
    ENOTBLK,         /* Block device required */
    EBUSY,           /* Resource busy */
    EEXIST,          /* File exists */
    EXDEV,           /* Cross-device link */
    ENODEV,          /* Operation not supported by device */
    ENOTDIR,        /* Not a directory */

    EISDIR,        /* Is a directory */
    EINVAL,          /* Invalid argument */
    ENFILE,          /* Too many open files in system */
    EMFILE,          /* Too many open files */
    ENOTTY,          /* Inappropriate ioctl for device */
    ETXTBSY,         /* Text file busy */
    EFBIG,           /* File too large */
    ENOSPC,         /* No space left on device */
    ESPIPE,          /* Illegal seek */
    EROFS,           /* Read-only file system */

    EMLINK,          /* Too many links */
    EPIPE,          /* Broken pipe */
    EDOM,            /* Numerical argument out of domain */
    ERANGE,          /* Result too large */
    EAGAIN,         /* Resource temporarily unavailable */
    EINPROGRESS,     /* Operation now in progress */
    EALREADY,       /* Operation already in progress */
    ENOTSOCK,        /* Socket operation on non-socket */
    EDESTADDRREQ,    /* Destination address required */
    EMSGSIZE,        /* Message too long */

    EPROTOTYPE,     /* Protocol wrong type for socket */
    ENOPROTOOPT,     /* Protocol not available */
    EPROTONOSUPPORT, /* Protocol not supported */
    ESOCKTNOSUPPORT, /* Socket type not supported */
    ENOTSUP,        /* Operation not supported */
    EPFNOSUPPORT,   /* Protocol family not supported */
    EAFNOSUPPORT,   /* Address family not supported by protocol family */
    EADDRINUSE,     /* Address already in use */
    EADDRNOTAVAIL,   /* Can't assign requested address */
    ENETDOWN,       /* Network is down */

    ENETUNREACH,    /* Network is unreachable */
    ENETRESET,      /* Network dropped connection on reset */
    ECONNABORTED,    /* Software caused connection abort */
    ECONNRESET,      /* Connection reset by peer */
    ENOBUFS,         /* No buffer space available */
    EISCONN,         /* Socket is already connected */
    ENOTCONN,       /* Socket is not connected */
    ESHUTDOWN,       /* Can't send after socket shutdown */
    ETOOMANYREFS,    /* Too many references: can't splice */
    ETIMEDOUT,      /* Operation timed out */

    ECONNREFUSED,    /* Connection refused */
    ELOOP,           /* Too many levels of symbolic links */
    ENAMETOOLONG,    /* File name too long */
    EHOSTDOWN,       /* Host is down */
    EHOSTUNREACH,   /* No route to host */
    ENOTEMPTY,      /* Directory not empty */
    EPROCLIM,      /* Too many processes */
    EUSERS,          /* Too many users */
    EDQUOT,         /* Disc quota exceeded */
    ESTALE,         /* Stale NFS file handle */

    EREMOTE,        /* Too many levels of remote in path */
    EBADRPC,         /* RPC struct is bad */
    ERPCMISMATCH,    /* RPC version wrong */
    EPROGUNAVAIL,    /* RPC prog. not avail */
    EPROGMISMATCH,   /* Program version wrong */
    EPROCUNAVAIL,    /* Bad procedure for program */
    ENOLCK,          /* No locks available */
    ENOSYS,          /* Function not implemented */
    EFTYPE,          /* Inappropriate file type or format */
    EAUTH,          /* Authentication error */

    ENEEDAUTH,       /* Need authenticator */
    EPWROFF,        /* Device power is off */
    EDEVERR,         /* Device error, e.g. paper out */
    EOVERFLOW,       /* Value too large to be stored in data type */
    EBADEXEC,       /* Bad executable */
    EBADARCH,        /* Bad CPU type in executable */
    ESHLIBVERS,      /* Shared library version mismatch */
    EBADMACHO,       /* Malformed Macho file */
    ECANCELED,       /* Operation canceled */
    EIDRM,           /* Identifier removed */

    ENOMSG,          /* No message of desired type */
    EILSEQ,        /* Illegal byte sequence */
    ENOATTR,        /* Attribute not found */
    EBADMSG,         /* Bad message */
    EMULTIHOP,       /* Reserved */
    ENODATA,         /* No message available on STREAM */
    ENOLINK,         /* Reserved */
    ENOSR,           /* No STREAM resources */
    ENOSTR,        /* Not a STREAM */
    EPROTO,        /* Protocol error */

    ETIME,          /* STREAM ioctl timeout */
    EOPNOTSUPP,     /* Operation not supported on socket */
    ENOPOLICY,     /* No such policy registered */
    ENOTRECOVERABLE, /* State not recoverable */
    EOWNERDEAD,      /* Previous owner died */
    EQFULL   /* Interface output queue is full */
};

#define N 106

#else

enum {
    EPERM = 1,         
    ENOENT,          
    ESRCH,          
    EINTR,    
    EIO,            
    ENXIO,           
    E2BIG,          
    ENOEXEC,         
    EBADF,          
    ECHILD,

    EAGAIN,       
    ENOMEM,        
    EACCES,       
    EFAULT,         
    ENOTBLK,   
    EBUSY,          
    EEXIST,         
    EXDEV,           
    ENODEV,         
    ENOTDIR,

    EISDIR,       
    EINVAL,        
    ENFILE,          
    EMFILE,          
    ENOTTY,          
    ETXTBSY,         
    EFBIG,          
    ENOSPC,       
    ESPIPE,          
    EROFS, 

    EMLINK,          
    EPIPE,          
    EDOM,           
    ERANGE, 
    EDEADLK,
 	ENAMETOOLONG,
 	ENOLCK,
 	ENOSYS,
 	ENOTEMPTY,
    ELOOP,

    ENOMSG = 42,
    EIDRM,
    ECHRNG,
    EL2NSYNC,
    EL3HLT,
    EL3RST,
    ELNRNG,
    EUNATCH,
    ENOCSI,

    EL2HLT,
    EBADE,
    EBADR,
    EXFULL,
    ENOANO, 
    EBADRQC,
    EBADSLT,
    EBFONT = 59,
    ENOSTR,

    ENODATA,
    ETIME,
    ENOSR,
    ENONET,
    ENOPKG,
    EREMOTE,
    ENOLINK,
    EADV,
    ESRMNT,
    ECOMM,

    EPROTO,
    EMULTIHOP,
    EDOTDOT,
    EBADMSG,
    EOVERFLOW,
    ENOTUNIQ,
    EBADFD,
    EREMCHG,
    ELIBACC,
    ELIBBAD,

    ELIBSCN,
    ELIBMAX,
    ELIBEXEC,
    EILSEQ,
    ERESTART,
    ESTRPIPE,
    EUSERS,
    ENOTSOCK,
    EDESTADDRREQ,
    EMSGSIZE,

    EPROTOTYPE,
    ENOPROTOOPT,
    EPROTONOSUPPORT,
    ESOCKTNOSUPPORT,
    EOPNOTSUPP,
    EPFNOSUPPORT,
    EAFNOSUPPORT,
    EADDRINUSE,
    EADDRNOTAVAIL,
    ENETDOWN,

    ENETUNREACH,
    ENETRESET,
    ECONNABORTED,
    ECONNRESET,
    ENOBUFS,
    EISCONN,
    ENOTCONN,
    ESHUTDOWN,
    ETOOMANYREFS,
    ETIMEDOUT,

    ECONNREFUSED,
    EHOSTDOWN,
    EHOSTUNREACH,
    EALREADY,
    EINPROGRESS,
    ESTALE,
    EUCLEAN,
    ENOTNAM,
    ENAVAIL,
    EISNAM,

    EREMOTEIO,
    EDQUOT,
    ENOMEDIUM,
    EMEDIUMTYPE,
    ECANCELED,
    ENOKEY,
    EKEYEXPIRED,
    EKEYREVOKED,
    EKEYREJECTED,
    EOWNERDEAD,

    ENOTRECOVERABLE
};

#define N 133

#endif // MAC
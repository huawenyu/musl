#  Function Category

## Introduction

This chapter briefly describes these function categories:

  * character type macros 
  * string utility 
  * mathematical 
  * varying-length argument list 
  * general utility 
  * program control 
  * memory allocation 
  * diagnostic control 
  * timing 
  * I/O 
  * file management 
  * system interface and environment variables 
  * signal-handling. 

## Character Type Macros and Functions

The character type header files, `<ctype.h>` and `<lctype.h>`, define several
macros that are useful in the analysis of text data. Most of these macros
enable you to determine quickly the type of a character (whether it is
alphabetic, numeric, punctuation, and so on). These macros refer to an
external array that is indexed by the character itself, so they are generally
much faster than functions that check the character against a range or
discrete list of values. Note that this array is actually indexed by the
character value plus 1, so the standard `EOF` value ( - 1) can be tested in a
macro without yielding a nonsense result. `EOF` yields a 0 result for all of
the macros because it is not defined as any of the character types. Also, note
that the results produced by most of these functions are affected by the
current locale's `LC_CTYPE` category, which may cause a different character
type array to be used than the one supplied for the default C locale. See
Chapter 10, "Localization," in _ SAS/C Library Reference, Third Edition,
Volume 2,& Release 6.00_ for details on locales.

Another advantage of the character type macros is that they prevent problems
when programs are moved between machines that use ASCII versus EBCDIC
character sets. Programs using these macros are not dependent on a specific
character set.

The following are character type macros and functions:

`isalnum`

    alphanumeric character test 
`isalpha`

    alphabetic character test 
`isascii`

    ASCII character test 
`iscntrl`

    control character test 
`iscsym`

    test for valid C identifier symbol 
`iscymf`

    test for valid C identifier initial symbol 
`isdigit`

    test for numeric character 
`isebcdic`

    EBCDIC character test 
`isgraph`

    graphic character test 
`islower`

    lowercase alphabetic character test 
`isprint`

    printing character test 
`ispunct`

    punctuation test 
`isspace`

    white space test 
`isupper`

    uppercase alphabetic character test 
`isxdigit`

    hexadecimal digit test 
`toebcdic`

    reduce integer to EBCDIC character 
`tolower`

    translate uppercase character to lowercase 
`toupper`

    translate lowercase character to uppercase. 

Table 2.1 lists the macros defined in the character type header files
`<ctype.h>` and `<lctype.h>`. The library conforms to the ISO/ANSI
specification in that the macro arguments are evaluated only once. However,
many implementations do not conform to this specification. For maximum
portability, beware of the side effects of using expressions such as function
calls and increment or decrement operators. You should include `<ctype.h>` or
`<lctype.h>` if you use any of these macros; otherwise, the compiler generates
a reference to a function of the same name.

Table 2.1 _Character Type Macros and Functions and Their Return Values_

* * *
    
    
       Function      Return Value
     

* * *
    
    
       isalnum(c)     nonzero if c is alphabetic or digit; 0 if
                      not
    
       isalpha(c)     nonzero if c is alphabetic; 0 if not
    
       isascii(c) *   nonzero if c is the EBCDIC equivalent of
                      an ASCII character; 0 if not
    
       iscntrl(c)     nonzero if c is control character; 0 if
                      not
    
       iscsym(c) *    nonzero if valid character for C
                      identifier; 0 if not
    
       iscsymf(c)     nonzero if valid first character for C
                      identifier; 0 if not
    
       isdigit(c) *   nonzero if c is a digit 0 - 9; 0 if not
    
       isebcdic(c) *  nonzero if a valid EBCDIC character; 0 if
                      not
    
       isgraph(c)     nonzero if c is graphic (excluding the
                      blank character); 0 if not
    
       islower(c)     nonzero if c is lowercase; 0 if not
    
       isprint(c)     nonzero if c is printable (including
                      blank); 0 if not
    
       ispunct(c)     nonzero if c is punctuation; 0 if not
    
       isspace(c)     nonzero if c is white space; 0 if not
    
       isupper(c)     nonzero if c is uppercase; 0 if not
    
       isxdigit(c) *  nonzero if c is a hexadecimal digit
                      (0 - 9, A - F, a - f); 0 if not
    
       toebcdic(c) *  truncates integer to valid EBCDIC
                      character
    
       tolower(c)     converts c to lowercase, if uppercase
    
       toupper(c)     converts c to uppercase, if lowercase
     

*These functions are not affected by the locale's `LC_TYPE` category. 

* * *

**Note:** The `toupper` and `tolower` macros generate the value of `c` unchanged if it does not qualify for the conversion. 

## String Utility Functions

The C library provides several functions to perform many string manipulations.
There are three general categories of string utility functions:

functions that begin with the letter `a`

     convert character strings to numbers. 
functions that begin with the letters `str`

     treat their arguments as strings that are terminated with a null character. 
functions that begin with the letters `mem`

     treat their arguments as byte strings in which a null character is not considered a terminator. The `mem` routines are always passed an explicit string length since the string may contain no null characters, or more than one null character. 

Two standard string functions that begin with the letters `str`, `strcoll`,
and `strxfrm` pertain to localization and are discussed in Chapter 10,
"Localization," in _SAS/C Library Reference, Volume 2_ .

The following are string functions:

`atof`

    convert a string to floating point 
`atoi`

    convert a string to integer 
`atol`

    convert a string to long 
`memchr`

    locate first occurrence of a character 
`memcmp`

    compare two blocks of memory 
`memcmpp`

    compare two blocks of memory with padding 
`memcpy`

    copy characters 
`memcpyp`

    copy characters (with padding) 
`memfil`

    fill a block of memory with a multicharacter string 
`memlwr`

    translate a memory block to lowercase 
`memmove`

    copy characters 
`memscan`

    scan a block of memory using a translate table 
`memscntb`

    build a translate table for use by `memscan`
`memset`

    fill a block of memory with a single character 
`memupr`

    translate a memory block to uppercase 
`memxlt`

    translate a block of memory 
`stcpm`

    unanchored pattern match 
`stcpma`

    anchored pattern match 
`strcat`

    concatenate two null-terminated strings 
`strchr`

    locate first occurrence of a character in a string 
`strcmp`

    compare two null-terminated strings 
`strcpy`

    copy a null-terminated string 
`strcspn`

    locate the first occurrence of the first character in a set 
`strlen`

    compute length of null-terminated string 
`strlwr`

    convert a string from uppercase to lowercase 
`strncat`

    concatenate two null-terminated strings (limited) 
`strncmp`

    compare portions of two strings 
`strncpy`

    copy a limited portion of a null-terminated string 
`strpbrk`

    find first occurrence of character of set in string 
`strrchr`

    locate the last occurrence of a character in a string 
`strrcspn`

    locate the last character in a set 
`strrspn`

    locate the last character of a search set not in a given set 
`strsave`

    allocate a copy of a character string 
`strscan`

    scan a string using a translate table 
`strscntb`

    build a translate table for use by `strscan`
`strspn`

    locate the first occurrence of the first character not in a set 
`strstr`

    locate first occurrence of a string within a string 
`strtod`

    convert a string to double 
`strtok`

    get a token from a string 
`strtol`

    convert a string to long integer 
`strtoul`

    convert a string to an unsigned long integer 
`strupr`

    convert a string from lowercase to uppercase 
`strxlt`

    translate a character string 
`xltable`

    build character translation table. 

### Terms Used in String Function Descriptions

These terms are used in the descriptions of string utility functions:

string

    is zero or more contiguous characters terminated by a null byte. The first character of a string is at position 0. Functions that return the `int` or `unsigned` position of a character in a string compute the position beginning at 0. 
character sequence

    is a set of contiguous characters, not necessarily null-terminated. 

### Optimizing Your Use of memcmp, memcpy, and memset

You can optimize your use of the built-in functions `memcmp`, `memcpy`, and
`memset` by controlling the type of the `length` argument. The compiler
inspects the type before the argument is converted to the type specified in
the function prototype. If the type of the `length` argument is one of the
types in Table 2.2, the compiler generates only the code required for the
maximum value of the type. Table 2.2 shows the maximum values of these types.
Note that these values can be obtained from the `<limits.h>` header file.

You can use only the types shown in Table 2.2 (in addition to `size_t`). If
the `length` argument has any other type, the compiler issues a warning
message.

Table 2.2 _Types Acceptable as Length Arguments in Built-in Functions_

* * *
    
    
       Type            Maximum Value
     

* * *
    
    
       char             255
    
       unsigned char    255
    
       short            32767
    
       signed short     32767
    
       unsigned short   65535
     

* * *

If Table 2.2 lists the type of the `length` argument, the function will not be
required to operate on more than 16 megabytes of data. Therefore, the compiler
does not generate a call to the true (that is, separately linked) function to
handle that case.

If the `length` argument is one of the `char` types, the compiler generates a
MOVE instruction (which can handle up to 256 characters) rather than a MOVE
LONG (which can handle up to 16 megabytes of characters). Because the MOVE
LONG instruction is one of the slowest instructions in the IBM 370 instruction
set, generating a MOVE saves execution time.

### Getting the Most Efficient Code

To get the compiler to generate the most efficient code sequence for string
functions, follow these guidelines:

  1. Use the built-in version of the function. Built-in functions are defined as macros in the appropriate header file. Always include `<string.h>` or `<lcstring.h>`, and do not use the function name in an `#undef` preprocessing directive. 
  2. Declare or cast the `length` argument as one of the types in Table 2.2. 
  3. Do not cast the `length` argument to a wider type. This defeats the compiler's inspection of the type. 

You may want to define one or more macros that cast the `length` argument to a
shorter type. For example, here is a program that defines two such macros:

    
    
     #include <string.h>
    
        /* Copy up to 32767 characters. */
     #define memcpys(to, from, length) memcpy(to, from, (short)length)
    
        /* Copy up to 255 characters. */
     #define memcpyc(to, from, length) memcpy(to, from, (char)length)
     .
     .
     .
     int strsz;          /* strsz is known to be less than 32K. */
     char *dest, *src;
    
     memcpys(dest, src, strsz);         /* casts strsz to short */
     .
     .
     .
     

Some recent IBM processors include a hardware feature called the Logical
String Assist, which implements the C functions `strlen`, `strcpy`, `strcmp`,
`memchr`, and `strchr` in hardware. To make use of this hardware feature,
`#define` the symbol `_USELSA` before including `<string.h>` or
`<lcstring.h>`. The resulting code will not execute on hardware that does not
have the Logical String Assist feature installed.

## Mathematical Functions

The mathematical functions include a large proportion of the floating-point
math functions usually provided with traditional UNIX C compilers. The header
file `<math.h>` should be included when using most of these functions. See the
individual function descriptions to determine whether the header file is
required for that function.

The library also provides the standard header file `<float.h>`, which provides
additional information about floating-point arithmetic. The contents of this
header file are listed here:

    
    
     #define FLT_RADIX 16          /* hardware float radix               */
     #define FLT_ROUNDS 0          /* float addition does not round.     */
    
     #define FLT_MANT_DIG 6        /* hex digits in float mantissa       */
     #define DBL_MANT_DIG 14       /* hex digits in double mantissa      */
     #define LDBL_MANT_DIG 14      /* hex digits in long double mantissa */
    
     #define FLT_DIG 6             /* float decimal precision            */
     #define DBL_DIG 16            /* double decimal precision           */
     #define LDBL_DIG 16           /* long double decimal precision      */
    
     #define FLT_MIN_EXP -64       /* minimum exponent of 16 for float   */
     #define DBL_MIN_EXP -64       /* minimum exponent of 16 for double  */
     #define LDBL_MIN_EXP -64      /* minimum exponent of 16 for long    */
                                   /* double                             */
    
     #define FLT_MIN_10_EXP -78    /* minimum float power of 10          */
     #define DBL_MIN_10_EXP -78    /* minimum double power of 10         */
     #define LDBL_MIN_10_EXP -78   /* minimum long double power of 10    */
    
     #define FLT_MAX_EXP 63        /* maximum exponent of 16 for float   */
     #define DBL_MAX_EXP 63        /* maximum exponent of 16 for double  */
     #define LDBL_MAX_EXP 63       /* maximum exponent of 16 for long    */
                                   /* double                             */
     #define FLT_MAX_10_EXP 75     /* maximum float power of 10          */
     #define DBL_MAX_10_EXP 75     /* maximum double power of 10         */
     #define LDBL_MAX_10_EXP 75    /* maximum long double power of 10    */
    
     #define FLT_MAX .7237005e76F              /* maximum float          */
     #define DBL_MAX .72370055773322621e76     /* maximum double         */
     #define LDBL_MAX .72370055773322621e76L   /* maximum long double    */
    
        /* smallest float x such that 1.0 + x != 1.0                     */
     #define FLT_EPSILON .9536743e-6F
    
        /* smallest double x such that 1.0 + x != 1.0                    */
     #define DBL_EPSILON .22204460492503131e-15
    
        /* smallest long double x such that 1.0 - x != 1.0               */
     #define LDBL_EPSILON .22204460492503131e-15L
    
     #define FLT_MIN .5397606e-78F                /* minimum float       */
     #define DBL_MIN .53976053469340279e-78       /* minimum double      */
     #define LDBL_MIN .53976053469340279e-78L     /* minimum long double */
     

Additionally, the header file `<lcmath.h>` declares useful mathematical
constants, as listed in Table 2.3.

Table 2.3 _Constant Values Declared in lcmath.h_

* * *
    
    
       Constant   Representation
     

* * *
    
    
       M_PI        pi
    
       M_PI_2      pi/2
    
       M_PI_4      pi/4
    
       M_1_PI      1/pi
    
       M_2_PI      2/pi
    
       M_E         e
    
       HUGE*       largest possible double
    
       TINY        double closest to zero
    
       LOGHUGE     log(HUGE)
    
       LOGTINY     log(TINY)
    
     

*`math.h` defines the value `HUGE_VAL`, which is an ANSI-defined symbol with the same value. 

* * *

The following are mathematical functions:

`abs`

    integer conversion: absolute value 
`acos`

    compute the trigonometric arc cosine 
`asin`

    compute the trigonometric arc sine 
`atan`

    compute the trigonometric arc tangent 
`atan2`

    compute the trigonometric arc tangent of a quotient 
`ceil`

    round up a floating-point number 
`cos`

    compute the trigonometric cosine 
`cosh`

    compute the hyperbolic cosine 
`div`

    integer conversion: division 
`erf`

    compute the error function 
`erfc`

    compute the complementary error function 
`exp`

    compute the exponential function 
`fabs`

    floating-point conversion: absolute value 
`floor`

    round down a floating-point number 
`fmax`

    find the maximum of two doubles 
`fmin`

    find the minimum of two doubles 
`fmod`

    floating-point conversion: modules 
`frexp`

    floating-point conversion: fraction-exponent split 
`gamma`

    compute the logarithm of the gamma function 
`hypot`

    compute the hypotenuse function 
`j0`

    Bessel function of the first kind, order 0 
`j1`

    Bessel function of the first kind, order 1 
`jn`

    Bessel function of the first kind, order _n_
`labs`

    integer conversion: absolute value 
`ldexp`

    floating-point conversion: load exponent 
`_ldexp`

    fast implementation of `ldexp`
`ldiv`

    integer conversion: division 
`log`

    compute the natural logarithm 
`log10`

    compute the common logarithm 
`_matherr`

    handle math function error 
`max`

    find the maximum of two integers 
`min`

    find the minimum of two integers 
`modf`

    floating-point conversion: fraction-integer split 
`pow`

    compute the value of the power function 
`rand`

    simple random number generation 
`sin`

    compute the trigonometric sine 
`sinh`

    compute the hyperbolic sine 
`sqrt`

    compute the square root 
`srand`

    simple random number generation 
`tan`

    compute the trigonometric tangent 
`tanh`

    compute the hyperbolic tangent 
`y0`

    Bessel function of the second kind, order 0 
`y1`

    Bessel function of the second kind, order 1 
`yn`

    Bessel function of the second kind, order _n_. 

## Varying-Length Argument List Functions

This category of functions contains three macros that advance through a list
of arguments whose number and type are unknown when the function is compiled.
The macros are

`va_arg`

    access an argument from a varying-length argument list 
`va_end`

    end varying-length argument list processing 
`va_start`

    begin varying length argument list processing. 
These macros and the type `va_list` are defined in the header file
`<stdarg.h>`. For more information on `<stdarg.h>`, see the function
description for `va_start`.

## General Utility Functions

The four utility functions are

`bsearch`

    perform a binary search 
`pdset`

    packed decimal conversion: double to packed decimal 
`pdval`

    packed decimal conversion: packed decimal to double 
`qsort`

    sort an array of elements. 

## Program Control Functions

The program entry mechanism, which is the means by which the `main` function
gains control, is system dependent. However, program exit is not always system
dependent, although it does have some implementation dependencies.

One simple way to terminate execution of a C program is for the `main`
function to execute a `return` statement; another is for the `main` function
to drop through its terminating brace. However, in many cases, a more flexible
program exit capability is needed. This capability is provided by the `exit`
function described in this section. This function offers the advantage of
allowing any function (not just `main`) to terminate the program, and it
allows information to be passed to other programs.

For programs using the compiler `indep` feature, program execution can also be
terminated by calling the L$UEXIT routine from non-C code, as described in
Appendix 5, "Using the indep Option for Interlanguage Communication," in the _
SAS/C Compiler and Library User's Guide, Fourth Edition _

You can use the `atexit` function to define a function to be called during
normal program termination, either due to a call to `exit` or due to return
from the `main` function.

The `abend` and `abort` functions can also be used to terminate execution of a
C program. These functions cause abnormal termination, which causes both
library cleanup and user cleanup (defined by `atexit` routines) to be
bypassed.

In some cases, it is useful for a program to pass control directly to another
part of the program (within a different function) without having to go through
a long and possibly complicated series of function returns. The `setjmp` and
`longjmp` functions provide a general capability for passing control in this
way.

You can use the SAS/C extension `blkjmp` to intercept calls to `longjmp` that
cause the calling routine to be terminated. This is useful for functions that
allocate resources that must be released before the function is terminated.
You can also use `blkjmp` to intercept calls to `exit`.

**Note:** The jump functions use a special type, `jmp_buf`, which is defined in the `<setjmp.h>` header file. 

Several of the program control functions have a special version for use in the
Systems Programming Environment. See [Implementation of Functions](http://supp
ort.sas.com/documentation/onlinedoc/sasc/doc/lr1/lrv1ch1.htm#impfunc) for more
details.

The program control functions are

`abend`

    abnormally terminate execution via ABEND 
`abort`

    abnormally terminate execution 
`atexit`

    register program cleanup function 
`blkjmp`

    intercept nonlocal gotos 
`exit`

    terminate execution 
`longjmp`

    perform nonlocal goto 
`onjmp`

    define target for nonlocal goto 
`onjmpout`

    intercept nonlocal gotos 
`setjmp`

    define label for nonlocal goto. 

## Memory Allocation Functions

The standard library provides several different levels of memory allocation,
providing varying levels of portability, efficiency, and convenience. The
`malloc` family of functions (`calloc`, `malloc`, `free`, and `realloc`)
conforms to the ISO/ANSI standard and is therefore the most portable (and
usually the most convenient) technique for memory allocation. The `pool`
family of functions (`pool`, `palloc`, `pfree`, and `pdel`) is not portable
but is more efficient for many applications. Finally, the `sbrk` function
provides compatibility with traditional UNIX low-level memory management but
is inflexible because the maximum amount of memory that can be allocated is
fixed independently of the size of the region or virtual machine. All of the
memory allocation functions return a pointer of type `void *` that is
guaranteed to be properly aligned to store any object.

All of these interfaces, except `sbrk`, use the operating system's standard
memory allocation technique (GETMAIN under MVS, DMSFREE under CMS, or CMSSTOR
under bimodal CMS) to allocate memory blocks. This means that blocks allocated
by the C language may be interspersed with blocks allocated by the operating
system or by other programs. It also means that the C program is always able
to allocate memory up to the limits imposed by the region or virtual machine
size.

If your application requires more complete control of memory allocation
parameters, you can call the GETMAIN, DMSFREE, and CMSSTOR functions yourself,
as described in Chapter 14, "Systems Programming with the SAS/C Compiler," of
the _ SAS/C Compiler and Library User's Guide, Fourth Edition _ . Because the
other memory allocation functions do not invoke the operating system every
time they are called, they are generally more efficient than direct use of the
operating system services.

Under MVS, all SAS/C memory allocation (except when the program invokes the
GETMAIN SVC directly) is task related. Thus, it is not valid to use `malloc`
to allocate a block of memory under one TCB and free it under another. Even if
the two tasks share all MVS subpools, this error will cause memory management
chains to become erroneously linked, which will eventually cause a memory
management ABEND in one or more of the involved tasks.

Even the SAS/C pool allocation functions, such as `palloc`, do not allow
memory allocation to be managed across task boundaries. `palloc` calls
`malloc` to extend a pool if necessary; therefore, it may corrupt memory
chains if used under the wrong task. Additionally, the code generated by
`palloc` and `pfree` does no synchronization, which means that simultaneous
use on the same pool in several tasks could cause the same element to be
allocated twice, or lost from the memory chains.

If an application requires multiple SAS/C subtasks with memory shared between
subtasks, we recommend that you assign to a single task the job of performing
all shared memory allocation and deallocation for the application. All other
tasks should then use POST/WAIT logic to request the allocation task to
allocate or free memory. This design ensures that all shared memory is managed
as a unit and avoids synchronization issues caused by simultaneous allocation
requests.

The memory allocation functions are

`calloc`

    allocate and clear memory 
`free`

    free a block of memory 
`malloc`

    allocate memory 
`palloc`

    allocate an element from a storage pool 
`pdel`

    delete a storage pool 
`pfree`

    return an allocated element to a storage pool 
`pool`

    allocate a storage pool 
`realloc`

    change the size of an allocated memory block 
`sbrk`

    traditional UNIX low-level memory allocation. 

## Diagnostic Control Functions

The functions in this category allow you to control the processing of errors
by the library. For example, you can put diagnostics into programs with
`assert`, generate a library traceback with `btrace`, and suppress library
diagnostics with `quiet`.

The diagnostic control functions are

`assert`

    put diagnostics into programs 
`btrace`

    generate a traceback 
`perror`

    write diagnostic message 
`quiet`

    control library diagnostic output 
`strerror`

    map error number to a message string. 

## Timing Functions

The SAS/C library supports all of the ISO/ANSI timing functions. Timing
functions allow determination of the current time of day, and the processing
and formatting of time values. Programs using any of these functions must
include the header file `<time.h>`.

The POSIX standards mandate several changes to the SAS/C timing functions. As
a result, the SAS/C Release 6.00 library assumes a new default epoch and can
process time-zone information defined via the `TZ` environment variable.

In previous releases of SAS/C, `time_t` values were measured from the 370
epoch, starting at January 1, 1900. In accordance with the POSIX specification
, the SAS/C Release 6.00 library measures time from the UNIX epoch, starting
at January 1, 1970.

A program with special requirements can specifically define its own epoch by
declaring the extern variable `_epoch`, as in the following example:

    
    
     #include <time.h>
    
     time_t _epoch = _EPOCH_370;
     

This declaration specifies the 370 epoch. You can also use the value
`_EPOCH_UNIX` to specify the standard UNIX epoch. Any legitimate `time_t`
value can be used as the epoch, as in this example, which defines the start of
the epoch as January 1, 1971:

    
    
     #include <time.h>
    
     time_t _epoch = _EPOCH_UNIX+365*86400;
     

Also, if the `TZ` environment variable is set, the SAS/C `mktime`, `ctime`,
`localtime`, and `strftime` routines will take time-zone information into
account. For TSO or CMS programs, `TZ` may be defined as an external or
permanent scope environment variable.

**Note:** The `TZ` environment variable expresses offset from Greenwich mean time. The SAS/C library assumes that the hardware time-of-day clock has been set to accurately reflect Greenwich time, as recommended by the IBM ESA Principles of Operation. If the hardware time-of-day clock does not accurately reflect Greenwich time, then processing of the `TZ` information will not be correct, and applications depending on accurate local time information may fail. 

The `<time.h>` header file defines two types that describe time values:
`time_t` and `struct tm`. The type `time_t` is a numeric type used to contain
time values expressed in the seconds after some implementation-defined base
point (or era). The type `struct tm` is a structure that is produced by
several of the timing routines; it contains time and date information in a
more readily usable form. The `struct tm` structure is defined to contain the
following components:

    
    
        int tm_sec;     /* seconds after the minute (0-59)  */
        int tm_min;     /* minutes after the hour (0-59)    */
        int tm_hour;    /* hours since midnight (0-23)      */
        int tm_mday;    /* day of the month (1-31)          */
        int tm_mon;     /* months since January (0-11)      */
        int tm_year;    /* years since 1900                 */
        int tm_wday;    /* days since Sunday (0-6)          */
        int tm_yday;    /* days since January 1 (0-365)     */
        int tm_isdst;   /* Daylight Savings Time flag.      */
     

Routines are provided to convert `time_t` values to `struct tm` values and to
convert either of these types to a formatted string suitable for printing.

The resolution and accuracy of time values vary from implementation to
implementation. Timing functions under traditional UNIX C compilers return a
value of type `long`. The library implements `time_t` as a `double` to allow
more accurate time measurement. Keep this difference in mind for programs
ported among several environments.

The timing functions are

`asctime`

    convert time structure to character string 
`clock`

    measure program processor time 
`ctime`

    convert local time value to character string 
`difftime`

    compute the difference of two times 
`gmtime`

    break Greenwich mean time into components 
`localtime`

    break local time value into components 
`mktime`

    generate encoded time value 
`strftime`

    convert time to string 
`time`

    return the current time 
`tzset`

    store time zone information. 

## I/O Functions

The SAS/C library provides a large set of input/output functions. These
functions are divided into two groups, standard I/O functions and UNIX style
I/O functions.

The library's I/O implementation is designed to

  * support the ISO/ANSI C standard 
  * support the execution of existing programs developed with other C implementations 
  * support the development of new portable programs 
  * support the effective use of native MVS and CMS I/O facilities and file types. 

The library provides several I/O techniques to meet the needs of different
applications. To achieve the best results, you must make an informed choice
about the techniques to use. Criteria that should influence your choice are

  * the need for portability (For example, will the program execute on several different systems?) 
  * the required capabilities (For example, will the program need to alter the file position randomly during processing?) 
  * the need for efficiency (For example, can the program accept some restrictions on file format to achieve good performance?) 
  * the intended use of the files (For example, will files produced by the program later be processed by an editor or by a program written in another language?). 

To make these choices, you need to understand general C I/O concepts as well
as the native I/O types and file structures supported by the 370 operating
systems, MVS and CMS.

Details about C I/O concepts and functions can be found in [I/O Functions](htt
p://support.sas.com/documentation/onlinedoc/sasc/doc/lr1/lrv1ch3.htm#chap3) .

The I/O functions are

`afflush`

    flush file buffers to disk 
`afopen`

    open a file with system-dependent options 
`afread`

    read a record 
`afread0`

    read a record (possibly length zero) 
`afreadh`

    read part of a record 
`afreopen`

    reopen a file with system-dependent options 
`afwrite`

    write a record 
`afwrite0`

    write a record (possibly length 0) 
`afwriteh`

    write part of a record 
`aopen`

    open a file for UNIX style access with amparms 
`clearerr`

    clear error flag 
`close`

    close a file opened by `open`
`_close`

    close an HFS file 
`closedir`

    close a directory 
`clrerr`

    clear error flag and return status 
`creat`

    create and open a file for UNIX style I/O 
`ctermid`

    get a filename for the terminal 
`dup`

    duplicate a file descriptor 
`dup2`

    duplicate a file descriptor to a specific file descriptor number 
`fattr`

    return file attribute information 
`fclose`

    close a file 
`fcntl`

    control open files or sockets 
`_fcntl`

    control open file descriptors for OpenEdition HFS files 
`fdopen`

    access an OpenEdition file descriptor via standard I/O 
`feof`

    test for end of file 
`ferror`

    test error flag 
`ffixed`

    test for fixed-length records 
`fflush`

    flush output buffer 
`fgetc`

    read a character from a file 
`fgetpos`

    store the current file position 
`fgets`

    read a string from a file 
`fileno`

    return file descriptor number 
`fnm`

    return filename 
`fopen`

    open a file 
`fprintf`

    write formatted output to a file 
`fputc`

    write a character to a file 
`fputs`

    write a string to a file 
`fread`

    read items from a file 
`freopen`

    reopen a file 
`fscanf`

    read formatted input from a file 
`fseek`

    reposition a file 
`fsetpos`

    reposition a file 
`fsync`

    flush buffers for a UNIX style file to disk 
`_fsync`

    flush HFS file buffers to disk 
`ftell`

    obtain the current file position 
`fterm`

    terminal file test 
`ftruncate`

    truncate an OpenEdition file 
`fwrite`

    write items to a file 
`getc`

    read a character from a file 
`getchar`

    read a character from the standard input stream 
`gets`

    read a string from the standard input stream 
`isatty`

    test for terminal file 
`kdelete`

    delete current record from keyed file 
`kgetpos`

    return position information for keyed file 
`kinsert`

    insert record into keyed file 
`kreplace`

    replace record in keyed file 
`kretrv`

    retrieve next record from keyed file 
`ksearch`

    search keyed file for matching record 
`kseek`

    reposition a keyed stream 
`ktell`

    return RBA of current record 
`lseek`

    position a file opened for UNIX style access 
`_lseek`

    position an OpenEdition HFS file 
`open`

    open a file for UNIX style I/O 
`_open`

    open an OpenEdition HFS file 
`opendir`

    open an OpenEdition HFS directory 
`pclose`

    close a pipe opened by `popen`
`pipe`

    create and open a pipe 
`popen`

    open pipe I/O to an OpenEdition shell command 
`printf`

    write formatted output to the standard output stream 
`putc`

    write a character to a file 
`putchar`

    write a character to the standard output stream 
`puts`

    write a string to the standard output stream 
`read`

    read data from a file opened for UNIX style access 
`_read`

    read data from an OpenEdition HFS file 
`readdir`

    read an OpenEdition directory entry 
`rewind`

    position to start of file 
`rewinddir`

    positions an OpenEdition directory stream to the beginning 
`scanf`

    read formatted data from the standard input stream 
`setbuf`

    change stream buffering 
`setvbuf`

    change stream buffering 
`snprintf`

    write a limited amount of formatted output to a string 
`sprintf`

    write formatted output to a string 
`sscanf`

    read formatted data from a string 
`tmpfile`

    create and open a temporary file 
`tmpnam`

    generate temporary filename 
`ttyname`

    get name of open terminal file 
`ungetc`

    push back an input character 
`vfprintf`

    write formatted output to a file 
`vprintf`

    write formatted output to the standard output stream 
`vsnprintf`

    write a limited amount of formatted output to a string 
`vsprintf`

    write formatted output to a string 
`write`

    write data to a file open for UNIX-style access 
`_write`

    write data to an OpenEdition HFS file. 

## File Management Functions

The SAS/C library provides a number of file management functions that enable
you to interact with the file system in various ways. For example, functions
are provided to test and change file attributes, remove or rename files, and
search for all files whose names match a pattern. The file management
functions are

`access`

    test for the existence and access privileges of a file 
`_access`

    test for OpenEdition HFS file existence or access privileges 
`chdir`

    change the OpenEdition working directory 
`chmod`

    change the protection bits of an OpenEdition HFS file 
`cmsdfind`

    find the first CMS fileid matching a pattern 
`cmsdnext`

    find the next CMS fileid matching a pattern 
`cmsffind`

    find the first CMS fileid matching a pattern 
`cmsfnext`

    find the next CMS fileid matching a pattern 
`cmsfquit`

    release data held by `cmsffind`
`cmsstat`

    fill in a structure with information about a CMS file 
`fchmod`

    change the protection bits of an OpenEdition file 
`fstat`

    get status information for an OpenEdition file 
`getcwd`

    return the name of the OpenEdition working directory 
`link`

    create a hard link to an existing OpenEdition file 
`lstat`

    get status information about an OpenEdition file or symbolic link 
`mkdir`

    create a new OpenEdition directory 
`mkfifo`

    create an OpenEdition FIFO special file 
`oeddinfo`

    get information about a DD statement allocated to an OpenEdition HFS file 
`osddinfo`

    obtain information about a data set by DDname 
`osdfind`

    find the first MVS file/member matching a pattern 
`osdnext`

    find the next MVS file/member matching a pattern 
`osdquit`

    terminate MVS file/member search 
`osdsinfo`

    obtain information about an MVS data set by dsname 
`readlink`

    read the contents of an OpenEdition symbolic link 
`remove`

    delete a file 
`rename`

    rename a file 
`_rename`

    rename an OpenEdition disk file or directory 
`rmdir`

    remove an empty OpenEdition directory 
`sfsstat`

    return information about a CMS shared file system file or directory 
`stat`

    get status information for an OpenEdition file 
`symlink`

    create a symbolic link to an OpenEdition file 
`unlink`

    delete a file 
`_unlink`

    delete an OpenEdition HFS file 
`utime`

    update the access and modification times for an OpenEdition file. 

## System Interface and Environment Variables

The system interface and environment variables enable a program to interact
with the operating system. These functions are described in detail in
[Environment Variables](http://support.sas.com/documentation/onlinedoc/sasc/do
c/lr1/lrv1ch4.htm#chap4) .

The system interface functions are

`clearenv`

    delete environment variables 
`cuserid`

    get current userid 
`getenv`

    get value of environment variable 
`getlogin`

    determine user login name 
`iscics`

    return CICS environment information 
`oslink`

    call an MVS utility program 
`putenv`

    update environment variable 
`setenv`

    update environment variable 
`system`

    execute a system command. 

## Signal-Handling Functions

The signal-handling feature of the SAS/C library is a collection of library
functions that enables you to handle unexpected conditions and interrupts
during execution of a C program. These functions are described in detail in
[Signal-Handling Functions](http://support.sas.com/documentation/onlinedoc/sas
c/doc/lr1/lrv1ch5.htm#chap5) . Using this facility, you can

  * define which signals are managed by the SAS/C library and which ones are managed by OpenEdition 
  * define a function called a signal handler that performs special processing when a signal occurs 
  * control which signals are processed by your program, which are ignored, and which are handled using the system default action 
  * block the reception of some signals 
  * generate signals 
  * define signals for your own needs. 

The signal-handling functions are

`alarm, alarmd`

    request a signal after a real-time interval 
`ecbpause`

    delay program execution until the occurrence of a C signal or the POSTing of an Event Control Block (obsolete function) 
`ecbsuspend`

    delay program execution until the occurrence of a C signal or the POSTing of an Event Control Block 
`kill`

    send a signal to a process 
`oesigsetup`

    define which signals are managed by the SAS/C library and which signals are managed by OpenEdition 
`pause`

    suspend execution until a signal is received 
`raise`

    generate an artificial signal 
`sigaction`

    define a signal handler 
`sigaddset  
sigdelset  
sigemptyset  
sigfillset  
sigismember`

    manipulate `sigset_t` objects 
`sigblock`

    inhibit discovery of asynchronous signals (obsolete function) 
`sigchk`

    check for asynchronous signals 
`siggen`

    generate an artificial signal with additional information 
`siginfo`

    obtain information about a signal 
`siglongjmp`

    restore a previously saved stack environment and signal mask 
`signal`

    define program signal handling 
`sigpause`

    suspend execution and block discovery of signals (obsolete function) 
`sigpending`

    determine pending signals for a process 
`sigprocmask`

    inhibit or permit discovery of signals 
`sigsetjmp`

    saves the current stack environment and signal mask 
`sigsetmask`

    inhibit or permit discovery of signals (obsolete function) 
`sigsuspend`

    suspend program execution until a signal is generated 
`sleep, sleepd`

    suspend execution for a period of time. 

* * *

![](./libc_files/button.books.gif)

[Copyright (c) 1998 SAS Institute Inc.](http://support.sas.com/documentation/o
nlinedoc/sasc/doc/common/images/copyrite.htm) Cary, NC, USA. All rights
reserved.


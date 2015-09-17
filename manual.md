musl 1.0.0 Reference Manual
===========================

Part I - Introduction
---------------------

musl is an implementation of the userspace portion of the standard
library functionality described in the ISO C and POSIX standards, plus
common extensions. It can be used both as the system-wide C library
for operating system installations and distributions, and as a tool
for building individual application binaries deployable on a wide
range of systems compatible with the Linux system calls API.

This manual covers many details of musl which may be of interest to
programmers, systems integrators, and end users. It is a work in
progress.


### Conformance

The interfaces in musl are modeled upon and intended to conform to the
requirements of the ISO C99 standard (ISO/IEC 9899-1999), including
Annex F, and POSIX 2008 / Single Unix Standard Version 4, with all
current technical corrigenda applied. However, musl has not been
certified by any standards body, and no guarantee of conformance is
made by the copyright holders or any other party with an interest in
musl.

Moreover, since musl provides only the userspace portion of the
standard system interfaces, conformance to the requirements of POSIX
depends in part on the behavior of the underlying kernel. Linux 2.6.39
or later is believed to be sufficient; earlier versions in the 2.6
series will work, but with varying degrees of non-conformance,
particularly in the area of signal handling behavior and close-on-exec
race conditions.

Likewise, conformance to the requirements of ISO C, and especially
Annex F (IEEE floating point semantics), depends in part on both the
compiler used to build musl and the compiler used when building
applications against musl. At this time there is no known fully
conforming compiler.


### Supported Targets

* i386
    * Minimum CPU model is actually 80486 unless kernel emulation of
      the `cmpxchg` instruction is added

* x86_64

* ARM
    * EABI, standard or hard-float VFP variant
    * Little-endian default; big-endian variants also supported
    * Compiler toolchains only support armv4t and later

* MIPS
    * ABI is o32
    * Big-endian default; little-endian variants also supported
    * Default ABI variant uses FPU registers; alternate soft-float ABI
      that does not use FPU registers or instructions is available
    * MIPS2 or later, or kernel emulation of ll/sc (standard in Linux)
      is required

* PowerPC
    * Only 32-bit is supported
    * Compiler toolchain must provide 64-bit long double, not IBM
      double-double or IEEE quad
    * For dynamic linking, compiler toolchain must be configured for
      "secure PLT" variant

* Microblaze
    * Big-endian default; little-endian variants also supported
    * Soft-float
    * Requires support for lwx/swx instructions


### Experimental Targets

The following additional targets are available for build, but may not
work correctly and may not yet have ABI stability:

* SuperH (SH)
    * Little-endian by default; big-endian variant also supported
    * Full FPU ABI or soft-float ABI is supported, but the
      single-precision-only FPU ABI is not supported (musl always
      requires IEEE single and double to be supported)

* x32 (x86_64 ILP32 ABI)



Part II - Setup and Usage
-------------------------

### Build and Installation

The build system for musl uses the well-known `./configure` idiom.
musl's configure script is not based on GNU autoconf, but is intended
to closely match the configure command line interface documented in
the GNU Coding Standards. Running configure produces a `config.mak`
file which can further be edited by hand, if necessary.

#### Prerequisites

The only build-time prerequisites for musl are the standard POSIX
shell and utilities, GNU Make (version 3.81 or later) and a
freestanding C99 compiler toolchain targeting the desired instruction
set architecture and ABI, with support for gcc-style inline assembly,
weak aliases, and stand-alone assembly source files.

The system used to build musl does not need to be Linux-based, nor do
the Linux kernel headers need to be available.

If support for dynamic linking is desired, some further requirements
are placed on the compiler and linker. In particular, the linker must
support the `-Bsymbolic-functions` option, and the compiler must not
generate gratuitous GOT relocations where GOT-relative or PC-relative
addressing could be used instead.

#### Supported compilers

A recent version of GCC or LLVM/clang is recommended for compiling
musl. However, the following compilers are known to have built musl
successfully:

* GCC 4.6 or later. Versions back to 3.4.6 or possibly earlier will
  work but have floating point bugs which affect i386.

* LLVM/clang 3.2 or later. Earlier versions are known to have bugs
  that produce a malfunctioning libc.

* PCC 1.1.0.DEVEL or later.

* Firm/cparser, for static libc only.

#### Build options

Running `./configure --help` from the top-level source directory will
print usage information for configure. In most cases, the only options
which should be needed are:

* `--prefix`, used to control where musl will be installed. The prefix
  for musl defaults to `/usr/local/musl` rather than `/usr/local` to
  avoid breaking an existing non-musl environment on the host. If musl
  will be used as the primary system libc, prefix should usually be
  set to `/usr` or `/`.

* `--syslibdir`, used to specify the location at which the dynamic
  linker should be installed and found at runtime. The default of
  `/lib` should only be overridden when installing in `/lib` is
  impossible, since the pathname of the dynamic linker is stored in
  all dynamic-linked executables, and executables using non-standard
  paths for the dynamic linker may be difficult to deploy on other
  systems.

Both `--prefix` and `--syslibdir` should reflect the final runtime
location where musl will be installed. If musl should be installed to
a different location to prepare a package file or new target system
image, the `DESTDIR` variable can be set when running `make install`.
In this case, `DESTDIR` will be prepended to all installation paths,
but will not be saved anywhere in the files installed.

Other build options of interest are:

* `CC=...`, to choose a non-default compiler.

* `CFLAGS=...`, to pass custom options to the compiler.

* `--disable-shared`, to disable building shared `libc.so` if it will
  not be needed. This cuts the build time in half.

* `--disable-static`, to disable building `libc.a`. Other (empty) `.a`
  files are still built. This also cuts the build time in half.

* `--enable-optimize=`*list*, where *list* is a comma-separated list
  of components (subdirectories of `src`, or glob patterns) which will
  be optimized at `-O3` rather than the default optimization level
  `-Os`. Manually specifying an optimization level in the provided
  `CFLAGS`, or using `--enable-debug` or `--disable-optimize`, will
  turn off default optimizations.

* `--enable-warnings`, to turn on the recommended set of GCC warning
  options with which musl is intended to compile warning-free.

* `--enable-debug`, to turn on debugging. Adding `-g` to `CFLAGS`
  manually also works. In the future, `--enable-debug` may also enable
  additional debugging features at the source level.

See `./configure --help` for additional options.

#### Compiling and Installing

After running configure, run `make` to compile and `make install` to
install. If desired, `make install` can be invoked directly without
first running `make`, but it may be desirable to do these as separate
steps if elevated privileges are needed to install to the final
destination. musl's makefile is fully declarative and non-recursive,
and may be arbitrarily parallelized with the `-j` option.

Note: The `install` target in musl's `Makefile` is fully declaratory,
and its proper operation depends on file timestamps being correct. If
files with newer/future timestamps already exist in the destination,
updated files may fail to be installed. This can be avoided by
deleting the offending files, fixing their timestamps, or installing
first to a fresh `DESTDIR` then moving the files into place.

#### After Installation

If installing for the first time and using dynamic linking, it may be
necessary to create a path file for the dynamic linker. See
`../etc/ld-musl-$(ARCH).path` under the heading *Additional Files
Used* later in this part of the manual.



### Installed Components

In the following, `$(syslibdir)`, `$(includedir)`, and `$(libdir)`
refer to the paths chosen at build time (by default, `/lib`,
`$(prefix)/include`, and `$(prefix)/lib`, respectively) and `$(ARCH)`
refers to the *full* name for the target CPU architecture/ABI,
including the "subarch" component.

#### Dynamic linking runtime

`$(syslibdir)/ld-musl-$(ARCH).so.1` provides the dynamic linker, or
"program interpreter", for dynamically linked ELF programs using musl.
The absolute pathname to this file must be stored in all such
programs. The build and installation system provided with musl sets it
up as a symbolic link to `$(libdir)/libc.so`, but system integrators
may choose to make it available in whichever ways they find suitable.

#### Development environment

Header files for use by the C compiler are installed in
`$(includedir)`. The standard headers are fully self-contained, and do
not make use of kernel-provided or compiler-provided headers or
otherwise require such headers to be present.

The file `libc.a` installed in `$(libdir)` provides the entire
standard library implementation for static linking. The file `libc.so`
provides the linker with access to the standard library's symbols for
use at link-time in producing dynamic-linked binaries. It is not
searched at runtime; the standard library is resolved as part of the
program interpreter at `$(syslibdir)/ld-musl-$(ARCH).so.1`.

Additional files `libm.a`, `librt.a`, `libpthread.a`, `libcrypt.a`,
`libutil.a`, `libxnet.a`, `libresolv.a`, and `libdl.a` are provided in
`$(libdir)` as empty library archives. They contain no code, but are
present to satisfy the POSIX requirement that options of the form
`-lm`, `-lpthread`, etc. be accepted by the `c99` compiler.

Several bare object files are also included in `$(libdir)`: `crt1.o`
and `Scrt1.o` are the normal and position-independent versions,
respectively, of the entry point code linked into every program.
`crti.o` and `crtn.o`, also linked into every program and into shared
libraries, provide support for legacy means by which the compiler can
arrange for global constructors and destructors to be executed. It is
possible to setup a legacy-free compiler toolchain that does not need
the `crti.o` and `crtn.o` files if desired.

#### Compiler wrapper

Included with musl is a wrapper script `musl-gcc` which can be used
with an existing GCC compiler toolchain to build programs using musl.
If installed, the script itself is located at `$(bindir)/musl-gcc`,
and a supporting GCC specs file it uses is located at
`$(libdir)/musl-gcc.specs`.


### Filesystem Layout Dependencies

musl aims to avoid imposing filesystem policy; however, the following
minimal set of filesystems dependencies must be met in order for
programs using musl to function correctly:

* `/dev/null` - device node, required by POSIX

* `/dev/tty` - device node, required by POSIX

* `/tmp` - required by POSIX to exist as a directory, and used by
  various temporary file creation functions.

* `/bin/sh` - an executable file providing a POSIX-conforming shell

* `/proc` - must be a mount point for Linux procfs or a symlink to
  such. Several functions such as realpath, fexecve, and a number of
  the "at" functions added in POSIX 2008 need access to /proc to
  function correctly.

* `$(syslibdir)/ld-musl-$(ARCH).so.1` - must resolve to the musl
  dynamic linker/libc.so binary in order for dynamic-linked programs
  to run. For static-linked programs it is unnecessary.

While some programs may operate correctly even without some or all of
the above, musl's behavior in their absence is unspecified.


### Additional Files Used

* `/dev/log` - a UNIX domain socket to which the `syslog()` interface
  sends log messages. If absent, log messages will be discarded.

* `/dev/shm` - a directory; should have permissions 01777. If absent,
  POSIX shared memory and named semaphore interfaces will fail;
  programs not using these features will be unaffected.

* `/dev/ptmx` and `/dev/pts` - device node and devpts filesystem mount
  point, respectively. If absent, `posix_openpt()` and `openpty()`
  will fail.

* `/etc/passwd` and `/etc/group` - text files containing the user and
  group databases, mappings between names and numeric ids, and group
  membership lists, in the standard traditional format. If absent,
  user and/or group lookups will fail.

* `/etc/shadow` - text file containing shadow password hashes for some
  or all users. If absent (and TCB shadow files are also absent),
  shadow password lookups will fail.

* `/etc/tcb/`*user*`/shadow` - text file containing a single shadow
  password record for *user*, based on the Openwall TCB alternative
  for shadow password storage. If absent for *user*, `/etc/shadow`
  will be searched.

* `/etc/resolv.conf` - text file providing addresses of nameservers to
  be used for DNS lookups. If absent, DNS requests will be sent to the
  loopback address and will fail unless the host has its own
  nameserver.

* `/etc/hosts` - text file mapping hostnames to IP addresses. If
  absent, only DNS will be used.

* `/etc/services` - text file mapping network service names to port
  numbers. If absent, only numeric service/port strings can be used.

* `/etc/shells` - a list of shell pathnames to be returned by the
  `getusershell` interface. If absent a built-in default list will be
  used.

* `/usr/share/zoneinfo`, `/share/zoneinfo`, and `/etc/zoneinfo` -
  directories searched for time zone files when the `TZ` environment
  variable is set to a relative pathname. If absent, only absolute
  zoneinfo file pathnames or POSIX timezone specifications can be
  used.

* `../etc/ld-musl-$(ARCH).path`, taken relative to the location of the
  "program interpreter" specified in the program's headers - if
  present, this will be processed as a text file containing the shared
  library search path, with components delimited by newlines or
  colons. If absent, a default path of
  `"/lib:/usr/local/lib:/usr/lib"` will be used. Not used by
  static-linked programs.


### Environment Variables

* `PATH` - Used by execvp, execlp, and posix_spawnp as specified in
  POSIX. If unset, a default search path of
  `"/usr/local/bin:/bin:/usr/bin"` is used.

* `TZ` - Specifies the local timezone to be used for functions which
  deal with local time. The value of `TZ` can be either a POSIX
  timezone specification in the form
  `stdoffset[dst[offset][,start[/time],end[/time]]]` or the name of a
  zoneinfo-binary-format timezone file (the form used by glibc and
  most other systems). The latter is interpreted as an absolute
  pathname if it begins with a slash, a relative pathname if it begins
  with a dot, and otherwise is searched in `/usr/share/zoneinfo`,
  `/share/zoneinfo`, and `/etc/zoneinfo`. When searching these paths,
  strings including any dots are rejected. If the program was invoked
  setuid, setgid, or with other elevated capabilities, the absolute
  and relative pathname options are not available.

* `DATEMSK` - Used by the `getdate` function as a pathname for the
  file containing date formats to scan, per POSIX.

* `PWD` - Used by the nonstandard `get_current_dir_name` function; if
  it matches the actual current directory, it is returned instead of
  using `getcwd` to obtain the canonical pathname.

* `LOGNAME` - The `getlogin` function simply returns the value of the
  `LOGNAME` variable.

* `LD_PRELOAD` - Colon-separated list of shared libraries that will be
  preloaded by the dynamic linker before processing the application's
  dependency list. Components can be absolute or relative pathnames or
  filenames in the default library search path. This variable is
  completely ignored in programs invoked setuid, setgid, or with other
  elevated capabilities.

* `LD_LIBRARY_PATH` - Colon-separated list of pathnames that will be
  searched for shared libraries requested without an explicit
  pathname. This path is searched prior to the default path (which is
  specified in `$(syslibdir)/../etc.ld-musl-$(ARCH).path` with
  built-in default fallback if this file is missing). This variable is
  completely ignored in programs invoked setuid, setgid, or with other
  elevated capabilities.



Part III - Programmers' Manual
------------------------------

### Compiler Support

All public interfaces in musl, at both the header file and library
level, are intended to be mostly compatible with any C99, C11, or C++
compiler targeting the same CPU architecture and ABI musl was built
for. C89 compilers are also supported provided that they accept the
`long long` type and wide character literals as extensions. A few
public header files do, however, require compiler-specific extensions
in order to provide the mandated standard features:

* `complex.h` requires `1.0fi` to be accepted as a constant expression
  suitable for defining `_Complex_I`.

* `tgmath.h` requires the `__typeof__` extension. Future versions may
  offer a portable C11 version of `tgmath.h` using `_Generic` as well.

* `stdarg.h` requires the `__builtin_va_list` type and related builtin
  functions.

* `netinet/tcp.h` requires anonymous unions, available in C11 and as
  an extension in GCC and compatible compilers, in the default feature
  profile. In strict ISO C and POSIX profiles, anonymous unions are
  not needed.

In addition, the definitions of `NAN` (in `math.h`) and `offsetof` (in
`stddef.h`) require the `__builtin_nanf` and `__builtin_offsetof`
extensions, respectively, to provide fully conforming definitions.
When used with compilers which do not predefine `__GNUC__`, these
headers will fallback to alternate definitions.


### System Header Files

#### Introduction to Namespace Issues

Any C program using a library, whether the standard library or a
third-party library, needs to observe a contract with the library
regarding usage of identifiers - in particular, which identifiers are
used as part of the library's public interface or header file
implementation, and which identifiers are used by the application.
Having a clear contract is especially important when the library being
used is not a single fixed implementation, but may have multiple
versions or multiple independent implementations. The canonical
example of such a library is the standard library.

ISO C reserves all identifiers which are not explicitly defined or
reserved by the standard for use by the application. POSIX, however,
exposes a number of additional identifiers, and popular extensions
outside of the standards define even more. In order to support
applications which are written with different expectations on which
identifiers may be used for the application's purposes, and which ones
are defined by the system, a mechanism must be provided for choosing
*which contract* will be used.

#### Introduction to Feature Test Macros

To solve this problem, POSIX introduced the concept of *feature test
macros*. These are macros which an application may define *prior to
the inclusion of any system header* (either at the source level, or
via `-D` options passed as arguments to the compiler) in order to
request a particular namespace contract. POSIX 2008 specifies two such
feature test macros:

* `_POSIX_C_SOURCE`, defined to `200809L` to request all interfaces
  defined in the POSIX base standard.

* `_XOPEN_SOURCE`, defined to `700` to request all interfaces defined
  under the XSI option in addition to POSIX base.

No requirements are placed on the namespace when neither of these
macros is defined by the application. If one or both of these macros
is defined by the application, two constraints are placed on the
system headers:

* They must define all macros and declare all functions and objects
  which the standard specifies for that header to provide.

* They must not make use of any identifier not specified or reserved
  for that header.

There is, however, an exception to the second rule: since the standard
does not define behavior when the application has defined macros whose
names are reserved for system use, implementations may specify their
own feature test macros to expose additional identifiers alongside the
standard ones.

This is what musl, and most other implementations of the standard
library, do.

#### Feature Test Macros Supported by musl

If no feature test macros are defined, musl's headers operate in
"default features" mode, exposing the equivalent of the `_BSD_SOURCE`
option below. This corresponds fairly well to what most applications
unaware of feature test macros expect, and also provides a number of
more modern features.

Otherwise, if at least one of the below-listed feature test macros is
defined, they are treated additively, starting from pure ISO C as a
base. Unless otherwise specified, musl ignores the value of the macro
and only checks whether it is defined.

* `__STRICT_ANSI__`

    Adds nothing; only suppresses the default features. This macro is
    defined automatically by GCC and other major compilers in strict
    standards-conformance modes.

* `_POSIX_C_SOURCE` (or `_POSIX_SOURCE`)

    As specified by POSIX 2008; adds POSIX base. If defined to a value
    less than `200809L`, or if the deprecated version `_POSIX_SOURCE`
    is defined at all, interfaces which were removed from the standard
    but which are still in widespread use are also exposed.

* `_XOPEN_SOURCE`

    As specified by POSIX 2008; adds all interfaces in POSIX including
    the XSI option. If defined to a value less than `700`, interfaces
    which were removed from the standard but which are still in
    widespread use are also exposed.

* `_BSD_SOURCE`

    Adds everything above, plus a number of traditional and modern
    interfaces modeled after BSD systems, or supported on current BSD
    systems based on older standards such as SVID.

* `_GNU_SOURCE` (or `_ALL_SOURCE`)

    Adds everything above, plus interfaces modeled after GNU libc
    extensions and interfaces for making use of Linux-specific
    features.

Documentation of specific extensions provided by the nonstandard
feature test macros will be added in a future edition of this manual.



### Library Interfaces

For all interfaces provided by musl that are specified by standards to
which musl aims for conformance, the relevant standards documents are
the official documentation.

* The current edition of the C99 standard with TC1/2/3 applied is
  available from <http://www.open-std.org> as document WG14 N1256.

* The POSIX 2008 standard with TC1 applied is available from The Open
  Group at <http://pubs.opengroup.org/onlinepubs/9699919799/>.

This portion of the manual is incomplete. Future editions will
document musl's behavior where the standards specify that it is
implementation-defined, non-standard extensions musl implements, and
additional properties of musl's implementation.

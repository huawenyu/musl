/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2004 H. Peter Anvin - All Rights Reserved
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------------------------------------------------------- */

#ifndef _BITS_IO_H
#define _BITS_IO_H

int iopl(int);
int ioperm(unsigned long, unsigned long, int);

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void outb(unsigned char __v, unsigned short __p)
{
	__asm__ volatile ("outb %0,%1" : : "a" (__v), "dN"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void outw(unsigned short __v, unsigned short __p)
{
	__asm__ volatile ("outw %0,%1" : : "a" (__v), "dN"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void outl(unsigned int __v, unsigned short __p)
{
	__asm__ volatile ("outl %0,%1" : : "a" (__v), "dN"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static unsigned char inb(unsigned short __p)
{
	unsigned char __v;
	__asm__ volatile ("inb %1,%0" : "=a" (__v) : "dN"(__p));
	return __v;
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static unsigned short inw(unsigned short __p)
{
	unsigned short __v;
	__asm__ volatile ("inw %1,%0" : "=a" (__v) : "dN"(__p));
	return __v;
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static unsigned int inl(unsigned short __p)
{
	unsigned int __v;
	__asm__ volatile ("inl %1,%0" : "=a" (__v) : "dN"(__p));
	return __v;
}


#if __STDC_VERSION__ >= 199901L
inline
#endif
static void outsb(unsigned short __p, const void *__d, unsigned long __n)
{
	__asm__ volatile ("cld; rep; outsb"
		      : "+S" (__d), "+c"(__n)
		      : "d"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void outsw(unsigned short __p, const void *__d, unsigned long __n)
{
	__asm__ volatile ("cld; rep; outsw"
		      : "+S" (__d), "+c"(__n)
		      : "d"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void outsl(unsigned short __p, const void *__d, unsigned long __n)
{
	__asm__ volatile ("cld; rep; outsl"
		      : "+S" (__d), "+c"(__n)
		      : "d"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void insb(unsigned short __p, void *__d, unsigned long __n)
{
	__asm__ volatile ("cld; rep; insb"
		      : "+D" (__d), "+c"(__n)
		      : "d"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void insw(unsigned short __p, void *__d, unsigned long __n)
{
	__asm__ volatile ("cld; rep; insw"
		      : "+D" (__d), "+c"(__n)
		      : "d"(__p));
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void insl(unsigned short __p, void *__d, unsigned long __n)
{
	__asm__ volatile ("cld; rep; insl"
		      : "+D" (__d), "+c"(__n)
		      : "d"(__p));
}

#endif
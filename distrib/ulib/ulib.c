#include "xv6/types.h"
#include "xv6/stat.h"
#include "xv6/fcntl.h"
#include "xv6/user.h"
#include "xv6/x86.h"

char*
gets(char *buf, int max)
{
    int i, cc;
    char c;

    for (i = 0; i + 1 < max; ) {
        cc = read(0, &c, 1);
        if (cc < 1)
            break;
        buf[i++] = c;
        if (c == '\n' || c == '\r')
            break;
    }
    buf[i] = '\0';
    return buf;
}

int
stat(char *n, struct stat *st)
{
    int fd;
    int r;

    fd = open(n, O_RDONLY);
    if (fd < 0)
        return -1;
    r = fstat(fd, st);
    close(fd);
    return r;
}

int
atoi(const char *s)
{
    int n;

    n = 0;
    while ('0' <= *s && *s <= '9')
        n = n * 10 + *s++ - '0';
    return n;
}


char *strcpy(register char *to, register const char *from)
{
    char *save = to;
    for (; (*to = *from); ++from, ++to);
    return(save);
}

char *strncpy(char *dst, const char *src, register uint n)
{
    if (n != 0) {
        register char *d = dst;
        register const char *s = src;

        do {
            if ((*d++ = *s++) == 0) {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }
    return (dst);
}

int strcmp(register const char *s1, register const char *s2)
{
    while (*s1 == *s2++)
        if (*s1++ == 0)
            return (0);
    return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int strncmp(register const char *s1, register const char *s2, register uint n)
{

    if (n == 0)
        return (0);
    do {
        if (*s1 != *s2++)
            return (*(unsigned char *)s1 - *(unsigned char *)--s2);
        if (*s1++ == 0)
            break;
    } while (--n != 0);
    return (0);
}

uint strlen(const char *str)
{
    register const char *s;

    for (s = str; *s; ++s);
    return(s - str);
}

char *strchr(register const char *p, register const char ch)
{
    for (;; ++p) {
        if (*p == ch)
            return((char *)p);
        if (!*p)
            return((char *)0);
    }
    /* NOTREACHED */
}


char *strrchr(register const char *p, register const char *ch)
{
    register char *save;

    for (save = 0;; ++p) {
        if (*p == ch)
            save = (char *)p;
        if (!*p)
            return(save);
    }
    /* NOTREACHED */
}

char *strstr(register const char *s, register const char *find)
{
    register char c, sc;
    register uint len;

    if ((c = *find++) != 0) {
        len = strlen(find);
        do {
            do {
                if ((sc = *s++) == 0)
                    return (0);
            } while (sc != c);
        } while (strncmp(s, find, len) != 0);
        s--;
    }
    return ((char *)s);
}

char *strcat(register char *s, register const char *append)
{
    char *save = s;

    for (; *s; ++s);
    while ((*s++ = *append++));
    return(save);
}

char *strncat(char *dst, const char *src, register uint n)
{
    if (n != 0) {
        register char *d = dst;
        register const char *s = src;

        while (*d != 0)
            d++;
        do {
            if ((*d = *s++) == 0)
                break;
            d++;
        } while (--n != 0);
        *d = 0;
    }
    return (dst);
}


void *memccpy(void *t, const void *f, int c, register uint n)
{
    if (n) {
        register unsigned char *tp = t;
        register const unsigned char *fp = f;
        register unsigned char uc = c;
        do {
            if ((*tp++ = *fp++) == uc)
                return (tp);
        } while (--n != 0);
    }
    return (0);
}

void *memcpy(void *vdst, const void *vsrc, register uint n)
{
    char *dst = (char *)vdst;
    const char *src = (const char *)vsrc;

    while (n-- > 0)
        *dst++ = *src++;
    return vdst;
}


void *memchr(const void *s, register unsigned char c, register uint n)
{
    if (n != 0) {
        register const unsigned char *p = s;

        do {
            if (*p++ == c)
                return ((void *)(p - 1));
        } while (--n != 0);
    }
    return (0);
}

int memcmp(const void *s1, const void *s2, uint n)
{
    if (n != 0) {
        register const unsigned char *p1 = s1, *p2 = s2;

        do {
            if (*p1++ != *p2++)
                return (*--p1 - *--p2);
        } while (--n != 0);
    }
    return (0);
}

void *memset(void *dst, register int c, register uint n)
{
    stosb(dst, c, n);
    return dst;
}


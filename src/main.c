#include <stdio.h>  //  for printf
#include <string.h> // for strlen, strcpy, strcmp, strdup
#include <errno.h>  // for errno (ft_write, ft_read)
#include <unistd.h> // for write, read (ft_write, ft_read)
#include <fcntl.h>  // for open (ft_read)
#include <stdlib.h> // for free (ft_strdup)
#include "libasm.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define LABEL(str)      GREEN str RESET
#define EXPECTED        GREEN " | expected: " RESET
#define HEADER(str)     YELLOW BOLD "\n=== " str " ===\n" RESET
#define EQ      GREEN " = " RESET

int main(void)
{
    /* ft_strlen */
    printf(HEADER("ft_strlen"));
    {
        printf(LABEL("ft_strlen(\"Hello\") ") EQ "%zu" EXPECTED "%zu\n", ft_strlen("Hello"),  strlen("Hello"));
        printf(LABEL("ft_strlen(\"\")      ") EQ "%zu" EXPECTED "%zu\n", ft_strlen(""),       strlen(""));
        printf(LABEL("ft_strlen(\"a\")     ") EQ "%zu" EXPECTED "%zu\n", ft_strlen("a"),      strlen("a"));
    }

    /* ft_strcpy */
    printf(HEADER("ft_strcpy"));
    {
        char dst1[64];
        char dst2[64];

        printf(LABEL("ft_strcpy(dst, \"hello\") ") EQ "%s" EXPECTED "%s\n", ft_strcpy(dst1, "hello"), strcpy(dst2, "hello"));
        printf(LABEL("ft_strcpy(dst, \"\")      ") EQ "%s" EXPECTED "%s\n", ft_strcpy(dst1, ""), strcpy(dst2, ""));
    }

    /* ft_strcmp */
    printf(HEADER("ft_strcmp"));
    {
        printf(LABEL("ft_strcmp(\"Hello\", \"Hello\") ") EQ "%d" EXPECTED "%d\n", ft_strcmp("Hello", "Hello"), strcmp("Hello", "Hello"));
        printf(LABEL("ft_strcmp(\"Hello\", \"World\") ") EQ "%d" EXPECTED "%d\n", ft_strcmp("Hello", "World"), strcmp("Hello", "World"));
        printf(LABEL("ft_strcmp(\"\", \"\")           ") EQ "%d" EXPECTED "%d\n", ft_strcmp("", ""),           strcmp("", ""));
        printf(LABEL("ft_strcmp(\"a\", \"\")          ") EQ "%d" EXPECTED "%d\n", ft_strcmp("a", ""),          strcmp("a", ""));
    }

    /* ft_write */
    printf(HEADER("ft_write"));
    fflush(stdout); // flush before direct fd writes to avoid color bleed
    {
        ssize_t r1 = ft_write(1, "ft_write: Hello World\n", 22);
        ssize_t r2 =    write(1,    "   write: Hello World\n", 22);
        fflush(stdout);
        printf(LABEL("ft_write return ") EQ "%zd" EXPECTED "%zd\n", r1, r2);

        ssize_t r3 = ft_write(-1, "test", 4);
        ssize_t r4 =    write(-1, "test", 4);
        printf(LABEL("ft_write bad fd ") EQ "%zd" GREEN ", errno = " RESET "%d" EXPECTED "%zd" GREEN ", errno = " RESET "%d\n", r3, errno, r4, errno);
    }

    /* ft_read */
    printf(HEADER("ft_read"));
    {
        int fd;
        char buf1[32]; char buf2[32];

        fd = open("test_read.txt", O_RDONLY);
        ssize_t r1 = ft_read(fd, buf1, 5);
        buf1[r1] = '\0'; close(fd);

        fd = open("test_read.txt", O_RDONLY);
        ssize_t r2 =    read(fd, buf2, 5);
        buf2[r2] = '\0'; close(fd);

        printf(LABEL("ft_read(5 bytes) ") EQ "%s" EXPECTED "%s\n", buf1, buf2);
        printf(LABEL("ft_read return   ") EQ "%zd" EXPECTED "%zd\n", r1, r2);

        ssize_t r3 = ft_read(-1, buf1, 5);
        ssize_t r4 =    read(-1, buf2, 5);
        printf(LABEL("ft_read bad fd   ") GREEN EQ RESET "%zd" GREEN ", errno = " RESET "%d" EXPECTED "%zd" GREEN ", errno = " RESET "%d\n", r3, errno, r4, errno);

    }

    /* ft_strdup */
    printf(HEADER("ft_strdup"));
    {
        char *s1 = ft_strdup("Hello");
        char *s2 =    strdup("Hello");
        printf(LABEL("ft_strdup(\"Hello\")       ") EQ "%s" EXPECTED "%s\n", s1, s2);
        printf(LABEL("are different pointers ? ") EQ "%d" EXPECTED "1\n", s1 != s2);
        free(s1);
        free(s2);
    }

    return EXIT_SUCCESS;
}
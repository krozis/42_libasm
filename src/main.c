#include <stdio.h>  //  for printf
#include <string.h> // for strlen, strcpy, strcmp
#include <errno.h> 
#include <unistd.h> // for write, read
#include <fcntl.h>  // for open
#include "libasm.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

int main(void)
{

    /* ft_strlen */
    {
        printf(YELLOW BOLD "=== ft_strlen ===\n" RESET);

        printf(GREEN"ft_strlen(\"Hello\")  = " RESET " %zu " GREEN "| expected: " RESET "%zu\n", ft_strlen("Hello"),  strlen("Hello"));
        printf(GREEN"ft_strlen(\"\")       = " RESET " %zu " GREEN "| expected: " RESET "%zu\n", ft_strlen(""),       strlen(""));
        printf(GREEN"ft_strlen(\"a\")      = " RESET " %zu " GREEN "| expected: " RESET "%zu\n", ft_strlen("a"),      strlen("a"));
    }

    /* ft_strcpy */
    {
        printf(YELLOW BOLD "\n=== ft_strcpy ===\n" RESET);
        char dst1[64];
        char dst2[64];
        printf(GREEN"ft_strcpy(dst, \"hello\")  = " RESET " %s " GREEN "| expected: " RESET "%s\n", ft_strcpy(dst1, "hello"),  strcpy(dst2, "hello"));
        printf(GREEN"ft_strcpy(dst, \"\")       = " RESET " %s " GREEN "| expected: " RESET "%s\n", ft_strcpy(dst1, ""),  strcpy(dst2, ""));
    }

    /*  ft_strcmp */    
    {
        printf(YELLOW BOLD "\n=== ft_strcmp ===\n" RESET);

        printf(GREEN"ft_strcmp(\"Hello\", \"Hello\")  = " RESET " %d " GREEN "| expected: " RESET "%d\n", ft_strcmp("Hello", "Hello"),  strcmp("Hello", "Hello"));
        printf(GREEN"ft_strcmp(\"Hello\", \"World\")  = " RESET " %d " GREEN "| expected: " RESET "%d\n", ft_strcmp("Hello", "World"),  strcmp("Hello", "World"));
        printf(GREEN"ft_strcmp(\"\")             = " RESET " %d " GREEN "| expected: " RESET "%d\n", ft_strcmp("", ""),  strcmp("", ""));
        printf(GREEN"ft_strcmp(\"a\", \"\") = " RESET " %d " GREEN "| expected: " RESET "%d\n", ft_strcmp("a", ""), strcmp("a", ""));
    }

    /* ft_write */
    {
        printf(YELLOW BOLD "\n=== ft_write ===\n" RESET);

        ssize_t r1 = ft_write(1, "ft_write: Hello World\n", 22);
        ssize_t r2 =    write(1,    "   write: Hello World\n", 22);
        printf("ft_write return = %zd | expected: %zd\n", r1, r2);

        ssize_t r3 = ft_write(-1, "test", 4);
        ssize_t r4 =    write(-1, "test", 4);
        printf("ft_write bad fd = %zd, errno = %d | expected: %zd, errno = %d\n", r3, errno, r4, errno);
    }

    
    /* ft_read */
    {
        printf(YELLOW BOLD "\n=== ft_read ===\n" RESET);
        int fd = open("test_read.txt", O_RDONLY);
        char buf1[32]; char buf2[32];
        ssize_t r1 = ft_read(fd, buf1, 5); buf1[r1] = '\0'; close(fd);
        fd = open("test_read.txt", O_RDONLY);
        ssize_t r2 =    read(fd, buf2, 5); buf2[r2] = '\0'; close(fd);
        printf("ft_read(5 bytes)  = %s | expected: %s\n", buf1, buf2);
        printf("ft_read return    = %zd | expected: %zd\n", r1, r2);

        ssize_t r3 = ft_read(-1, buf1, 5);
        ssize_t r4 =    read(-1, buf2, 5);
        printf("ft_read bad fd    = %zd, errno = %d | expected: %zd, errno = %d\n", r3, errno, r4, errno);
    }
    
    return 0;
}
 
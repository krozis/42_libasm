#include <stdio.h>
#include <string.h>
#include "libasm.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

int main(void)
{
    /* ft_strlen */
    printf(YELLOW BOLD "=== ft_strlen ===\n" RESET);
    printf(GREEN"ft_strlen(\"Hello\")  = " RESET " %zu " GREEN "| expected: " RESET "%zu\n", ft_strlen("Hello"),  strlen("Hello"));
    printf(GREEN"ft_strlen(\"\")       = " RESET " %zu " GREEN "| expected: " RESET "%zu\n", ft_strlen(""),       strlen(""));
    printf(GREEN"ft_strlen(\"a\")      = " RESET " %zu " GREEN "| expected: " RESET "%zu\n", ft_strlen("a"),      strlen("a"));
 
    /* ft_strcpy */
    printf(YELLOW BOLD "\n=== ft_strcpy ===\n" RESET);
    char dst1[64];
    char dst2[64];
    printf(GREEN"ft_strcpy(dst, \"hello\")  = " RESET " %s " GREEN "| expected: " RESET "%s\n", ft_strcpy(dst1, "hello"),  strcpy(dst2, "hello"));
    printf(GREEN"ft_strcpy(dst, \"\")       = " RESET " %s " GREEN "| expected: " RESET "%s\n", ft_strcpy(dst1, ""),  strcpy(dst2, ""));
 
    return 0;
}
 
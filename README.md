# 42_libasm
libasm project from 42 Advanced

This project is about discovering x86_64 assembly by reimplementing standard C library functions in assembly language.
The goal is to create a static library `libasm.a` containing these functions, which can be used in C programs.

## Mandatory functions

- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`

## Bonus functions

- `ft_atoi_base`
- `ft_list_push_front`
- `ft_list_size`
- `ft_list_sort`
- `ft_list_remove_if`

## Project requirements

- Intel syntax (not AT&T)
- 64-bit code
- No inline ASM, only `.s` files
- Compile with `nasm`
- The `-no-pie` flag is forbidden


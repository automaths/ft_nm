#include "ft_nm.h"

char	symtab_section_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char    c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
        {
            c = 'W';
            if (sym.st_shndx == SHN_UNDEF)
                c = 'w';
        }
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
        {
            c = 'V';
            if (sym.st_shndx == SHN_UNDEF)
                c = 'v';
        }
    else
        c = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}

//     bind, type, st_info, st_shndx, st_other
// A 
// B 1 0 16 26 0, 1 0 16 26 0, 
// b 0 1 1 26 0, 
// C
// D 1 0 16 25 0, 1 0 16 25 0, 1 1 17 25 2, 1 1 17 25 2,
// d 0 1 1 22 0, 0 1 1 21 0, 0 1 1 24 0, 0 1 1 23 0,
// G
// g
// i
// N
// p
// R 1 1 17 18 0, 
// r 0 1 1 4 0, 0 1 1 20 0, 0 0 0 19 0, 
// S
// s
// T 1 2 18 16 0, 1 2 18 16 0, 1 2 18 17 2, 1 2 18 12 2, 1 2 18 1 0
// t 0 2 2 16 0, 0 2 2 16 0, 0 2 2 16 0, 
// U 1 2 18 0 0, 1 2 18 0 0, 1 0 16 0 0,
// u
// V
// v
// W 2 0 32 25 0, 2 0 32 0 0, 2 0 32 0 0, 2 0 32 0 0, 
// w 2 2 34 0 0, 
// -
// ?

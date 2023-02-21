#include "ft_nm.h"

//i section specific for implementation of DLLs
//I indirect reference to another symbol
//n in read-only data section
//S s unitializaed section for small objects
//W w weak symbol not tagged as weak symbol

// char	symtab_section_type(Elf64_Sym sym, Elf64_Shdr *shdr)
// {
//     char c;

//     if (sym.st_shndx == SHN_ABS)
//         return 'A';
//     else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS)
//     {
//         if (sym.st_shndx == 26)
//             c = 'B';
//         else
//             c = 'D';
//         //G in unitialized for small objects
//     }
//     else if (sym.st_shndx == SHN_COMMON)
//         c = 'C';
//     else if (shdr[sym.st_shndx].sh_type == SHT_ALPHA_DEBUG)
//         return 'N';
//     else if (shdr[sym.st_shndx].sh_type == SHT_PARISC_UNWIND)
//         return 'p';
//     else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
//              && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
//         c = 'R';
//     else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
//              && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
//         c = 'T';
//     else if (sym.st_info == 32)
//         c = 'W';
//     else if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
//         return 'u';
//     else if (sym.st_shndx == SHN_UNDEF)
//         return 'U';    
//     else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
//         c = 'V';
//     else
//         return '?';
//     if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
//         c += 32;
//     return c;
// }

char	symtab_section_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char    c;
    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    //
    else if (sym.st_shndx == 25)
        c = 'D';
    else if (!ELF64_ST_BIND(sym.st_info) && ELF64_ST_TYPE(sym.st_info) == 1 && sym.st_info == 1 && sym.st_shndx > 20)
        return 'd';
    else if (sym.st_info == 32)
    {
        if (ELF64_ST_VISIBILITY(sym.st_info) == 0)
            return 'w';
        else
            return 'W';
    }
    //
    else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
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
    // else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    //     {
    //         c = 'W';
    //         if (sym.st_shndx == SHN_UNDEF)
    //             c = 'w';
    //     }
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

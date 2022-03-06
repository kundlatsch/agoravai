// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

void CPU::syscall(void * msg)
{
    ASM(
        //Salvando contexto
        "str lr, [sp, #-8]!   \n"
        "stp x0, x1, [sp, #-16]  \n"
        "stp x2, x3, [sp, #-16]  \n"
        //Chamando sycall
        "mov x0, %0 \n"

        "SVC 0x0    \n"

        //Retornando contexto
        "ldp x2, x3, [sp, #16]  \n"
        "ldp x0, x12, [sp, #16]   \n"
        "ldr lr, [sp, #8]!   \n"
        "" :: "r"(msg)
    );
}

__END_SYS
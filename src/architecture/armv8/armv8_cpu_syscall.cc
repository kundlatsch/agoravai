// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

void CPU::syscall(void * msg)
{
    ASM(
        //Salvando contexto
        "str lr, [sp, #-8]!   \n"
        "stp x0, x12, [sp, #-16]  \n"
        //Chamando sycall
        // "mov x0, %0 \n"
        // "mov x12, [sp] \n"  // salvar tmp sp_usr
        // "mrs [sp], [sp_usr] \n" // carregar sp_svc
        // "msr [sp_usr], x12 \n"// salvar sp_usr

        // "SVC 0x0    \n"

        // "mov x12, [sp] \n"  //salvar tmp sp_svc
        // "mrs [sp], [sp_usr] \n" //carregar sp_usr
        // "msr [sp_usr], x12 \n" //salver_sp_svc

        //Retornando contexto
        "ldp x0, x12, [sp, #16]   \n"
        "ldr lr, [sp, #8]!   \n"
        "" :: "r"(msg)
    );
}

__END_SYS
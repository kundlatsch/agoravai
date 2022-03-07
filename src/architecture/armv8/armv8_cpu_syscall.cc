// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

void CPU::syscall(void * msg)
{
      ASM(
        "mov %0, x0     \n" 
        "SVC 0x0    \n"
        "" :: "r"(msg)
    );
}

__END_SYS
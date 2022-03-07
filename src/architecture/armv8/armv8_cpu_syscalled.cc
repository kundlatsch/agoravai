// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

extern "C" { void _sysexec(); }

__BEGIN_SYS

void CPU::syscalled() {
      ASM("stp x0, lr, [sp, #-16]  \n"
          "bl _sysexec   \n"
          "ldp x0, lr, [sp], #16  \n"
      );
}

__END_SYS
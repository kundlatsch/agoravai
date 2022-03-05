// EPOS ARMv7 CPU Mediator Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

unsigned int CPU::_cpu_clock;
unsigned int CPU::_bus_clock;

void CPU::Context::save() volatile {
    ASM(R"(
        // Store Registers
    	stp x0,  x1,  [%0,  #8]
        stp x2,  x3,  [%0, #24]
        stp x4,  x5,  [%0, #40]
        stp x6,  x7,  [%0, #56]
        stp x8,  x9,  [%0, #72]
        stp x10, x11, [%0, #88]
        stp x12, x13, [%0, #104]
        stp x14, x15, [%0, #120]
        stp x16, x17, [%0, #136]
        stp x18, x19, [%0, #152]
        stp x20, x21, [%0, #168]
        stp x22, x23, [%0, #184]
        stp x24, x25, [%0, #200]
        stp x26, x27, [%0, #216]
        stp x28, x29, [%0, #232]
        // Save LR and PC (Before LR)
        adr x16, ret
        stp x30, x16, [%0, #248]
        
        // Compute and store PSR
        mrs x16, daif
        mrs x17, nzcv
        orr x16, x16, x17
        mrs x17, CurrentEL
        orr x16, x16, x17
        mrs x17, SPSel
        orr x16, x16, x17
        str x16,      [%0,  #0]
        // Restore IPC Registers
        ldp x16, x17, [%0, #136]
        ret: ret
    )"::"r"(this));
}

void CPU::Context::load() const volatile
{
    sp(this);
    Context::pop();
}

void CPU::switch_context(Context ** o, Context * n)
{
    // Push the context into the stack and update "o"
    Context::push();
    *o = sp();

    // Set the stack pointer to "n" and pop the context
    sp(n);
    Context::pop();

    // Cross-domain return point used in save_regs()
    iret();
}

__END_SYS

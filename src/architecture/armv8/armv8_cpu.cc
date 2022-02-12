// EPOS ARMv7 CPU Mediator Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

unsigned int CPU::_cpu_clock;
unsigned int CPU::_bus_clock;

// Class methods

// Class methods
void CPU::Context::save() volatile
{
    ASM(
        "stp	x0, x1, [sp, #-16]!                                                 \n" // store pair
        "stp	x2, x3, [sp, #-16]!                                                 \n"
        "stp	x4, x5, [sp, #-16]!                                                 \n"
        "stp	x6, x7, [sp, #-16]!                                                 \n"
        "stp	x8, x9, [sp, #-16]!                                                 \n"
        "stp	x10, x11, [sp, #-16]!                                               \n"
        "stp	x12, x13, [sp, #-16]!                                               \n"
        "stp	x14, x15, [sp, #-16]!                                               \n"
        "stp	x16, x17, [sp, #-16]!                                               \n"
        "stp	x18, x19, [sp, #-16]!                                               \n"
        "stp	x20, x21, [sp, #-16]!                                               \n"
        "stp	x22, x23, [sp, #-16]!                                               \n"
        "stp	x24, x25, [sp, #-16]!                                               \n"
        "stp	x26, x27, [sp, #-16]!                                               \n"
        "stp	x28, x29, [sp, #-16]!                                               \n"
        "str	x30, [sp, #-8]!                                                     \n" // store register
        "bl _ZN4EPOS1S2IC8dispatchEj                                                \n");
}

void CPU::Context::load() const volatile
{
    sp(this);
    Context::pop();
}

// void CPU::Context::load() const volatile
// {
//     ASM(
//         "ldp	x0, x1, [sp], #16                                                   \n" // load pair
//         "ldp	x2, x3, [sp], #16                                                   \n"
//         "ldp	x2, x3, [sp], #16                                                   \n"
//         "ldp	x4, x5, [sp], #16                                                   \n"
//         "ldp	x6, x7, [sp], #16                                                   \n"
//         "ldp	x8, x9, [sp], #16                                                   \n"
//         "ldp	x10, x11, [sp], #16                                                 \n"
//         "ldp	x12, x13, [sp], #16                                                 \n"
//         "ldp	x14, x15, [sp], #16                                                 \n"
//         "ldp	x16, x17, [sp], #16                                                 \n"
//         "ldp	x18, x19, [sp], #16                                                 \n"
//         "ldp	x20, x21, [sp], #16                                                 \n"
//         "ldp	x22, x23, [sp], #16                                                 \n"
//         "ldp	x24, x25, [sp], #16                                                 \n"
//         "ldp	x26, x27, [sp], #16                                                 \n"
//         "ldp	x28, x29, [sp], #16                                                 \n"
//         "ldr	x30, [sp], #8                                                       \n"); // load register
// }



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

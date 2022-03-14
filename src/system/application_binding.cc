// EPOS Applicaiton Component Implementation

#include <utility/ostream.h>
#include <utility/heap.h>
#include <machine.h>
#include <memory.h>
#include <process.h>
#include <system.h>
#include <syscall/stub_thread.h>


__BEGIN_SYS
OStream kerr;
__END_SYS



// Bindings
extern "C" {
    void _panic() { _API::Stub_Thread::exit(-1); }
    void _exit(int s) { _API::Stub_Thread::exit(s); for(;;); }
}

__USING_SYS;
// Bindings
extern "C" {
    void _syscall(void * m) { CPU::syscall(m); }

    // OStream
    void _print(const char * s) {
        Message msg(0, Message::ENTITY::DISPLAY, Message::PRINT);
        msg.set_params(reinterpret_cast<unsigned long>(s));
        msg.act();
    }
}
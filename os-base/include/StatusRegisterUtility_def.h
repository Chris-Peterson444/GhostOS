#ifndef STATUSREGISTERUTILITY_DEF_H
#define STATUSREGISTERUTILITY_DEF_H
#include "ChipsetRegisters.h"
#include "Threads.h"

__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mstatus" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val){
    asm volatile ("csrw mstatus, %0" : : "r"(val));
}

__attribute__((always_inline)) inline uint32_t csr_mepc_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mepc" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mepc_write(uint32_t val){
    asm volatile ("csrw mepc, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val){
    asm volatile ("csrw mie, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_enable_interrupts(void){
    asm volatile ("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_disable_interrupts(void){
    asm volatile ("csrci mstatus, 0x8");
}

__attribute__((always_inline)) inline uint32_t thread_pointer_read(void){
    uint32_t result;
    asm volatile ("mv %0, tp" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void thread_pointer_write(uint32_t val){
    asm volatile ("mv tp, %0" : : "r"(val));
}


__attribute__((always_inline)) inline TCPUInterruptState CPUHALSuspendInterrupts(void){
    uint32_t result;
    asm volatile ("csrrci %0, mstatus, 0x8" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void CPUHALResumeInterrupts(TCPUInterruptState state){
    asm volatile ("csrs mstatus, %0" : : "r"(state & 0x8));
}

__attribute__((always_inline)) inline uint32_t csr_mcause_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mcause" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void external_interrupt_enable_all(void){
    INTERRUPT_ENABLE = (uint32_t) 0x37;
}

__attribute__((always_inline)) inline void external_interrupt_enable(uint32_t val){
    INTERRUPT_ENABLE &= val;
}

__attribute__((always_inline)) inline void external_interrupt_clear(uint32_t val){
   uint32_t temp = INTERRUPT_PENDING;
    INTERRUPT_PENDING = temp | val;
}

__attribute__((always_inline)) inline void CART_interrupt_clear(void){
    INTERRUPT_PENDING = INTERRUPT_PENDING | (uint32_t) 0x1;
}

__attribute__((always_inline)) inline void VID_interrupt_clear(void){
    INTERRUPT_PENDING = INTERRUPT_PENDING | (uint32_t) 0x2;
}

__attribute__((always_inline)) inline void CMD_interrupt_clear(void){
    INTERRUPT_PENDING = INTERRUPT_PENDING | (uint32_t) 0x4;
}

__attribute__((always_inline)) inline void DMA1_interrupt_clear(void){
    INTERRUPT_PENDING = INTERRUPT_PENDING | (uint32_t) 0x10;
}

__attribute__((always_inline)) inline void DMA2_interrupt_clear(void){
    INTERRUPT_PENDING = INTERRUPT_PENDING | (uint32_t) 0x20;
}

#endif
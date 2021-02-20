// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code

#ifndef STATUSREGISTERUTILITY_H
#define STATUSREGISTERUTILITY_H
#include <stdint.h>
#include "StatusRegisterUtility_def.h"


__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void);

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val);

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val);

__attribute__((always_inline)) inline void csr_enable_interrupts(void);


__attribute__((always_inline)) inline void csr_disable_interrupts(void);

__attribute__((always_inline)) inline uint32_t csr_mcause_read(void);

 // inline uint32_t csr_mstatus_read(void);
 // inline void csr_mstatus_write(uint32_t val);
 // inline void csr_write_mie(uint32_t val);
 // inline void csr_enable_interrupts(void);
 // inline void csr_disable_interrupts(void);
 // inline uint32_t csr_mcause_read(void);

//  // Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
// __attribute__((always_inline)) inline uint32_t csr_mstatus_read(void){
//     uint32_t result;
//     asm volatile ("csrr %0, mstatus" : "=r"(result));
//     return result;
// }

// __attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val){
//     asm volatile ("csrw mstatus, %0" : : "r"(val));
// }

// __attribute__((always_inline)) inline void csr_write_mie(uint32_t val){
//     asm volatile ("csrw mie, %0" : : "r"(val));
// }

// __attribute__((always_inline)) inline void csr_enable_interrupts(void){
//     asm volatile ("csrsi mstatus, 0x8");
// }

// __attribute__((always_inline)) inline void csr_disable_interrupts(void){
//     asm volatile ("csrci mstatus, 0x8");
// }

// __attribute__((always_inline)) inline uint32_t csr_mcause_read(void){
//     uint32_t result;
//     asm volatile ("csrr %0, mcause" : "=r"(result));
//     return result;
// }



#endif
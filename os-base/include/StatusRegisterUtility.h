// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code

#ifndef STATUSREGISTERUTILITY_H
#define STATUSREGISTERUTILITY_H
#include <stdint.h>
#include "StatusRegisterUtility_def.h"


//Get mstatus reg
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void);

//Write to mstatus
__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val);

//Write to mie
__attribute__((always_inline)) inline void csr_write_mie(uint32_t val);

//Enable Global Interrupts
__attribute__((always_inline)) inline void csr_enable_interrupts(void);

//Disable Global Interrupts
__attribute__((always_inline)) inline void csr_disable_interrupts(void);

//Get Interrupt Cause
__attribute__((always_inline)) inline uint32_t csr_mcause_read(void);

//Enable all external interrupts
__attribute__((always_inline)) inline void external_interrupt_enable_all(void);

/*Write to interrupt register
0 - Cartridge Interrupt Enable
1 - Video Interrupt Enable
2 - Command Interrupt Enable
4 - DMA Channel 1 Interrupt Enable
5 - DMA Channel 2 Interrupt Enable
*/
__attribute__((always_inline)) inline void external_interrupt_enable(uint32_t val);

/* Write to the pending interrupt register to clear interrupt. Corresponding bits
   to those found in external_interrupt_enable_all
*/
__attribute__((always_inline)) inline void external_interrupt_clear(uint32_t val);

//Sugar for external_interrupt_enable(0x1)
__attribute__((always_inline)) inline void CMD_interrupt_clear(void);

//Sugar for external_interrupt_enable(0x2)
__attribute__((always_inline)) inline void VID_interrupt_clear(void);

//Sugar for external_interrupt_enable(0x4)
__attribute__((always_inline)) inline void CART_interrupt_clear(void);

//Sugar for external_interrupt_enable(0x10)
__attribute__((always_inline)) inline void DMA1_interrupt_clear(void);

//Sugar for external_interrupt_enable(0x20)
__attribute__((always_inline)) inline void DMA2_interrupt_clear(void);



#endif
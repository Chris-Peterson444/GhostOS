#include <stdint.h>
#include <stdio.h>
#include "SystemUtil.h"
#include "ThreadInterface.h"
#include "Sleep.h"

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// // Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
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


ThreadQueueManager* threadManager;


#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
#define CONTROLLER      (*((volatile uint32_t *)0x40000018))
#define CARTRIDGE       (*((volatile uint32_t *)0x4000001C))
#define INT_EN          (*((volatile uint32_t *)0x40000000))
#define INT_PEND        (*((volatile uint32_t *)0x40000004))
#define GRAPHICS_MODE   (*((volatile uint32_t *)0x500FF414))



void init(void){
    uint8_t *Source = _erodata;
    uint8_t *Base = _data < _sdata ? _data : _sdata;
    uint8_t *End = _edata > _esdata ? _edata : _esdata;

    while(Base < End){
        *Base++ = *Source++;
    }
    Base = _bss;
    End = _ebss;
    while(Base < End){
        *Base++ = 0;
    }

    threadManager = (ThreadQueueManager*) getThreadQueueManager();
    // uint32_t ticksElapsed = 0;
    // uint32_t timerTicks = getTimerTicks();
    // uint32_t lastTick = timerTicks;
    // uint32_t seconds = 0;
    // while(1){
    //     timerTicks = getTimerTicks();
    //     if(lastTick != timerTicks){
    //         ticksElapsed += timerTicks - lastTick;
    //         printf("App ticks: %d\r",ticksElapsed);
    //         fflush(stdout);
    //     }
    // }
    // while(1){
    //     printf("APP: Seconds %d\r",seconds);
    //     fflush(stdout);
    //     sleep(1000);
    //     seconds++;
    // }
    // appThreadinit(threadManager);

}
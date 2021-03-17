// #include <stdint.h>
// #define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
// #define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
// #define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
// #define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
// #define CONTROLLER      (*((volatile uint32_t *)0x40000018))
// #define CARTRIDGE       (*((volatile uint32_t *)0x4000001C))
// #define INT_EN          (*((volatile uint32_t *)0x40000000))
// #define INT_PEND        (*((volatile uint32_t *)0x40000004))

// extern volatile int global;
// extern void timer_callback(void);
// extern void external_interrupt_clear(uint32_t val);
// extern volatile uint32_t controller_status;

// void timer_ISR(void){

//     uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
//     NewCompare += 100;
//     MTIMECMP_HIGH = NewCompare>>32;
//     MTIMECMP_LOW = NewCompare;
//     global++;
//     controller_status = CONTROLLER;
//     timer_callback();
//     external_interrupt_clear((uint32_t) 0x1);

// }
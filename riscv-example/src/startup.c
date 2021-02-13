#include <stdint.h>

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mstatus" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val){
    asm volatile ("csrw mstatus, %0" : : "r"(val));
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

__attribute__((always_inline)) inline uint32_t csr_mcause_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mcause" : "=r"(result));
    return result;
}



#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
#define CONTROLLER      (*((volatile uint32_t *)0x40000018))
#define CARTRIDGE       (*((volatile uint32_t *)0x4000001C))
#define INT_EN          (*((volatile uint32_t *)0x40000000))
#define INT_PEND        (*((volatile uint32_t *)0x40000004))



__attribute__((always_inline)) inline void external_enable_all_interrupts(void){
    INT_EN = (uint32_t) 0x37;
}

__attribute__((always_inline)) inline void external_enable_CMD_interrupt(void){
    INT_EN = (uint32_t) 0x4;
}

__attribute__((always_inline)) inline void external_enable_VID_interrupts(void){
    INT_EN = (uint32_t) 0x2;
}

__attribute__((always_inline)) inline void external_enable_CART_interrupts(void){
    INT_EN = (uint32_t) 0x1;
}

__attribute__((always_inline)) inline void external_interrupt_clear(uint32_t val){
   uint32_t temp = INT_PEND;
    INT_PEND = temp | val;
}

__attribute__((always_inline)) inline void CMD_interrupt_clear(void){
    INT_PEND = INT_PEND | (uint32_t) 0x4;
}

__attribute__((always_inline)) inline void VID_interrupt_clear(void){
    INT_PEND = INT_PEND | (uint32_t) 0x2;
}

__attribute__((always_inline)) inline void CART_interrupt_clear(void){
    INT_PEND = INT_PEND | (uint32_t) 0x1;
}


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

    csr_write_mie(0x888);       // Enable all interrupt soruces
    csr_enable_interrupts();    // Global interrupt enable
    MTIMECMP_LOW = 100;
    MTIMECMP_HIGH = 0;
    external_enable_all_interrupts(); //Enable all external interrupts
}
int pressed = 1;
extern volatile int global;
extern volatile uint32_t controller_status;
extern void timer_callback(void);
volatile int timerIgnore = 1;
__attribute__((always_inline)) inline void timer_ISR(void);
void graphics_ISR(void);
void external_ISR();
void cmd_ISR(void);

// void c_interrupt_handler(void){
//     uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
//     NewCompare += 100;
//     MTIMECMP_HIGH = NewCompare>>32;
//     MTIMECMP_LOW = NewCompare;
//     global++;
//     controller_status = CONTROLLER;
// }

void c_interrupt_handler(void){

    //Check mcause reg
    uint32_t mcause_reg = csr_mcause_read();

    //If isInterrupt is not 1, then sys error (need to check for this eventually)
    uint32_t isInterrupt = mcause_reg & 0x7FFFFFFF; //

    // Get interrupt reason
    uint32_t maskoff = 0x7FFFFFFF;
    mcause_reg = maskoff & mcause_reg;

    // // Check if an external interrupt
    // if (mcause_reg == (uint32_t) 11 ){

    //     if( INT_PEND & (uint32_t) 0x4 ){
    //         pressed = 1;
    //     }
    //     // else{
    //     //     pressed = 0;
    //     // }
        
    // }
    // Else it's a system interrupt
    // else{

    // }
    // if( pressed ){

    //     timer_ISR();

    // }
    switch(mcause_reg){
        case 7:
            timer_ISR();
            break;
        case 11:
            external_ISR();
            break;
        default:
        break;
    }

 
}

void external_ISR(uint32_t fid){
        
    if (INT_PEND & (uint32_t) 0x4){
        if(timerIgnore){
            timerIgnore = 0;
        }
        else{
            timerIgnore = 1;
        }
    }
    CMD_interrupt_clear();



}



void timer_ISR(void){

    uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
    NewCompare += 200;
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;
    csr_disable_interrupts();
    if(timerIgnore){
    timer_callback();
    global++;
    controller_status = CONTROLLER;
    }
    csr_enable_interrupts();
        // timer_callback();
    
    // external_interrupt_clear((uint32_t) 0x1);

}

#include <stdint.h>
#include "ChipsetRegisters.h"
#include "VideoControllerMap.h"
#include "StatusRegisterUtility.h"
#include "VideoControllerUtility.h"

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];


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
    external_interrupt_enable_all(); //Enable all external interrupts
    graphics_refresh_rate(0x5A);
    // graphics_text_mode();
}

int pressed = 1;
extern volatile int global;
extern volatile uint32_t controller_status;
extern void graphics_callback(void);
extern void timer_callback(void);
volatile int timerIgnore = 1;
__attribute__((always_inline)) inline void timer_ISR(void);
__attribute__((always_inline)) inline void graphics_ISR(void);
void external_ISR();
void cmd_ISR(void);

// void c_interrupt_handler(void){
//     uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
//     NewCompare += 100;
//     MTIMECMP_HIGH = NewCompare>>32;
//     MTIMECMP_LOW = NewCompare;
//     global++;
//     controller_status = CONTROLLER_STATUS;
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

    //     if( INTERRUPT_PENDING & (uint32_t) 0x4 ){
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
        csr_disable_interrupts();
            external_ISR();
        csr_enable_interrupts();
            break;
        default:
        break;
    }

 
}

void external_ISR (uint32_t fid){
        
    if (INTERRUPT_PENDING & (uint32_t) 0x4){

        if(timerIgnore){
            timerIgnore = 0;
        }
        else{
            timerIgnore = 1;
        }

        CMD_interrupt_clear();
    }
    else if (INTERRUPT_PENDING & (uint32_t) 0x2){
        graphics_ISR();
        VID_interrupt_clear();
    }
    else if (INTERRUPT_PENDING & (uint32_t) 0x1){
        // timerIgnore = 1;
        // graphics_graphic_mode();
        uint32_t jmp_point = CARTRIDGE_STATUS;
        jmp_point = jmp_point & (uint32_t) 0xFFFFFFFC;
        void (*foo)() = jmp_point;
        foo();
        // CART_interrupt_clear();
        
        // asm("jal ra, %0" : : "r"(jmp_point));
        // asm volatile ("call %0" : : "r"(jmp_point));
        // asm("call 0x20000000");
        
        // foo = CARTRIDGE_STATUS;
        

    }




}


__attribute__((always_inline)) inline void graphics_ISR(void){
    graphics_callback();
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
    controller_status = CONTROLLER_STATUS;
    }
    csr_enable_interrupts();
        // timer_callback();
    
    // external_interrupt_clear((uint32_t) 0x1);

}

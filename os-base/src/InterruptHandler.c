
#include "StatusRegisterUtility.h"
#include "InterruptMask.h"


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

uint32_t c_syscall(uint32_t param){
 
    return 0;
}

void c_interrupt_handler(void){

    //Check mcause reg
    uint32_t mcause_reg = csr_mcause_read();

    //If isInterrupt is not 1, then sys error (need to check for this eventually)
    uint32_t isInterrupt = mcause_reg & 0x7FFFFFFF; //

    // Get interrupt reason
    uint32_t maskoff = 0x7FFFFFFF;
    mcause_reg = maskoff & mcause_reg;

    switch(mcause_reg){
    	// Timer interrupt
        case INTERNAL_TIMER:
            timer_ISR();
            break;
        // External Interrupt
        case EXTERNAL_INTERRUPT:
            external_ISR();
            break;
        default:
        break;
    }

}

inline void external_ISR (void){
    
    // CMD interrupt
    if (INTERRUPT_PENDING & CMD_MASK){

    	//Do short work
        if(timerIgnore){
            timerIgnore = 0;
        }
        else{
            timerIgnore = 1;
        }

        //Clear interrupt
        CMD_interrupt_clear();
    }
    else if (INTERRUPT_PENDING & VID_MASK){
        graphics_ISR();
        VID_interrupt_clear();
    }
    else if (INTERRUPT_PENDING & CART_MASK){
       
        uint32_t jmp_point = CARTRIDGE_STATUS & (uint32_t) 0xFFFFFFFC;
        
        void (*jump)() =  jmp_point;

        jump();
        
        

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
   
    if(timerIgnore){
	    timer_callback();
	    global++;
	    controller_status = CONTROLLER_STATUS;
    }
 

}
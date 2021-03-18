#include "InterruptHandler.h"
#include "StatusRegisterUtility.h"
#include "InterruptCodes.h"
#include "SystemCallCodes.h"
#include "Syscalls.h"


int pressed = 1;
extern void graphics_callback(void);
void external_ISR();
void cmd_ISR(void);
__attribute__((always_inline)) inline void graphics_ISR(void){
    graphics_callback();
}


volatile int CartridgeInserted = 0;
TEntryFunction EntryFunction;


uint32_t c_syscall(uint32_t code, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5){
    uint32_t a0;
    switch(code){
        case CONTROLLERSTATUS:  a0 = _getControllerStatus();
                                break;

        case GRAPHICMODESET:    a0 = _graphicsMode(a1);
                                break;

        case REFRESHRATE:       a0 = _setRefreshRate(a1);
                                break;

        case PRINTTEXT:         a0 = _printText((char *) a1, a2);
                                break;

        case SETIMAGE:          a0 = _setImage(a1, a2, a3, a4, a5);
                                break;

        case MOVEIMAGE:         a0 = _moveImage(a1, a2, a3, a4);
                                break;

        case SETIMAGEPALETTE:   a0 = _setImagePalette( a1, a2);
                                break;

        case FILLPALETTE:       a0 = _setPalette( a1, (uint32_t *) a2);
                                break;

        case FILLIMAGE:         a0 = _imageFill( a1, (uint8_t *) a2, a3);
                                break;

        case CLEARTEXT:         a0 = _clearTextScreen();
                                break;

        case THREADMANAGER:     a0 = _getThreadManager();
                                break;
        case TIMERTICKS:        a0 = _getTimerTicks();
                                break;

        default:
                                a0 = 0;
        break;
    }
    // if(code == 42){
    //     *(volatile char *)(0x50000000 + 0xFE800) = 'B';
    // }
    // else{
    //     *(volatile char *)(0x50000000 + 0xFE800 + 1) = 'B';
    // }
    // _graphicsMode(0);
    // *(volatile char *)(0x50000000 + 0xFE800 + 1) = 'B';

    return a0;
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

        //Clear interrupt
        CMD_interrupt_clear();
    }
    else if (INTERRUPT_PENDING & VID_MASK){
        // graphics_ISR();
        VID_interrupt_clear();
    }
    else if (INTERRUPT_PENDING & CART_MASK){

    	// Get entry point
        // uint32_t jmp_point = CARTRIDGE_STATUS & (uint32_t) 0xFFFFFFFC;
        // Make a function pointer and jump
        EntryFunction = (TEntryFunction)(CARTRIDGE_STATUS & (uint32_t) 0xFFFFFFFC);
        CartridgeInserted = 1;
        // jump();
        CART_interrupt_clear();

    }

}


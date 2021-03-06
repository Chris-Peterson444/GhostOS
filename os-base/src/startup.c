#include <stdint.h>
#include "ChipsetRegisters.h"
#include "VideoControllerMap.h"
#include "StatusRegisterUtility.h"
#include "VideoControllerUtility.h"
#include "Threads.h"

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

volatile ThreadQueueManager TQManager;

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
    _threadInit(&TQManager);               // Init threading needs

    csr_write_mie(0x888);       // Enable all interrupt soruces

    csr_enable_interrupts();    // Global interrupt enable
    MTIMECMP_LOW = 100;
    MTIMECMP_HIGH = 0;
    external_interrupt_enable_all(); //Enable all external interrupts
    // graphics_refresh_rate();
    // graphics_text_mode();
}


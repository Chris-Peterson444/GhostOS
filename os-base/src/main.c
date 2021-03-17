#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VideoControllerMap.h"
#include "ChipsetRegisters.h"
#include "VideoControllerUtility.h"
#include "InterruptHandler.h"
#include "StatusRegisterUtility.h"
#include "Threads.h"
#include "Sleep.h"

extern volatile int CartridgeInserted;
extern TEntryFunction EntryFunction;

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile int time = 0;
void timer_callback(void);
volatile int gmodeCounter = 0;
void graphics_callback(void);
void old_wait_prog(void);

int x_pos = 12;
int last_global = 42;
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);
volatile char *SPRITE = (volatile char *)(0x500FF114);
volatile uint32_t *PALETTE = (volatile uint32_t *)(0x500FC000);
volatile uint32_t *BACK_CTRL = (volatile uint32_t *)(0x500FF100);

extern volatile ThreadQueueManager TQManager;


extern volatile uint32_t TimerTicks;

uint32_t Thread1(void *ptr){
    TCPUStackRef *ThreadPointers = (TCPUStackRef *)ptr;
    uint32_t LastTicks = TimerTicks;
    csr_enable_interrupts();
    while(1){
        if(LastTicks != TimerTicks){
            printf("T: %d\r",TimerTicks);
            fflush(stdout);
            // if((LastTicks / 100) != (TimerTicks / 100)){
            //     TCPUInterruptState PreviousState = CPUHALSuspendInterrupts();
            //     CPUHALContextSwitch(&ThreadPointers[1],ThreadPointers[0]);
            //     CPUHALResumeInterrupts(PreviousState);
            // }
            LastTicks = TimerTicks;
        }
    }
} 

uint32_t Thread2(void *ptr){
    TCPUStackRef *ThreadPointers = (TCPUStackRef *)ptr;
    uint32_t LastTicks = TimerTicks;
    uint32_t seconds = 0;

    ThreadContext* context = CPUHALGetSelfContext();
    // printf("Thread 1 context: %08X\n",context);
    // fflush(stdout);
    CPUHALThreadStatus(context, WAIT);

    while(1){

        printf("seconds: %d\r",seconds);
        fflush(stdout);

        _sleep(1000);
        seconds++;
    }
} 




int main() {

    // printf("%s\n", "Please insert cartridge");

    _clearText();
    uint32_t LastTicks = 0;
    uint32_t Thread1Stack[8192];
    TCPUStackRef ThreadPointers[2];
    ThreadPointers[1] = CPUHALContextInitialize((TCPUStackRef)(Thread1Stack+2048),Thread1,ThreadPointers);

    printf("Hello World\n");

    // for(int i = 0; i < 14; i++){
    //     printf("%2d: %08X @%p\n",13 - i, ThreadPointers[1][13-i],&ThreadPointers[1][13-i]);
    // }
    ThreadContext* thread1Context = CPUHALAddThread(&TQManager, ThreadPointers[1],Thread2, OS_THREAD);
    // printf("Thread 1 context: %08X\n",thread1Context);
    // fflush(stdout);
    // printf("thread1tp %08X\r",thread1Context);
    // fflush(stdout);


    while (1) {
        // if(CartridgeInserted){
        //     _clearText();
        //     EntryFunction();
        // }

        // if(global != last_global){
        //     // old_wait_prog();
        //     last_global = global;
        // }

                            if(LastTicks != TimerTicks){
                            printf("M: %d\r",TimerTicks);
                            fflush(stdout);
                            LastTicks = TimerTicks;

                            // _sleep(60000);
                            if (LastTicks = 1000){
                                CPUHALThreadStatus(thread1Context, READY);
                            }
                            
                        }



    }
    return 0;
}


inline void old_wait_prog(void){
    int cur_time = time / 10;
    VIDEO_MEMORY[0] = '0' + (((cur_time / 600)) % 10);
    VIDEO_MEMORY[1] = '0' + (( cur_time/ 60) % 10);
    VIDEO_MEMORY[3] =  '0' + ((cur_time % 60) / 10);
    VIDEO_MEMORY[4] = '0'+ (cur_time % 10);

    if(controller_status){
        VIDEO_MEMORY[x_pos] = ' ';
        if(controller_status & 0x1){
            if(x_pos & 0x3F){
                x_pos--;
            }
        }
        if(controller_status & 0x2){
            if(x_pos >= 0x40){
                x_pos -= 0x40;
            }
        }
        if(controller_status & 0x4){
            if(x_pos < 0x8C0){
                x_pos += 0x40;
            }
        }
        if(controller_status & 0x8){
            if((x_pos & 0x3F) != 0x3F){
                x_pos++;
            }
        }
        if(controller_status & 0x10){
            if(x_pos & 0x3F){
                x_pos--;
            }
        }
        if(controller_status & 0x20){
            if(x_pos >= 0x40){
                x_pos -= 0x40;
            }
        }
        if(controller_status & 0x40){
            if(x_pos < 0x8C0){
                x_pos += 0x40;
            }
        }
        if(controller_status & 0x80){
            if((x_pos & 0x3F) != 0x3F){
                x_pos++;
            }
        }
        VIDEO_MEMORY[x_pos] = 'X';
    }
}

void timer_callback(void){
    time += 1;
    // VIDEO_MEMORY[1] = 'B';
}

__attribute__((always_inline)) inline void graphics_callback(void){
    gmodeCounter += 1;
    uint32_t intermediate = GRAPHICS_MODE_CONTROL & (uint32_t) 0x1;
    if ( intermediate == (uint32_t) 0x0){
    int cur_count = gmodeCounter % 30;
    switch(cur_count){
        case 1:
            VIDEO_MEMORY[0 + 64*15] = 'I';
            VIDEO_MEMORY[1 + 64*15] = ' ';
            VIDEO_MEMORY[2 + 64*15] = ' ';
            VIDEO_MEMORY[3 + 64*15] = ' ';
            VIDEO_MEMORY[4 + 64*15] = ' ';
            VIDEO_MEMORY[5 + 64*15] = ' ';
            VIDEO_MEMORY[6 + 64*15] = ' ';
            VIDEO_MEMORY[7 + 64*15] = ' ';
            VIDEO_MEMORY[8 + 64*15] = ' ';
            break;
        case 6:
            VIDEO_MEMORY[0 + 64*15] = 'C';
            VIDEO_MEMORY[1 + 64*15] = 'H';
            VIDEO_MEMORY[2 + 64*15] = 'A';
            VIDEO_MEMORY[3 + 64*15] = 'N';
            VIDEO_MEMORY[4 + 64*15] = 'G';
            VIDEO_MEMORY[5 + 64*15] = 'E';
            VIDEO_MEMORY[6 + 64*15] = ' ';
            VIDEO_MEMORY[7 + 64*15] = ' ';
            VIDEO_MEMORY[8 + 64*15] = ' ';
            break;
        case 12:
            VIDEO_MEMORY[0 + 64*15] = 'W';
            VIDEO_MEMORY[1 + 64*15] = 'I';
            VIDEO_MEMORY[2 + 64*15] = 'T';
            VIDEO_MEMORY[3 + 64*15] = 'H';
            VIDEO_MEMORY[4 + 64*15] = ' ';
            VIDEO_MEMORY[5 + 64*15] = ' ';
            VIDEO_MEMORY[6 + 64*15] = ' ';
            VIDEO_MEMORY[7 + 64*15] = ' ';
            VIDEO_MEMORY[8 + 64*15] = ' ';
            break;
        case 18:
            VIDEO_MEMORY[0 + 64*15] = 'V';
            VIDEO_MEMORY[1 + 64*15] = 'I';
            VIDEO_MEMORY[2 + 64*15] = 'D';
            VIDEO_MEMORY[3 + 64*15] = 'E';
            VIDEO_MEMORY[4 + 64*15] = 'O';
            VIDEO_MEMORY[5 + 64*15] = ' ';
            VIDEO_MEMORY[6 + 64*15] = ' ';
            VIDEO_MEMORY[7 + 64*15] = ' ';
            VIDEO_MEMORY[8 + 64*15] = ' ';
            break;
        case 23:
            VIDEO_MEMORY[0 + 64*15] = 'I';
            VIDEO_MEMORY[1 + 64*15] = 'N';
            VIDEO_MEMORY[2 + 64*15] = 'T';
            VIDEO_MEMORY[3 + 64*15] = 'E';
            VIDEO_MEMORY[4 + 64*15] = 'R';
            VIDEO_MEMORY[5 + 64*15] = 'R';
            VIDEO_MEMORY[6 + 64*15] = 'U';
            VIDEO_MEMORY[7 + 64*15] = 'P';
            VIDEO_MEMORY[8 + 64*15] = 'T';
            break;
        default:
            break;

    }
    }
    

}
#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile int time = 0;
void timer_callback(void);
volatile int gmodeCounter = 0;
void graphics_callback(void);

#define GRPAHICS_MODE (*((volatile uint32_t *)0x500FF414))

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);
int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;

    VIDEO_MEMORY[0] = '0';
    VIDEO_MEMORY[1] = '0';
    VIDEO_MEMORY[2] = ':';
    VIDEO_MEMORY[3] = '0';
    VIDEO_MEMORY[4] = '0';

    char string_1[] = "Please see above timer for timer functionality";
    char string_2[] = "Use controls to move \'x\'";
    char string_3[] = "Press CMD to star and pause timer and controls";
    
    // VIDEO_MEMORY[0 + 64*2] = string_1; 
    // VIDEO_MEMORY[0 + 64*2] = 'H';
    // VIDEO_MEMORY[1 + 64*2] = 'e';
    // VIDEO_MEMORY[2 + 64*2] = 'l';
    // VIDEO_MEMORY[3 + 64*2] = 'l';
    // VIDEO_MEMORY[4 + 64*2] = 'o';
    // VIDEO_MEMORY[5 + 64*2] = ' ';
    // VIDEO_MEMORY[6 + 64*2] = 'W';
    // VIDEO_MEMORY[7 + 64*2] = 'o';
    // VIDEO_MEMORY[8 + 64*2] = 'r';
    // VIDEO_MEMORY[9 + 64*2] = 'l';
    // VIDEO_MEMORY[10 + 64*2] = 'd';
    // VIDEO_MEMORY[11 + 64*2] = '!';
    // VIDEO_MEMORY[12 + 64*2] = 'X';
    


    while (1) {
        int c = a + b + global;
        if(global != last_global){
            int cur_time = time / 10;
            VIDEO_MEMORY[0] = '0' + (((cur_time / 600)) % 10);
            VIDEO_MEMORY[1] = '0' + (( cur_time/ 60) % 10);
            VIDEO_MEMORY[3] =  '0' + ((cur_time % 60) / 10);
            VIDEO_MEMORY[4] = '0'+ (cur_time % 10);
            for(int i = 0; i <= (sizeof(string_1)/sizeof(*string_1)); i++){
            VIDEO_MEMORY[i + 64*2] = string_1[i];
            }

            for(int i = 0; i <= (sizeof(string_2)/sizeof(*string_2)); i++){
            VIDEO_MEMORY[i + 64*4] = string_2[i];
            }

            for(int i = 0; i <= (sizeof(string_3)/sizeof(*string_3)); i++){
            VIDEO_MEMORY[i + 64*7] = string_3[i];
            }

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
            last_global = global;
        }
    }
    return 0;
}

void timer_callback(void){
    time += 1;
    // VIDEO_MEMORY[1] = 'B';
}

__attribute__((always_inline)) inline void graphics_callback(void){
    gmodeCounter += 1;
    uint32_t intermediate = GRPAHICS_MODE & (uint32_t) 0x1;
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
            VIDEO_MEMORY[6 + 63*15] = ' ';
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
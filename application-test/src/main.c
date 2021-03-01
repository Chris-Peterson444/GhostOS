#include <stdint.h>
#include "GraphicUtil.h"
#include "SystemUtil.h"

volatile int global = 42;
volatile uint32_t controller_status = 0; 
volatile uint32_t status = 0;
volatile int time = 0;
void timer_callback(void);
volatile int gmodeCounter = 0;
void graphics_callback(void);

// uint32_t SystemCall(uint32_t param);
// uint32_t SystemCall(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6);


// volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);
int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;

    char buffer[TEXT_BUFF_SIZE];

    char string_1[] = "Changed into application";
    for(int i = 0; i < (sizeof(string_1)/sizeof(*string_1)); i++){
        buffer[i] = string_1[i];
    }
    char string_2[] = "w,a,s,d,u,j, and k will change screen color";
    for(int i = 0; i < (sizeof(string_2)/sizeof(*string_2)); i++){
        buffer[i + 64*2] = string_2[i];
    }
    char string_3[] = "Press i to come back to this screen";
    for(int i = 0; i < (sizeof(string_3)/sizeof(*string_3)); i++){
        buffer[i + 64*4] = string_3[i];
    }
    char string_4[] = "a - red";
    char string_5[] = "w - blue";
    char string_6[] = "d - green";
    char string_7[] = "x - pink";
    char string_8[] = "u - ";
    char string_9[] = "j - ";
    char string_10[] = "k - ";
    char string_11[] = "i - instructions (here)";

    for(int i = 0; i <  (sizeof(string_4)/sizeof(*string_4)); i++){
        buffer[i + 64*10] = string_4[i];
    }
    for(int i = 0; i < (sizeof(string_5)/sizeof(*string_5)); i++){
        buffer[i + 64*12] = string_5[i];
    }
    for(int i = 0; i < (sizeof(string_6)/sizeof(*string_6)); i++){
        buffer[i + 64*14] = string_6[i];
    }
    for(int i = 0; i < (sizeof(string_7)/sizeof(*string_7)); i++){
        buffer[i + 64*16] = string_7[i];
    }
    for(int i = 0; i < (sizeof(string_8)/sizeof(*string_8)); i++){
        buffer[i + 64*18] = string_8[i];
    }

    printText(buffer, TEXT_BUFF_SIZE);


    //Create some images and palettes to send to devices
    uint32_t palette_1[256];
    uint32_t palette_2[256];
    uint32_t palette_3[256];
    uint8_t image_1[IMAGE_BUFF_SIZE];
    uint8_t image_2[IMAGE_BUFF_SIZE];
    uint8_t image_3[IMAGE_BUFF_SIZE];
    uint8_t image_4[IMAGE_BUFF_SIZE];
    uint8_t image_5[IMAGE_BUFF_SIZE];
    uint8_t image_6[IMAGE_BUFF_SIZE];
    uint8_t image_7[IMAGE_BUFF_SIZE];

    //Half of palette 1 is red
    for(int i = 0; i < 128; i++){
        palette_1[i] = 0xFF0000FF;
    }
    //Other half is blue
    for(int i = 128; i < 256; i++){
        palette_1[i] = 0x0000FFFF;
    }
    //Half of palette 2 is green
    for(int i = 0; i < 128; i++){
        palette_2[i] = 0x00FF00FF;
    }
    //Other half is pink
    for(int i = 128; i < 256; i++){
        palette_2[i] = 0xFFFF00FF;
    }
    //Half of palette 3 is white
    for(int i = 0; i < 128; i++){
        palette_2[i] = 0xFFFFFFFF;
    }
    //Other half is black
    for(int i = 128; i < 256; i++){
        palette_2[i] = 0x000000FF;
    }

    // Syscalls to set palette
    setPalette(0,palette_1);
    setPalette(1,palette_2);
    setPalette(2,palette_3);


    // Image 1 - 3 index first color of palette
    for(int i = 0; i < IMAGE_BUFF_SIZE; i++){
        image_1[i] = 0;
        image_2[i] = 0;
        image_3[i] = 0;
    }
    // Image 4 - 6 index second color of palette
    for(int i = 0; i < IMAGE_BUFF_SIZE; i++){
        image_4[i] = 128;
        image_5[i] = 128;
        image_6[i] = 128;
    }
    // Image 7 is half and half
    for(int i = 0; i < IMAGE_BUFF_SIZE/2; i++){
        image_7[i] = 0;
    }
        for(int i = IMAGE_BUFF_SIZE/2; i < IMAGE_BUFF_SIZE; i++){
        image_7[i] = 128;
    }


    graphicsMode(1);
    //             //Syscall to move last image to bottom
    // setImage(0, FULL_X, FULL_Y, BOTTOM, 0);

    //   //Set current image            last_img = 0;
    // //Syscall to set the image
    // imageFill(0, image_1, IMAGE_BUFF_SIZE);
    //             //Syscall to move the image into place
    // setImage(0, FULL_X, FULL_Y, TOP, 0);

    // uint8_t status_modes[8] = {128, 64, 32, 16, 4, 2, 1, 0};



    // graphicsMode(1);
    // for(int i = 0; i < 255; i++){
    //     PALETTE[i] = 0xFF0000FF;
    // }
    // PALETTE[128] = 0x00FF00FF;
    // // *BACK_CTRL = *BACK_CTRL | 0b11111111110100100000010010000000;
    // uint8_t data[IMAGE_BUFF_SIZE] = {0};
    // for(int i = 0; i < IMAGE_BUFF_SIZE; i++){
    //     data[i] = 128;
    // }
    // _fillImage(0,data,IMAGE_BUFF_SIZE);
    // _imageSet(0,512,288,4,0);

    while (1) {
        int c = a + b + global;
        int last_img = 0;

        status = getControllerStatus();

        // while(1){
        //     status = getControllerStatus();
        //     char digit = status;
        //     printText(&digit,1);
        // }
                 // Syscall to set graphics mode 
    


        // if(status != 0){
        //     controller_status = status;
        // }
        // switch(controller_status){
        //      0:
        //         graphicsMode(0);
        //         break;
        //     // red
        //     case 128:
        //         //Syscall to set graphics mode 
        //         graphicsMode(1);
        //         //Syscall to move last image to bottom
        //         setImage(last_img, FULL_X, FULL_Y, BOTTOM, 0);

        //         //Set current image
        //         last_img = 0;
        //         //Syscall to set the image
        //         imageFill(0, image_1, IMAGE_BUFF_SIZE);
        //         //Syscall to move the image into place
        //         setImage(0, FULL_X, FULL_Y, TOP, 0);
        //         break;
        //     case 64:
        //         //Syscall to set graphics mode 
        //         graphicsMode(1);
        //         //Syscall to move last image to bottom
        //         setImage(last_img, FULL_X, FULL_Y, BOTTOM, 0);

        //         //Set current image
        //         last_img = 1;
        //         //Syscall to set the image
        //         imageFill(1, image_2, IMAGE_BUFF_SIZE);
        //         //Syscall to move the image into place
        //         setImage(1, FULL_X, FULL_Y, TOP, 0);
        //         break;
        //     case 32:
        //         //Syscall to set graphics mode 
        //         graphicsMode(1);
        //         //Syscall to move last image to bottom
        //         setImage(last_img, FULL_X, FULL_Y, BOTTOM, 0);

        //         //Set current image
        //         last_img = 2;
        //         //Syscall to set the image
        //         imageFill(2, image_3, IMAGE_BUFF_SIZE);
        //         //Syscall to move the image into place
        //         setImage(2, FULL_X, FULL_Y, TOP, 0);
        //         break;
        //     case 16:
        //         //Syscall to set graphics mode 
        //         graphicsMode(1);
        //         //Syscall to move last image to bottom
        //         setImage(last_img, FULL_X, FULL_Y, BOTTOM, 0);

        //         //Set current image
        //         last_img = 3;
        //         //Syscall to set the image
        //         imageFill(3, image_4, IMAGE_BUFF_SIZE);
        //         //Syscall to move the image into place
        //         setImage(3, FULL_X, FULL_Y, TOP, 0);
        //         break;
        //     default:
        //         //Syscall to set graphics mode 
        //         graphicsMode(1);
        //         //Syscall to move last image to bottom
        //         setImage(last_img, FULL_X, FULL_Y, BOTTOM, 0);

        //         //Set current image
        //         last_img = 3;
        //         //Syscall to set the image
        //         imageFill(3, image_4, IMAGE_BUFF_SIZE);
        //         //Syscall to move the image into place
        //         setImage(3, FULL_X, FULL_Y, TOP, 0);
        //         break;

        // }

        }
    return 0;
}

void timer_callback(void){
    time += 1;
    // VIDEO_MEMORY[1] = 'B';
}

// __attribute__((always_inline)) inline void graphics_callback(void){
//     gmodeCounter += 1;
//     int cur_count = gmodeCounter % 30;
//     switch(cur_count){
//         case 1:
//             VIDEO_MEMORY[0 + 64*15] = 'A';
//             VIDEO_MEMORY[1 + 64*15] = 'P';
//             VIDEO_MEMORY[2 + 64*15] = 'P';
//             VIDEO_MEMORY[3 + 64*15] = ' ';
//             VIDEO_MEMORY[4 + 64*15] = 'N';
//             VIDEO_MEMORY[5 + 64*15] = 'O';
//             VIDEO_MEMORY[6 + 64*15] = 'W';
//             VIDEO_MEMORY[7 + 64*15] = ' ';
//             VIDEO_MEMORY[8 + 64*15] = ' ';
//             break;
//         case 6:
//             VIDEO_MEMORY[0 + 64*15] = 'I';
//             VIDEO_MEMORY[1 + 64*15] = 'S';
//             VIDEO_MEMORY[2 + 64*15] = ' ';
//             VIDEO_MEMORY[3 + 64*15] = ' ';
//             VIDEO_MEMORY[4 + 64*15] = ' ';
//             VIDEO_MEMORY[5 + 64*15] = ' ';
//             VIDEO_MEMORY[6 + 64*15] = ' ';
//             VIDEO_MEMORY[7 + 64*15] = ' ';
//             VIDEO_MEMORY[8 + 64*15] = ' ';
//             break;
//         case 12:
//             VIDEO_MEMORY[0 + 64*15] = 'L';
//             VIDEO_MEMORY[1 + 64*15] = 'O';
//             VIDEO_MEMORY[2 + 64*15] = 'A';
//             VIDEO_MEMORY[3 + 64*15] = 'D';
//             VIDEO_MEMORY[4 + 64*15] = 'E';
//             VIDEO_MEMORY[5 + 64*15] = 'D';
//             VIDEO_MEMORY[6 + 64*15] = ' ';
//             VIDEO_MEMORY[7 + 64*15] = ' ';
//             VIDEO_MEMORY[8 + 64*15] = ' ';
//             break;
//         case 18:
//             VIDEO_MEMORY[0 + 64*15] = 'H';
//             VIDEO_MEMORY[1 + 64*15] = 'E';
//             VIDEO_MEMORY[2 + 64*15] = 'L';
//             VIDEO_MEMORY[3 + 64*15] = 'L';
//             VIDEO_MEMORY[4 + 64*15] = 'O';
//             VIDEO_MEMORY[5 + 64*15] = ' ';
//             VIDEO_MEMORY[6 + 64*15] = ' ';
//             VIDEO_MEMORY[7 + 64*15] = ' ';
//             VIDEO_MEMORY[8 + 64*15] = ' ';
//             break;
//         case 23:
//             VIDEO_MEMORY[0 + 64*15] = 'W';
//             VIDEO_MEMORY[1 + 64*15] = 'O';
//             VIDEO_MEMORY[2 + 64*15] = 'R';
//             VIDEO_MEMORY[3 + 64*15] = 'L';
//             VIDEO_MEMORY[4 + 64*15] = 'D';
//             VIDEO_MEMORY[5 + 64*15] = ' ';
//             VIDEO_MEMORY[6 + 64*15] = ' ';
//             VIDEO_MEMORY[7 + 64*15] = ' ';
//             VIDEO_MEMORY[8 + 64*15] = ' ';
//             break;
//         default:
//             break;

//     }

// }
#ifndef VIDEOCONTROLLERMAP_H
#define VIDEOCONTROLLERMAP_H

/*  
*  *******************
*  *     GENERAL     *
*  *******************
*/



#define BACKGROUND_DATA                (*((volatile uint32_t *)0x50000000))
#define LARGE_SPRITE_DATA              (*((volatile uint32_t *)0x500B4000))
#define SMALL_SPRITE_DATA              (*((volatile uint32_t *)0x500F4000))

#define BACKGROUND_PALETTES            (*((volatile uint32_t *)0x500FC000))
#define SPRITE_PALETTES                (*((volatile uint32_t *)0x500FD000))

#define FONT_DATA                      (*((volatile uint32_t *)0x500FE000))
#define TEXT_DATA                      (*((volatile uint32_t *)0x500FE800))

#define BACKGROUND_CONTROL             (*((volatile uint32_t *)0x500FF100))
#define LARGE_SPRITE_CONTROL           (*((volatile uint32_t *)0x500FF114))
#define SMALL_SPRITE_CONTROL           (*((volatile uint32_t *)0x500FF214))
#define GRAPHICS_MODE_CONTROL          (*((volatile uint32_t *)0x500FF414))

#define BACKGROUND_DATA_IMG_0          (*((volatile uint32_t *)0x50000000))
#define BACKGROUND_DATA_IMG_1          (*((volatile uint32_t *)0x50024000))
#define BACKGROUND_DATA_IMG_2          (*((volatile uint32_t *)0x50048000))
#define BACKGROUND_DATA_IMG_3          (*((volatile uint32_t *)0x5006C000))
#define BACKGROUND_DATA_IMG_4          (*((volatile uint32_t *)0x50090000))

#define BACKGROUND_CTRL_0              (*((volatile uint32_t *)0x500FF100))
#define BACKGROUND_CTRL_1              (*((volatile uint32_t *)0x500FF104))
#define BACKGROUND_CTRL_2              (*((volatile uint32_t *)0x500FF108))
#define BACKGROUND_CTRL_3              (*((volatile uint32_t *)0x500FF10C))
#define BACKGROUND_CTRL_4              (*((volatile uint32_t *)0x500FF110))


/*  
*  *******************
*  *      TEXT       *
*  *******************
*/

#define ROWS_PER_SCREEN               36
#define CHARS_PER_ROW                 64
#define SCREEN_BUFF_SIZE              2304   // 64 x 36


/*  
*  *******************
*  *      IMAGE      *
*  *******************
*/

#define IMAGE_BUFF_SIZE              147456  // 512 x 288


/*  
*  *******************
*  *     SPRITES     *
*  *******************
*/



/* There are 64 large sprites to access. Each is 4KiB (0x1000) in size.
   Instead of making a #define for each, the user should just add 0x1000 * n
   where n is the sprite number, up to n = 63
*/
#define LARGE_SPRITE_DATA_0            (*((volatile uint32_t *)0x500B4000))
// #define LARGE_SPRITE_DATA_1         (*((volatile uint32_t *)0x500B5000))

#define LARGE_SPRITE_CONTROL_0         (*((volatile uint32_t *)0x500FF114))
// #define LARGE_SPRITE_CONTROL_1      (*((volatile uint32_t *)0x500FF118))



/* There are 128 small sprites to access. Each is 256B (0x100) in size.
   Instead of making a #define for each, the user should just add 0x1000 * n
   where n is the sprite number, up to n = 63
*/
#define SMALL_SPRITE_DATA_0            (*((volatile uint32_t *)0x500F4000))
// #define SMALL_SPRITE_DATA_1         (*((volatile uint32_t *)0x500F4100))

#define SMALL_SPRITE_CONTROL_0         (*((volatile uint32_t *)0x500FF214))
// #define SMALL_SPRITE_CONTROL_1      (*((volatile uint32_t *)0x500FF218))


/*  
*  *******************
*  *     PALETTE     *
*  *******************
*/

#define PALETTE_SIZE                   256

#define BACKGROUND_PALETTE_0           (*((volatile uint32_t *)0x500FC000))
#define BACKGROUND_PALETTE_1           (*((volatile uint32_t *)0x500FC400))
#define BACKGROUND_PALETTE_2           (*((volatile uint32_t *)0x500FC800))
#define BACKGROUND_PALETTE_3           (*((volatile uint32_t *)0x500FCC00))

#define SPRITE_PALETTE_0               (*((volatile uint32_t *)0x500FD000))
#define SPRITE_PALETTE_1               (*((volatile uint32_t *)0x500FD400))
#define SPRITE_PALETTE_2               (*((volatile uint32_t *)0x500FD800))
#define SPRITE_PALETTE_3               (*((volatile uint32_t *)0x500FDC00))





#endif
#ifndef CHIPSETREGISTER_H
#define CHIPSETREGISTER_H


#define INTERRUPT_ENABLE             (*((volatile uint32_t *)0x40000000))
#define INTERRUPT_PENDING            (*((volatile uint32_t *)0x40000004))

#define MTIME_LOW                    (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH                   (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW                 (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH                (*((volatile uint32_t *)0x40000014))

#define CONTROLLER_STATUS            (*((volatile uint32_t *)0x40000018))

#define CARTRIDGE_STATUS             (*((volatile uint32_t *)0x4000001C))

#define DMA_CHANNEL_1_SOURCE         (*((volatile uint32_t *)0x40000020))
#define DMA_CHANNEL_1_DEST           (*((volatile uint32_t *)0x40000024))
#define DMA_CHANNEL_1_CMD            (*((volatile uint32_t *)0x40000028))
#define DMA_CHANNEL_1_STATUS         (*((volatile uint32_t *)0x4000002C))

#define DMA_CHANNEL_2_SOURCE         (*((volatile uint32_t *)0x40000030))
#define DMA_CHANNEL_2_DEST           (*((volatile uint32_t *)0x40000034))
#define DMA_CHANNEL_2_CMD            (*((volatile uint32_t *)0x40000038))
#define DMA_CHANNEL_2_STATUS         (*((volatile uint32_t *)0x4000003C))

#define RAM_BASE                     (*((volatile uint32_t *)0x70000000))



#define MACHINE_CLOCK_REG            (*((volatile uint32_t *)0x40000040))






#endif
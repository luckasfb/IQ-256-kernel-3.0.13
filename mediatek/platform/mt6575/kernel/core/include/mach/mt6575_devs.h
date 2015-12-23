
#ifndef __MT6575_DEVS_H__
#define __MT6575_DEVS_H__

#include <board-custom.h>
#include <mach/board.h>

#define CFG_DEV_UART1
#define CFG_DEV_UART2
// LuckAs add
//#ifndef CONFIG_MT6575_FPGA
// #define CFG_DEV_UART3
// #define CFG_DEV_UART4
//#endif
// orig
#define CFG_DEV_UART3
#define CFG_DEV_UART4
// LuckAs and


#define MT6575_UART_SIZE 0x100


extern int mt6575_board_init(void);

#endif  /* !__MT6575_DEVS_H__ */


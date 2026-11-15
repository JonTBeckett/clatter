#include <stdint.h>

extern uint32_t _estack;

void Reset_Handler(void);
int main(void);

/* Minimal Vector Table placed at 0x10000000 */
__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {
    (uint32_t)&_estack,        /* Initial Stack Pointer */
    (uint32_t)Reset_Handler    /* Reset Handler */
};

/* MPS2-AN521 CMSDK UART0 Registers */
#define UART0_BASE  0x40200000UL
#define UART0_DR    (*(volatile uint32_t *)(UART0_BASE + 0x00))
#define UART0_STATE (*(volatile uint32_t *)(UART0_BASE + 0x04))
#define UART0_CTRL  (*(volatile uint32_t *)(UART0_BASE + 0x08))

static void uart_init(void) {
    UART0_CTRL = 0x01; /* Enable TX */
}

static void uart_puts(const char *s) {
    while (*s) {
        while (UART0_STATE & 0x01) { /* Wait while TX buffer is full */ }
        UART0_DR = (uint32_t)(*s++);
    }
}

void Reset_Handler(void) {
    main();
    while (1) {
        __asm__("wfi");
    }
}

int main(void) {
    uart_init();
    uart_puts("Hello from Cortex-M33!\n");

    while (1) {
        __asm__("wfi");
    }
    return 0;
}

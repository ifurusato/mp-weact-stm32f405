/*
    GNU linker script for STM32H562xI (WEACT_H562RGT6)
*/

/* Specify the memory areas */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K   /* 1MB Flash */
    RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 640K    /* 640KB RAM */
}

/* produce a link error if there is not this amount of RAM for these sections */
_minimum_stack_size = 2K;
_minimum_heap_size = 16K;

/* Define the stack.  The stack is full descending so begins just above last byte
   of RAM.  Note that EABI requires the stack to be 8-byte aligned for a call. */
_estack = ORIGIN(RAM) + LENGTH(RAM) - _estack_reserve;
_sstack = _estack - 16K; /* tunable */

/* RAM extents for the garbage collector */
_ram_start = ORIGIN(RAM);
_ram_end = ORIGIN(RAM) + LENGTH(RAM);
_heap_start = _ebss; /* heap starts just after statically allocated memory */
_heap_end = _sstack;

/* --------------------------------------------------------------------------
 * MicroPython flash storage and RAM cache symbols (required by flashbdev.c)
 * Adjust storage size/offsets as needed for your application!
 * -------------------------------------------------------------------------- */

/* Place internal flash filesystem at the last 128 KB of flash.
   Adjust this if you want a larger or smaller filesystem.
   1MB = 0x100000, so start at 0x080E0000 for 128 KB at end. */
_micropy_hw_internal_flash_storage_start = ORIGIN(FLASH) + 0xE0000;
_micropy_hw_internal_flash_storage_end   = ORIGIN(FLASH) + LENGTH(FLASH);

/* Place RAM cache at the end of RAM (optional, but required by MicroPython STM32 port) */
_micropy_hw_internal_flash_storage_ram_cache_start = ORIGIN(RAM) + 0x9C000; /* last 16 KB of 640 KB */
_micropy_hw_internal_flash_storage_ram_cache_end   = ORIGIN(RAM) + LENGTH(RAM);

PROVIDE(_micropy_hw_internal_flash_storage_start = _micropy_hw_internal_flash_storage_start);
PROVIDE(_micropy_hw_internal_flash_storage_end = _micropy_hw_internal_flash_storage_end);
PROVIDE(_micropy_hw_internal_flash_storage_ram_cache_start = _micropy_hw_internal_flash_storage_ram_cache_start);
PROVIDE(_micropy_hw_internal_flash_storage_ram_cache_end = _micropy_hw_internal_flash_storage_ram_cache_end);

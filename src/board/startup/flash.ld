MEMORY
{
    VECTORS             (rx):   ORIGIN = 0x00000000,    LENGTH = 0xC0
    FLASH_CONFIGURATION (rx):   ORIGIN = 0x00000400,    LENGTH = 0x00000410
    FLASH               (rx):   ORIGIN = 0x00000410,    LENGTH = 128K - 0x00000410
    SRAM                (rwx):  ORIGIN = 0x1FFFF000,    LENGTH = 16K
}

ENTRY(_reset_handler)
_estack = 0x20002FF8;

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > VECTORS

    .text :
    {
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /DISCARD/ :
    {
        *(.ARM.exidx*)
    }

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .preinit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } > FLASH

    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } > FLASH

    .finit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__finit_array_start = .);
        KEEP(*SORT(.finit_array.*))
        KEEP(*(.finit_array*))
        PROVIDE_HIDDEN (__finit_array_end = .);
        . = ALIGN(4);
    } > FLASH

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT > FLASH

    . = ALIGN(4);

    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
        _end = .;
    } > SRAM
}

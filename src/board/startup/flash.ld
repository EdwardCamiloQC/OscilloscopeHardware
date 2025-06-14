ENTRY(_reset_handler)

/*========================================*/
/* Definición De Memoria */
/*========================================*/
MEMORY
{
    VECTORS             (rx):   ORIGIN = 0x00000000,    LENGTH = 0xC0
    FLASH_CONFIGURATION (rx):   ORIGIN = 0x00000400,    LENGTH = 0x00000410
    FLASH               (rx):   ORIGIN = 0x00000410,    LENGTH = 128K - 0x00000410
    SRAM                (rwx):  ORIGIN = 0x1FFFF000,    LENGTH = 16K
}

/*========================================*/
/* Tamaños De Heap Y Stack */
/*========================================*/
_Min_Heap_Size = 0x1000; /* 4KB */
_Min_Stack_Size = 0x1000; /* 4KB */

/*========================================*/
/* Símbolos Globales */
/*========================================*/
_sheap = ORIGIN(SRAM);
_eheap = _sheap + _Min_Heap_Size;
_sstack = _estack - _Min_Stack_Size;
_estack = ORIGIN(SRAM) + LENGTH(SRAM);   /*0x20002FF8*/

/*========================================*/
/* Secciones */
/*========================================*/
SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > VECTORS

    /* stubs interworking (ARM -> Thumb; casi vacio en cortex M) */
    .glue_7 :
    {
        . = ALIGN(4);
        KEEP(*(.glue_7))
        . = ALIGN(4);
    } > FLASH

    /* stubs interworking (Thumb -> ARM;  casi vacio en cortex M) */
    .glue_7t :
    {
        . = ALIGN(4);
        KEEP(*(.glue_7t))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    /* Funciones que se ejecutan antes del _init */
    .preinit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } > FLASH

    /* Código del CRT que se ejecuta justo antes de constructores */
    .init :
    {
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
    } > FLASH

    /* constructores de C++ (objetos globales/estáticos) */
    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } > FLASH

    /* Destructores de C++ (objectos globales/estáticos) */
    .finit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__finit_array_start = .);
        KEEP(*SORT(.finit_array.*))
        KEEP(*(.finit_array*))
        PROVIDE_HIDDEN (__finit_array_end = .);
        . = ALIGN(4);
    } > FLASH

    /* Código del CRT que se ejecuta despues de destructores */
    .fini :
    {
        . = ALIGN(4);
        KEEP(*(.fini))
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
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        _end = .;
    } > SRAM

    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE(end = .);
        PROVIDE(_end = .);
        . = . + _Min_Heap_Size;
        . = ALIGN(8);
    } > SRAM

    /DISCARD/ :
    {
        *(.ARM.exidx*)
    }
}

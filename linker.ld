MEMORY
{
    RAM (rwx)  : ORIGIN = 0x00000000, LENGTH = 64K
    MMIO (rw)  : ORIGIN = 0x02000000, LENGTH = 64K
}

SECTIONS
{
    .text : {
        *(.text.start)
        *(.text*)
    } > RAM

    .data : {
        *(.data*)
    } > RAM

    .bss : {
        *(.bss*)
        *(COMMON)
    } > RAM

    _stack_top = ORIGIN(RAM) + LENGTH(RAM);

    .mmio (NOLOAD) : {
        mmio = .;
    } > MMIO
}

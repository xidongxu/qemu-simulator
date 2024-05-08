void semihosting_putc(int c) {
	asm volatile (
		"mov	r1, %0\n\t"
		"mov	r0, #3\n\t"
		"bkpt	0xab\n"
		:
		: "r" (&c)
		: "r0", "r1"
	);
}

void semihosting_shutdown(void) {
	asm volatile (
		"mov	r0, 0x18\n"
		"bkpt	0xab\n"
		:
		:
		: "r0"
	);
}

__attribute__((weak)) int putchar(int c) {
	if (c == '\n') {
		semihosting_putc('\r');
    }
	semihosting_putc(c);
	return c;
}

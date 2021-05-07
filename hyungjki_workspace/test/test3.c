#include <stdio.h>

int main(void)
{
	printf("123456789 \b\b\b\b\b\b\n"); // 123456789\n
	printf("123456789 \b\b\b\b\b\b\n\b"); // 123456789\n
	printf("123456789 \b\b \b\b\b\b\n\b"); // 12345678\n
	printf("123456789\b\b\b\b\b\b\n\b"); // 123456789\n
	printf("123456789 \b\b \b\b \b\b\n\b"); // 1234567\n
	printf("123456789 \b\b \b\b               \b\b\n\b"); // 1234567\n
	printf("123456789\b\b\b\b\b\b\b\n"); //123456789
	printf("123456789\b\b  \b\b\n"); //1234567
	printf("123456789\b\b\n"); //123456789

}
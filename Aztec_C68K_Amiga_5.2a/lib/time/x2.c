#define TIME_MCH2AZTEC -2082844800L
unsigned long x = 0x9c000000, result;
main()
{
	result = x + TIME_MCH2AZTEC;
	printf("%ul\n", result);
}

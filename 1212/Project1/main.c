#include <stdio.h>
#include <Windows.h>



int main()
{
	while (1)
	{
		printf("\x1B[0;0H ~(- _ - )~");
		Sleep(300);
		printf("\x1B[0;0H ~( - _ -)~");
		Sleep(300);
	}
	return 0;
}
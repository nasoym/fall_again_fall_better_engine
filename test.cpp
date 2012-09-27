#include <stdio.h>
#include <string>
#include <windows.h>



void	shutdown(){
	printf("shutdown \n");
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
//int main(int argc, char *argv[]) {

	printf("TESTING:\n");
	Sleep(1000);
	system("shutdown -r");
	return 0;
}




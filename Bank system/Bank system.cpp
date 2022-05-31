#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include "Parent.h"
#include "Screen.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESCAPE 27
#define KEY_ENTER 13

#pragma comment(lib, "user32")


int main()
{
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	//cout << "                                                 **" << endl;
	//cout << "                                                 **" << endl;
	//cout << "                                                 **" << endl;
	//cout << "                                                 **" << endl;
	//cout << "                                                 **" << endl;
	//cout << "**                ****                  **       **         ********                **********              **********                   ****                ****                ********        " << endl;
	//cout << " **              **  **                **        **        **      **             **                       **        **                 **  **              **  **              **      **       " << endl;
	//cout << "  **            **    **              **         **       **        **           **                       **          **               **    **            **    **            **        **      " << endl;
	//cout << "   **          **      **            **          **      *************          **                       **            **             **      **          **      **           *************     " << endl;
	//cout << "    **        **        **          **           **      **                    **                       **              **           **        **        **        **          **                " << endl;
	//cout << "     **      **          **        **            **      **                    **                       **              **          **          **      **          **         **                " << endl;
	//cout << "      **    **            **      **             **       **                    **                       **            **          **            **    **            **         **               " << endl;
	//cout << "       **  **               **   **              **        **      **            **                       **          **          **              **  **              **         **      **      " << endl;
	//cout << "        ****                 ****                **         ********               ***********             ************          **                ****                **         ********       " << endl;

	//cout << endl << endl << endl << "                                                                                 Press Enter To Start The programe " << endl;
	//cin.get();
	//system("cls");
	//cout << "loading...." << endl;
	////initializing
	//bool initialized = false;
	//if (!initialized) {
	//	string files[3] = { "clientId.txt" ,"employeeLastId.txt" , "adminLastId.txt" };
	//	initialized = true;
	//	for (int i = 0; i < 3; i++) {
	//	fstream file(files[i], ios::out);
	//	file << 1;
	//	file.close();
	//	}
	//}
	//Sleep(2000);
	//system("cls");

	Screen::menuSystem();
}
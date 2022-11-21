#include "View.h"

void View::setFinish(const bool& finish)
{
	this->finish = finish;
}
bool View::getFinish()
{
	return finish;
}
void View::Menu() {
	cout << "Enter 1: To choice player 1.";
	cout << "\nEnter 2: To choice player 2.";
	cout << "\nEnter 3: To play off." ;
	cout << "\nEnter 4: To import file.";
	cout << "\nEnter 5: To create account.";
	cout << "\nEnter 6: To show account list.";
	cout << "\nEnter 7: To exit.";
}
void View::setTableSize(int x) {
    this->tableSize = x;
}
int View::getTableSize() {
    return tableSize;
}

void View::showTableOnl() {
	system("cls");
	for (int i = 0; i < tableSize * 4 + 1; i++)
	{
		cout << '-';
	}
	cout << endl;
	for (int i = 0; i < tableSize; i++)
	{

		for (int j = 0; j < tableSize; j++)
		{
			cout << '|' << ' ' << ' ' << ' ';
		}
		cout << '|' << endl;
		for (int i = 0; i < tableSize * 4 + 1; i++)
		{
			cout << '-';
		}
		cout << endl;
	}
}

void View::showTable() {
    cout << "Enter table size: "; cin >> this->tableSize;
	system("cls");
	for (int i = 0; i < tableSize * 4 + 1; i++)
	{
		cout << '-';
	}
	cout << endl;
	for (int i = 0; i < tableSize; i++)
	{
		
		for (int j = 0; j < tableSize; j++)
		{
			cout << '|' << ' ' << ' ' << ' ';
		}
		cout << '|' << endl;
		for (int i = 0; i < tableSize * 4 + 1; i++)
		{
			cout << '-';
		}
		cout << endl;
	}
}
COORD View:: checkClick() {
	INPUT_RECORD ir[128];
	DWORD        nRead;
	COORD        xy;
	HANDLE       hStdInput = NULL;
	HANDLE       hStdOutput = NULL;
	HANDLE       hEvent = NULL;

	
	hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdInput);
	SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE handles[2] = { hEvent, hStdInput };
	while (WaitForMultipleObjects(2, handles, FALSE, INFINITE)) {
		ReadConsoleInput(hStdInput, ir, 128, &nRead);
		for (unsigned int i = 0; i < nRead; i++) {
			if (ir[i].EventType == MOUSE_EVENT) {
				xy.X = ir[i].Event.MouseEvent.dwMousePosition.X, xy.Y = ir[i].Event.MouseEvent.dwMousePosition.Y;
				if (((int)ir[i].Event.MouseEvent.dwButtonState & 0x07) == 1) {
					
					return xy;
				}
			}
		}
	}
}
void View::cls(HANDLE hStdOut)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coordScreen = { 0,0 };
	DWORD cCharsWritten;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hStdOut, coordScreen);

	return;
}
void  View::gotoXY(int pX, int pY) {
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

    

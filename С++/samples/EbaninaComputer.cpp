#include <iostream>
#include "Ebanina.h"

#pragma comment(linker, "/STACK:134217728")

using namespace std;

int main()
{
	cout <<
		"   ___  ____    ____  ____   ____  ____    ____ \n"
		"  /  _]|    \\  /    ||    \\ |    ||    \\  /    |\n"
		" /  [_ |  o  )|  o  ||  _  | |  | |  _  ||  o  |\n"
		"|    _]|     ||     ||  |  | |  | |  |  ||     |\n"
		"|   [_ |  O  ||  _  ||  |  | |  | |  |  ||  _  |\n"
		"|     ||     ||  |  ||  |  | |  | |  |  ||  |  |\n"
		"|_____||_____||__|__||__|__||____||__|__||__|__|\n";

	cout << "Select mode:\n"
		"0: output ebanina to the console window\n"
		"1: write ebanina to file\n"
		"2: combine 1 and 2"
		"\n> ";

	bool outConsole = true;
	bool outFile = false;

	string mode;
	cin >> mode;
	if (mode == "1")
	{
		outConsole = false;
		outFile = true;
	}
	else if (mode == "2") outFile = true;

	cout << "Print a number to convert to Mighty Ebanina" << endl;

	while (true)
	{
		cout << "> ";

		string number;
		cin >> number;

		Ebanina ebanina(number);
		ebanina.create();

		if (outConsole)
		{
			cout << "Here is your Ebanina\n";
			cout << ebanina.getString() << endl;
		}

		if(outFile)
			ebanina.toFile("Ebanina-" + number + ".txt");
	}
	
	system("pause");
}


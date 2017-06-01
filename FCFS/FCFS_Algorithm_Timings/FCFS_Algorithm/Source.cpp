// ------------- This programm demonstrate First-Come, First-Served algorithm for CPU Burst ------------------ //
// ---------------------------------Values http://studopedia.org/6-14475.html -------------------------------- //
#include <iostream>
#include <windows.h>
#include <iomanip>


//  For fullscreen mode;
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1
using namespace std;



using namespace std;

int main(int argc, char* argv[])
{
	// Text color in CLI;
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);

	int processQuantity, averageWaitTime = 0, averageTurnArround = 0;
	int burstTime[30], waitTime[30], turnAroundTime[30];
	int i, j;
	char confirm_continue_programm (NULL);
	
	// Fullscreen mode begin;

	COORD Mode;
	
	CHANGESTATECONSOLE SetConsoleDisplayMode;
	// L in (L"kernel32") error C2664.VS2015;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); 
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
	GetProcAddress(hKernel32, "SetConsoleDisplayMode");

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// Switching to fullscreen
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

	while (confirm_continue_programm != 'n')
	{ 
		cout << "--------- This program illustrating timing planning algorithm ------------------\n\n"
			 << "----------------------- First-Come, First-Served  -------------------------------\n\n"
			 << "================================================================================= " << endl << endl;;
		cout << "Enter the quantity of processes (30th max):\n";
		cin >> processQuantity;
		// Validation of input number of processes;
		if (processQuantity <= 0 || processQuantity >30 )
		{					
			cout << "Invalid quantity of processes. Exiting...\n";
			break;
		}
		// Check that entered symbol is numeral;
			else if (!cin)
			{
				cout << "Please enter the number. Exiting..." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
			
			cout << "\nEnter process time\n";

			for (i = 0; i < processQuantity; i++)
			{
				cout << "P[" << i << "]:";
				cin >> burstTime[i];
			}
			// Waiting time for first process;
			waitTime[0] = 0;						

			// Wait time calculation;
			for (i = 0; i < processQuantity; i++)
			{					
				waitTime[i] = 0;
					for (j = 0; j < i; j++)
						waitTime[i] += burstTime[j];
			}

			cout << "\nProcess\t\tBurst-time\tWait-time\tTurn around-time";

			// Turn around time calculation;

			for (i = 0; i < processQuantity; i++)
			{
				turnAroundTime[i] = burstTime[i] + waitTime[i];
				averageWaitTime += waitTime[i];
				averageTurnArround += turnAroundTime[i];
				cout << "\nP[" << i << "]" << setw(18) << burstTime[i] << setw(18) << waitTime[i] << setw(18) << turnAroundTime[i];
			}

			averageWaitTime /= i;				
			averageTurnArround /= i;				
			cout << "\n\nAverage wait time:" << averageWaitTime << endl;
			cout << "\nAverage turn around time:" << averageTurnArround << endl;
			cout << "\nUsed materials: " << endl << "http://studopedia.org/6-14475.html;" << endl;
			cout << "\nDo you want to continue?\n" << "Enter [y/n] for continue/exit \n\n";
			cin >> confirm_continue_programm;

			if (confirm_continue_programm == 'n'|| confirm_continue_programm =='y') system("cls");
						
			else break; 
						
	}
	system ("pause");
	return 0;
}
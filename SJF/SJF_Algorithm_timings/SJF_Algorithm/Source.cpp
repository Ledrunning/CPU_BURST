#include <iostream>
#include <windows.h>
#include <iomanip>

// Fullscreen mode;
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1
using namespace std;

int main(int argc, char* argv[])
{
	int burstTime[30], process[30], waitTime[30], turnArroundTime[30], i, j;
	int numberOfProcess, total = 0, position, temp;
	char confirmation(NULL);
	float averageWaitTime, averageTurnarround;
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);


    // Fullscreen mode begin;

	COORD Mode;
	CHANGESTATECONSOLE SetConsoleDisplayMode;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); // L в (L"kernel32") error C2664. VS2015;
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
	GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

	// Fullscreen mode end;
while (confirmation != 'n' || confirmation == 'y')
{ 
	
	cout << "--------- Planning timer algorithm Shortest Job First  ---------" << endl << endl
		 << "-----------------------for CPU-BURST ---------------------------" << endl << endl
		 << "================================================================" << endl;
	cout << "Enter the number of process(30 Max): " << endl;
	cin >> numberOfProcess;
	
	// Number of process range;
	if (numberOfProcess <= 0 || numberOfProcess >30 )
	{					
			cout << "Please enter correct value. Exiting....\n";
			break;
	}
	
	cout << endl;

	cout << "Enter process time: " << endl;

			for (i = 0; i < numberOfProcess; i++) 
			{	
				cout << "P[" << i << "]:";
				cin >> burstTime[i];
				if (!cin)
				{
					cout << "Please enter valid data!" << endl;
					cin.clear();
					fflush(stdin);
     			}
				process[i] = i + 1;           
			}

				// Sorting burst time from lower to upper;
				for (i = 0; i<numberOfProcess; i++) 
				{			
					position = i;
					for (j = i + 1; j < numberOfProcess; j++) 
					{
						if (burstTime[j] < burstTime[position])
							position = j;
					}

					temp = burstTime[i];
					burstTime[i] = burstTime[position];
					burstTime[position] = temp;
					temp = process[i];
					process[i] = process[position];
					process[position] = temp;
				}

				waitTime[0] = 0;				

	// Calculate Wait time;					  
	for (i = 1; i<numberOfProcess; i++) 
	{		
		waitTime[i] = 0;
		for (j = 0; j < i; j++)
			waitTime[i] += burstTime[j];
			total += waitTime[i];
	}

	averageWaitTime = (float)total / numberOfProcess;      
	total = 0;
	cout << endl;

	// Print result;
	cout << "Process   \tBurst Time    \tWait Time   \tTurnaround Time" << endl
		 << "____________________________________________________________________________" << endl;
	for (i = 0; i < numberOfProcess; i++) 
	{
		turnArroundTime[i] = burstTime[i] + waitTime[i];     
		total += turnArroundTime[i];
		cout << setw(18) << "\nP[" << i << "]" << setw(18) << burstTime[i] 
			 << setw(18) << waitTime[i] << setw(18) << turnArroundTime[i];
	}
	
	averageTurnarround = (float)total / numberOfProcess;		   
	cout << "\n\nAverage Waiting Time = " << averageWaitTime << endl;
	cout << "\nAverage Turnaround Time =" << averageTurnarround << endl;
	
	cout << "Do you want to continue y/n ?" << endl;
	cin >> confirmation; cout << confirmation;
	if (confirmation == 'y') 
	{
		system("cls");
	}
	else if (confirmation != 'y' || confirmation != 'n')
	{
		cout << "You enter wrong confirmation" << endl;
		break;
	}
	else  break;
	
  }
    system("pause");
	return 0;
}

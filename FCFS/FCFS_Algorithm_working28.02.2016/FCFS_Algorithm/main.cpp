/*
 * Author Osman Mazinov
 * 2016
 * This code example illustrates the CPU burst 
 * planning process using the FCFS algorithm
 * -------------------------------- HELP -----------------------------------------//
 * http://studopedia.org/6-14475.html;
 * Turnaround time – amount of time to execute a particular process
 * CPU utilization – keep the CPU as busy as possible
 * Throughput – # of processes that complete their execution per time unit
 * Turnaround time – amount of time to execute a particular process
 * Waiting time – amount of time a process has been waiting in the ready queue
 * Response time – amount of time from when a request was submitted until the first response is produced.
*/

#include <iostream>
#include <windows.h>
#include <iomanip>
#define MAX_PROCESSES 100	

// fullscreen mode;
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1
using namespace std;

struct Process
{
	int pId; // Number of process;
	int burstTime;
	int waitingTime;
	int turnAroundTime;
};

// Process time table print function;
void PrintTable(Process cpuProcess[], int processQuantity);		
// Gant char print function;
void PrintGanttChart(Process cpuProcess[], int processQuantity);		


int main(int argc, char* argv[])
{   
//****************************** Fullscreen mode ****************************** //

	COORD Mode;

	CHANGESTATECONSOLE SetConsoleDisplayMode;
	// L in (L"kernel32") VS2015;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); 
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
	GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

//**************************************************************************** //
	
	Process cpuProcess[MAX_PROCESSES];					
	int i, j, processQuantity;
	int waitingTimeSum = 0, turnAroundTimeSum = 0;
	char continueConfirmation;
	while (continueConfirmation != 'n' || continueConfirmation=='y')
	{ 
			cout << "------ This programm illustrate First-Come, First-Served algorithms ------" << endl;
			cout << "---------------------------- for CPU-BURST--------------------------------" << endl;
			cout << "==========================================================================" << endl;
			// Check for digit;
				cout << "Enter the process quantity: ";
				cin >> processQuantity;
				if (!cin)
				{
					cout << "Please enter number! Exiting..." << endl;
					cin.clear();
					fflush(stdin);
					break;
				}
		
			cout << "Enter Burst time for current process: " << endl;

			for (i = 0; i<processQuantity; i++)
			{						
				cpuProcess[i].pId = i;
				cout << "P[" << i << "]" << ": ";
				cin >> cpuProcess[i].burstTime;
				cpuProcess[i].waitingTime = cpuProcess[i].turnAroundTime = 0;
			}

			//  Calculating Wait and turnaround times;
			cpuProcess[0].turnAroundTime = cpuProcess[0].burstTime;

			for (i = 1; i<processQuantity; i++)
			{
				cpuProcess[i].waitingTime = cpuProcess[i - 1].waitingTime + cpuProcess[i - 1].burstTime;
				cpuProcess[i].turnAroundTime = cpuProcess[i].waitingTime + cpuProcess[i].burstTime;
			}

			// Caalculating waiting time sum and turn around time sum;
			for (i = 0; i<processQuantity; i++)
			{
				waitingTimeSum += cpuProcess[i].waitingTime;
				turnAroundTimeSum += cpuProcess[i].turnAroundTime;
			}

/* Print table into console 
 * Process          Burst Time
 *        P0                                 24
 *        P1                                  3
 *        P2                                  3	
 * Wait time для P0 = 0; P1 = 24; P2 = 27
 * Average wait time: (0 + 24 + 27)/3 = 17
 * Average turnaround time: (24+27+30)/2 = 27
*/

			cout << endl;	
			PrintTable(cpuProcess, processQuantity);
			cout << endl;	
			cout << "Average waiting time    : " << (double)(waitingTimeSum / processQuantity) << endl; 
			cout << "Average turnaround time : " << (double)(turnAroundTimeSum / processQuantity) << endl; 
			cout << "Total waiting time      : " << waitingTimeSum << endl; 
			cout << "Total turnaround time   : " << turnAroundTimeSum << endl;
			cout << endl; 
			cout << "         \t\t ===================          " << endl;
			cout << "         \t\t  PROCESS DIAGRAM          " << endl;
			cout << "         \t\t ===================          " << endl;
			PrintGanttChart(cpuProcess, processQuantity);

			// CLI menu;
			cout << "\nTo continue the program уnter [y], " << endl;
			cout << "if you want to exit enter [n] \n" << endl;
			cin >> continueConfirmation; 
			cout << continueConfirmation;

			// Confirmation and validate entered data for continue;
			if (continueConfirmation == 'y')
			{ 
				system("cls");  
			}					
			else if (continueConfirmation == 'n')
			{
				cout << "\nExiting..." << endl;
				break;
			}
				
			else
			{
				cout << "\nExeption! Exiting..." << endl;
				break;
			}
	}
	system("pause"); 
	return 0;
}


void PrintTable(Process cpuProcess[], int processQuantity)
{
	int i;

	cout << "+-------------+--------------+----------------+-----------------+" << endl;
	cout << "| #  Process  |  Burst Time  |    Wait Time   | Turnaround time |" << endl;
	cout << "+---------------------------------------------------------------+" << endl;

	for (i = 0; i<processQuantity; i++) 
	{
		cout << "|" << setw(7) << cpuProcess[i].pId << setw(7) << "|" << setw(8) << cpuProcess[i].burstTime
			 <<  setw(7) << "|" << setw(9) << cpuProcess[i].waitingTime << setw(8) << "|"
			 << setw(8) << cpuProcess[i].turnAroundTime << setw(10) << "|" << endl;
		cout << "+-------------+--------------+----------------+-----------------+" << endl;
	}

}

void PrintGanttChart(Process cpuProcess[], int processQuantity)
{
	int i, j;
	// Top bar printing;
	cout << "+";
	for (i = 0; i<processQuantity; i++) 
	{
		for (j = 0; j < cpuProcess[i].burstTime; j++) cout << "--";
		cout <<"+";
	}
	cout << endl << "|";
	// Print the number of process in the midlle;
	for (i = 0; i<processQuantity; i++) 
	{
		for (j = 0; j<cpuProcess[i].burstTime - 1; j++) cout << " ";
		cout << "P" << cpuProcess[i].pId;
		for (j = 0; j<cpuProcess[i].burstTime - 1; j++) cout << " ";
			cout << "|";
	}
	cout << endl;
	// Print the bottom boarder of the table;
	cout << "+";
	for (i = 0; i < processQuantity; i++) 
	{
		for (j = 0; j < cpuProcess[i].burstTime; j++) cout << "--";
		cout << "+";
	}
	cout << "\n";

	// Print the wait line;
	cout << "0";
	for (i = 0; i<processQuantity; i++) 
	{
		for (j = 0; j < cpuProcess[i].burstTime; j++) cout << "  ";
		if (cpuProcess[i].turnAroundTime > 9) cout << "\b"; // backspace 
		cout << cpuProcess[i].turnAroundTime;

	}
	cout << "\n";
}

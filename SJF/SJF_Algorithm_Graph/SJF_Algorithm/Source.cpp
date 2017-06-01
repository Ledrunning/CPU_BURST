#include<iostream>
#include<windows.h>
#include<iomanip>

using namespace std;

int numberOfProcesses, totalCPUBurstTime, *arrivalTime;
int *CPUBurstTime, *processNumber, minimumArrivalTime;
float averageWaitingTime=0, averageTurnAroundTime=0;

void DrawGraph();
void FreeMemory();

// Fullscreen mode begin code;
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1



int main(int argc, char* argv[])
{
	// Fullscreen mode end code;

	COORD Mode;
	
	CHANGESTATECONSOLE SetConsoleDisplayMode;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); // L в (L"kernel32")error C2664. В VS2015;
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
		GetProcAddress(hKernel32, "SetConsoleDisplayMode");

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

	// Fullscreen end code;

				
	int i,j,temp;
	cout << "--------- ====================================== -----------" << endl;
	cout << "---- This program illustrate Short Job First algorithm ------\n"<<endl;
	cout << "--------- ====================================== -----------\n"<< endl;
    cout << "Enter process quantity: ";

    cin >> numberOfProcesses;
    arrivalTime = new int [numberOfProcesses];
    CPUBurstTime = new int [numberOfProcesses];
    processNumber = new int [numberOfProcesses];

    // Enter data;
    minimumArrivalTime=2147483647;

    for(i=0;i<numberOfProcesses;i++)
    {
      processNumber[i]=i;
      cout << "\nNumber of current process P : " << i << endl;
	  cout << "Priority time  : " << endl;
      cin >> arrivalTime[i];
      cout << "CPU Burst time : " << endl;
      cin >> CPUBurstTime[i];
      totalCPUBurstTime+=CPUBurstTime[i];
		 if(minimumArrivalTime>arrivalTime[i])
               minimumArrivalTime=arrivalTime[i];
    }
     
				// Bubble sort;
                             
                for(i=0;i<numberOfProcesses;i++)
                {
                  for(j=0;j<numberOfProcesses-i-1;j++)
                  {
                    if(CPUBurstTime[j]>CPUBurstTime[j+1])
                    {
                       temp=arrivalTime[j];
                       arrivalTime[j]=arrivalTime[j+1];
                       arrivalTime[j+1]=temp;
                       temp=CPUBurstTime[j];
                       CPUBurstTime[j]=CPUBurstTime[j+1];
                       CPUBurstTime[j+1]=temp;
                       temp=processNumber[j];
                       processNumber[j]=processNumber[j+1];
                       processNumber[j+1]=temp;
                    }
                  }
                }

		cout << endl;

		cout << "----------------------------- Entered values -----------------------------" << endl;

        for(i=0;i<numberOfProcesses;i++)
        {
			cout << "\nP" << processNumber[i]<< " -> " << "[" << arrivalTime[i] << "]"
				 << "[" << CPUBurstTime[i] << "]" << endl; 
        }
           
				DrawGraph();
				cout << "\nUsed materials: " << endl;
				cout << "--------------------------------------------------------------------" << endl;
				cout << "1. http://www.intuit.ru/studies/courses/2192/31/lecture/972?page=4" << endl;
				cout << "2. http://life-prog.ru/1_1057_algoritmi-planirovaniya.html" << endl;
				cout << "--------------------------------------------------------------------" << endl;
				
				FreeMemory();

				system("pause");
               
}

// Print graph;
void DrawGraph()
{              
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);
				const int maxWidth=100;
                int scalingFactor,i,counter,tempi,currentTime;
                cout << "\nProcess diagram : " << endl << endl;
               
                scalingFactor=maxWidth/totalCPUBurstTime;
                for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
                {
                     cout << "-";
								
                }
				cout << endl << "|";
                counter=0,tempi=0;
                for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
                {      
                     if(i==CPUBurstTime[counter]*scalingFactor+tempi)
                     {
                           counter++;
                           tempi=i;
						   cout << "|"; 
                     }
                     else if(i==(CPUBurstTime[counter]*scalingFactor)/2+tempi)
                     {
                        cout << "P" << processNumber[counter];
                     }
                     else
                     {
                        cout << " ";
                     }
                               
                }
                cout << "|" << endl;
                for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
                {
                   cout << "-";
                }
                cout << endl;

				// Print times in Gant chart

                counter=0;
                tempi=0;
                currentTime=minimumArrivalTime;
                cout << currentTime;
                for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
                {
					 if(i==CPUBurstTime[counter]*scalingFactor+tempi)
                     {
                                               
						 tempi=i;
                         currentTime+=CPUBurstTime[counter];
                         averageWaitingTime+=currentTime;
                         counter++;
                         cout << currentTime;
                     }
                     else
                     {
						cout << " ";
                     }
                }
                currentTime+=CPUBurstTime[counter];
               
				cout << currentTime << endl << endl;
				averageWaitingTime = averageWaitingTime /  numberOfProcesses;
                averageTurnAroundTime = averageWaitingTime+totalCPUBurstTime / numberOfProcesses;
				
                cout << "Average wait time  : " << averageWaitingTime << endl; 
                cout << "Average turnarround time : " << averageTurnAroundTime << endl;

}

void FreeMemory()
{
	delete[] arrivalTime;
	delete[] CPUBurstTime;
	delete[] processNumber;
}
//----------------------------------------------------- Программа демонстрации алгоритма Shortest Job First для CPU Burst ------------------------------------------- //
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
// --------------------------- fullscreen mode ----------------------------------------- //
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1
using namespace std;

//--------------------------- Основная программа --------------------------------------- //



int main()
{
	int BURST_TIME[30], p[30], WAIT_TIME[30], TURN_AROUNDTIME[30], i, j;
	int NUMBER_OF_PROCESS, total = 0, position, temp;
	char confirmation(NULL);
	float avg_WAITTIME, avg_TURNAROUND;
	setlocale(LC_CTYPE, "Russian");
	cout.setf(ios::fixed);
	cout.precision(2);


// --------------------------- fullscreen mode begin ------------------------------------ //

	COORD Mode;
	// Извращаемся 
	CHANGESTATECONSOLE SetConsoleDisplayMode;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); // L в (L"kernel32") устранило ошибку error C2664. В VS2015 работает без нее.
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
	GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// Переключаемся в fullscreen
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

// --------------------------- fullscreen mode end ---------------------------------------- //
while (confirmation != 'n') { 

	cout << "--------- Программа иллюстрирующая алгоритм планирования Shortest Job First  ---------\n\n"
		 << "----------------- для CPU-BURST. Студент группы PST1522 Мазинов Осман ---------------------- \n\n"
		 << "============================================================================================= \n\n";
	cout << "Введите количество процессов(максимум 30): \n";
	cin >> NUMBER_OF_PROCESS;
	if (NUMBER_OF_PROCESS <= 0 || NUMBER_OF_PROCESS >30 ) {					// Проверяем правильность ввода количества процессов;
			cout << "Вы ввели некорректное количество процессов!\n";
		break;
		}
	cout << "\nВведите время процесса:\n";

			for (i = 0; i<NUMBER_OF_PROCESS; i++) {		// Вводим время процесса;
				cout << "P[" << i << "]:";
				cin >> BURST_TIME[i];
				p[i] = i + 1;           // Тут храним номера процессов;
			}

				
				for (i = 0; i<NUMBER_OF_PROCESS; i++) {			// Сортировка burst времени по возрастанию;
					position = i;
					for (j = i + 1; j<NUMBER_OF_PROCESS; j++) {
						if (BURST_TIME[j]<BURST_TIME[position])
							position = j;
					}

					temp = BURST_TIME[i];
					BURST_TIME[i] = BURST_TIME[position];
					BURST_TIME[position] = temp;

					temp = p[i];
					p[i] = p[position];
					p[position] = temp;
				}

				WAIT_TIME[0] = 0;				 // Время первого процесса равно 0;

						  
	for (i = 1; i<NUMBER_OF_PROCESS; i++) {		// Расчет времени ожидания;
		WAIT_TIME[i] = 0;
		for (j = 0; j<i; j++)
			WAIT_TIME[i] += BURST_TIME[j];
			total += WAIT_TIME[i];
	}

	avg_WAITTIME = (float)total / NUMBER_OF_PROCESS;      // Среднее время ожидания;
	total = 0;
//--------------------------------- Тут выводим результат в консоль ----------------------------- //
	cout << "\nПроцесс   \tBurst Время    \tВремя ожидания   \tВремя обращения\n"
		 << "____________________________________________________________________________\n";
	for (i = 0; i<NUMBER_OF_PROCESS; i++) {
		TURN_AROUNDTIME[i] = BURST_TIME[i] + WAIT_TIME[i];     // Расчет времени обращения;
		total += TURN_AROUNDTIME[i];
		cout << setw(18) << "\nP[" << i << "]" << setw(18) << BURST_TIME[i] 
			 << setw(18) << WAIT_TIME[i] << setw(18) << TURN_AROUNDTIME[i];
	}

	avg_WAITTIME = (float)total / NUMBER_OF_PROCESS;		   // Среднее время обращения;
	cout << "\n\nAverage Waiting Time= " << avg_WAITTIME << endl;
	cout << "\nAverage Turnaround Time=" << avg_TURNAROUND << endl;
	cout << "\nХотите продолжить?\n" << "Для продолжения нажмите y, для завершения программы нажмите n\n";
				cin >> confirmation;
				if (confirmation == 'n'|| confirmation =='y') { //Если n или y - продолжаем 
					system("cls"); 
					continue; 
				}					// Очищаем экран и продолжаем;
						else break; 
  }
    system("pause");
	return 0;
}
//----------------------------------------------------- Программа демонстрации алгоритма First-Come, First-Served для CPU Burst ------------------------------------------- //
//-------------------------------Значения подгонял отсюда http://studopedia.org/6-14475.html;
//------------------------------- и отсюда: http://www.gitam.edu/eresource/comp/gvr(os)/5.3.htm; 

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#define MAX 100				// Максимум процессов;
// --------------------------- fullscreen mode ----------------------------------------- //
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1
using namespace std;

//--------------------------- Структура времен --------------------------------------- //

typedef struct
{
	int pid;
	int burst_time;
	int waiting_time;
	int turnaround_time;
} Process;

void print_table(Process p[], int n);			// Прототип функции печати таблицы;
void print_gantt_chart(Process p[], int n);		// Прототип функции печати графика;

//--------------------------- Основная программа --------------------------------------- //

int main()
{   
// --------------------------- Режим fullscreen  ------------------------------------ //

	COORD Mode;

	CHANGESTATECONSOLE SetConsoleDisplayMode;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); // L в (L"kernel32") устранило ошибку error C2664. В VS2015 работает без нее.
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
	GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// Переключаемся в fullscreen
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

// --------------------------------------------------------------------------------- //
	setlocale(LC_CTYPE, "Russian");	// Рус.яз в консоли;
	Process p[MAX];					// Макс. количество процессов;
	int i, j, n;
	int sum_waiting_time = 0, sum_turnaround_time;
	puts(" ");					// Пустая строка;
	puts("--------- Программа иллюстрирующая алгоритм планирования First-Come, First-Served  ---------");
	puts("----------------- для CPU-BURST. Студент группы PST1522 Мазинов Осман ----------------------");
	puts("============================================================================================");
	printf("Введите количество процессов: ");
	scanf_s("%d", &n);
	printf("Введите Burst время для текущего процесса:\n");

// -------------------------- Крутим, пока не введем время всех процессов-------------------------- //
	for (i = 0; i<n; i++) {						
		p[i].pid = i;
		printf("P[%d] : ", i);
		scanf_s("%d", &p[i].burst_time);
		p[i].waiting_time = p[i].turnaround_time = 0;
	}

// ------------------------ Считаем время ожидания и время оборота процесса-------------------------//
	p[0].turnaround_time = p[0].burst_time;

	for (i = 1; i<n; i++) {
		p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
		p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
	}

// -----------------------Вычесляем сумму времени ожидания и времени оборота -----------------------//
	for (i = 0; i<n; i++) {
		sum_waiting_time += p[i].waiting_time;
		sum_turnaround_time += p[i].turnaround_time;
	}

// ------------------------------ Выводим таблицу в консоль ---------------------------------------//
	/* Process          Burst Time
          P0                                 24
          P1                                  3
          P2                                  3	
	 Время ожидания для P0 = 0; P1 = 24; P2 = 27
     Среднее время ожидания: (0 + 24 + 27)/3 = 17
	 Среднее время обращения: (24+27+30)/2 = 27
	 Пример для проверки, взято с http://www.gitam.edu/eresource/comp/gvr(os)/5.3.htm
	*/

	puts("");	// Пустая строка;
	print_table(p, n); // Вызываем функцию печати значений в таблице;
	puts("");	// Пустая строка;
	printf("Среднее время ожидания   : %-2.2lf\n", (double)sum_waiting_time / (double)n); // Сумму делим на кол-во процессов;
	printf("Среднее время обращения : %-2.2lf\n", (double)sum_turnaround_time / (double)n); // Сумму делим кол-во процессов;
	printf("Общее время ожидания    : %-2d\n", sum_waiting_time); // Общая сумма времени ожидания;
	printf("Общее время обращения   : %-2d\n", sum_turnaround_time); // Общая сумма времени обращения к процессу;

// ------------------------------------ Печатаем начало диаграммы  -------------------------------//
	puts(""); // Empty line
	puts("         \t\t ===================          ");
	puts("         \t\t ДИАГРАММА ПРОЦЕССОВ          ");
	puts("         \t\t ===================          ");
	print_gantt_chart(p, n);
	system("pause"); // системная пауза;
	return 0;
}

// ------------------------------------ Функция печати таблицы  ---------------------------------//
void print_table(Process p[], int n)
{
	int i;

	puts("+-------------+--------------+----------------+-----------------+");
	puts("| № Процесса  | Burst Время  | Время Ожидания | Время Обращения |");
	puts("+---------------------------------------------------------------+");

	for (i = 0; i<n; i++) {
		printf("|    %2d       |      %2d      |      %2d        |        %2d       |\n"
			, p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
		puts("+-------------+--------------+----------------+-----------------+");
	}

}

// ------------------------------------ Функция печати дмаграммы  ---------------------------------//
void print_gantt_chart(Process p[], int n)
{
	int i, j;
	// Печать верхнего бара;
	printf(" ");
	for (i = 0; i<n; i++) {
		for (j = 0; j<p[i].burst_time; j++) printf("--");
		printf(" ");
	}
	printf("\n|");
	// Печать номера процесса по середине;
	for (i = 0; i<n; i++) {
		for (j = 0; j<p[i].burst_time - 1; j++) printf(" ");
		printf("P%d", p[i].pid);
		for (j = 0; j<p[i].burst_time - 1; j++) printf(" ");
		printf("|");
	}
	printf("\n ");
	// Печать нижней границы таблицы;
	for (i = 0; i<n; i++) {
		for (j = 0; j<p[i].burst_time; j++) printf("--");
		printf(" ");
	}
	printf("\n");

	// Печать временной линии
	printf("0");
	for (i = 0; i<n; i++) {
		for (j = 0; j<p[i].burst_time; j++) printf("  ");
		if (p[i].turnaround_time > 9) printf("\b"); // backspace : убираем 1 пробел
		printf("%d", p[i].turnaround_time);

	}
	printf("\n");
}
// -------------------------------- Шпаргалки -----------------------------------------//
// Turnaround time – amount of time to execute a particular process 
// Оборотное время - количество времени, чтобы выполнить определенный процесс
// CPU utilization – keep the CPU as busy as possible
// Throughput – # of processes that complete their execution per time unit
// Turnaround time – amount of time to execute a particular process
// Waiting time – amount of time a process has been waiting in the ready queue
// Response time – amount of time from when a request was submitted until the first response is produced.
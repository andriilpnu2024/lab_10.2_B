#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h> 
using namespace std;
enum Spec { KN, INF, MATEC, FIZNF, TRUD };
string specStr[] =
{ "Комп'ютерні науки",
"Інформатика",
"Математика та економіка",
"Фізика та інформатика",
"Трудове навчання" };
struct Studik
{
	string prizv;
	unsigned kurs;
	unsigned fiz;
	unsigned mat;
	Spec spec;
	union
	{
		int prog;
		int chiselmethod;
		int pedagog;
	};
};
void Create(Studik* p, const int N);
void Print(Studik* p, const int N);
int BinSearch(Studik* p, const int N, unsigned fiz, unsigned kurs);
int* IndexSort(Studik* p, const int N);
void PrintIndexSorted(Studik* p, int* I, const int N);
void SaveToFile(Studik* p, const int N, const char* filename);
void LoadFromFile(Studik*& p, int& N, const char* filename);
void Sort(Studik* p, const int N);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int fiz;
	int k = 0;
	int N;
	cout << "Введіть кількість студентів : "; cin >> N;
	char filename[100];
	Studik* p = new Studik[N];
	int ikurs;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - бінарний пошук студента за курсом та оцінкою з фізики" << endl;
		cout << " [5] - індексне впорядкування та вивід даних" << endl;
		cout << " [6] - запис даних у файл" << endl;
		cout << " [7] - зчитування даних із файлу" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Курс: "; cin >> ikurs;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " Оцінка з фізики : "; cin >> fiz;
			cout << endl;
			if ((found = BinSearch(p, N, fiz, ikurs)) != -1)
				cout << "Знайдено Студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого Студента не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 6:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 7:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Studik* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " спеціальність: (0 - Комп'ютерні науки,1 - Інформатика, 2 - Математика та економіка , 3 - Фізика та інформатика , 4 - Трудове навчання):  ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " курс: "; cin >> p[i].kurs;
		cout << " Оцінка з фізики: "; cin >> p[i].fiz;
		cout << " Оцінка з математики: "; cin >> p[i].mat;
		switch (p[i].spec)
		{
		case KN:
			cout << " Програмування : "; cin >> p[i].prog;
			break;
		case INF:
			cout << " Чисельний метод : "; cin >> p[i].chiselmethod;
			break;
		default:
			cout << " Педагогіка : "; cin >> p[i].pedagog;
		}
	}
}
void Print(Studik* p, const int N)
{
	cout << "================================================================================================================================" << endl;
	cout << "| №   | Прізвище       | Курс | Спеціальність            | Фізика | Математика | Програмування | Чисельний метод |  Педагогіка |" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(15) << left << p[i].prizv // Прізвище 
			<< "| " << setw(4) << right << p[i].kurs << " "// Курс
			<< "| " << setw(25) << left << specStr[p[i].spec] // Спеціальність 
			<< "| " << setw(6) << right << p[i].fiz << " "    // Фізика 
			<< "| " << setw(10) << right << p[i].mat << " ";   // Математика
			switch (p[i].spec)
			{
			case KN:
				cout << "| " << setw(13) << setprecision(2) << fixed << right << p[i].prog << " |" << setw(17) << " " << "|" << setw(13) << " " << "|" << endl;
				break;
			case INF:
				cout << "| " << setw(14) << " " << "| " << setw(15) << setprecision(2) << fixed << right << p[i].chiselmethod << " |" << setw(13) << " " << "|" << endl;
				break;
			default:
				cout << "| " << setw(14) << " " << "| " << setw(16) << " " << "| " << setw(11) << setprecision(2) << fixed << right << p[i].pedagog << " |" << endl;
				break;
			}
	}
	cout << "================================================================================================================================"
		<< endl;
}
int BinSearch(Studik* p, const int N, unsigned fiz, unsigned kurs)
{
	// Повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	while (L <= R) {
		m = L + (R - L) / 2;  // Безпечний спосіб обчислення середини
		if (p[m].fiz == fiz && p[m].kurs == kurs)
			return m;  // Знайшли елемент

		if (p[m].kurs > kurs || (p[m].kurs == kurs && p[m].fiz > fiz)) {
			L = m + 1;  // Шукаємо в правій половині
		}
		else {
			R = m - 1;  // Шукаємо в лівій половині
		}
	}
	return -1;  // Якщо елемент не знайдено
}

int* IndexSort(Studik* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].fiz > p[value].fiz) ||
				(p[I[j]].fiz == p[value].fiz &&
					p[I[j]].kurs > p[value].kurs) ||
				(p[I[j]].fiz == p[value].fiz &&
					p[I[j]].kurs == p[value].kurs &&
					p[I[j]].prizv > p[value].prizv)
				);
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Studik* p, int* I, const int N)
{
	cout << "================================================================================================================================" << endl;
	cout << "| №   | Прізвище       | Курс | Спеціальність            | Фізика | Математика | Програмування | Чисельний метод |  Педагогіка |" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(15) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(25) << left << specStr[p[I[i]].spec]
			<< "| " << setw(6) << right << p[I[i]].fiz << " "
			<< "| " << setw(10) << right << p[I[i]].mat << " ";
			switch (p[i].spec)
			{
			case KN:
				cout << "| " << setw(13) << setprecision(2) << fixed << right << p[i].prog << " |" << setw(17) << " " << "|" << setw(13) << " " << "|" << endl;
				break;
			case INF:
				cout << "| " << setw(14) << " " << "| " << setw(15) << setprecision(2) << fixed << right << p[i].chiselmethod << " |" << setw(13) << " " << "|" << endl;
				break;
			default:
				cout << "| " << setw(14) << " " << "| " << setw(16) << " " << "| " << setw(11) << setprecision(2) << fixed << right << p[i].pedagog << " |" << endl;
				break;
			}
	}
	cout << "================================================================================================================================"
		<< endl;
	cout << endl;
}
void Sort(Studik* p, const int N)
{
	Studik tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].fiz < p[i1 + 1].fiz)
				||
				(p[i1].fiz == p[i1 + 1].fiz &&
					p[i1].kurs < p[i1 + 1].kurs)
				||
				p[i1].fiz == p[i1 + 1].fiz &&
				p[i1].kurs == p[i1 + 1].kurs && p[i1].prizv < p[i1 + 1].prizv)
			{
				tmp = p[i1 + 1];
				p[i1 + 1] = p[i1];
				p[i1] = tmp;
			}
}
void SaveToFile(Studik* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Studik)); // записали елементи масиву
	fout.close(); // закрили файл
}
void LoadFromFile(Studik*& p, int& N, const char* filename)
{
	delete[] p; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	p = new Studik[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Studik)); // прочитали елементи масиву
	fin.close(); // закрили файл
}

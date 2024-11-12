#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h> 
using namespace std;
enum Spec { KN, INF, MATEC, FIZNF, TRUD };
string specStr[] =
{ "����'����� �����",
"�����������",
"���������� �� ��������",
"Գ���� �� �����������",
"������� ��������" };
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
	cout << "������ ������� �������� : "; cin >> N;
	char filename[100];
	Studik* p = new Studik[N];
	int ikurs;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ������� ����� �������� �� ������ �� ������� � ������" << endl;
		cout << " [5] - �������� ������������� �� ���� �����" << endl;
		cout << " [6] - ����� ����� � ����" << endl;
		cout << " [7] - ���������� ����� �� �����" << endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������ ����� ������:" << endl;
			cout << " ����: "; cin >> ikurs;
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << " ������ � ������ : "; cin >> fiz;
			cout << endl;
			if ((found = BinSearch(p, N, fiz, ikurs)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 6:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 7:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;

		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Studik* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ������������: (0 - ����'����� �����,1 - �����������, 2 - ���������� �� �������� , 3 - Գ���� �� ����������� , 4 - ������� ��������):  ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������ � ������: "; cin >> p[i].fiz;
		cout << " ������ � ����������: "; cin >> p[i].mat;
		switch (p[i].spec)
		{
		case KN:
			cout << " ������������� : "; cin >> p[i].prog;
			break;
		case INF:
			cout << " ��������� ����� : "; cin >> p[i].chiselmethod;
			break;
		default:
			cout << " ��������� : "; cin >> p[i].pedagog;
		}
	}
}
void Print(Studik* p, const int N)
{
	cout << "================================================================================================================================" << endl;
	cout << "| �   | �������       | ���� | ������������            | Գ���� | ���������� | ������������� | ��������� ����� |  ��������� |" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(15) << left << p[i].prizv // ������� 
			<< "| " << setw(4) << right << p[i].kurs << " "// ����
			<< "| " << setw(25) << left << specStr[p[i].spec] // ������������ 
			<< "| " << setw(6) << right << p[i].fiz << " "    // Գ���� 
			<< "| " << setw(10) << right << p[i].mat << " ";   // ����������
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
	// ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	int L = 0, R = N - 1, m;
	while (L <= R) {
		m = L + (R - L) / 2;  // ��������� ����� ���������� ��������
		if (p[m].fiz == fiz && p[m].kurs == kurs)
			return m;  // ������� �������

		if (p[m].kurs > kurs || (p[m].kurs == kurs && p[m].fiz > fiz)) {
			L = m + 1;  // ������ � ����� �������
		}
		else {
			R = m - 1;  // ������ � ��� �������
		}
	}
	return -1;  // ���� ������� �� ��������
}

int* IndexSort(Studik* p, const int N)
{
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
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
	cout << "| �   | �������       | ���� | ������������            | Գ���� | ���������� | ������������� | ��������� ����� |  ��������� |" << endl;
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
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
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
	ofstream fout(filename, ios::binary); // ������� ������� ���� ������
	fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Studik)); // �������� �������� ������
	fout.close(); // ������� ����
}
void LoadFromFile(Studik*& p, int& N, const char* filename)
{
	delete[] p; // ������� �������� ���
	ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
	fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
	p = new Studik[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Studik)); // ��������� �������� ������
	fin.close(); // ������� ����
}

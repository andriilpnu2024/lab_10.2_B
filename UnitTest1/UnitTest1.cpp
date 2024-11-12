#include "pch.h"
#include "CppUnitTest.h"
#include "../PR-10.2-B/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int spec = 0;
			int k = 0;
			int N = 1;
			int i = 0;
			int fiz = 4;
			int ikurs = 3;
			Studik* p = new Studik[N];
			p[i].prizv = "Кан";
			p[i].kurs = 3;
			p[i].fiz = 4;
			p[i].mat = 5;
			p[i].chiselmethod = 5;
			p[i].pedagog = 2;
			p[i].prog = 2;
			int n = BinSearch(p, N, fiz, ikurs);
			Assert::AreEqual(n, 0);
		}
	};
}

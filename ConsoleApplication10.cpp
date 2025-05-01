#include<iostream>
#include<cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

template<class Item>
class PQ
{
private:
    Item* pq;
    int N, head, tail, numb;
    const int MAX = 100;

    void exch(Item& A, Item& B)
    {
        Item t = A;
        A = B;
        B = t;
    }
    void compexch(Item& A, Item& B)
    {
        if (B < A) exch(A, B);
    }
public:
    PQ()
    {
        pq = new Item[MAX];
        N = MAX;
        head = 0;
        tail = 0;
        numb = 0;
    }
    PQ(int maxN)
    {
        pq = new Item[maxN];
        N = maxN;
        head = 0;
        tail = 0;
        numb = 0;
    }
    int empty()  const
    {
        return numb == 0;
    }
    void insert(Item item)
    {
        pq[tail++] = item;
        if (numb < N)
            numb++;
        if (tail == N)
            tail = 0;
    }
    Item getmax()
    {
        int max = numb - 1;
        for (int j = numb - 2; j >= head; j--)
            if (pq[max] < pq[j])
                max = j;
        exch(pq[max], pq[numb - 1]);
        tail = numb - 1;
        return pq[--numb];
    }
    Item getmin()
    {
        int min = numb - 1;
        for (int j = numb - 2; j >= head; j--)
            if (pq[j] < pq[min])
                min = j;
        exch(pq[min], pq[numb - 1]);
        tail = numb - 1;
        return pq[--numb];
    }
    void print()  const
    {
        for (int y = head; y < numb; y++)
            cout << pq[y] << "   ";
    }
};
bool pass_iscorrect(string p)
{
    if (p.length() != 4)
        return false;
    int isnum = 0;
    for (int i = 0; i < 4; i++)
        if (isdigit(p[i])) isnum++;
    if (isnum == 4 and p[0] != '0')
        return true;
    else return false;
}
int main()
{
    cout << "number 1"<<endl;
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SHOW_FULLSCREEN);
    char curr_dir[MAX_PATH], s;
    HANDLE hFile;
    WIN32_FIND_DATA f_file;
    GetCurrentDirectory(sizeof(curr_dir), curr_dir);
    lstrcat(curr_dir, "\\*.*");
    SYSTEMTIME sys = { 0 };
    if ((hFile = FindFirstFile(curr_dir, &f_file)) == 0)
    {
        cout << "Error";
    }
    do
    {
        FileTimeToSystemTime(&f_file.ftCreationTime, &sys);
        wcout << left << setw(40) << f_file.cFileName << setw(10) << (f_file.nFileSizeHigh * (1 + MAXDWORD)) + f_file.nFileSizeLow;
        wcout << setw(4) << sys.wYear << '.' << setw(2) << sys.wMonth << '.' << setw(4) << sys.wDay << setw(2) << sys.wHour << ':' << setw(2) << sys.wMinute << ':' << setw(2) << sys.wSecond;
        if (f_file.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) cout << setw(3) << 'H';
        if (f_file.dwFileAttributes & FILE_ATTRIBUTE_READONLY) cout << setw(3) << 'R';
        cout << endl;
    } while ((FindNextFile(hFile, &f_file)) != 0);



    cout << "number 2"<<endl;
    setlocale(LC_ALL, "rus");
    PQ<int> p(10);
    cout << "Выполнение сдвига: \n\n";
    for (int i = 0; i < 10; i++)
        p.insert(i + 1);
    p.print();
    p.insert(15);
    p.insert(25);
    p.insert(20);
    cout << endl;
    p.print();
    cout << "\n\nПриоритет: минимальное значение числового параметра: \n\n";
    while (!p.empty())
        cout << p.getmin() << "   ";
    cout << "\n\nПри совпадении параметров LIFO: \n";
    for (int i = 0; i < 5; i++)
        p.insert(i + 1);
    for (int i = 0; i < 5; i++)
        p.insert(i + 1);
    cout << endl;
    p.print();
    cout << "\n\nmin = " << p.getmin() << endl;
    cout << endl;
    p.print();
    cout <<"\n"<< "number 3"<<endl;
    cout << "Input 4-digit passord from 1000 to 9999: ";
    string password;
    cin >> password;
    if (!pass_iscorrect(password))
    {
        cout << "Incorrect password\n";
        return 1;
    }

    int count = 1;
    fstream fout;
    fout.open("pass.txt", ios_base::app);
    if (fout)
    {
        int attempt = 1000;
        while (to_string(attempt) != password)
        {
            fout << attempt << endl;
            attempt++;
            count++;
        }
        cout << "Password " << attempt << " is found in " << count << " attempts\n";
        cout <<"Found password:"<< attempt << endl;
        fout << attempt << endl;
        fout.close();
    }
    else cout << "Error file" << endl;
    return 0;
}
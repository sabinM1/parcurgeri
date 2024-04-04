#include <fstream>
#include <iostream>
#include <cstring>
#include <map>
#include <windows.h>

using namespace std;

struct nod {
    int info;
    nod *urm;
};

nod *L[100001];
int n, m, k, q[100001];
bool viz[100001];


void eroare(short o, int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
    switch(o) {
        case 1: {
            cout<<"EROARE! Numărul "<<x<<" nu aparține intervalului [0, 100000]\n\n";
            exit(0);
        }
        case 2: {
            cout<<"EROARE! Graful este vid! Vă rugăm citiți valori corecte!\n\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            return ;
        }
        case 3: {
            cout<<"EROARE! Vârful selectat, "<<x<<" nu aparține grafului, reîncercați citirea cu date noi.\n\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            return ;
        }
        case 4: {
            cout<<"\nEROARE! Numărul de muchii, "<<x<<" este mai mare decât n*(n-1)/2, reîncercați citirea cu date noi.\n\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            return ;
        }
        default: {
            cout<<"!!! Altă eroare !!!";
            exit(0);
        }
    }
}

void validint(int x) {
    if (x>=0 && x<=100000)
        return ;
    eroare(1, x);
}

void add(int x, int y) {
    nod *p = new nod;
    p->info = y;
    p->urm = L[x];
    L[x]=p;
    p=L[x];
    while(p && p->urm && p->info > p->urm->info) {
        swap (p->info, p->urm->info);
        p=p->urm;
    }
}

void f1() { // citire fisier
    ifstream fin("graf.in");
    fin>>n>>m>>k;
    validint(n);
    validint(m);
    validint(k);
    if (k>n) {
        eroare(3, k);
        k=0;
        fin.close();
        return ;
    }
    if (m > n*(n-1)/2) {
        eroare(4, m);
        k=0;
        fin.close();
        return ;
    }
    int x, y;
    for (int i=1; i<=m; ++i) {
        fin>>x>>y;
        validint(x);
        validint(y);
        add(x, y);
        add(y, x);
    }
    fin.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"\nCitire efectuată cu succes!\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void f2() { // citire consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"\nIntroduceți valorile:\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    cin>>n>>m>>k;
    validint(n);
    validint(m);
    validint(k);
    if (k>n) {
        eroare(3, k);
        k=0;
        return ;
    }
    if (m > n*(n-1)/2) {
        eroare(4, m);
        k=0;
        return ;
    }
    int x, y;
    for (int i=1; i<=m; ++i) {
        cin>>x>>y;
        validint(x);
        validint(y);
        add(x, y);
        add(y, x);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"\nCitire efectuată cu succes!\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void lad(int x) { // lista de adiacenta
    nod *p = L[x];
    while(p) {
        cout << p->info << ' ';
        p = p->urm;
    }
}

int grad(int x) { // gradul unui nod
    int dt = 0;
    nod *p = L[x];
    while(p) {
        ++dt;
        p=p->urm;
    }
    return dt;
}

void dfs(int x) {
    viz[x]=1;
    cout<<x<<' ';
    for (nod *p=L[x]; p!=NULL; p=p->urm)
        if (viz[p->info]==0)
            dfs(p->info);
}

void bfs (int start) {
    int st, dr, x, i;
    q[1]=start;
    viz[start]=1;
    cout<<start<<' ';
    st=dr=1;
    while(st<=dr) {
        x=q[st];
        ++st;
        for (nod *p=L[x]; p!=NULL; p=p->urm)
            if (viz[p->info]==0) {
                viz[p->info]=1;
                q[++dr]=p->info;
                cout<<(p->info)<<' ';
            }
    }
}

void f3(int x) {
    if (n==0 || m==0 || k==0) {
        eroare(2, 0);
        return ;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"Parcurgerea BFS este: ";
    for (int i=0; i<=100000; ++i)
        q[i]=viz[i]=0; // reset
    bfs(x);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout<<"\n\n";
}

void f4(int x) {
    if (n==0 || m==0 || k==0) {
        eroare(2, 0);
        return ;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"Parcurgerea DFS este: ";
    for (int i=1; i<=100000; ++i)
        viz[i]=0; // reset
    dfs(x);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout<<"\n\n";
}

void f() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"Proiect realizat de:\n";
    cout<<"1. Artimon Sebastian\n";
    cout<<"2. Sabin Maxim\n";
    cout<<"3. Tanu Alexandru\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

int main() {
    SetConsoleOutputCP(65001);
    int optiune;
    do {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout<<"Algoritmi de parcurgere\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        cout<<"Opțiuni:\n";
        cout<<"1: citire din fișier a trei valori: n - numărul de vârfuri, m - numărul de muchii și un vârf X; pe următoarele m linii vor fi m muchii, care aparțin unui graf neorientat\n";
        cout<<"2: citire de la consolă a trei valori: n - numărul de vârfuri, m - numărul de muchii și un vârf X; pe următoarele m linii vor fi m muchii, care aparțin unui graf neorientat\n";
        cout<<"3: afișarea vârfurilor vizitate în urma parcurgerii în latime (BFS) din vârful X\n";
        cout<<"4: afișarea vârfurilor vizitate în urma parcurgerii în adâncime (DFS) din vârful X\n";
        //cout<<"optiunea 5: citirea din consola a variabilelor pentru evaluare\n";
        //cout<<"optiunea 6: evaluarea expresiei\n";
        cout<<"0: ieșire\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout<<"\nIntroduceți opțiunea:\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        cin>>optiune;
        cout<<"\n";
        switch(optiune)
        {
        case 1: {
            f1();
            break;
        }
        case 2: {
            f2();
            break;
        }
        case 3: {
            f3(k);
            break;
        }
        case 4: {
            f4(k);
            break;
        }
        case 0: {
            f();
            break;
        }
        default: {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
            cout<<"\nOpțiune invalidă!\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        }
        }
        cout<<"\n";
    }while(optiune);

    return 0;
}


# Import any needed libraries

class Node:
    def __init__(self, info):
        self.info = info
        self.next = None


L = [None] * 100001
n, m, k = 0, 0, 0
q = [0] * 100001
viz = [False] * 100001

def eroare(o, x):
    if o == 1:
        print(f"EROARE! Vârful {x} nu aparține intervalului [1, 100000]\n\n")
        return
    elif o == 2:
        print("EROARE! Graful este vid! Vă rugăm citiți valori corecte!\n\n")
        return
    elif o == 3:
        print(
            f"EROARE! Vârful selectat, {x} nu aparține grafului, reîncercați citirea cu date noi.\n\n")
        return
    elif o == 4:
        print(
            f"\nEROARE! Numărul de muchii, {x} este mai mare decât n*(n-1)/2, reîncercați citirea cu date noi.\n\n")
        return
    else:
        print("!!! Altă eroare !!!")
        exit(0)


def validint(x):
    if 0 < x <= 100000:
        return
    eroare(1, x)


def add(x, y):
    global L
    p = Node(y)
    p.next = L[x]
    L[x] = p
    p = L[x]
    while p and p.next and p.info > p.next.info:
        p.info, p.next.info = p.next.info, p.info
        p = p.next


def f2():
    global n, m, k
    global viz, q, L
    q = [0] * 100001
    viz = [False] * 100001
    L = [None] * 100001
    print("\nIntroduceți valoarea lui n:\n")
    n = int(input())
    validint(n)
    print("\nIntroduceți valoarea lui m:\n")
    m = int(input())
    validint(m)
    if m > n * (n - 1) // 2:
        eroare(4, m)
        k = 0
        return
    print("\nIntroduceți valoarea lui X:\n")
    k = int(input())
    validint(k)
    if k > n:
        eroare(3, k)
        k = 0
        return
    print("\nIntroduceți muchiile, sub forma x y, unde există muchie de la x la y, pe fiecare linie\n")
    for i in range(m):
        x, y = map(int, input().split())
        validint(x)
        validint(y)
        add(x, y)
        add(y, x)
    print("\nCitire efectuată cu succes!\n\n")


def lad(x):
    p = L[x]
    while p:
        print(p.info, end=' ')
        p = p.next


def grad(x):
    dt = 0
    p = L[x]
    while p:
        dt += 1
        p = p.next
    return dt

dfscnp = 1

def dfs(x):
    global dfscnp
    if dfscnp == 0:
        return
    dfscnp = dfscnp - 1
    viz[x] = True
    print(x, end=' ')
    p = L[x]
    while p:
        if not viz[p.info]:
            dfs(p.info)
        p = p.next


def bfs(start):
    cnp = n
    st, dr = 0, 0
    q[0] = start
    viz[start] = True
    print(start, end=' ')
    while st <= dr:
        x = q[st]
        st += 1
        p = L[x]
        while p:
            if not viz[p.info]:
                viz[p.info] = True
                dr += 1
                q[dr] = p.info
                print(p.info, end=' ')
                cnp = cnp - 1
                if cnp == 1:
                    return
            p = p.next


def f3(x):
    global n, m, k
    global viz, q, L
    q = [0] * 100001
    viz = [False] * 100001
    if n == 0 or m == 0 or k == 0:
        eroare(2, 0)
        return
    print("Parcurgerea BFS este: ", end='')
    viz[:100000] = [False] * 100000
    q[:100000] = [0] * 100000
    bfs(x)
    print("\n\n")


def f4(x):
    global n, m, k
    global dfscnp
    global viz
    global q
    global L
    dfscnp = n
    if n == 0 or m == 0 or k == 0:
        eroare(2, 0)
        return
    print("Parcurgerea DFS este: ", end='')
    viz[:] = [False] * 100001
    q = [0] * 100001
    viz = [False] * 100001
    dfs(x)
    print("\n\n")


def f():
    print("Proiect realizat de:\n")
    print("1. Artimon Sebastian\n")
    print("2. Sabin Maxim\n")
    print("3. Tanu Alexandru\n")


while True:
    print("Algoritmi de parcurgere\n")
    print("Opțiuni:\n")
    print("1: citire de la consolă a trei valori: n - numărul de vârfuri, m - numărul de muchii și\n   un vârf X; pe următoarele m linii vor fi m muchii, care aparțin unui graf neorientat\n")
    print("2: afișarea vârfurilor vizitate în urma parcurgerii în latime (BFS) din vârful X\n")
    print("3: afișarea vârfurilor vizitate în urma parcurgerii în adâncime (DFS) din vârful X\n")
    print("0: ieșire\n")
    print("\nIntroduceți opțiunea:\n")
    optiune = int(input())
    print("\n")
    if optiune == 1:
        f2()
    elif optiune == 2:
        f3(k)
    elif optiune == 3:
        f4(k)
    elif optiune == 0:
        f()
        break
    else:
        print("\nOpțiune invalidă!\n\n")
    print("\n")

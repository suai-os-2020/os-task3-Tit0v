#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;
//
// lab3 code should be located here!
//

#define THREAD_COUNT 12
#define SEMAPHORE_COUNT 5

DWORD ThreadID;
HANDLE hThread[THREAD_COUNT];
HANDLE hSemaphore[SEMAPHORE_COUNT];
HANDLE hMutex;

unsigned int lab3_thread_graph_id()
{
    return 14;
}

const char* lab3_unsynchronized_threads()
{
    return "cde";
}

const char* lab3_sequential_threads()
{
    return "pkm";
}

DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);
DWORD WINAPI thread_n(LPVOID);
DWORD WINAPI thread_p(LPVOID);

int lab3_init()
{

    hMutex = CreateMutex(NULL, 0, NULL);
    if (hMutex == NULL) {
        cout << "CreateMutex error: " << GetLastError();
        return 1;
    }

    for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        hSemaphore[i] = CreateSemaphore(NULL, i == 0 ? 1 : 0, 1, NULL);
        if (hSemaphore[i] == NULL) {
            cout << "CreateSemaphore error: " << GetLastError();
            return 1;
        }
    }

    // t0-a
    hThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (hThread[1] == NULL) {
        return GetLastError();
    }

    // wait b
    WaitForSingleObject(hThread[1], INFINITE);
    // close a
    CloseHandle(hThread[1]);

    CloseHandle(hMutex);

    for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        CloseHandle(hSemaphore[i]);
    }

    return 0;
}


DWORD WINAPI thread_a(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "a" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam) {
    hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (hThread[0] == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    WaitForSingleObject(hThread[0], INFINITE);
    hThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (hThread[2] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    ReleaseSemaphore(hSemaphore[3], 1, NULL);
    WaitForSingleObject(hThread[2], INFINITE);
    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    WaitForSingleObject(hSemaphore[3], INFINITE);
    //2
    hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (hThread[3] == NULL) {
        return GetLastError();
    }
    hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (hThread[4] == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    WaitForSingleObject(hThread[4], INFINITE);
    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam) {

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    WaitForSingleObject(hThread[3], INFINITE);
    //3
    hThread[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (hThread[5] == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    ReleaseSemaphore(hSemaphore[4], 1, NULL);
    WaitForSingleObject(hThread[5], INFINITE);
    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    // e
    WaitForSingleObject(hSemaphore[4], INFINITE);
    //4
    hThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[6] == NULL) {
        return GetLastError();
    }
    hThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (hThread[7] == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    WaitForSingleObject(hThread[6], INFINITE);
    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    //h
    WaitForSingleObject(hThread[7], INFINITE);
    //5
    hThread[8] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (hThread[8] == NULL) {
        return GetLastError();
    }
    hThread[9] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
    if (hThread[9] == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    ReleaseSemaphore(hSemaphore[3], 1, NULL);
    ReleaseSemaphore(hSemaphore[4], 1, NULL);
    WaitForSingleObject(hThread[9], INFINITE);
    return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "k" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    //g
    WaitForSingleObject(hSemaphore[3], INFINITE);

    //6
    hThread[11] = CreateThread(NULL, 0, thread_p, NULL, 0, &ThreadID);
    if (hThread[11] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[1], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "k" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[2], 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_n(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "n" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_p(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[0], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "p" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[1], 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "m" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    //g
    WaitForSingleObject(hSemaphore[4], INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[2], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "m" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[0], 1, NULL);
    }
    //k,p
    WaitForSingleObject(hThread[8], INFINITE);
    WaitForSingleObject(hThread[11], INFINITE);

    //6
    hThread[10] = CreateThread(NULL, 0, thread_n, NULL, 0, &ThreadID);
    if (hThread[10] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "m" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    WaitForSingleObject(hThread[10], INFINITE);
    return 0;
}
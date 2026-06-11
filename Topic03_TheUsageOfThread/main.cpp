#include <windows.h>
#include <stdio.h>
#include <time.h>

const int G_N_MATRIX_SIZE = 1000;
const int G_N_THREAD_COUNT = 16;

int g_nMatrixA[G_N_MATRIX_SIZE][G_N_MATRIX_SIZE];
int g_nMatrixB[G_N_MATRIX_SIZE][G_N_MATRIX_SIZE];
int g_nMatrixC[G_N_MATRIX_SIZE][G_N_MATRIX_SIZE];
int g_nMatrixD[G_N_MATRIX_SIZE][G_N_MATRIX_SIZE];

typedef struct tagThreadParam {
    int nThreadId;
    int nStartRow;
    int nEndRow;
} THREAD_PARAM, * PTHREAD_PARAM;

static DWORD WINAPI MatrixMultiplyWorker(LPVOID lpParam)
{
    PTHREAD_PARAM pData = (PTHREAD_PARAM)lpParam;
    if (pData == NULL) return 0;

    for (int i = pData->nStartRow; i < pData->nEndRow; ++i)
    {
        for (int j = 0; j < G_N_MATRIX_SIZE; ++j)
        {
            int nSum = 0;
            for (int k = 0; k < G_N_MATRIX_SIZE; ++k)
            {
                nSum += g_nMatrixA[i][k] * g_nMatrixB[k][j];
            }
            g_nMatrixC[i][j] = nSum;
        }
    }

    return 0;
}

static void InitializeMatrices()
{
    for (int i = 0; i < G_N_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < G_N_MATRIX_SIZE; ++j)
        {
            g_nMatrixA[i][j] = rand() % 100;
            g_nMatrixB[i][j] = rand() % 100;
            g_nMatrixC[i][j] = 0;
            g_nMatrixD[i][j] = 0;
        }
    }
}

int main()
{
	srand(time(NULL)); // Use current time as seed for random generator

    InitializeMatrices();

    printf("Single thread is executing...\n");

    ULONGLONG dwStartSingle = GetTickCount64(); // Get current time

    for (int i = 0; i < G_N_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < G_N_MATRIX_SIZE; ++j)
        {
            int nSum = 0;
            for (int k = 0; k < G_N_MATRIX_SIZE; ++k)
            {
                nSum += g_nMatrixA[i][k] * g_nMatrixB[k][j];
            }
            g_nMatrixD[i][j] = nSum;
        }
    }

    ULONGLONG dwEndSingle = GetTickCount64(); // Get time after single thread execution

    printf("The CPU time is %llums.\n", dwEndSingle - dwStartSingle);

    printf("Multi-thread is executing...\n");

    HANDLE hThreadArray[G_N_THREAD_COUNT] = { NULL };
    THREAD_PARAM stParamArray[G_N_THREAD_COUNT] = { 0 };

    int nRowsPerThread = G_N_MATRIX_SIZE / G_N_THREAD_COUNT;

    ULONGLONG dwStartMulti = GetTickCount64();
    for (int i = 0; i < G_N_THREAD_COUNT; ++i)
    {
        stParamArray[i].nThreadId = i;
        stParamArray[i].nStartRow = i * nRowsPerThread;
        stParamArray[i].nEndRow = (i == G_N_THREAD_COUNT - 1) ? G_N_MATRIX_SIZE : (i + 1) * nRowsPerThread;

        hThreadArray[i] = CreateThread(
            NULL,
            0,
            MatrixMultiplyWorker,   
            &stParamArray[i],
            0,
            NULL
        );
    }

    WaitForMultipleObjects(G_N_THREAD_COUNT, hThreadArray, TRUE, INFINITE);

    ULONGLONG dwEndMulti = GetTickCount64();
    printf("The CPU time is %llums.\n", dwEndMulti - dwStartMulti);

    for (int i = 0; i < G_N_THREAD_COUNT; ++i)
    {
		CloseHandle(hThreadArray[i]);
    }
    return 0;
}
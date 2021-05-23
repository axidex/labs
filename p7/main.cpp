// Sorts.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>

#define N 10000

template <class T>
vector<T> bubble_sort(vector<T> vec, int count = N)
{
    bool flag = true;

    for (int j = 0; j < count; j++)
    {
        int tmp = 0;
        if (!flag)
            break;
        flag = false;
        for (int i = 0; i < count - 1; i++)
        {
            if (vec[i] > vec[i + 1])
            {
                tmp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = tmp;
                flag = true;
            }
        }
    }
    return vec;
}
template <class T>
void heapify(T arr[], int n, int i)
{
    int largest = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

template <class T>
void heapSort(T arr[], int n = N)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify<T>(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {

        swap(arr[0], arr[i]);

        heapify<T>(arr, i, 0);
    }
}

int main()
{
    int *random_h = new int[N];
    int *up_h = new int[N];
    int *down_h = new int[N];

    time_t time1, time2;
    int arr1[N];
    vector<int> random;
    vector<int> up;
    vector<int> down;
    vector<int> res;

    for (int i = 0; i < N; i++)
    {
        up_h[i] = i;
    }
    for (int i = N; i > 0; i--)
    {
        down_h[i] = i;
    }
    for (int i = 0; i < N; i++)
    {
        up.push_back(i);
    }
    for (int i = N; i > 0; i--)
    {
        down.push_back(i);
    }
    for (int i = 0; i < N; i++)
    {
        srand(i);
        arr1[i] = (int)(sin((double)rand()) * N);
    }

    ofstream fout("arr1.txt");
    if (fout)
    {
        fout << N << "\n";
        for (int i = 0; i < N; i++)
            fout << arr1[i] << " ";
        fout.close();
    }
    //-----------------------
    ifstream fin("arr1.txt");
    int len;
    if (fin)
    {
        fin >> len;
        int a = 0;

        while (fin >> a)
        {
            random.push_back(a);
        }
        time1 = clock();

        res = bubble_sort<int>(random);

        time2 = clock();
        cout << ((double)(time2)-time1) / CLOCKS_PER_SEC << endl;

        ofstream fres_bubble_random("random_bubble.txt");
        if (fres_bubble_random)
        {
            fres_bubble_random << N << "\n";
            for (auto el : res)
            {
                fres_bubble_random << el << " ";
            }

            fres_bubble_random.close();
        }
        fin.close();
    }
    //-----------------------
    ifstream fin2("arr1.txt");
    {
        fin >> len;
        for (int i = 0; i < N; i++)
        {
            fin2 >> random_h[i];
        }

        time1 = clock();

        heapSort<int>(random_h, len);

        time2 = clock();
        cout << ((double)(time2)-time1) / CLOCKS_PER_SEC << endl;
        ofstream fres_heap_random("random_heap.txt");
        if (fres_heap_random)
        {
            fres_heap_random << N << "\n";
            for (int i = 0; i < N; i++)
            {
                fres_heap_random << random_h[i] << " ";
            }

            fres_heap_random.close();
        }
        fin2.close();
    }
    //-----------------------
    time1 = clock();

    res = bubble_sort<int>(up);

    time2 = clock();
    cout << ((double)(time2)-time1) / CLOCKS_PER_SEC << endl;
    ofstream fres_bubble_up("up_bubble.txt");
    if (fres_bubble_up)
    {
        fres_bubble_up << N << "\n";
        for (auto el : res)
        {
            fres_bubble_up << el << " ";
        }

        fres_bubble_up.close();
    }
    //-----------------------
    time1 = clock();

    res = bubble_sort<int>(down);

    time2 = clock();
    cout << ((double)(time2)-time1) / CLOCKS_PER_SEC << endl;
    ofstream fres_bubble_down("down_bubble.txt");
    if (fres_bubble_down)
    {
        fres_bubble_down << N << "\n";
        for (auto el : res)
        {
            fres_bubble_down << el << " ";
        }

        fres_bubble_down.close();
    }
    //-----------------------
    time1 = clock();

    heapSort<int>(up_h,N);

    time2 = clock();
    cout << ((double)(time2)-time1) / CLOCKS_PER_SEC << endl;
    ofstream fres_heap_up("up_heap.txt");
    if (fres_heap_up)
    {
        fres_heap_up << N << "\n";
        for (int i = 0; i < N; i++)
        {
            fres_heap_up << up_h[i] << " ";
        }

        fres_heap_up.close();
    }
    //-----------------------
    time1 = clock();

    heapSort<int>(down_h,N);

    time2 = clock();
    cout << ((double)(time2)-time1) / CLOCKS_PER_SEC << endl;
    ofstream fres_heap_down("down_heap.txt");
    if (fres_heap_down)
    {
        fres_heap_down << N << "\n";
        for (int i = 0; i < N; i++)
        {
            fres_heap_down << up_h[i] << " ";
        }

        fres_heap_down.close();
    }
    //-----------------------
    delete[] random_h;
    delete[] up_h;
    delete[] down_h;
    return 0;
}
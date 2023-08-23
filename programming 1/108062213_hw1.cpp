#include<iostream>
#include<ctime>
#include<random>
#include<cstdlib>
#include<cmath>
#include<algorithm>


using namespace std;

int Select(int* , int ,int, int, int);
int Select_Random(int* , int ,int, int);
int partition_random(int* , int, int);
int partition(int*, int, int, int);
void Swap(int*, int*);
void InsertionSort(int *, int, int);
int median(int*, int, int, int);


int main(){
    int n, k;
    int g;
    cin>>n>>k;
    cin>>g;
    srand( time(nullptr) );

    // random in c++11
    const int max = 10000000;
    const int min = 1;
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(min,max);
/*
    int cnt = 20;
    int run_time = 1;
    double total_time_random = 0;
    double total_time_3 = 0;
    double total_time_5 = 0;
    double total_time_7 = 0;
    double total_time_9 = 0;

    cout<<"Start test"<<endl;
    int *testcase_generate = new int[n]();
    int *testcase = new int[n]();
    //generate random testcase
    for(int i = 0; i < n; i++){
        testcase_generate[i] = dis(gen);
    }
    cout<<"finish generate testcase"<<endl;
    while(cnt--){

        //random
        for(int i = 0; i < n; i++){
            testcase[i] = testcase_generate[i];
        }
        clock_t start = clock();
        int ans = testcase[Select_Random(testcase, 0, n-1, k)];
        clock_t end = clock();
        double running_time = (double)(end-start) / CLOCKS_PER_SEC;
        total_time_random += running_time;
        cout<<"(random) "<< run_time <<":"<< " Running Time(clock per second) = "<< running_time<<" Ans: "<<ans<<endl;

        //g = 3
        for(int i = 0; i < n; i++){
            testcase[i] = testcase_generate[i];
        }
        start = clock();
        int ans_3 = testcase[Select(testcase, 0, n-1, k, 3)-1];

        end = clock();
        running_time = (double)(end-start) / CLOCKS_PER_SEC;
        total_time_3 += running_time;
        cout<<"(g=3) "<< run_time <<":"<< " Running Time(clock per second) = "<< running_time<<" Ans: "<<ans_3<<endl;

        //g = 5;
        for(int i = 0; i < n; i++){
            testcase[i] = testcase_generate[i];
        }
        start = clock();
        int ans_5 = testcase[Select(testcase, 0, n-1, k, 5)-1];
        end = clock();
        running_time = (double)(end-start) / CLOCKS_PER_SEC;
        total_time_5 += running_time;
        cout<<"(g=5) "<< run_time <<":"<< " Running Time(clock per second) = "<< running_time<<" Ans: "<<ans_5<<endl;

        //g = 7
        for(int i = 0; i < n; i++){
            testcase[i] = testcase_generate[i];
        }
        start = clock();
        int ans_7 = testcase[Select(testcase, 0, n-1, k, 7)-1];
        end = clock();
        running_time = (double)(end-start) / CLOCKS_PER_SEC;
        total_time_7 += running_time;
        cout<<"(g=7) "<< run_time <<":"<< " Running Time(clock per second) = "<< running_time<<" Ans: "<<ans_7<<endl;

        //g = 9
        for(int i = 0; i < n; i++){
            testcase[i] = testcase_generate[i];
        }
        start = clock();
        int ans_9 = testcase[Select(testcase, 0, n-1, k, 9)-1];
        end = clock();
        running_time = (double)(end-start) / CLOCKS_PER_SEC;
        total_time_9 += running_time;
        cout<<"(g=9) "<< run_time <<":"<< " Running Time(clock per second) = "<< running_time<<" Ans: "<<ans_9<<endl;

        //delete testcase
        

        cout<<"delete all testcase"<<endl;
        run_time++;
    }
    
    cout<<"average running time (random) : "<<total_time_random/20 << endl;
    cout<<"average running time (g = 3) : "<<total_time_3/20 << endl;
    cout<<"average running time (g = 5) : "<<total_time_5/20 << endl;
    cout<<"average running time (g = 7) : "<<total_time_7/20 << endl;
    cout<<"average running time (g = 9) : "<<total_time_9/20 << endl;
    
    delete [] testcase_generate;
    delete [] testcase;
*/


    int *testcase = new int[n]();
    for(int i = 0; i < n; i++){
        cin>>testcase[i];
    }
    // int *testcase_random = new int[n+1]();
    // int *testcase_sort = new int[n+1]();

    // cout<<"success malloc"<<endl;
    //     for(int i = 0; i < n; i++){
    //         testcase_sort[i] = testcase_random[i] = dis(gen);
    //         if(testcase_random[i] > m)    m = testcase_random[i];
    //     }
    //     cout<<"success create testcase"<<endl;
    // for(int i = 0; i < n; i++){
    //     cout<<testcase[i]<<" ";
    // }
    // std::sort(testcase_sort, (testcase_sort)+n);
    // int ans_sort = testcase_sort[k-1];
    int ans = testcase[Select_Random(testcase, 0, n-1, k)-1];
    // int ans_3 = testcase[Select(testcase, 0, n-1, k, 5)-1];
    cout<<ans<<endl;
    // for(int i = 0; i < n; i++){
    //     cout<<testcase[i]<<" ";
    // }
    delete [] testcase;
    // delete [] testcase_random;
    // delete [] testcase_sort;

    return 0;
}


int Select(int *arr, int l, int r, int k, int g){

    int length = r-l+1;
    if(length <= g){
        InsertionSort(arr, l, r);
        return l+k;
    }else{
        int m_idx = median(arr, l, r, g);
        int q = partition(arr, m_idx, l, r);

        if(q-l == k)   return q;
        else if(q-l > k)  return Select(arr, l, q, k, g);
        else    return Select(arr, q+1, r, k-(q-l+1), g);
    }
}

int Select_Random(int *arr, int l, int r, int i){
    if(l==r) return l;
    int q = partition_random(arr, l, r);
    int k = q-l+1;
    if(k == i) return q;
    else if(i < k)  return Select_Random(arr, l, q, i);
    else    return Select_Random(arr, q+1, r, i-k);
}

int partition_random(int *arr, int l ,int r){
    int pivot_pos = (rand()%(r-l))+l;
    Swap(&arr[pivot_pos], &arr[r]);
    int pivot = arr[r];

    int i = l-1;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    i++;
    Swap(&arr[i], &arr[r]);
    return i;
}

int partition(int *arr, int pivot_pos, int l, int r){

    Swap(&arr[pivot_pos], &arr[r]);
    int pivot = arr[r];

    int i = l-1;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    i++;
    Swap(&arr[i], &arr[r]);
    return i;
}

void Swap(int *a, int *b){

    int tmp = *a;
    *a = *b;
    *b = tmp;

}

void InsertionSort(int *arr, int l, int r){
    for (int i = l+1; i <= r; i++) {
        int key = arr[i];
        int j = i;
        while (key < arr[j-1] && j-1 >= l) {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = key;
    }
}

int median(int *arr, int l, int r, int g) {

    int numMedians = (r-l+(g-1))/g;
    int i, subl, subr;
    int medianIdx;
    for(i = 0; i < numMedians; i++) {
        subl = l + i*g;
        subr = subl + (g-1);
        if(subr > r)    subr = r;
        medianIdx = Select(arr, subl, subr, (subr-subl)/2, g);
        Swap(&arr[l+i], &arr[medianIdx]);
    }
    //printf("median %d %d\n", l, r);
    return Select(arr, l, l+numMedians, numMedians/2, g);
}
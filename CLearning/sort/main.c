#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE(a) (sizeof(a) / sizeof(a[0]))
#define SWAP(arr, i, j)  \
    {                    \
        int t  = arr[i]; \
        arr[i] = arr[j]; \
        arr[j] = t;      \
    }

/*************************************************************
 *						  COMMENT                            *
 **************************************************************/

void print_array(int* arr, int n) {
    for (int i = 0; i < n; i++) { printf("%d ", arr[i]); }
    printf("\n");
}

void insertion_sort(int* arr, int n);

void shell_sort(int* arr, int n);

void merge_sort(int* arr, int n);

// int partition1(int* arr, int left, int right);
// int partition2(int* arr, int left, int right);
void quick_sort(int* arr, int n);

void heap_sort(int* arr, int n);

int main(void) {
    int arr[] = {6, 5, 2, 7, 1, 3, 9, 0, 8, 4};
    print_array(arr, SIZE(arr));

    // insertion_sort(arr, SIZE(arr));
    // shell_sort(arr, SIZE(arr));
    // merge_sort(arr, SIZE(arr));
    // printf("%d\n", partition1(arr, 0, 9));
    // printf("%d\n", partition2(arr, 0, 9));
    //quick_sort(arr, SIZE(arr));
    heap_sort(arr, SIZE(arr));

    print_array(arr, SIZE(arr));

    return 0;
}

/******************************************************************
 *                           插入排序                              *
 *******************************************************************/
void insertion_sort(int* arr, int n) {
    int val = 0;
    for (int i = 1; i < n; i++) {
        val   = arr[i];
        int j = i - 1;
        while (j > -1 && arr[j] > val) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = val;

        // debug information
        print_array(arr, n);
    }
}

/******************************************************************
 *                           希尔排序                              *
 *******************************************************************/
void shell_sort(int* arr, int n) {
    int gap = n >> 1;
    int val;
    while (gap) {
        for (int i = gap; i < n; i++) {
            val   = arr[i];
            int j = i - gap;
            while (j > -1 && arr[j] > val) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = val;
        }
        gap >>= 1;

        print_array(arr, n);
    }
}

/******************************************************************
 *                           归并排序                              *
 *******************************************************************/
#define N 10
int temp[N];
void merge(int* arr, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) { temp[k++] = arr[i++]; }
    while (j <= right) { temp[k++] = arr[j++]; }

    for (int i = left; i <= right; i++) { arr[i] = temp[i]; }
}

void m_sort(int* arr, int left, int right) {
    // 闭区间 [left, right]

    // 边界条件
    if (left >= right) return;
    // 递归公式
    // int mid = left + right >> 1;  // 如果 int 只占 2 个字节，可能发生溢出
    int mid = left + (right - left >> 1);
    // 分别排序左右区间
    m_sort(arr, left, mid);
    m_sort(arr, mid + 1, right);
    // merge
    merge(arr, left, mid, right);

    print_array(arr, 10);
}

void merge_sort(int* arr, int n) { m_sort(arr, 0, n - 1); }

/******************************************************************
 *                           快速排序                              *
 *******************************************************************/
// 单向分区
int partition1(int* arr, int left, int right) {
    // 闭区间[left, right]
    int pivot = arr[right];  // 基准值
    int s     = left;        // 下一个小于等于pivot的元素应该放置的位置
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            SWAP(arr, s, i);
            s++;
        }
    }
    // 交换 s 和 right 位置的两个元素
    SWAP(arr, s, right);
    // 返回 pivot(基准值) 所在的位置
    return s;
}

// 双向分区
int partition2(int* arr, int left, int right) {
    int pivot = arr[left];
    int i     = left;
    int j     = right;

    while (i < j) {
        while (i < j && arr[j] >= pivot) { j--; }
        arr[i] = arr[j];
        while (i < j && arr[i] <= pivot) { i++; }
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    return i;
}

void q_sort(int* arr, int left, int right) {
    // 闭区间[left, right]
    // 1. 边界条件
    if (left >= right) return;
    // 2. 递归公式
    // 分区
    int idx = partition2(arr, left, right);

    q_sort(arr, left, idx - 1);
    q_sort(arr, idx + 1, right);
}

void quick_sort(int* arr, int n) {
    // 闭区间[0, n-1]
    q_sort(arr, 0, n - 1);
}

/******************************************************************
 *                           堆排序                              *
 *******************************************************************/
void heapify(int* arr, int i, int len) {
    // arr: 数组
    // i: 根节点的索引
    // len: 堆的范围
    // 前置条件: i的左右子树都是大顶堆
    while (i < len) {
        int lchild = 2 * i + 1;
        int rchild = 2 * i + 2;

        int maxIdx = i;
        if (lchild < len && arr[lchild] > arr[maxIdx]) { maxIdx = lchild; }
        if (rchild < len && arr[rchild] > arr[maxIdx]) { maxIdx = rchild; }
        if (maxIdx == i) { break; /* 根节点就是最大的，退出 */ }
    
        SWAP(arr, i, maxIdx);
        i = maxIdx;
    }
}

void build_heap(int* arr, int n) {
    // 从后往前找第一个非叶子节点
    // lchild(i) = 2i + 1 <= n-1
    // i <= (n-2)/2
    for (int i = (n - 2 >> 1); i >= 0; i--) { heapify(arr, i, n); }
}

void heap_sort(int* arr, int n) {
    // 1. 构建大顶堆
    build_heap(arr, n);
    // 2. 排序
    int len = n;  // 无序区的长度
    while (len > 1) {
        // 交换堆顶元素和无序区的最后一个元素
        SWAP(arr, 0, len - 1);
        // 无序区的长度减一
        len--;
        // 将无序区重新调整成大顶堆
        heapify(arr, 0, len);
    }
}
// .h : 头文件
// 结构体的定义，以及暴露给外界使用的函数(API)的声明

typedef int E;

//动态数组的数据定义
typedef struct
{
	int* elements;		// 元素
	int size;			// 目前大小
	int capacity;		// 总共大小
} vector;

// 创建
vector* vector_create(void);

// 销毁
void vector_destroy(vector* v);

// 扩容
void grow_capacity(vector* v);

// 增加元素
void push_back(vector* v, E val);
#include <stdio.h>

/**
 * @brief declare a pointer int and print its address and value
 * 
 */
void pointer_declare(void) {
    int b = 10;
    int *p = &b;
    printf("Address of b: %p\n", (void*)&b);
    printf("Value of b using pointer: %d\n", *p);
}

/**
 * @brief swap two integers using pointers
 * 
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief sum array of integers using pointer arithmetic
 * 
 */
int sum_array(int *arr) {
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);
    }
    return sum;
}

/**
 * @brief print array of integers using pointer
 * 
 */
void print_array(int *arr) {
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

/**
 * @brief print size of data types using void pointer
 * 
 */
void print_sizeof() {
    void *ptr;
    printf("Size of int: %zu bytes\n", sizeof(*(int *)ptr));
    printf("Size of float: %zu bytes\n", sizeof(*(float *)ptr));
    printf("Size of double: %zu bytes\n", sizeof(*(double *)ptr));
    printf("Size of char: %zu bytes\n", sizeof(*(char *)ptr));
}

/**
 * @brief print a elenment of an integer array using pointer arithmetic
 * 
 */
void print_element(int *arr, int index) {
    int *p;
    p = arr;
    printf("Element at index %d: %d\n", index, *(p + index));
}

/**
 * @brief count elements of an array using pointer arithmetic
 * 
 */
int count_elements(int *arr) {
    int count = 0;
    while (*(arr + count) != '\0') {
        count++;
    }
    return count;
}

/**
 * @brief modify an integer value using pointer
 * 
 */
void modify_value(int *p) {
    *p = 20;
}

/**
 * @brief compare addresses of two elements in an array using pointers
 * 
 */
void compare_addresses(int *arr, int index1, int index2) {
    int *p1 = arr + index1;
    int *p2 = arr + index2;
    if (p1 < p2) {
        printf("Address of element at index %d is less than address of element at index %d\n", index1, index2);
    } else if (p1 > p2) {
        printf("Address of element at index %d is greater than address of element at index %d\n", index1, index2);
    } else {
        printf("Addresses are equal\n");
    }
}

/**
 * @brief string copy using pointers
 * 
 */
void string_copy(char *src, char *dest) {
    while(*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

/**
 * @brief using malloc to allocate memory for an integer array and print its elements (random values)
 * 
 */
void allocate_memory(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // assign random values
    }
    print_array(arr);
    free(arr);
}

/**
 * @brief find maximum element in an integer array using pointers
 * 
 */
int* find_max(int *arr) {
    int size = sizeof(arr) / sizeof(arr[0]);
    int *max = arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *max) {
            max = arr + i;
        }
    }
    return max;
}

/**
 * @brief reverse an integer array using pointers
 * 
 */
void reverse_array(int *arr) {
    int size = sizeof(arr) / sizeof(arr[0]);
    int *start = arr;
    int *end = arr + size - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

/**
 * @brief create a 2D matrix using pointers and print its elements (random values)
 * 
 */
void create_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // assign random values
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * @brief sum two matrices using pointers
 * 
 */
void sum_matrices(int **mat1, int **mat2, int **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(result + i) + j) = *(*(mat1 + i) + j) + *(*(mat2 + i) + j);
        }
    }
}

int add(int a, int b) {return a + b;}
int sub(int a, int b) {return a - b;}
int mul(int a, int b) {return a * b;}
int divi(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        return (int)(NULL);
    }
}
/**
 * @brief using array of function pointers to perform different operations, input the choice of operation
 * 
 */
void perform_operation(int a, int b, char op) {
    int (*operations[4])(int, int) = {add, sub, mul, divi};
    switch(op) {
        case '+':
            printf("Result: %d\n", operations[0](a, b));
            break;
        case '-':
            printf("Result: %d\n", operations[1](a, b));
            break;
        case '*':
            printf("Result: %d\n", operations[2](a, b));
            break;
        case '/':
            printf("Result: %d\n", operations[3](a, b));
            break;
        default:
            printf("Invalid operation\n");
            break;
    }
}

/**
 * @brief create a linked list using pointers and print its elements
 * 
 */
typedef struct Node {
    int data;
    struct Node *next;
} linkedListNode;

/**
 * @brief Use pointers to manipulate NxM dynamic matrices.
 * 
 */
void manipulate_dynamic_matrices(int N, int M) {
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            matrix[i][j] = i + j; // initialization
        }
    }
    // Print the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * @brief Use void pointer to write general swap function for all types.
 * 
 */
void swap_void(void *a, void *b, size_t size) {
    void *temp = malloc(size);
    if (temp) {
        memcpy(temp, a, size);
        memcpy(a, b, size);
        memcpy(b, temp, size);
        free(temp);
    }
}

void main() {
    print("No 11:\n");
    pointer_declare();
    
    print("No 12:\n");
    int x = 5, y = 10;
    swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);

    print("No 13:\n");
    int arr1[] = {1, 2, 3, 4, 5};
    printf("Sum of array: %d\n", sum_array(arr1));

    print("No 14:\n");
    print_array(arr1);

    print("No 15:\n");
    print_sizeof();

    print("No 16:\n");
    print_element(arr1, 2);

    print("No 17:\n");
    printf("Count of elements: %d\n", count_elements(arr1));

    print("No 18:\n");
    int val = 15;
    modify_value(&val);
    printf("Modified value: %d\n", val);

    print("No 19:\n");
    compare_addresses(arr1, 1, 3);

    print("No 20:\n");
    char src[] = "Hello, World!";
    char dest[50];
    string_copy(src, dest);
    printf("Copied string: %s\n", dest);

    print("No 21:\n");
    allocate_memory(5);

    print("No 22:\n");
    int arr2[] = {3, 5, 7, 2, 8};
    int *max = find_max(arr2);
    printf("Maximum element: %d\n", *max);

    print("No 23:\n");
    reverse_array(arr2);
    print_array(arr2);

    print("No 24:\n");
    create_matrix(3, 3);

    print("No 25:\n");
    int rows = 2, cols = 2;
    int **mat1 = (int **)malloc(rows * sizeof(int *));
    int **mat2 = (int **)malloc(rows * sizeof(int *));
    int **result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        mat1[i] = (int *)malloc(cols * sizeof(int));
        mat2[i] = (int *)malloc(cols * sizeof(int));
        result[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = (i + j) * 2;
        }
    }
    sum_matrices(mat1, mat2, result, rows, cols);
    printf("Resultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < rows; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(result[i]);
    }
    free(mat1);
    free(mat2);
    free(result);

    print("No 26 27:\n");
    int a = 20, b = 4;
    perform_operation(a, b, '+');
    perform_operation(a, b, '-');
    perform_operation(a, b, '*');
    perform_operation(a, b, '/');

    print("No 28:\n");
    linkedListNode *head = (linkedListNode *)malloc(sizeof(linkedListNode));
    head->data = 10;
    head->next = (linkedListNode *)malloc(sizeof(linkedListNode));
    head->next->data = 20;
    head->next->next = NULL;
    linkedListNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    free(head->next);
    free(head);

    print("No 29:\n");
    manipulate_dynamic_matrices(3, 4);

    print("No 30:\n");
    int m = 10, n = 20;
    printf("Before swap: m = %d, n = %d\n", m, n);
    swap_void(&m, &n, sizeof(int));
    printf("After swap: m = %d, n = %d\n", m, n);
}
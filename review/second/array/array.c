#include <stdio.h>

/**
 * @brief input an array of integers from the user and sum them up.
 * 
 */
int sum_array() {
    int n, i, sum = 0;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    return sum;
}

/**
 * @brief find the maximum element in an array of integers.
 * 
 */
int find_max(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/**
 * @brief find the odd and even numbers in an array of integers.
 * 
 */
void find_odd_even(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Odd numbers: ");
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\nEven numbers: ");
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

/**
 * @brief reverse an array of integers.
 * 
 */
void reverse_array(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    int temp;
    for (int i = 0; i < n / 2; i++) {
        temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

/**
 * @brief find the maximum element and its index in an array of integers.
 * 
 */
void find_max_and_index(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = arr[0];
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }
    printf("Maximum element: %d\n", max);
    printf("Index of maximum element: %d\n", index);
}

/**
 * @brief find if an x integer is present in an array of integers.
 * 
 */
int find_element(int *arr, int x) {
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief find the average of elements in an array of integers.
 * 
 */
float find_average(int *arr) {
    int sum = 0;
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (float)sum / n;
}

/**
 * @brief combine two arrays of integers into one.
 * 
 */
void combine_arrays(int *arr1, int *arr2, int *result) {
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    *result = malloc((n1 + n2) * sizeof(int));
    for (int i = 0; i < n1; i++) {
        result[i] = arr1[i];
    }
    for (int i = 0; i < n2; i++) {
        result[n1 + i] = arr2[i];
    }
}

/**
 * @brief sort an array of integers in ascending order.
 * 
 */
void sort_array(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
            i = -1;
        }
    }
}

/**
 * @brief remove an element at a given index from an array of integers.
 * 
 */
void remove_element(int *arr, int index) {
    int n = sizeof(arr) / sizeof(arr[0]);
    if (index < 0 || index >= n) {
        printf("Invalid index\n");
        return;
    }
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

/**
 * @brief insert an element at a given index in an array of integers.
 * 
 */
void insert_element(int *arr, int index, int value) {
    int n = sizeof(arr) / sizeof(arr[0]);
    if (index < 0 || index > n) {
        printf("Invalid index\n");
        return;
    }
    for (int i = n; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
}

/**
 * @brief find which elements are most frequent in an array of integers.
 * 
 */
int find_most_frequent(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = 0, max_count = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            index = i;
        }
    }
    return arr[index];
}

/**
 * @brief remove duplicate elements from an array of integers.
 * 
 */
void remove_duplicates(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    int *temp = malloc(n * sizeof(int));
    int j = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int k = 0; k < j; k++) {
            if (arr[i] == temp[k]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[j++] = arr[i];
        }
    }
    memcpy(arr, temp, j * sizeof(int));
    free(temp);
}

/**
 * @brief reverse every group of 3 elements in an array of integers.
 * 
 */
void reverse_group_of_3(int *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i += 3) {
        if (i + 2 < n) {
            int temp = arr[i];
            arr[i] = arr[i + 2];
            arr[i + 2] = temp;
        }
    }
}

/**
 * @brief sum of even elements in an array of integers.
 * 
 */
int sum_of_even_elements(int *arr) {
    int sum = 0;
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

/**
 * @brief sum of diagonal elements in a 3x3 matrix.
 * 
 */
int sum_diagonal_elements_matrix_3x3(int matrix[3][3]) {
    int sum = 0;
    for(int i = 0; i < 3; i++) {
        sum += matrix[i][i];
    }
    return sum;
}

/**
 * @brief sum of secondary diagonal elements in a 3x3 matrix.
 * 
 */
int sum_secondary_diagonal_matrix_3x3(int matrix[3][3]) {
    int sum = 0;
    int n = 3;
    for(int i = 0; i < n; i++) {
        sum += matrix[i][n - 1 - i];
    }
    return sum;
}

/**
 * @brief check symmatricity of a matrix.
 * 
 */
int check_symmetric_matrix(int **matrix) {
    int n_rows = sizeof(matrix) / sizeof(matrix[0]);
    int n_cols = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    if (n_rows != n_cols) {
        return -1;
    }
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return -1;
            }
        }
    }
    return 0;
}

/**
 * @brief sum 2 matrices 3x3.
 * 
 */
void sum_matrices_3x3(int matrix1[3][3], int matrix2[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

/**
 * @brief multiply 2 matrices 3x3.
 * 
 */
void multiply_matrices_3x3(int matrix1[3][3], int matrix2[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {

    printf("No 11: Sum array = %d\n", sum_array());
    
    int arr1[] = {1, 3, 5, 7, 9, 5, 3, 1, 5};
    printf("No 12: Max element = %d\n", find_max(arr1));

    printf("No 13: Odd and Even elements:\n");
    find_odd_even(arr1);

    printf("No 14: Reversed array = ");
    reverse_array(arr1);
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("No 15:\n");
    find_max_and_index(arr1);

    int x = 7;
    int index = find_element(arr1, x);
    if (index != -1) {
        printf("No 16: Element %d found at index %d\n", x, index);
    } else {
        printf("No 16: Element %d not found\n", x);
    }
    printf("No 17: Average = %.2f\n", find_average(arr1));

    int arr2[] = {2, 4, 6, 8};
    int combined[sizeof(arr1) / sizeof(arr1[0]) + sizeof(arr2) / sizeof(arr2[0])];
    combine_arrays(arr1, arr2, combined);
    printf("No 18: Combined array = ");
    for (int i = 0; i < sizeof(combined) / sizeof(combined[0]); i++) {
        printf("%d ", combined[i]);
    }
    printf("\n");

    sort_array(arr1);
    printf("No 19: Sorted array = ");
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    remove_element(arr1, 2);
    printf("No 20: Array after removing element at index 2 = ");
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]) - 1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    insert_element(arr1, 2, 10);
    printf("No 21: Array after inserting 10 at index 2 = ");
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("No 22: Most frequent element = %d\n", find_most_frequent(arr1));

    remove_duplicates(arr1);
    printf("No 23: Array after removing duplicates = ");
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    reverse_group_of_3(arr1);
    printf("No 24: Array after reversing every group of 3 elements = ");
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("No 25: Sum of even elements = %d\n", sum_of_even_elements(arr1));
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("No 26: Sum of diagonal elements = %d\n", sum_diagonal_elements_matrix_3x3(matrix));

    printf("No 27: Sum of secondary diagonal elements = %d\n", sum_secondary_diagonal_matrix_3x3(matrix));

    // Symmetric matrix check
    int *sym_matrix[3];
    int row0[] = {1, 2, 3};
    int row1[] = {2, 4, 5};
    int row2[] = {3, 5, 6};
    sym_matrix[0] = row0;
    sym_matrix[1] = row1;
    sym_matrix[2] = row2;
    if (check_symmetric_matrix(sym_matrix) == 0) {
        printf("No 28: The matrix is symmetric\n");
    } else {
        printf("No 28: The matrix is not symmetric\n");
    }

    int matrix1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int matrix2[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    int result[3][3];

    sum_matrices_3x3(matrix1, matrix2, result);
    printf("No 29. Sum of matrices:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    multiply_matrices_3x3(matrix1, matrix2, result);
    printf("No 30. Product of matrices:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
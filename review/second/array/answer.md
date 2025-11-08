1. Mảng là một tập hợp các phần tử cùng kiểu dữ liệu với kiểu dữ liệu của mảng, các phần tử được phẩn bổ bộ nhớ liên tiếp nhau. Một mảng sẽ chiếm một bộ nhớ tương đương với số lượng phần tử * kiểu dữ liệu của mảng đó. Các phần tử có số thứ tự (index) tương ứng với vị trí của chúng trong mảng, số thứ tự này sẽ tương ứng với số thứ tự vị trí địa chỉ của chúng trong vùng nhớ của mảng.
2. Để khai báo mảng 1 chiều, ta cần khai báo đủ:
- Kiểu dữ liệu
- Tên mảng
- Số lượng phần tử trong mảng
Ví dụ:
```
int arr[5];
int arr[5] = {1, 2, 3, 4, 5};
int arr[5] = {1, 2};
int arr[]  = {1, 2, 3, 4, 5};
```
3. Kích thước của mảng được xác định vào:
- Thời điểm biên dịch (compile time) đối với mảng tĩnh.
- Trong quá trình chạy (runtime) đối với mảng động.
4. Tên mảng chính là con trỏ trỏ tới phần tử đầu tiên của mảng. Tên mảng không thể bị thay đổi. Tên mảng có thể được coi là một con trỏ trong một biểu thức, nhưng nó không phải là một biến con trỏ thực sự.
5. arr[i] và *(arr + i) là 2 cách truy cập tương đương nhau để truy cập vào giá trị của một phần tử mảng. arr[i] truy cập vào giá trị của phần tử thứ i trong mảng, trong khi *(arr + i) truy cập vào giá trị của vùng nhớ phần tử i khi di chuyển con trỏ arr (vị trí vùng nhớ của phần từ đầu tiên) đi i lần.
6. Để tính toán số lượng phần tử trong một mảng, ta dùng công thức sau:
sizeof(arr)/sizeof(arr[0])
ví dụ: 
```
int arr[10];
int elements = sizeof(arr)/sizeof(arr[0]);
```
Giải thích:
- int có giá trị 4 bytes -> sizeof(arr) là tổng kích thước của arr = 10 * 4 = 40 bytes.
- kích thước của phần tử đầu tiên, aka sizeof(arr[0]) sẽ là sizeof(int) -> 4 bytes.
- kết quả của phép chia sizeof(arr)/sizeof(arr[0]) sẽ là 40 / 4 = 10 phần tử trong mảng.
7. Sự khác nhau giữa mảng tĩnh và mảng động:
- Mảng tĩnh:
    - Phẩn bổ bộ nhớ trong quá trình biên dịch.
    - Cú pháp: ví dụ int arr[5]; int arr[1] = {0, 1}; ...
    - Không thể thay đổi kích thước sau khi khai báo.
    - Vòng đời tuần theo quy định scope của C (global, local).
    - Tốc độ cao vì được phân bổ sẵn.
    - An toàn cao, biến tự động được chương trình giải phóng.
- Mảng động:
    - Phẩn bộ bộ nhớ trong quá trình chạy, sử dụng vùng nhớ heap.
    - Cú pháp thông qua calloc, malloc, ... Ví dụ: int *arr = malloc(n * sizeof(int));
    - Có thể thay đổi kích thước (thông qua calloc, malloc, ...).
    - Vòng đời tồn tại tới khi nào gọi hàm free().
    - Tốc độ chậm hơn vì cần phân bổ bộ nhớ tại thời điểm đó.
    - Có thể gây ra memory leak nếu không sử dụng cẩn thận.
Cả hai đều có thể được truy cập ngoài phạm vi scope local nếu sử dụng con trỏ để truy cập, tuy nhiên mảng tĩnh sẽ bị giải phóng khỏi bộ nhớ sau khi hàm kết thúc, con trỏ truy cập vào mảng tĩnh sẽ có giá trị là NULL sau thời điểm mảng tĩnh được giải phóng.
8. Một số sự khác nhau giữa truyền biến và truyền mảng:
- Truyền biến bình thường:
    - Giá trị truyền là giá trị được copy, không phải giá trị gốc.
    - Thay đổi giá trị biến mới sau khi truyền biến sẽ không ảnh hưởng tới giá trị của biến gốc.
- Truyền mảng:
    - Khi truyền mảng, chỉ có địa chỉ của phần tử đầu tiên (tên hàm chính là một con trỏ trỏ tới địa chỉ của phần tử đầu tiên) là được truyền, không phải toàn bộ mảng. 
    - Giá trị truyền là giá trị tham chiếu (thông qua con trỏ).
    - Thay đổi giá trị trong mảng mới sẽ thay đổi cả giá trị của mảng cũ, vì tất cả các mảng được truyền đều chia sẻ chung 1 địa chỉ với mảng gốc.
9. Mảng 2 chiều trong C được lưu trữ trong bộ nhớ theo thứ tự theo hàng (row-major order). Các phần từ trong hàng đầu tiên sẽ được lưu trữ liên tiếp nhau, sau đó sẽ lưu trữ tới phần tử của hàng tiếp theo và tiếp tục như vậy.
10. Không thể gán arr1 = arr2 vì 2 mảng này là 2 khu vực nhớ khác nhau, không phải là biến mà là địa chỉ cố định. Vì vậy không thể gán trực tiếp cho nhau. Ta phải copy hoặc set giá trị của từng phần tử của mảng thứ hai giống với mảng thứ nhất nếu muốn giá trị giống nhau (với điều kiện số lượng phần từ bằng nhau).

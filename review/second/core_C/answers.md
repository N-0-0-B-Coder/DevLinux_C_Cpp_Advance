1. Typedef dùng để định nghĩa một kiểu dữ liệu mới, tuy nhiên cung cấp thêm alias cho kiểu dữ liệu này để phục vụ cho việc đơn giản hóa khai báo biến theo kiểu dữ liệu mới, tăng việc đọc hiểu và porting code.
2. Nên so sánh hiệu của chúng với một giá trị rất nhỏ (epsilon). Vì với kiểu số thực (floating-point) như float hoặc double, các giá trị trên C thường bao gồm sai số làm tròn do việc biểu diễn nhị phân (binary representation). Kể cả khi 2 giá trị này nhìn có vẻ bằng nhau, nhưng thực chất giá trị nhị phân của chúng sẽ sai khác nhau với một giá trị rất nhỏ. Toán tử "==" sẽ so sánh giá trị bằng nhau giữa 2 số nên toán tử này sẽ không đúng với trường hợp này (vì có sai số).
3. Macro là một chỉ thị tiền xử lý (ví dụ #define) thực hiện thay thế phần nội dung mã trước khi biên dịch. Khi đó, tất cả các macro trong đoạn code sẽ được thay thế bằng nội dung của nó. Các ứng dụng điển hình như: Định nghĩa các hằng số, định nghĩa các đoạn mã hoặc các điều kiện biên dịch (ví dụ #if ... #endif).
4. Mảng con trỏ hàm là một tập hợp các con trỏ, mỗi con trỏ trong mảng này là một con trỏ hàm, các con trỏ hàm này có thể được trỏ tới địa chỉ của một hàm với các tham số đã được định nghĩa kiểu dữ liệu tương ứng với con trỏ hàm trỏ tới. Ví dụ của con trỏ hàm:
```
#include <stdio.h>
int add(int a, int b) {return a + b;}
int sub(int a, int b) {return a - b;}
int mul(int a, int b) {return a * b;}
int divi(int a, int b) {
    if(b == 0) {return (int)(NULL);}
    else return a / b;
}
int main(void) {
    int (*operation[4])(int, int) = {add, sub, mul, divi};
    int x = 5, y = 10;
    printf("Add: %d\n", operation[0](x, y));
    printf("Sub: %d\n", operation[1](x, y));
    printf("Mul: %d\n", operation[2](x, y));
    printf("Div: %d\n", operation[3](x, y));
    return 0;
}
```
5. Sự khác biệt giữa const và #define:
- const:
    - Được xử lý trong quá trình biên dịch.
    - Có kiểu dữ liệu.
    - Được phân bổ vùng nhớ riêng cho const.
    - Scope theo quy tắc của C (global, local).
    - Hiển thị được trong quá trình debug.
- #define
    - Chỉ thị tiền xử lý (trước biên dịch).
    - Không có kiểu dữ liệu.
    - Được lưu trong vùng nhớ .text cùng với mã nguồn.
    - Scope chỉ global.
    - Không thể hiển thị trong debug.
6. Hàm __inline__ gợi ý cho trình biên dịch chèn mã hàm trực tiếp tại nơi gọi.
- Lợi thế:
    - Nhanh, không cần phải gọi hàm.
    - Có thể sử dụng cho các hàm nhỏ và xài thường xuyêm
- Bất lợi:
    - Tăng kích thước mã.
    - Compiler có thể bỏ qua __inline__ trong một số trường hợp.
7. month = 1 là một phép gán, và trong trường hợp này nó sẽ luôn luôn cho kết quả là true nên điều kiện sẽ luôn rơi vào trường hợp true và in ra "January".
8. 
```	
void strcpy(char *des, const char *src) {
    while (*src) {
        *des++ = *src++;
    }
    *des = '\0';
}
```
9. Chương trình này sẽ in ra từ 0 đến 255 và lặp lại vô hạn. Vì unsigned char có giá trị là 8 bit không dấu, giá trị có độ lớn từ 0-255. Tuy nhiên điều kiện for là c < 999 nhưng c không bao giờ lớn hơn được 999 nên vòng lặp for sẽ không bao giờ kết thúc.
10. Hàm này sẽ lấy giá trị b chia a và trả về kết quả là phần nguyên của thương. Hàm không có điều kiện xử lý khi a == 0. Nếu a == 0 chương trình sẽ bị crash.
11. Chương trình sau in ra dãy số 9876543210. Vì --i sẽ thực hiện trừ i xuống 1 đơn vị trước khi sử dụng i để thực hiện đoạn mã nên vòng lặp while đầu tiên i sẽ được tính là giá trị 9. Ở vòng lặp với giá trị i lúc đó là 1, vì giá trị vẫn chưa phải 0 nên vẫn vào được trong vòng lặp, sau đó được giảm đi 1 đơn vị còn 0 nên vẫn in ra giá trị 0.
12. Chương trình sẽ in ra giá trị từ 10 đến 0, sau đó lặp lại việc in từ giá trị 4,294,967,296 về 0 vô hạn. Vì tại thời điểm khi i = 0, vòng lặp for vẫn thỏa điều kiện chạy vòng lặp, và sẽ thực hiện giảm 1 đơn vị của i để tiếp tục vòng lặp tiếp theo. Tuy nhiên vì i được khai báo giá trị unsigned int nên khi lùi giá trị của 0 về 1 đơn vị thì i sẽ tiến ngược về giá trị lớn nhất của unsigned int là 4,294,967,296; giá trị này vẫn thỏa điều kiện của vòng lặp for là >= 0 nên vòng lặp. Tới khi i có giá trị = 0 thì sẽ lại xảy ra trường hợp như trên.
13. Hàm vẫn chạy, nhưng sẽ có trường hợp bị sai như sau:
-  Trong quá trình thực hiện phép công với char, ngôn ngữ C sẽ ép kiểu dữ liệu về int để tính toán, sau đó ép trả về char. Tuy nhiên trong trường hợp kết quả vượt quá 255, giá trị cuối cùng sẽ bị overflow và quay ngược lại (ví dụ 100 + 200 sẽ thành 300 % 256 = 44), gây nên các hành vi bất thường.
- Ngoài ra khi ép kiểu từ int (32 bit) về unsigned char (8 bit), giá trị sẽ bị cắt về 8 bit nên sẽ xuất hiện các kết quả sai khác.
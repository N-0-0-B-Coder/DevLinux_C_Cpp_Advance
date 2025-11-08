1. Bitwise.c
2. Bitwise.c
3. Bitwise.c
4. Bitwise.c
5. Bitwise.c
6. Bitwise.c
7. Bitwise.c
8. Bitwise.c
9. Bitwise.c
10. Bitwise.c
11. Bitwise.c
12. Bitwise.c
13. Bitwise.c
14. Bitwise.c
15. Không
16. 
Cách hoạt động của hàm:
- Khai báo 3 biến:
    - Biến integer g, giá trị 0.
    - Biến integer h, giá trị 2 với từ khóa static (vẫn tồn tại và lưu giá trị sau khi hàm kết thúc).
    - Con trỏ i kiểu char, giá trị NULL (không lưu trữ địa chỉ nào).
- Cấp phát động cho i một ô nhớ với độ lớn bằng 20 lần kích thước kiểu char.
- Kiểm tra điều kiện i không bằng NULL (i đã được cấp địa chỉ ô nhớ). Nếu thỏa điều kiện thì giải phóng ô nhớ của i.
Vị trí cấp phát của các biến trong ví dụ:
- Biến a, b: vùng nhớ uninitialized data.
- Hằng c: vùng nhớ initialized data.
- Biến g, h: vùng nhớ stack.
- Con trỏ i: vùng nhớ stack. Ô nhớ được cấp phát động cho i: vùng nhớ heap.
17. Initialized data
18. Sẽ bị out of memory vì memory leak.
19. Đoạn mã thiếu phần in ra *p và thiếu phần giải phóng con trỏ p. Sử dụng hàm printf để in ra "Hello".
20. 
- Biến a, b, c, g được lưu trong vùng nhớ initialized data.
- Biến d được lưu trong vùng nhớ uninitialized data.
- Biến h và i được lưu trong vùng nhớ stack.
21. Không
22. 
- Con trỏ S1 chưa được khởi tạo giá trị ban đầu, dễ gây ra lỗi.
- Logic đoạn code *dst++ = *s1 bị sai.
- Không cần sử dụng con trỏ S1 trung gian.
23. Không giải phóng p, tiềm ẩn nguy cơ memory leak.
24. Có
25. 
- Biến a, b, c lưu trong initialized data
- Biến d lưu trong stack
26. Không có điều kiện kết thúc đệ quy, sẽ gây stack overflow.
27. Không. Vì con trỏ p đã được gán địa chỉ của a, vì vậy khi con trỏ p tiến hành thay đổi giá trị phần tử [0] thì giá trị của a cũng sẽ thay đổi.
28. Chuỗi str[] là biến local, vì vậy sau khi kết thúc hàm sẽ không còn biến này nữa, dẫn tới hàm printf sẽ không hiển thị gì cả (NULL).
29. 
- Kết quả 1 2 3
- Nếu bỏ từ khóa static, kết quả sẽ là 1 1 1
- Biến count được lưu ở vùng nhớ initialized data
30. Code này không biến dịch được, vì x với từ khóa register được lưu trong thanh ghi CPU, không phải trên ram. Vì thế x không có địa chỉ nên hàm printf địa chỉ sẽ bị lỗi: address of register variable ‘x’ requested.
31. 8 bytes và 5 bytes
32. 8
33. 12 bytes
34. #pragma pack(1) sẽ không có padding và sắp xếp theo từng byte. sizeof(struct B) sẽ là 7 bytes.
35. 16 bytes
36. C4
37. 8 bytes
38. 
- Litte-endian: 78 56 34 12
- Big-endian: 12 34 56 78
39. 8 bytes
40. 
- flag: 5, mode: 25, value: 171
- trên big-endian, MSB và LSB sẽ đảo ngược lại, vì vậy bitfield sẽ bắt đầu từ vị trí khác với litte-endian.
- vì tổng số bit của struct bitfield là 16 bit, raw với kiểu dữ liệu short là 2 byte (16 bit) và kiểu dữ liệu Data là union, vì vậy vùng nhớ của bitfield và raw sẽ trùng lên nhau, dẫn tới việc các biến bitfield sẽ đọc giá trị từ các bit tương ứng của biến raw.
41. 
- 2 bytes
- Struct bits trong union có các biến với kiểu dữ liệu int. Trong một số compiler sẽ lấy int (4 bytes) làm chuẩn để sắp xếp, từ đó union sẽ là 4 bytes và sizeof(packet) sẽ là 8 bytes hoặc 5 bytes nếu có từ khóa #pragma pack(1).
42. 
- 1 byte
- Vì 2 struct này cùng nằm trong 1 union, và 2 stuct này có cùng độ lớn là 1 byte.
- Có
43. 
- EN=0, MODE=1, CLK=11
- ctrl.bits và ctrl.reg là 2 thành phần trong một union và chúng có độ lớn bằng nhau, vì vậy chúng chia sẻ chung một vùng nhớ, dẫn đến ảnh hưởng trực tiếp tới nhau.
- 
```
typedef union {
    struct {
        unsigned int CLK  : 4;
        unsigned int MODE : 2;
        unsigned int EN   : 1;
        unsigned int RSV  : 1;
    } bits;
    unsigned char reg;
} CTRL_REG
```
44. 
- 2 bytes
- len=938, type=6, crc=5
- Trên một số compiler ARMCC, thứ tự sắp xếp bitfield (MSB first) sẽ khác với GCC (LSB first) vì vậy giá trị sẽ có thể khác nhau.
1. Có các phân đoạn vùng nhớ sau:
   - Stack (RAM): 
     - Lưu biến local, tham số hàm, địa chỉ trả về.
     - Tăng giảm kích thước tự động khi hàm đuợc gọi.
   - Heap (RAM):
     - Cấp phát động biến thông qua các hàm như malloc, calloc, alloc.
     - Tăng giảm kích thước khi có cấp phát động biến, không tự động giảm kích thước.
     - Giải phóng biến thủ công thông qua hàm free(). Heap giảm kich thước sau khi biến đuợc giải phóng.
   - Initialize data (.data) (RAM):
     - Chứa biến global / static đã khởi tạo khác 0.
   - Uinitialize data (.bss) (RAM):
     - Chứa biến global / static chưa khởi tạo hoặc khởi tạo = 0.
   - Text (.rodata) (ROM):
     - Chứa hằng số: Biến const toàn cục, code instructions.
     - Chỉ đọc (read-only).
2. Lý do phải chia ra vùng .data và .bss:
   - Để quản lý dữ liệu hiệu quả, tách biệt dữ liệu tĩnh, động, mã lệnh, và biến tạm thời.
   - Tối ưu dung lượng file thực thi và tăng tốc khởi động chương trình.
     - .data: cần lưu giá trị khởi tạo thật.
     - .bss: không cần lưu giá trị, chỉ cần biết giá trị kích thước.
   - Khi load chương trình:
     - .data: copy từ file vào RAM
     - .bss: chỉ cần fill kích thước cần chiếm giữ vào RAM.
3. Biến toàn cục không khởi tạo nằm ở .bss segment. Lý do không có giá trị khởi tạo. Khi chương trình chạy, biến sẽ đuợc zero-fill.
4. Biến có giá trị 0 coi như chưa khởi tạo, được lưu ở .bss. Biến có giá trị 10 đã khởi tạo được lưu ở .data.
5. Khi chương trình gọi hàm đệ quy nhiều lần, vùng nhớ stack bị ảnh hưởng nhiều nhất, vì:
   - Mỗi lần gọi hàm, chương trình cần tạo stack frame mới. Với mỗi stack frame, các biến local, return address sẽ được lưu, dẫn đến stack segment sẽ tăng thêm.
6. Biến const thường nằm trong .rodata thay vì .data vì:
   - const không được phép thay đổi.
   - Compiler sẽ ưu tiên đặt vào vùng read-only giúp bảo vệ và tiết kiệm RAM. Vùng read-only cụ thể nhất chính là .rodata.
7. Nếu muốn dữ liệu tồn tại suốt vòng đời chương trình, nên đặt ở:
   - .data hoặc .bss vì sẽ không bị xóa trong quá trình chạy chương trình.
   - có thể lưu ở heap nếu trong quá trình chạy không free.
8. .bss không chiếm nhiều dung lượng trong file .bin nhưng chiếm RAM khi chạy vì:
   - File .bin không lưu dữ liệu .bss. File .bin chỉ lưu kích thước .bss và địa chỉ load.
   - Khi chương trình chạy, OS sẽ cấp RAM cho vùng .bss này để zero-fill giá trị cho các biến chưa khởi tạo hoặc khởi tạo giá trị 0.
9. Khi hàm kết thúc, nhưng biến static trong hàm đó vẫn được giữ giá trị thì kích thuớc stack không bị ảnh hưởng gì, vì với từ khóa static thì scope cuủ biến đã trở thành global và được lưu trữ trong .bss hoặc .data segment (tùy thuộc vào việc biến đã được khởi tạo hay chưa), không đuợc lưu ở stack như biến local.
10. Memory Leak là tình trạng hệ thống không đủ bộ nhớ để cấp phát cho heap/stack segment trong quá trình chuơng trình hoạt động, xảy ra khi cấp phát động biến trên vùng heap nhưng không giải phóng biến bằng free() khi không còn sử dụng, dẫn tới việc hệ thống không còn đủ bộ nhớ để cấp phát động cho heap hoặc cấp tự động cho vùng stack khi gọi hàm, dẫn đến lỗi này. Cách debug:
  - Sử dụng Valgrind
  - Sử dụng AddressSanitizer
  - Theo dõi thủ công quy trình cấp phát động/free trong quá trình viết code.
11. Stack overflow là tình trạng bộ nhớ stack không đủ để cấp phát cho stack frame trong quá trình chương trình hoạt động.
Stack overflow xảy ra khi:
  - Đệ quy vô hạn hoặc số lần đệ quy quá nhiều
  - Biến local quá lớn
  - Stack size không đủ
Cách debug:
  - Sử dụng GDB backtrace.
  - Tăng stack size
  - Tối ưu số lần đệ quy
12. Lỗi Segmentation Fault xảy ra khi truy cấp vào vùng nhớ không hợp lệ (NULL hoặc ngoài giới hạn vùng nhớ), một số trường hợp truy cập để ghi vào vùng nhớ read-only.
Cách debug:
  - Sử dụng GDB backtrace.
  - Kiểm tra pointer có hợp lệ không (khác NULL) trước khi tiếp tục công việc.
13. Lỗi Stack Smashing xảy ra khi vùng stack bị tràn ghi đè lên địa chỉ return.
Cách Compiler phát hiện bằng cơ chế Canary như sau:
  - Compiler chèn giá trị bảo vệ trước return address.
  - Kiểm tra địa chỉ return khi hàm kết thúc.
  - Huỷ bỏ quá trình biên dịch nếu bị thay đổi.
14. Heap Corruption xảy ra khi:
  - Khi ghi đè vùng nhớ cấp phát động (malloc/alloc ...)
  - Double free
Cách phát hiện bằng AddressSanitizer:
  - AddressSanitizer kiểm tra và báo lỗi chi tiết tại dòng code gây lỗi
15. Dangling Pointer là tình trạng con trỏ trỏ về vùng nhớ đã bị giải phóng.
Dangling Pointer nguy hiểm vì tạo ra hoạt động bất thường (Undefined behavior) gây crash ngẫu nhiên và khó debug.
Cách khắc phục Dangling Pointer: Đặt con trỏ về NULL sau khi đã giả phóng vùng nhớ.
16. Khi nào dùng AddressSanitizer thay vì Valgrind:
  - AddressSanitizer hoạt động trong quá trình biên dịch, có thể tích hợp vào quá trình build.
  - Tốc độ cao hơn valgrind.
  - AddressSanitizer thích hợp cho quá trình dev, valgrind thích hợp cho quá trình test.
Tóm lại: 
  - AddressSanitizer thích hợp trong quá trình dev, làm việc với command interface, build.
  - Valgrind thích hợp khi có .bin file, dùng cho quá trình chạy thử chương trình.
17. Wild pointer (con trỏ hoang dã) là con trỏ khai báo mà chưa được gán địa chỉ hợp lệ, đang trỏ vào vùng nhớ ngẫu nhiên.
Wild pointer dễ tạo ra hoạt động bất thường vì có thể ghi lung tung phá heap/stack, dẫn tới crash ngẫu nhiên.
Cách khắc phục: Với con trỏ chưa gán địa chỉ, cần gán giá trị NULL cho con trỏ.
18. Chương trình có một số lỗi sau:
  - p là wild pointer, đang trỏ đến địa chỉ rác. 
  - Khi truyền p vào myfunction() thì ta đang thay đổi giá trị của p tại địa chỉ ngẫu nhiên, có thể làm hỏng giá trị ở các vùng nhớ ngẫu nhiên gây crash hoặc segment fault.
19. a và b nằm trên .bss.
    c nằm trên .rodata vì "I am a string" là một hằng số string.
    d và c_frame là parameter của hàm, nằm trong stack frame.
    f nằm trong stack frame, nhưng vùng địa chỉ truyền vào f chưa biết ở đâu (phụ thuộc vào vùng của con trỏ truyền vào).
    g là biến local nằm trên stack.
    h là biến trong hàm nhưng kèm từ khoá static và có khởi tạo giá trị. Suy ra h là biến global và được đặt ở vùng nhớ .data.
    i là biến con trỏ local nằm trong stack, tuy nhiên sau khi được gán địa chỉ bằng cấp phát động, i sẽ chứa địa chỉ ở vùng heap. Vùng này sẽ không mất đi sau khi kết thúc hàm (mặc dù biến i sẽ mất) mà không được giải phóng trước đó.
20. a được cấp ở vùng stack vì a được khai báo và khởi tạo giá trị trong hàm main() nên a là biến local của hàm main().
    b là con trỏ local nằm trong hàm main() nên b được cấp ở vùng stack. Tuy nhiên vùng nhớ có giá trị "bar" mà b trỏ tới là một hằng số string nên vùng nhớ này nằm ở .rodata. Vì vậy b là con trỏ nằm trên stack trỏ tới vùng giá trị có địa chỉ nằm trên .rodata.
21. Với RAM = 2000 byte thì đoạn code này sẽ gây lỗi memory leak vì:
  - Mỗi lần lặp được cấp phát động 8 byte bộ nhớ (8 block kiểu dữ liệu char).
  - Trước khi chuyển sang lần lặp kế tiếp, vùng nhớ không được giải phóng và trong lần lặp tiếp theo biến lại được cấp phát động nên vùng nhớ heap sẽ không biến mất.
  - Vòng lặp này lặp 1000 lần, theo logic bên trên thì tổng cộng chương trình phải được cấp phát 8000 byte bộ nhớ heap sau khi kết thúc vòng lặp. Với RAM = 2000 byte thì không đủ và sẽ gây memory leak. Điều này chỉ tính riêng cho heap size, chưa tính tới stack size cho hàm và biến local.
22. Có 3 lỗi tồn tại:
  - p không thay đổi giá trị vì giá trị truyền vào cho myfunction() là giá trị copy, không phải địa chỉ của con trỏ p, vì vậy con trỏ q trong myfunction() không thay đổi bất kì thứ gì của p.
  - trong hàm myfunction(), q được cấp phát động nhưng khi kết thúc hàm không được giải phóng, gây nguy cơ memory leak. Vì q không phải là p, nên không thể giải phóng ngoài hàm myfunction() vì không biết được địa chỉ vùng nhớ sau khi hàm kết thúc.
  - không có hàm print để in ra giá trị con trỏ.
  Để in ra p, cần sửa lại chương trình như sau:
  
  ```
    void myfunction(char **q) {
      *q = (char *)malloc(8);
      if (*q) {
          memcpy(*q, "hello", 6); // gồm cả '\0'
      }
  }

  int main(void) {
      char *p = NULL;
      myfunction(&p);

      if (p) {
          printf("%s\n", p);  // in hello
          free(p);
          p = NULL;
      }
      return 0;
  }
  ```
23. a là biến global được khởi tạo giá trị, được cấp ở .data
    d là biến global chưa được khởi tạo giá trị, được cấp ở .bss
    b là biến mảng global được khởi tạo giá trị, được cấp ở .data
    c là hằng số global, được cấp ở .rodata
    g là biến trong hàm có từ khoá static, được cấp ở .data
    h là hằng số local, được cấp ở stack và vòng đời theo hàm
    i là biến local chưa khởi tạo, được cấp trên stack có giá trị rác
24. Đoạn mã có vài lỗi:
  - Ép kiểu char array có thể hiểu như (char *) sang (int *) làm thay đổi cấu trúc alignment gây bất thường, có thể gây crash ngẫu nhiên.
25. Đoạn mã có vài lỗi:
  - s1 là wild pointer, việc ghi vào s1 bằng câu lệnh "*s1++ = *scr++;" gây nguy hiểm vì không biết địa chỉ s1 đang trỏ tới là ở đâu, tiềm ẩn segment fault hoặc crash.
  - Dòng "*dst++ = *s1" bị sai logic khi đang copy giá trị rác vào con trỏ dst.
26. Đoạn code này tiềm ẩn một số lỗi:
  - strcpy() không kiểm soát kích thước copy, nếu trong trường hợp copy một chuỗi lớn hơn 8 bytes sẽ dẫn tới tràn buffer và gây crash chương trình nếu không xử lý tốt.
  - không kiểm tra kết quả trả về khi malloc(), nếu kết quả trả về NULL (không cấp phát được) thì con trỏ có thể gây segment fault.
  - Function không free vùng nhớ khi kết thúc, gây tiềm ẩn lỗi memory leak.
27. Đoạn mã không hợp lệ vì:
  - Với cách khai báo này, con trỏ str hiện tại đang ở trên stack tuy nhiên đang trỏ về vùng địa chỉ chuỗi có giá trị chuỗi kí tự "Hello" tại vùng .rodata. Với cách khai báo này, không thể thay đổi giá trị, dù kiểu array có thể hiểu là một con trỏ mang tên biến array.
28. a là biến global có khởi tạo giá trị khác 0, được lưu ở .data
    b là hằng số global, được lưu ở .rodata
    c là biến global với từ khoá static có khởi tạo giá trị khác 0, được lưu ở .data
    d là biến local theo hàm, được lưu ở stack
29. Đoạn mã này không có điều kiện kết thúc đệ quy, vì vậy nó sẽ đệ quy vô hạn và gây ra stack overflow.
30. Đoạn mã này sẽ không in ra đúng giá trị ban đầu. Lý do 1 byte đầu tiên trong biến a đã được thay đổi thông qua con trỏ char* p. Vì con trỏ p hiện tại đang trỏ về cùng một địa chỉ với con trỏ a và được ép kiểu thành kiểu char*, vì vậy khi thay đổi giá trị p[0] thì đang thay đổi byte đầu tiên của vùng nhớ này.
31. Đoạn mã này có lỗi như sau:
  - Đoạn code char str[] = "hello"; biến str này là một biến local array, cả biến này và giá trị của nó đều nằm trên stack. Khi hàm getString() trả giá trị về và kết thúc hàm thì biến trả về sẽ bị giải phóng theo hàm, dẫn tới con trỏ s trong đoạn mã "char *s = getString();" sẽ trở thành dangling pointer.
  - Việc đọc con trỏ này để in ra sẽ dẫn tới hành vi bất thường, có thể dẫn tới crash.
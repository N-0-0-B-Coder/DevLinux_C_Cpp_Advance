1. Các lớp lưu trữ (Storage class) trong C dùng để xác định:
    - Phạm vi truy cập (scope): biến dùng được ở đâu?
    - Thời gian tồn tại (lifetime): biến sống bao lâu?
    - Liên kết (linkage): có nhìn thấy từ file khác không?
    - Khu vực cấp phát bộ nhớ: stack / .data / .bss / thanh ghi cpu?
    - Có các loại lớp lưu trữ như sau: auto/static/extern/register/volatile
2. **auto** là lớp lưu trũ mặc định cho biến local. Lớp auto là mặc định, nên hầu như không bao giờ viết.
    Đặc điểm của auto:
    Scope: Trong hàm
    Lifetime: Trong phạm vi vòng đời của hàm
    Linkage: Không
    Storage: Stack
3. **static** là lớp lưu trữ cho các biến tồn tại lâu dài.
    - đối với biến local: static thay đổi thời gian tồn tại của biến sẽ thành cùng với thời gian tồn tại của chương trình, thay vì bị giải phóng khi hàm kết thúc. Đặc điểm của static sẽ như sau:
    Scope: Trong hàm
    Lifetime: Suốt chương trình
    Linkage: Không
    Storage: .data / .bss    
    - đối với biến global: static giữ nguyên thời gian tồn tại mặc định, tuy nhiên sẽ huỷ bỏ khả năng liên kết biến này ra ngoài file hiện tại. Đặc điểm của static sẽ như sau:
    Scope: Trong file hiện tại
    Lifetime: Suốt chương trình
    Linkage: Không
    Storage: .data / .bss     
4. **extern** thay đổi khả năng liên kết của biến ra bên ngoài. Biến có thể được định nghĩa, khởi tạo và gán giá trị tại nơi khác không thuộc vị trí file hiện tại.
    Đặc điểm của static:
    Scope: Trong tất cả các file có liên kết với nhau
    Lifetime: Suốt chương trình
    Linkage: External
    Storage: Nơi biến được định nghĩa    
5. **register** là lớp lưu trữ gợi ý cho compiler đưa vùng nhớ của biến này vào thanh ghi của cpu nếu được cho phép. Biến được lưu trong thanh ghi của cpu sẽ không có địa chỉ trên RAM mà phải truy cập vào địa chỉ của thanh ghi cpu có lưu biến này.
    Đặc điểm của register:
    Scope: Trong hàm
    Lifetime: Cùng với hàm
    Linkage: Không
    Storage: Thanh ghi phần cứng (nếu compiler cho phép)
6. **volatile** thông báo cho compiler giá trị của biến có thể thay đổi bất ngờ ở bên ngoài luồng thực thi hiện tại, nên không được tối ưu hóa bằng cách cache, bỏ đọc, hoặc gom lệnh mà mỗi lần đọc ghi biến volatile phải đọc ghi thật từ bộ nhớ hoặc thanh ghi phần cứng.
    Các trường hợp cần dùng volatile:
    - Biến cập nhật giá trị từ thanh ghi phần cứng.
    - Biến cập nhật giá trị từ ISR (interrupt service routing)
    - Biến được sử dụng giữa các thread
    - Biến cập nhật giá trị từ việc polling
7. Kết quả in ra: 1 2 3
    Nếu bỏ từ khóa static, kết quả sẽ là: 1 1 1 vì biến sẽ trở thành local và bị xoá sau khi kết thúc hàm, và được khởi tạo lại với giá trị 0, dẫn tới count++ sẽ có giá trị 1.
    Biến count được lưu trữ ở .bss vì có từ khoá static và giá trị khởi tạo bằng 0.
8. Đoạn mã này không biên dịch được, vì biến x được khai báo với từ khoá register vì vậy sẽ được lưu trên thanh ghi phần cứng dẫn tới không có địa chỉ, vì vậy compiler sẽ không lấy được địa chỉ cho đoạn code "printf("%p\n", &x);". Lỗi compiler sẽ như dưới đây:
    "error: cannot take the address of a register variable"

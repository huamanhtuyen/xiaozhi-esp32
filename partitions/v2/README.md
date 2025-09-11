# Bảng Phân Vùng Phiên Bản 2

Phiên bản này giới thiệu những cải tiến đáng kể so với v1 bằng cách thêm phân vùng `assets` để hỗ trợ nội dung có thể tải qua mạng và tối ưu hóa bố cục phân vùng cho các kích thước flash khác nhau.

## Những Thay Đổi Chính So Với v1

### Những Cải Tiến Chính

1. **Thêm Phân Vùng Assets**: Phân vùng `assets` mới cho nội dung có thể tải qua mạng
2. **Thay Thế Phân Vùng Model**: Phân vùng `model` cũ (960KB) được thay thế bằng phân vùng `assets` lớn hơn
3. **Tối Ưu Hóa Phân Vùng Ứng Dụng**: Giảm kích thước phân vùng ứng dụng để chứa assets
4. **Tăng Cường Tính Linh Hoạt**: Hỗ trợ cập nhật nội dung động mà không cần flash lại

### Tính Năng Phân Vùng Assets

Phân vùng `assets` lưu trữ:
- **Mô hình từ đánh thức**: Các mô hình từ đánh thức có thể tùy chỉnh có thể tải từ mạng
- **File theme**: Hệ thống theme hoàn chỉnh bao gồm:
  - Font chữ (font văn bản và font icon)
  - Hiệu ứng âm thanh và file âm thanh
  - Hình nền và các thành phần UI
  - Bộ emoji tùy chỉnh
  - File cấu hình ngôn ngữ
- **Nội Dung Động**: Tất cả nội dung có thể được cập nhật qua không khí qua tải xuống HTTP

## So Sánh Bố Cục Phân Vùng

### Bố Cục v1 (16MB)
- `nvs`: 16KB (lưu trữ không thay đổi)
- `otadata`: 8KB (dữ liệu OTA)
- `phy_init`: 4KB (dữ liệu khởi tạo PHY)
- `model`: 960KB (lưu trữ mô hình - nội dung cố định)
- `ota_0`: 6MB (phân vùng ứng dụng 0)
- `ota_1`: 6MB (phân vùng ứng dụng 1)

### Bố Cục v2 (16MB)
- `nvs`: 16KB (lưu trữ không thay đổi)
- `otadata`: 8KB (dữ liệu OTA)
- `phy_init`: 4KB (dữ liệu khởi tạo PHY)
- `ota_0`: 4MB (phân vùng ứng dụng 0)
- `ota_1`: 4MB (phân vùng ứng dụng 1)
- `assets`: 8MB (assets có thể tải qua mạng)

## Các Cấu Hình Có Sẵn

### Thiết Bị Flash 8MB (`8m.csv`)
- `nvs`: 16KB
- `otadata`: 8KB
- `phy_init`: 4KB
- `ota_0`: 3MB
- `ota_1`: 3MB
- `assets`: 2MB

### Thiết Bị Flash 16MB (`16m.csv`) - Chuẩn
- `nvs`: 16KB
- `otadata`: 8KB
- `phy_init`: 4KB
- `ota_0`: 4MB
- `ota_1`: 4MB
- `assets`: 8MB

### Thiết Bị Flash 16MB (`16m_c3.csv`) - Tối Ưu Cho ESP32-C3
- `nvs`: 16KB
- `otadata`: 8KB
- `phy_init`: 4KB
- `ota_0`: 4MB
- `ota_1`: 4MB
- `assets`: 4MB (4000K - bị giới hạn bởi số trang mmap có sẵn)

### Thiết Bị Flash 32MB (`32m.csv`)
- `nvsfactory`: 200KB
- `nvs`: 840KB
- `otadata`: 8KB
- `phy_init`: 4KB
- `ota_0`: 4MB
- `ota_1`: 4MB
- `assets`: 16MB

## Lợi Ích

1. **Quản Lý Nội Dung Động**: Người dùng có thể tải xuống và cập nhật mô hình từ đánh thức, theme và các assets khác mà không cần flash lại thiết bị
2. **Giảm Kích Thước Ứng Dụng**: Phân vùng ứng dụng được tối ưu hóa, cho phép không gian lớn hơn cho nội dung động
3. **Tăng Cường Tùy Chỉnh**: Hỗ trợ theme tùy chỉnh, từ đánh thức và gói ngôn ngữ nâng cao trải nghiệm người dùng
4. **Tính Linh Hoạt Mạng**: Assets có thể được cập nhật độc lập với firmware ứng dụng chính
5. **Sử Dụng Tài Nguyên Tốt Hơn**: Sử dụng bộ nhớ flash hiệu quả với lưu trữ assets có thể cấu hình
6. **Cập Nhật Assets OTA**: Assets có thể được cập nhật qua không khí qua tải xuống HTTP

## Chi Tiết Kỹ Thuật

- **Loại Phân Vùng**: Phân vùng Assets sử dụng subtype `spiffs` để tương thích với hệ thống file SPIFFS
- **Ánh Xạ Bộ Nhớ**: Assets được ánh xạ bộ nhớ để truy cập hiệu quả trong thời gian chạy
- **Xác Thực Checksum**: Kiểm tra tính toàn vẹn tích hợp đảm bảo tính hợp lệ dữ liệu assets
- **Tải Xuống Tiến Triển**: Assets có thể được tải xuống tiến triển với theo dõi tiến độ
- **Hỗ Trợ Fallback**: Fallback êm ái đến assets mặc định nếu cập nhật mạng thất bại

## Di Chuyển Từ v1

Khi nâng cấp từ v1 lên v2:
1. **Sao Lưu Dữ Liệu Quan Trọng**: Đảm bảo bất kỳ dữ liệu quan trọng nào trong phân vùng `model` cũ được sao lưu
2. **Flash Bảng Phân Vùng Mới**: Sử dụng bảng phân vùng v2 phù hợp với kích thước flash của bạn
3. **Tải Xuống Assets**: Thiết bị sẽ tự động tải xuống các assets cần thiết khi khởi động lần đầu
4. **Xác Minh Chức Năng**: Đảm bảo tất cả tính năng hoạt động đúng với bố cục phân vùng mới

## Ghi Chú Sử Dụng

- Kích thước phân vùng `assets` thay đổi theo cấu hình để tối ưu cho các kích thước flash khác nhau
- Thiết bị ESP32-C3 sử dụng phân vùng assets nhỏ hơn (4MB) do giới hạn số trang mmap có sẵn trong hệ thống
- Thiết bị 32MB có phân vùng assets lớn nhất (16MB) để lưu trữ nội dung tối đa
- Tất cả bảng phân vùng duy trì căn chỉnh đúng để hiệu suất flash tối ưu
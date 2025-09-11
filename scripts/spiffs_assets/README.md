# Trình Xây Dựng Tài Nguyên SPIFFS

Script này dùng để xây dựng phân vùng tài nguyên SPIFFS của dự án ESP32, đóng gói các file tài nguyên khác nhau thành định dạng có thể sử dụng trên thiết bị.

## Tính Năng Đặc Trưng

- Xử lý mô hình mạng đánh thức (WakeNet Model)
- Tích hợp file font văn bản
- Xử lý bộ sưu tập hình ảnh biểu tượng cảm xúc
- Tự động tạo file chỉ mục tài nguyên
- Đóng gói tạo file `assets.bin` cuối cùng

## Yêu Cầu Dependencies

- Python 3.6+
- Các file tài nguyên liên quan

## Cách Sử Dụng

### Cú Pháp Cơ Bản

```bash
./build.py --wakenet_model <thư_mục_mô_hình_wakenet> \
    --text_font <file_font_văn_bản> \
    --emoji_collection <thư_mục_bộ_sưu_tập_emoji>
```

### Giải Thích Tham Số

| Tham Số | Loại | Bắt Buộc | Giải Thích |
|------|------|------|------|
| `--wakenet_model` | đường dẫn thư mục | Không | Đường dẫn thư mục mô hình mạng đánh thức |
| `--text_font` | đường dẫn file | Không | Đường dẫn file font văn bản |
| `--emoji_collection` | đường dẫn thư mục | Không | Đường dẫn thư mục bộ sưu tập hình ảnh biểu tượng cảm xúc |

### Ví Dụ Sử Dụng

```bash
# Ví dụ tham số đầy đủ
./build.py \
    --wakenet_model ../../managed_components/espressif__esp-sr/model/wakenet_model/wn9_nihaoxiaozhi_tts \
    --text_font ../../components/xiaozhi-fonts/build/font_puhui_common_20_4.bin \
    --emoji_collection ../../components/xiaozhi-fonts/build/emojis_64/

# Chỉ xử lý file font
./build.py --text_font ../../components/xiaozhi-fonts/build/font_puhui_common_20_4.bin

# Chỉ xử lý biểu tượng cảm xúc
./build.py --emoji_collection ../../components/xiaozhi-fonts/build/emojis_64/
```

## Quy Trình Làm Việc

1. **Tạo Cấu Trúc Thư Mục Xây Dựng**
   - `build/` - Thư mục xây dựng chính
   - `build/assets/` - Thư mục file tài nguyên
   - `build/output/` - Thư mục file đầu ra

2. **Xử Lý Mô Hình Mạng Đánh Thức**
   - Sao chép file mô hình vào thư mục xây dựng
   - Sử dụng `pack_model.py` tạo `srmodels.bin`
   - Sao chép file mô hình đã tạo vào thư mục tài nguyên

3. **Xử Lý Font Văn Bản**
   - Sao chép file font vào thư mục tài nguyên
   - Hỗ trợ file font định dạng `.bin`

4. **Xử Lý Bộ Sưu Tập Biểu Tượng Cảm Xúc**
   - Quét file hình ảnh trong thư mục chỉ định
   - Hỗ trợ định dạng `.png` và `.gif`
   - Tự động tạo chỉ mục biểu tượng cảm xúc

5. **Tạo File Cấu Hình**
   - `index.json` - File chỉ mục tài nguyên
   - `config.json` - File cấu hình xây dựng

6. **Đóng Gói Tài Nguyên Cuối Cùng**
   - Sử dụng `spiffs_assets_gen.py` tạo `assets.bin`
   - Sao chép vào thư mục gốc xây dựng

## File Đầu Ra

Sau khi xây dựng hoàn tất, sẽ tạo các file sau trong thư mục `build/`:

- `assets/` - Tất cả file tài nguyên
- `assets.bin` - File tài nguyên SPIFFS cuối cùng
- `config.json` - Cấu hình xây dựng
- `output/` - File đầu ra trung gian

## Định Dạng Tài Nguyên Hỗ Trợ

- **File mô hình**: `.bin` (xử lý qua pack_model.py)
- **File font**: `.bin`
- **File hình ảnh**: `.png`, `.gif`
- **File cấu hình**: `.json`

## Xử Lý Lỗi

Script bao gồm cơ chế xử lý lỗi hoàn chỉnh:

- Kiểm tra file/thư mục nguồn có tồn tại không
- Xác minh kết quả thực thi subprocess
- Cung cấp thông tin lỗi và cảnh báo chi tiết

## Lưu Ý

1. Đảm bảo tất cả script Python dependencies ở cùng thư mục
2. Đường dẫn file tài nguyên sử dụng đường dẫn tuyệt đối hoặc tương đối so với thư mục script
3. Quá trình xây dựng sẽ dọn dẹp file xây dựng trước đó
4. Kích thước file `assets.bin` được tạo bị giới hạn bởi kích thước phân vùng SPIFFS

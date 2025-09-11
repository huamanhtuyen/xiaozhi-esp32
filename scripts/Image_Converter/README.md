# Công Cụ Chuyển Đổi Hình Ảnh LVGL

Thư mục này chứa hai script Python dùng để xử lý và chuyển đổi hình ảnh sang định dạng LVGL:

## 1. LVGLImage (LVGLImage.py)

Trích dẫn từ script chuyển đổi [LVGLImage.py](https://github.com/lvgl/lvgl/blob/master/scripts/LVGLImage.py) của [kho chính thức LVGL](https://github.com/lvgl/lvgl)

## 2. Công Cụ Chuyển Đổi Hình Ảnh LVGL (lvgl_tools_gui.py)

Gọi `LVGLImage.py`, chuyển đổi hàng loạt hình ảnh sang định dạng hình ảnh LVGL
Có thể dùng để sửa đổi biểu cảm mặc định của Xiao Zhi, hướng dẫn sửa đổi cụ thể [tại đây](https://www.bilibili.com/video/BV12FQkYeEJ3/)

### Tính Năng

- Hoạt động giao diện đồ họa, giao diện thân thiện hơn
- Hỗ trợ chuyển đổi hàng loạt hình ảnh
- Tự động nhận dạng định dạng hình ảnh và chọn định dạng màu tốt nhất để chuyển đổi
- Hỗ trợ đa độ phân giải

### Cách Sử Dụng

Tạo môi trường ảo
```bash
# Tạo venv
python -m venv venv
# Kích hoạt môi trường
source venv/bin/activate  # Linux/Mac
venv\Scripts\activate      # Windows
```

Cài đặt dependencies
```bash
pip install -r requirements.txt
```

Chạy công cụ chuyển đổi

```bash
# Kích hoạt môi trường
source venv/bin/activate  # Linux/Mac
venv\Scripts\activate      # Windows
# Chạy
python lvgl_tools_gui.py

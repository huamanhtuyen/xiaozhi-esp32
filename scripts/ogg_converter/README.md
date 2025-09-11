# ogg_converter Công Cụ Chuyển Đổi OGG Hàng Loạt Cho Xiao Zhi AI

Script này là công cụ chuyển đổi OGG hàng loạt, hỗ trợ chuyển đổi file âm thanh đầu vào thành định dạng OGG mà Xiao Zhi có thể sử dụng
Dựa trên thư viện Python bên thứ ba `ffmpeg-python` để triển khai
Hỗ trợ chuyển đổi hai chiều giữa OGG và âm thanh, điều chỉnh âm lượng v.v.

# Tạo Và Kích Hoạt Môi Trường Ảo

```bash
# Tạo môi trường ảo
python -m venv venv
# Kích hoạt môi trường ảo
source venv/bin/activate # Mac/Linux
venv\Scripts\activate # Windows
```

# Cài Đặt Dependencies

Vui lòng thực hiện trong môi trường ảo

```bash
pip install ffmpeg-python
```

# Chạy Script

```bash
python ogg_converter.py

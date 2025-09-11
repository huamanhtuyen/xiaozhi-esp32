# Công Cụ Chuyển Đổi Và Phát Định Dạng Âm Thanh P3

Thư mục này chứa các script Python dùng để xử lý file âm thanh định dạng P3:

## 1. Công Cụ Chuyển Đổi Âm Thanh (convert_audio_to_p3.py)

Chuyển đổi file âm thanh thông thường sang định dạng P3 (4 byte header + cấu trúc stream dữ liệu Opus) và chuẩn hóa âm lượng.

### Cách Sử Dụng

```bash
python convert_audio_to_p3.py <file âm thanh đầu vào> <file P3 đầu ra> [-l LUFS] [-d]
```

Trong đó, tùy chọn `-l` dùng để chỉ định mức âm lượng chuẩn hóa mục tiêu, mặc định là -16 LUFS; tùy chọn `-d` có thể tắt chuẩn hóa âm lượng.

Nếu file âm thanh đầu vào thỏa mãn một trong các điều kiện sau, khuyên dùng `-d` để tắt chuẩn hóa âm lượng:
- Âm thanh quá ngắn
- Âm thanh đã điều chỉnh âm lượng
- Âm thanh từ TTS mặc định (âm lượng mặc định của TTS mà Xiao Zhi hiện dùng đã là -16 LUFS)

Ví dụ:
```bash
python convert_audio_to_p3.py input.mp3 output.p3
```

## 2. Công Cụ Phát Âm Thanh P3 (play_p3.py)

Phát file âm thanh định dạng P3.

### Tính Năng

- Giải mã và phát file âm thanh định dạng P3
- Khi kết thúc phát hoặc người dùng ngắt, áp dụng hiệu ứng fade out để tránh tiếng vỡ
- Hỗ trợ chỉ định file cần phát qua tham số dòng lệnh

### Cách Sử Dụng

```bash
python play_p3.py <đường dẫn file P3>
```

Ví dụ:
```bash
python play_p3.py output.p3
```

## 3. Công Cụ Chuyển P3 Trở Lại Âm Thanh (convert_p3_to_audio.py)

Chuyển định dạng P3 trở lại file âm thanh thông thường.

### Cách Sử Dụng

```bash
python convert_p3_to_audio.py <file P3 đầu vào> <file âm thanh đầu ra>
```

File âm thanh đầu ra cần có phần mở rộng.

Ví dụ:
```bash
python convert_p3_to_audio.py input.p3 output.wav
```

## 4. Công Cụ Chuyển Đổi Hàng Loạt Âm Thanh/P3

Một công cụ giao diện đồ họa, hỗ trợ chuyển đổi hàng loạt âm thanh sang P3, P3 sang âm thanh

![](./img/img.png)

### Cách Sử Dụng:
```bash
python batch_convert_gui.py
```

## Cài Đặt Dependencies

Trước khi sử dụng các script này, vui lòng đảm bảo đã cài đặt các thư viện Python cần thiết:

```bash
pip install librosa opuslib numpy tqdm sounddevice pyloudnorm soundfile
```

Hoặc sử dụng file requirements.txt cung cấp:

```bash
pip install -r requirements.txt
```

## Giải Thích Định Dạng P3

Định dạng P3 là một định dạng âm thanh stream đơn giản, cấu trúc như sau:
- Mỗi khung âm thanh gồm một header 4 byte và một gói dữ liệu mã hóa Opus
- Định dạng header: [1 byte loại, 1 byte dự trữ, 2 byte độ dài]
- Tỷ lệ lấy mẫu cố định 16000Hz, đơn kênh
- Độ dài mỗi khung là 60ms
# Bảng DFRobot Hành Không K10

## Cấu Hình Nút Bấm
* A: Nhấn ngắn - Ngắt/Đánh thức, Nhấn dài 1s - Tăng âm lượng
* B: Nhấn ngắn - Ngắt/Đánh thức, Nhấn dài 1s - Giảm âm lượng

## Lệnh Cấu Hình Biên Dịch

**Cấu hình mục tiêu biên dịch là ESP32S3:**

```bash
idf.py set-target esp32s3
```

**Mở menuconfig:**

```bash
idf.py menuconfig
```

**Chọn board:**

```
Xiaozhi Assistant -> Board Type -> DFRobot Hành Không Bảng K10
```

**Sửa đổi cấu hình psram:**

```
Component config -> ESP PSRAM -> SPI RAM config -> Mode (QUAD/OCT) -> Octal Mode PSRAM
```

**Biên dịch:**

```bash
idf.py build
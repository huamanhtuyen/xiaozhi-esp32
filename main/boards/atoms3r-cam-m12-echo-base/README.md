# AtomS3R CAM/M12 + Echo Base

## Giới Thiệu

<div align="center">
    <a href="https://docs.m5stack.com/zh_CN/core/AtomS3R%20Cam"><b> Trang Sản Phẩm AtomS3R CAM </b></a>
    |
    <a href="https://docs.m5stack.com/zh_CN/core/AtomS3R-M12"><b> Trang Sản Phẩm AtomS3R M12 </b></a>
    |
    <a href="https://docs.m5stack.com/zh_CN/atom/Atomic%20Echo%20Base"><b> Trang Sản Phẩm Echo Base </b></a>
</div>

AtomS3R CAM, AtomS3R M12 là bộ điều khiển IoT có thể lập trình dựa trên ESP32-S3-PICO-1-N8R8 do M5Stack phát hành, được trang bị camera. Atomic Echo Base là đế nhận dạng giọng nói được thiết kế chuyên biệt cho series host M5 Atom, sử dụng giải pháp tích hợp bộ giải mã âm thanh đơn kênh ES8311, microphone MEMS và bộ khuếch đại công suất NS4150B.

Cả hai phiên bản phát triển **không có màn hình, không có nút bấm bổ sung**, cần sử dụng đánh thức giọng nói. Khi cần thiết, cần sử dụng `idf.py monitor` để xem log xác định trạng thái chạy.

## Lệnh Cấu Hình Và Biên Dịch

**Cấu hình mục tiêu biên dịch là ESP32S3**

```bash
idf.py set-target esp32s3
```

**Mở menuconfig và cấu hình**

```bash
idf.py menuconfig
```

Cấu hình lần lượt các tùy chọn sau:

- `Xiaozhi Assistant` → `Board Type` → Chọn `AtomS3R CAM/M12 + Echo Base`
- `Xiaozhi Assistant` → `IoT Protocol` → Chọn `Giao thức MCP` có thể mở chức năng nhận dạng camera
- `Partition Table` → `Custom partition CSV file` → Xóa nội dung gốc, nhập `partitions/v2/8m.csv`
- `Serial flasher config` → `Flash size` → Chọn `8 MB`

Nhấn `S` để lưu, nhấn `Q` để thoát.

**Biên dịch**

```bash
idf.py build
```

**Flash**

Kết nối AtomS3R CAM/M12 với máy tính, nhấn giữ nút RESET bên cạnh cho đến khi đèn xanh bên dưới nút RESET nhấp nháy.

```bash
idf.py flash
```

Sau khi flash hoàn tất, nhấn nút RESET để khởi động lại.

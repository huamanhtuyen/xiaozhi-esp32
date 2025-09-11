# Robot Trò Chuyện Dựa Trên MCP | Một Robot Trò Chuyện Dựa Trên MCP

(Tiếng Việt | [English](README_en.md) | [日本語](README_ja.md))

## Video

👉 [Con người: Cho AI gắn camera vs AI: Ngay lập tức phát hiện chủ nhân ba ngày chưa gội đầu【bilibili】](https://www.bilibili.com/video/BV1bpjgzKEhd/)

👉 [Tự tay chế tạo bạn gái AI của bạn, hướng dẫn dành cho người mới bắt đầu【bilibili】](https://www.bilibili.com/video/BV1XnmFYLEJN/)

## Giới Thiệu

Đây là một dự án ESP32 mã nguồn mở do Xa ca phát triển, phát hành theo giấy phép MIT, cho phép bất kỳ ai sử dụng miễn phí, bao gồm cả mục đích thương mại.

Chúng tôi hy vọng dự án này có thể giúp mọi người hiểu về phát triển phần cứng AI và áp dụng các mô hình ngôn ngữ lớn đang phát triển nhanh chóng vào các thiết bị phần cứng thực tế.

Nếu bạn có bất kỳ ý tưởng hoặc gợi ý nào, vui lòng thoải mái tạo Issues hoặc tham gia QQ group: 1011329060

### Điều Khiển Mọi Thứ Với MCP

Robot trò chuyện AI Xiao Zhi như một cổng tương tác giọng nói, tận dụng khả năng AI của các mô hình lớn như Qwen / DeepSeek, và thực hiện điều khiển đa thiết bị qua giao thức MCP.

![Điều khiển mọi thứ qua MCP](docs/mcp-based-graph.jpg)

### Các Chức Năng Đã Triển Khai

- Wi-Fi / ML307 Cat.1 4G
- Đánh thức giọng nói ngoại tuyến [ESP-SR](https://github.com/espressif/esp-sr)
- Hỗ trợ hai giao thức giao tiếp ([Websocket](docs/websocket.md) hoặc MQTT+UDP)
- Sử dụng codec âm thanh OPUS
- Tương tác giọng nói dựa trên kiến trúc streaming ASR + LLM + TTS
- Nhận dạng giọng nói, xác định danh tính người nói hiện tại [3D Speaker](https://github.com/modelscope/3D-Speaker)
- Màn hình OLED / LCD, hỗ trợ hiển thị biểu tượng cảm xúc
- Hiển thị pin và quản lý nguồn
- Hỗ trợ đa ngôn ngữ (Tiếng Trung, Tiếng Anh, Tiếng Nhật)
- Hỗ trợ nền tảng chip ESP32-C3, ESP32-S3, ESP32-P4
- Qua MCP phía thiết bị thực hiện điều khiển thiết bị (loa, đèn, servo, GPIO v.v.)
- Qua MCP phía đám mây mở rộng khả năng mô hình lớn (điều khiển nhà thông minh, thao tác desktop PC, tìm kiếm kiến thức, gửi/nhận email v.v.)

## Phần Cứng

### Thực Hành Làm Bằng Tay Trên Breadboard

Chi tiết xem hướng dẫn tài liệu Feishu:

👉 ["Bách Khoa Toàn Thư Robot Trò Chuyện AI Xiao Zhi"](https://ccnphfhqs21z.feishu.cn/wiki/F5krwD16viZoF0kKkvDcrZNYnhb?from=from_copylink)

Hình ảnh hiệu ứng breadboard như sau:

![Hình ảnh hiệu ứng breadboard](docs/v1/wiring2.jpg)

### Hỗ Trợ Hơn 70 Phần Cứng Mã Nguồn Mở (Chỉ Hiển Thị Một Phần)

- <a href="https://oshwhub.com/li-chuang-kai-fa-ban/li-chuang-shi-zhan-pai-esp32-s3-kai-fa-ban" target="_blank" title="Bảng Phát Triển ESP32-S3 Thực Chiến LiChuang">Bảng Phát Triển ESP32-S3 Thực Chiến LiChuang</a>
- <a href="https://github.com/espressif/esp-box" target="_blank" title="ESP32-S3-BOX3 Espressif">ESP32-S3-BOX3 Espressif</a>
- <a href="https://docs.m5stack.com/zh_CN/core/CoreS3" target="_blank" title="M5Stack CoreS3">M5Stack CoreS3</a>
- <a href="https://docs.m5stack.com/en/atom/Atomic%20Echo%20Base" target="_blank" title="AtomS3R + Echo Base">M5Stack AtomS3R + Echo Base</a>
- <a href="https://gf.bilibili.com/item/detail/1108782064" target="_blank" title="Nút Thần Kỳ 2.4">Nút Thần Kỳ 2.4</a>
- <a href="https://www.waveshare.net/shop/ESP32-S3-Touch-AMOLED-1.8.htm" target="_blank" title="Vi Tuyết Điện Tử ESP32-S3-Touch-AMOLED-1.8">Vi Tuyết Điện Tử ESP32-S3-Touch-AMOLED-1.8</a>
- <a href="https://github.com/Xinyuan-LilyGO/T-Circle-S3" target="_blank" title="LILYGO T-Circle-S3">LILYGO T-Circle-S3</a>
- <a href="https://oshwhub.com/tenclass01/xmini_c3" target="_blank" title="Xa Ca Mini C3">Xa Ca Mini C3</a>
- <a href="https://oshwhub.com/movecall/cuican-ai-pendant-lights-up-y" target="_blank" title="Movecall CuiCan ESP32S3">CuiCan·AI Mặt Dây Chuyền</a>
- <a href="https://github.com/WMnologo/xingzhi-ai" target="_blank" title="Vô Danh Khoa Công Nologo-Tinh Trí-1.54">Vô Danh Khoa Công Nologo-Tinh Trí-1.54TFT</a>
- <a href="https://www.seeedstudio.com/SenseCAP-Watcher-W1-A-p-5979.html" target="_blank" title="SenseCAP Watcher">SenseCAP Watcher</a>
- <a href="https://www.bilibili.com/video/BV1BHJtz6E2S/" target="_blank" title="Chó Robot Siêu Thấp Chi Phí ESP-HI">Chó Robot Siêu Thấp Chi Phí ESP-HI</a>

<div style="display: flex; justify-content: space-between;">
  <a href="docs/v1/lichuang-s3.jpg" target="_blank" title="Bảng Phát Triển ESP32-S3 Thực Chiến LiChuang">
    <img src="docs/v1/lichuang-s3.jpg" width="240" />
  </a>
  <a href="docs/v1/espbox3.jpg" target="_blank" title="ESP32-S3-BOX3 Espressif">
    <img src="docs/v1/espbox3.jpg" width="240" />
  </a>
  <a href="docs/v1/m5cores3.jpg" target="_blank" title="M5Stack CoreS3">
    <img src="docs/v1/m5cores3.jpg" width="240" />
  </a>
  <a href="docs/v1/atoms3r.jpg" target="_blank" title="AtomS3R + Echo Base">
    <img src="docs/v1/atoms3r.jpg" width="240" />
  </a>
  <a href="docs/v1/magiclick.jpg" target="_blank" title="Nút Thần Kỳ 2.4">
    <img src="docs/v1/magiclick.jpg" width="240" />
  </a>
  <a href="docs/v1/waveshare.jpg" target="_blank" title="Vi Tuyết Điện Tử ESP32-S3-Touch-AMOLED-1.8">
    <img src="docs/v1/waveshare.jpg" width="240" />
  </a>
  <a href="docs/v1/lilygo-t-circle-s3.jpg" target="_blank" title="LILYGO T-Circle-S3">
    <img src="docs/v1/lilygo-t-circle-s3.jpg" width="240" />
  </a>
  <a href="docs/v1/xmini-c3.jpg" target="_blank" title="Xa Ca Mini C3">
    <img src="docs/v1/xmini-c3.jpg" width="240" />
  </a>
  <a href="docs/v1/movecall-cuican-esp32s3.jpg" target="_blank" title="CuiCan">
    <img src="docs/v1/movecall-cuican-esp32s3.jpg" width="240" />
  </a>
  <a href="docs/v1/wmnologo_xingzhi_1.54.jpg" target="_blank" title="Vô Danh Khoa Công Nologo-Tinh Trí-1.54">
    <img src="docs/v1/wmnologo_xingzhi_1.54.jpg" width="240" />
  </a>
  <a href="docs/v1/sensecap_watcher.jpg" target="_blank" title="SenseCAP Watcher">
    <img src="docs/v1/sensecap_watcher.jpg" width="240" />
  </a>
  <a href="docs/v1/esp-hi.jpg" target="_blank" title="Chó Robot Siêu Thấp Chi Phí ESP-HI">
    <img src="docs/v1/esp-hi.jpg" width="240" />
  </a>
</div>

## Phần Mềm

### Flash Firmware

Người mới lần đầu vận hành khuyên không nên thiết lập môi trường phát triển ngay, trực tiếp sử dụng firmware flash không cần môi trường phát triển.

Firmware mặc định kết nối với máy chủ chính thức [xiaozhi.me](https://xiaozhi.me), người dùng cá nhân đăng ký tài khoản có thể sử dụng miễn phí mô hình thời gian thực Qwen.

👉 [Hướng Dẫn Flash Firmware Cho Người Mới](https://ccnphfhqs21z.feishu.cn/wiki/Zpz4wXBtdimBrLk25WdcXzxcnNS)

### Môi Trường Phát Triển

- Cursor hoặc VSCode
- Cài đặt plugin ESP-IDF, chọn phiên bản SDK 5.4 trở lên
- Linux tốt hơn Windows, tốc độ biên dịch nhanh, cũng tránh được phiền toái vấn đề driver
- Dự án này sử dụng phong cách mã C++ Google, khi submit mã vui lòng đảm bảo tuân thủ quy phạm

### Tài Liệu Nhà Phát Triển

- [Hướng Dẫn Bảng Mạch Tùy Chỉnh](main/boards/README.md) - Học cách tạo bảng mạch tùy chỉnh cho Xiao Zhi AI
- [Hướng Dẫn Sử Dụng Điều Khiển IoT Giao Thức MCP](docs/mcp-usage.md) - Hiểu cách điều khiển thiết bị IoT qua giao thức MCP
- [Quy Trình Tương Tác Giao Thức MCP](docs/mcp-protocol.md) - Cách triển khai giao thức MCP phía thiết bị
- [Tài Liệu Giao Thức Giao Tiếp Hỗn Hợp MQTT + UDP](docs/mqtt-udp.md)
- [Tài Liệu Chi Tiết Giao Thức Giao Tiếp WebSocket](docs/websocket.md)

## Cấu Hình Mô Hình Lớn

Nếu bạn đã có thiết bị robot trò chuyện AI Xiao Zhi và đã kết nối với máy chủ chính thức, có thể đăng nhập bảng điều khiển [xiaozhi.me](https://xiaozhi.me) để cấu hình.

👉 [Video Hướng Dẫn Hoạt Động Backend (Giao Diện Phiên Bản Cũ)](https://www.bilibili.com/video/BV1jUCUY2EKM/)

## Các Dự Án Mã Nguồn Mở Liên Quan

Triển khai máy chủ trên máy tính cá nhân, có thể tham khảo các dự án mã nguồn mở bên thứ ba sau:

- [xinnan-tech/xiaozhi-esp32-server](https://github.com/xinnan-tech/xiaozhi-esp32-server) Máy chủ Python
- [joey-zhou/xiaozhi-esp32-server-java](https://github.com/joey-zhou/xiaozhi-esp32-server-java) Máy chủ Java
- [AnimeAIChat/xiaozhi-server-go](https://github.com/AnimeAIChat/xiaozhi-server-go) Máy chủ Golang

Các dự án client bên thứ ba sử dụng giao thức giao tiếp Xiao Zhi:

- [huangjunsen0406/py-xiaozhi](https://github.com/huangjunsen0406/py-xiaozhi) Client Python
- [TOM88812/xiaozhi-android-client](https://github.com/TOM88812/xiaozhi-android-client) Client Android
- [100askTeam/xiaozhi-linux](http://github.com/100askTeam/xiaozhi-linux) Client Linux do Bách Vấn Công Nghệ cung cấp
- [78/xiaozhi-sf32](https://github.com/78/xiaozhi-sf32) Firmware chip Bluetooth của Tư Sát Công Nghệ
- [QuecPython/solution-xiaozhiAI](https://github.com/QuecPython/solution-xiaozhiAI) Firmware QuecPython do Di Viễn cung cấp

## Lịch Sử Star

<a href="https://star-history.com/#78/xiaozhi-esp32&Date">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=78/xiaozhi-esp32&type=Date&theme=dark" />
    <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=78/xiaozhi-esp32&type=Date" />
    <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=78/xiaozhi-esp32&type=Date" />
  </picture>
</a>

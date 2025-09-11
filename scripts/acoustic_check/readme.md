# Kiểm Tra Sóng Âm

GUI này dùng để kiểm tra việc nhận từ thiết bị Xiao Zhi qua `udp` truyền về `pcm` chuyển sang miền thời gian/tần số, có thể lưu âm thanh độ dài cửa sổ, dùng để phán đoán phân bố tần số nhiễu và kiểm tra độ chính xác truyền ascii sóng âm,

Để kiểm tra firmware cần mở `USE_AUDIO_DEBUGGER`, và thiết lập `AUDIO_DEBUG_UDP_SERVER` là địa chỉ máy local.
Sóng âm `demod` có thể qua `sonic_wifi_config.html` hoặc upload lên `PinMe` [Cấu Hình Mạng Sóng Âm Xiao Zhi](https://iqf7jnhi.pinit.eth.limo) để xuất sóng âm kiểm tra

# Ghi Chép Kiểm Tra Giải Mã Sóng Âm

> `✓` đại diện khi nhận tín hiệu PCM thô qua I2S DIN có thể giải mã thành công, `△` đại diện cần giảm nhiễu hoặc thao tác bổ sung để giải mã ổn định, `X` đại diện sau giảm nhiễu hiệu quả cũng không tốt (có thể giải mã một phần nhưng rất không ổn định).
> Một số ADC cần cấu hình I2C giai đoạn làm giảm nhiễu điều chỉnh tinh tế hơn, do thiết bị không phổ thông tạm chỉ theo config cung cấp trong boards để kiểm tra

| Thiết Bị | ADC | MIC | Hiệu Quả | Ghi Chú |
| ---- | ---- | --- | --- | ---- |
| bread-compact | INMP441 | MIC tích hợp MEMEMIC | ✓ | |
| atk-dnesp32s3-box | ES8311 | | ✓ | |
| magiclick-2p5 | ES8311 | | ✓ | |
| lichuang-dev  | ES7210 | | △ | Khi kiểm tra cần tắt INPUT_REFERENCE |
| kevin-box-2 | ES7210 | | △ | Khi kiểm tra cần tắt INPUT_REFERENCE |
| m5stack-core-s3 | ES7210 | | △ | Khi kiểm tra cần tắt INPUT_REFERENCE |
| xmini-c3 | ES8311 | | △ | Cần giảm nhiễu |
| atoms3r-echo-base | ES8311 | | △ | Cần giảm nhiễu |
| atk-dnesp32s3-box0 | ES8311 | | X | Có thể nhận và giải mã, nhưng tỷ lệ mất gói rất cao |
| movecall-moji-esp32s3 | ES8311 | | X | Có thể nhận và giải mã, nhưng tỷ lệ mất gói rất cao
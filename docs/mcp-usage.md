# Hướng dẫn sử dụng giao thức MCP cho điều khiển IoT

> Tài liệu này giới thiệu cách thực hiện điều khiển IoT cho thiết bị ESP32 dựa trên giao thức MCP. Vui lòng tham khảo [`mcp-protocol.md`](./mcp-protocol.md) để biết quy trình giao thức chi tiết.

## Giới thiệu

MCP (Model Context Protocol) là giao thức thế hệ mới được khuyến nghị sử dụng cho điều khiển IoT, thông qua định dạng JSON-RPC 2.0 chuẩn để khám phá và gọi "công cụ" (Tool) giữa thiết bị và backend, thực hiện điều khiển thiết bị linh hoạt.

## Quy trình sử dụng điển hình

1. Sau khi thiết bị khởi động, thiết lập kết nối với backend qua giao thức cơ bản (như WebSocket/MQTT).
2. Backend khởi tạo phiên qua phương thức `initialize` của giao thức MCP.
3. Backend lấy danh sách tất cả các công cụ (chức năng) mà thiết bị hỗ trợ và mô tả tham số qua `tools/list`.
4. Backend gọi công cụ cụ thể qua `tools/call` để thực hiện điều khiển thiết bị.

Định dạng giao thức và tương tác chi tiết vui lòng xem [`mcp-protocol.md`](./mcp-protocol.md).

## Hướng dẫn phương thức đăng ký công cụ phía thiết bị

Thiết bị đăng ký "công cụ" có thể được backend gọi qua phương thức `McpServer::AddTool`. Chữ ký hàm phổ biến như sau:

```cpp
void AddTool(
    const std::string& name,           // Tên công cụ, khuyến nghị duy nhất và có tính phân cấp, ví dụ self.dog.forward
    const std::string& description,    // Mô tả công cụ, giải thích ngắn gọn chức năng để mô hình lớn dễ hiểu
    const PropertyList& properties,    // Danh sách tham số đầu vào (có thể rỗng), hỗ trợ kiểu: boolean, integer, string
    std::function<ReturnValue(const PropertyList&)> callback // Triển khai callback khi công cụ được gọi
);
```
- name: Định danh duy nhất của công cụ, khuyến nghị sử dụng phong cách đặt tên "module.chức năng".
- description: Mô tả bằng ngôn ngữ tự nhiên, dễ hiểu cho AI/người dùng.
- properties: Danh sách tham số, hỗ trợ kiểu boolean, integer, string, có thể chỉ định phạm vi và giá trị mặc định.
- callback: Logic thực thi thực tế khi nhận yêu cầu gọi, giá trị trả về có thể là bool/int/string.

## Ví dụ đăng ký điển hình (lấy ESP-Hi làm ví dụ)

```cpp
void InitializeTools() {
    auto& mcp_server = McpServer::GetInstance();
    // Ví dụ 1: Không tham số, điều khiển robot tiến về phía trước
    mcp_server.AddTool("self.dog.forward", "Robot di chuyển về phía trước", PropertyList(), [this](const PropertyList&) -> ReturnValue {
        servo_dog_ctrl_send(DOG_STATE_FORWARD, NULL);
        return true;
    });
    // Ví dụ 2: Có tham số, thiết lập màu RGB cho đèn
    mcp_server.AddTool("self.light.set_rgb", "Thiết lập màu RGB", PropertyList({
        Property("r", kPropertyTypeInteger, 0, 255),
        Property("g", kPropertyTypeInteger, 0, 255),
        Property("b", kPropertyTypeInteger, 0, 255)
    }), [this](const PropertyList& properties) -> ReturnValue {
        int r = properties["r"].value<int>();
        int g = properties["g"].value<int>();
        int b = properties["b"].value<int>();
        led_on_ = true;
        SetLedColor(r, g, b);
        return true;
    });
}
```

## Ví dụ JSON-RPC gọi công cụ phổ biến

### 1. Lấy danh sách công cụ
```json
{
  "jsonrpc": "2.0",
  "method": "tools/list",
  "params": { "cursor": "" },
  "id": 1
}
```

### 2. Điều khiển chassis tiến về phía trước
```json
{
  "jsonrpc": "2.0",
  "method": "tools/call",
  "params": {
    "name": "self.chassis.go_forward",
    "arguments": {}
  },
  "id": 2
}
```

### 3. Chuyển đổi chế độ đèn
```json
{
  "jsonrpc": "2.0",
  "method": "tools/call",
  "params": {
    "name": "self.chassis.switch_light_mode",
    "arguments": { "light_mode": 3 }
  },
  "id": 3
}
```

### 4. Lật camera
```json
{
  "jsonrpc": "2.0",
  "method": "tools/call",
  "params": {
    "name": "self.camera.set_camera_flipped",
    "arguments": {}
  },
  "id": 4
}
```

## Ghi chú
- Tên công cụ, tham số và giá trị trả về vui lòng lấy theo đăng ký `AddTool` phía thiết bị.
- Khuyến nghị tất cả các dự án mới thống nhất sử dụng giao thức MCP cho điều khiển IoT.
- Giao thức chi tiết và cách sử dụng nâng cao vui lòng tham khảo [`mcp-protocol.md`](./mcp-protocol.md).
# 🎮 Game 2048 - SDL Edition

## 📌 Mô tả dự án

Đây là phiên bản game **2048** được xây dựng bằng thư viện **SDL2**, kết hợp với **SDL_ttf** (hiển thị văn bản) và **SDL_mixer** (âm thanh).  
Game này yêu cầu người chơi sử dụng các phím mũi tên (`↑ ↓ ← →`) để di chuyển các ô số trên bảng. Khi hai ô có cùng giá trị va chạm, chúng sẽ hợp nhất. Mục tiêu của game là tạo ra một ô có giá trị **2048**.

<img src="https://github.com/buiquangtho/2048-game/photo.png" width="300" height="300">

## 🔧 Chức năng chính

- **Hiển thị giao diện trò chơi** bằng thư viện **SDL2**.
- Hỗ trợ **di chuyển các ô** bằng các phím mũi tên `↑ ↓ ← →`.
- **Cập nhật và hiển thị điểm số**: Tổng điểm của người chơi sẽ được tính và hiển thị, cùng với điểm cao nhất (best score).
- **Âm thanh khi di chuyển ô**: Sử dụng **SDL_mixer** để phát âm thanh khi người chơi di chuyển các ô.
- **Chế độ thoát game**: Phím `ESC` sẽ đóng cửa sổ game và hiển thị điểm số trên một cửa sổ riêng biệt.
- **Chế độ chơi lại**: Khi game kết thúc, người chơi có thể nhấn `SPACE` để chơi lại.
- **Chế độ game-over**: Khi không còn nước đi hợp lệ nào, trò chơi sẽ kết thúc và yêu cầu nhấn `SPACE` để chơi lại.

## 🧠 Logic chính

- **Di chuyển các ô**: Được xử lý bằng cách **xoay bảng** trò chơi, giúp mã chỉ cần xử lý một hướng (chẳng hạn như `left`) và áp dụng cho các hướng còn lại.
- **Gộp ô**: Khi hai ô có giá trị giống nhau va chạm, chúng sẽ gộp lại thành một ô mới có giá trị gấp đôi.
- **spawnNewTile()**: Sau mỗi lượt đi hợp lệ, game sẽ sinh ra một ô mới có giá trị `2` hoặc `4` ngẫu nhiên.
- **isGameOver()**: Kiểm tra xem có còn lượt đi hợp lệ nào không, nếu không game sẽ kết thúc.

## 🎮 Cách chơi

1. **Điều khiển game**: 
   - Dùng các phím mũi tên (`↑ ↓ ← →`) để di chuyển các ô.
   - Khi hai ô có giá trị giống nhau va chạm, chúng sẽ hợp nhất thành một ô mới.
2. **Mục tiêu**: Cố gắng tạo ra một ô có giá trị **2048**.
3. **Thua cuộc**: Khi không còn lượt đi hợp lệ nào, game sẽ kết thúc và yêu cầu nhấn `SPACE` để chơi lại.

## 🎥 Video giới thiệu

**👉 Link video demo & trình bày mã nguồn**: [Xem video demo trên Google Drive](https://drive.google.com/file/d/1HNZAg7l5VvGEOFmdrre2pTAaNW4ceHNB/view?usp=sharing)

*Nội dung video gồm:*
- Giới thiệu cấu trúc mã nguồn.
- Trình bày từng file chính và cách thức hoạt động của game.
- Giải thích về logic xoay bảng, sinh ô mới, và tính điểm.
- Demo cách chơi game và tính năng hiển thị điểm khi game kết thúc.

## 📚 Tham khảo & Tài nguyên

- **Tài nguyên sử dụng**:
  - Font: `Arial.ttf` được tải từ các nguồn trực tuyến.
  - Âm thanh: `move.wav` được tải từ [freesound.org](https://freesound.org/).

## ⚙️ Cấu trúc dự án

- **src/**: Chứa mã nguồn chính của game.
- **assets/**: Chứa các tài nguyên như font, âm thanh, hình ảnh.
- **README.md**: File này, chứa thông tin về dự án.

## 🔧 Cách cài đặt và chạy

1. **Cài đặt các thư viện cần thiết**:
   - Cài đặt SDL2: [SDL2 Installation Guide](https://wiki.libsdl.org/Installation)
   - Cài đặt SDL_ttf và SDL_mixer.
2. **Clone repository**:
   ```bash
   git clone https://github.com/buiquangtho/2048-game.git
   cd 2048-game

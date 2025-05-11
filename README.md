# 🎮 Game 2048 - SDL Edition

## 📌 Mô tả dự án

Đây là phiên bản game 2048 được xây dựng bằng thư viện **SDL2** kết hợp với **SDL_ttf** (hiển thị văn bản) và **SDL_mixer** (âm thanh).  
Người chơi sử dụng các phím mũi tên để di chuyển các ô số. Khi hai ô có cùng giá trị va chạm, chúng sẽ hợp nhất. Mục tiêu là tạo ra ô có giá trị **2048**.

## 🔧 Chức năng chính

- Hiển thị giao diện trò chơi bằng **SDL2**
- Hỗ trợ di chuyển bằng các phím `↑ ↓ ← →`
- Cập nhật và hiển thị **Score** và **Best Score**
- Âm thanh khi di chuyển ô (dùng SDL_mixer)
- Thoát game bằng phím `ESC` sẽ hiển thị Score và Best Score trên cửa sổ riêng
- Khi thua, hiển thị thông báo “Press SPACE to play again”
- Hỗ trợ chơi lại game

## 🧠 Logic chính

- **Di chuyển các ô** được xử lý bằng cách **xoay bảng**, giúp viết mã chỉ cho một hướng (`left`) và sử dụng lại cho các hướng khác.
- **Gộp ô** khi hai ô liền kề có cùng giá trị.
- **spawnNewTile()** sinh ô giá trị `2` hoặc `4` ngẫu nhiên sau mỗi lượt đi hợp lệ.
- **isGameOver()** kiểm tra không còn lượt đi hợp lệ nào.

## 🎥 Video giới thiệu

**👉 Link video demo & trình bày mã nguồn**: https://drive.google.com/file/d/1HNZAg7l5VvGEOFmdrre2pTAaNW4ceHNB/view?usp=sharing

*Nội dung video gồm:*
- Giới thiệu cấu trúc mã nguồn
- Trình bày từng file chính
- Logic xoay bảng, sinh ô mới, tính điểm
- Demo chơi game, tính năng ESC và hiển thị điểm khi thua

## 📚 Tham khảo & Tài nguyên

- **Tài nguyên sử dụng**:
  - Font: `Arial.ttf` được download trên mạng
  - Âm thanh: `move.wav` từ [https://freesound.org/]





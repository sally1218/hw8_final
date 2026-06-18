# 體育器材租借系統 - 編譯和構建指南

## 🔨 編譯環境配置

### 系統要求
- **C++ 標準**：C++17 或更高版本
- **編譯器**：任選其一
  - GCC 7.0 或更高版本
  - Clang 5.0 或更高版本
  - MSVC 2017 或更高版本（Visual Studio 2017+）

### Windows 用戶

#### 安裝 MinGW-w64
1. 下載：https://www.mingw-w64.org/
2. 安裝到 `C:\mingw-w64`
3. 將 `C:\mingw-w64\bin` 添加到系統 PATH

#### 驗證安裝
```bash
g++ --version
cmake --version
```

### Linux/macOS 用戶

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install g++ cmake make
```

#### macOS (使用 Homebrew)
```bash
brew install gcc cmake make
```

#### 驗證安裝
```bash
g++ --version
cmake --version
make --version
```

---

## 🏗️ 構建項目

### 方式 1：使用編譯腳本（Windows）（推薦）

**最簡單、最自動化的方式**

```bash
cd d:\sally_school\大三\物件導向\hw8
build.bat
```

此腳本已經過全面升級，會自動進行以下編譯器偵測與相容性處理：
1. **偵測 MinGW/g++**：若系統中已安裝並配置 `g++`，將優先使用 `g++` 進行模組化編譯，並將產物置於 `obj` 目錄後連結。
2. **自動偵測 Visual Studio (MSVC)**：若找不到 `g++`，會自動透過微軟官方的 `vswhere.exe` 尋找您的 **Visual Studio** 安裝路徑（支援 Community、Professional、Enterprise 版本），載入開發者工具環境 (`VsDevCmd.bat`)，並調用微軟的 C++ 編譯器 `cl.exe` 進行編譯。
3. **解決字元編碼問題**：在 MSVC 編譯時會自動帶上 `/utf-8` 選項，確保源碼中的中文字串常數在 Windows 的 Big5 語系環境下不會因編碼判斷錯誤而產生編譯損毀或語法異常。
4. **排除標頭檔衝突**：本專案在原始碼中已處理 `NOMINMAX` 定義，避免 `<Windows.h>` 與 C++ 標準庫之 `std::max` 巨集衝突。
5. **清理暫存**：編譯成功後會自動清理中間產生的 `.obj` 檔案，維持專案乾淨。

### 方式 2：使用 CMake（推薦）

**跨平臺構建**

```bash
cd d:\sally_school\大三\物件導向\hw8
mkdir build
cd build

# 生成構建文件
cmake ..

# 執行編譯
cmake --build .
```

**Windows (Visual Studio)**
```bash
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

**Linux/macOS**
```bash
cmake ..
make
```

### 方式 3：使用 Makefile（Linux/macOS）

```bash
cd d:\sally_school\大三\物件導向\hw8
make              # 編譯
make run          # 編譯並運行
make clean        # 清理編譯文件
```

### 方式 4：手動 g++ 編譯

```bash
cd d:\sally_school\大三\物件導向\hw8

# 創建輸出目錄
mkdir obj

# 編譯各源文件
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/Equipment.cpp -o ./obj/Equipment.o
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/Ball.cpp -o ./obj/Ball.o
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/Racket.cpp -o ./obj/Racket.o
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/ProtectiveGear.cpp -o ./obj/ProtectiveGear.o
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/RentalRecord.cpp -o ./obj/RentalRecord.o
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/RentalSystem.cpp -o ./obj/RentalSystem.o
g++ -std=c++17 -Wall -Wextra -I./include -c ./src/main.cpp -o ./obj/main.o

# 鏈接成可執行文件
g++ -o rental_system ./obj/*.o
```

---

## ✅ 編譯驗證

編譯成功後，您會看到：

**Windows**
```
✓ 編譯成功！
可執行文件位置: ..\rental_system.exe
```

**Linux/macOS**
```
Linking CXX executable rental_system
[100%] Built target rental_system
```

---

## 🚀 運行程序

編譯完成後，運行可執行文件：

### Windows

#### 推薦方法 (避開中文亂碼)：
為了防止 Windows 終端機預設使用 Big5 (CP950) 導致中文字幕出現亂碼，請使用專案附帶的啟動批次檔：
* **直接雙擊**或在終端機中執行：
  ```bash
  .\START.bat
  ```
  *(此批次檔會自動呼叫 `chcp 65001` 切換編碼至 UTF-8，再啟動 `rental_system.exe`，最後提供 `pause` 防止視窗關閉。)*

#### 在當前 VS Code 終端機 (PowerShell) 中執行：
如果您是在 VS Code 的 Terminal 中，可複製以下指令來暫時切換輸出編碼並執行，防止亂碼：
```powershell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; .\rental_system.exe
```

#### 直接執行 exe（可能會因終端機預設編碼出現亂碼）：
```bash
# 當前目錄中運行
.\rental_system.exe
```

### Linux/macOS
```bash
# 當前目錄中運行
./rental_system

# 或從項目根目錄
./rental_system
```

---

## 🐛 編譯問題排除

### 問題 1：找不到編譯器
```
g++: command not found
```
**解決方案**
- 確認編譯器已安裝
- 確認 PATH 環境變量包含編譯器路徑
- 在 Windows 上，使用開發者命令提示符

### 問題 2：找不到頭文件
```
fatal error: Equipment.h: No such file or directory
```
**解決方案**
- 確認在 `include/` 目錄中有所有 .h 文件
- 確認使用了正確的 `-I./include` 參數

### 問題 3：找不到源文件
```
main.cpp: No such file or directory
```
**解決方案**
- 確認在 `src/` 目錄中有所有 .cpp 文件
- 確認使用了正確的文件路徑

### 問題 4：編譯錯誤（C++17 不支持）
```
error: 'auto' not allowed in function prototype
```
**解決方案**
- 確認使用了 `-std=c++17` 標記
- 更新編譯器版本

### 問題 5：鏈接錯誤
```
undefined reference to `Equipment::Equipment()'
```
**解決方案**
- 確認所有 .cpp 文件都被編譯了
- 確認沒有遺漏任何源文件
- 檢查 .h 和 .cpp 中的函數定義是否匹配

---

## 📊 編譯選項說明

### 常用 g++ 標記

| 標記 | 說明 |
|------|------|
| `-std=c++17` | 使用 C++17 標準 |
| `-Wall` | 啟用所有常見警告 |
| `-Wextra` | 啟用額外警告 |
| `-Wpedantic` | 啟用嚴格的 ISO C++ 檢查 |
| `-I./include` | 指定包含目錄 |
| `-c` | 只編譯，不鏈接 |
| `-o filename` | 指定輸出文件名 |

### 優化選項
```bash
# 發佈版本（優化性能）
g++ -std=c++17 -O2 -I./include src/*.cpp -o rental_system

# 調試版本（包含調試信息）
g++ -std=c++17 -g -I./include src/*.cpp -o rental_system
```

---

## 🔧 配置文件說明

### CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(SportEquipmentRentalSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/Equipment.cpp
    src/Ball.cpp
    src/Racket.cpp
    src/ProtectiveGear.cpp
    src/RentalRecord.cpp
    src/RentalSystem.cpp
)

add_executable(rental_system ${SOURCES})
```

### Makefile
```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDE = -Iinclude

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, obj/%.o, $(SOURCES))
TARGET = rental_system

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf obj $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```

---

## 📦 編譯產物

編譯成功後，產生的文件：

```
hw8/
├── rental_system         # Linux/macOS 可執行文件
├── rental_system.exe     # Windows 可執行文件
├── obj/                  # 編譯的目標文件（.o 文件）
│   ├── main.o
│   ├── Equipment.o
│   ├── Ball.o
│   ├── Racket.o
│   ├── ProtectiveGear.o
│   ├── RentalRecord.o
│   └── RentalSystem.o
└── build/                # CMake 構建目錄（可選）
```

---

## 🧹 清理構建文件

### 刪除編譯產物
```bash
# Linux/macOS (使用 Make)
make clean

# Windows (手動)
rmdir /s /q obj
del rental_system.exe

# CMake
rm -rf build
```

---

## 📈 性能優化編譯

為了獲得最佳性能，使用優化標記：

```bash
# 高度優化
g++ -std=c++17 -O3 -Wall -I./include src/*.cpp -o rental_system_optimized

# 帶調試信息和優化
g++ -std=c++17 -g -O2 -Wall -I./include src/*.cpp -o rental_system_debug
```

---

## 🎯 總結

| 方法 | 難度 | 推薦用途 |
|------|------|---------|
| build.bat | ⭐ 簡單 | Windows 快速編譯 |
| CMake | ⭐⭐ 中等 | 跨平臺專業項目 |
| Makefile | ⭐⭐ 中等 | Linux/macOS |
| 手動 g++ | ⭐⭐⭐ 複雜 | 學習和調試 |

---

**編譯指南版本**：1.0
**最後更新**：2024年

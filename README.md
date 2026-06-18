# 體育器材租借系統 - 項目總結

## 🎯 項目完成情況

本項目是一個完整的 C++ 面向物件課程作業，展示了以下核心概念：

### ✅ 完成的功能

#### 1. 類別繼承結構
- **Equipment（基類）** - 定義所有器材的共同屬性和方法
- **Ball** - 球類器材衍生類
- **Racket** - 拍類器材衍生類  
- **ProtectiveGear** - 保護裝備衍生類
- **RentalRecord** - 獨立的租借紀錄類

#### 2. 文件讀寫功能
- ✅ 設備數據保存到 CSV
- ✅ 設備數據從 CSV 加載
- ✅ 租借紀錄保存到 CSV
- ✅ 租借紀錄從 CSV 加載
- ✅ 自動保存和加載

#### 3. STL 類別庫使用
- ✅ `std::vector` - 容器管理
- ✅ `std::shared_ptr` - 智能指針
- ✅ `std::string` - 字符串操作
- ✅ `std::fstream` - 文件操作
- ✅ `std::algorithm` - 查詢和排序

#### 4. 完整的 UI 操作介面
- ✅ 菜單驅動界面
- ✅ 清屏功能（跨平臺）
- ✅ 美化的輸出格式
- ✅ 分層菜單結構
- ✅ 完整的用戶交互

#### 5. 完整的規格說明與開發迭代流程
- ✅ SPECIFICATION.md - 詳細的規格說明
- ✅ DEVELOPMENT.md - 8個迭代周期的開發流程
- ✅ 每個迭代都有具體的目標和任務

#### 6. 完整的說明文件
- ✅ README.md - 項目總體介紹
- ✅ ARCHITECTURE.md - 系統架構設計
- ✅ USAGE_GUIDE.md - 詳細的使用指南
- ✅ build.bat - Windows 編譯腳本

## 📁 項目結構

```
hw8/
├── Ball.h                     # 球類衍生類頭文件
├── Ball.cpp                   # 球類衍生類實現
├── Equipment.h                # 器材基類頭文件
├── Equipment.cpp              # 器材基類實現
├── ProtectiveGear.h          # 保護裝備頭文件
├── ProtectiveGear.cpp        # 保護裝備實現
├── Racket.h                   # 拍類衍生類頭文件
├── Racket.cpp                 # 拍類衍生類實現
├── RentalRecord.h             # 租借紀錄頭文件
├── RentalRecord.cpp           # 租借紀錄實現
├── RentalSystem.h             # 系統管理類頭文件
├── RentalSystem.cpp           # 系統管理實現
├── main.cpp                   # 主程序與 UI 介面
│
├── data/                      # 數據目錄
│   ├── equipment.csv          # 器材數據
│   └── rental_records.csv     # 租借紀錄
│
├── docs/                      # 文檔目錄
│   ├── README.md              # 項目介紹
│   ├── SPECIFICATION.md       # 規格說明
│   ├── DEVELOPMENT.md         # 開發迭代
│   ├── ARCHITECTURE.md        # 架構設計
│   └── USAGE_GUIDE.md         # 使用指南
│
├── CMakeLists.txt            # CMake 配置
├── Makefile                  # Make 配置
├── build.bat                 # Windows 編譯
└── README.md                 # 本文件
```

## 🚀 快速開始

### 編譯與執行

**Windows (推薦方法 - 避免亂碼)**
```bash
# 1. 執行編譯腳本 (自動偵測並調用 g++ 或 Visual Studio MSVC)
build.bat

# 2. 使用啟動腳本執行 (自動設定為 UTF-8 編碼確保中文顯示正常)
START.bat
```

*如果在 PowerShell 終端機直接執行 `rental_system.exe` 遇到中文亂碼，請改以以下指令啟動：*
```powershell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; .\rental_system.exe
```

**Linux/Mac**
```bash
# 編譯
make

# 執行
./rental_system
```

**使用 CMake**
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 📖 文檔清單

| 文檔 | 位置 | 內容 |
|------|------|------|
| README | docs/README.md | 完整的項目介紹和功能說明 |
| 規格說明 | docs/SPECIFICATION.md | 詳細的功能規格和需求 |
| 開發迭代 | docs/DEVELOPMENT.md | 8個迭代周期的完整過程 |
| 架構設計 | docs/ARCHITECTURE.md | 系統架構和設計模式 |
| 使用指南 | docs/USAGE_GUIDE.md | 詳細的使用說明和示例 |

## 🎓 技術亮點

### C++ 特性展示
- ✅ 類別設計和繼承
- ✅ 虛擬函數和多態性
- ✅ 智能指針（shared_ptr）
- ✅ STL 容器（vector）
- ✅ 文件 I/O 操作
- ✅ 字符串處理

### 軟件工程實踐
- ✅ 需求分析
- ✅ 系統設計
- ✅ 迭代開發
- ✅ 文檔編寫
- ✅ 測試驗證

## 💾 數據格式

### equipment.csv
```
ID,名稱,分類,價格,狀態,類型,詳細信息
1,籃球,球類,50.0,可租,球類-籃球|材料:橡膠|重量:600g|$50
```

### rental_records.csv
```
紀錄ID,器材ID,器材名稱,租借人,租借日期,歸還日期,天數,費用,已歸還
1,1,籃球,張三,2024-01-01,2024-01-03,2,100.0,1
```

## 🔧 系統要求

- **C++ 標準**：C++17
- **編譯器**：GCC 7.0+ 或 MSVC
- **操作系統**：Windows、Linux、macOS

## 📋 主要功能

- 🎯 器材管理（添加、編輯、刪除）
- 🎯 租借管理（租借、歸還、查詢）
- 🎯 搜索功能（按名稱、按分類）
- 🎯 統計分析（收入、用量）
- 🎯 數據持久化（CSV 格式）

## 📞 支援文檔

詳細的使用說明，請參考 [使用指南](docs/USAGE_GUIDE.md)

詳細的開發過程，請參考 [開發迭代](docs/DEVELOPMENT.md)

詳細的系統設計，請參考 [架構設計](docs/ARCHITECTURE.md)

詳細的功能規格，請參考 [規格說明](docs/SPECIFICATION.md)

---

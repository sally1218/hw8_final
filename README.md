# 體育器材租借系統

## 📋 項目簡介

**體育器材租借系統** 是一個使用 C++ 開發的完整租借管理系統，展示了面向物件程設的核心概念，包括類別繼承、多態性、文件操作和 STL 容器的使用。

## 🎯 系統功能

### 核心功能
- ✅ **器材管理**：添加、編輯、刪除體育器材
- ✅ **租借管理**：租借和歸還器材，跟蹤租借紀錄
- ✅ **搜索功能**：按名稱或分類搜索器材
- ✅ **統計分析**：生成系統統計信息和收入報告
- ✅ **文件持久化**：自動保存和加載數據（CSV 格式）

### 器材類別
1. **球類器材**（Ball）：籃球、足球、網球等
2. **拍類器材**（Racket）：網球拍、羽毛球拍等
3. **保護裝備**（ProtectiveGear）：安全帽、護膝、護肘等

## 🏗️ 項目架構

### 類別結構（繼承層次）
```
Equipment (基類)
├── Ball (球類 - 衍生類)
├── Racket (拍類 - 衍生類)
└── ProtectiveGear (保護裝備 - 衍生類)

RentalRecord (獨立類)
RentalSystem (系統管理類)
```

### 文件結構
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

## 💻 技術特性

### C++ 特性使用
- ✅ **類別繼承**：Equipment 基類，三個衍生類
- ✅ **虛擬函數**：實現多態性（displayInfo()、getDetails()）
- ✅ **智能指針**：使用 shared_ptr 管理動態對象
- ✅ **STL 容器**：vector 容器存儲器材和租借紀錄
- ✅ **文件 I/O**：fstream 進行文件讀寫
- ✅ **字符串操作**：string 和 stringstream

### STL 類別庫使用
- `std::vector` - 存儲器材和租借紀錄
- `std::shared_ptr` - 智能指針管理
- `std::string` - 字符串操作
- `std::fstream` / `std::ofstream` / `std::ifstream` - 文件操作
- `std::algorithm` - 算法（find_if）

### UI 特性
- 完整的菜單驅動終端界面
- 清屏功能（跨平臺支持）
- 視覺化的邊框和格式化輸出
- 分頁菜單系統

## 📦 安裝和編譯

### 系統要求
- **操作系統**：Windows、Linux 或 macOS
- **編譯器**：GCC 7+ 或 MSVC (Visual Studio 2017+)
- **C++ 標準**：C++17

### 編譯方式

#### 方式 1：Windows 批處理（推薦）
專案的 `build.bat` 已內建智慧編譯器偵測。直接執行即可：
```bash
build.bat   # 優先偵測並使用 MinGW g++。若無，將自動調用 Visual Studio MSVC (cl.exe) 完成編譯
```

#### 方式 2：使用 CMake（推薦）
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

#### 方式 3：使用 Make (Linux/macOS)
```bash
make        # 編譯
make run    # 編譯並運行
make clean  # 清理
```

#### 方式 4：手動直接編譯
```bash
g++ -std=c++17 -I. *.cpp -o rental_system
```

## 🚀 使用指南

### 啟動系統

**Windows (避免中文亂碼)：**
強烈推薦使用專案根目錄下的 **`START.bat`** 啟動：
```bash
.\START.bat
```
*(該批次檔會自動設定主控台為 UTF-8 編碼 `chcp 65001`，確保介面的中文字幕和表格邊框完美顯示。)*

**VS Code 終端機 (PowerShell)：**
若要在 PowerShell 終端機直接執行 `rental_system.exe`，請複製以下指令：
```powershell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; .\rental_system.exe
```

**Linux/macOS：**
```bash
./rental_system
```

### 主菜單選項
1. **查看所有器材** - 顯示系統中所有器材
2. **查看可租借器材** - 只顯示可用的器材
3. **器材管理** - 添加/編輯/刪除器材
4. **租借管理** - 租借/歸還器材，查看紀錄
5. **搜索器材** - 按名稱或分類搜索
6. **統計信息** - 顯示系統統計數據
7. **退出系統** - 關閉程序

### 使用示例

**租借流程：**
1. 進入"租借管理" → "租借器材"
2. 選擇一件可租借的器材
3. 輸入租借人名稱和租借天數
4. 系統自動計算費用並生成紀錄

**歸還流程：**
1. 進入"租借管理" → "歸還器材"
2. 輸入租借紀錄 ID
3. 系統更新器材狀態為可租借

## 📊 數據存儲

### CSV 文件格式

**equipment.csv**
```
ID,名稱,分類,價格,狀態,類型,詳細信息
1,籃球,球類,50.0,可租,球類-籃球|材料:橡膠|重量:600g|$50
```

**rental_records.csv**
```
紀錄ID,器材ID,器材名稱,租借人,租借日期,歸還日期,天數,費用,已歸還
1,1,籃球,張三,2024-01-01,2024-01-03,2,100.0,1
```

## 🔑 核心類別說明

### Equipment（基類）
```cpp
class Equipment {
private:
    int id;                  // 器材ID
    std::string name;        // 器材名稱
    std::string category;    // 器材分類
    double rentalPrice;      // 租借價格
    bool isAvailable;        // 是否可租
    std::string description; // 描述

public:
    virtual void displayInfo() const;     // 虛擬顯示方法
    virtual std::string getDetails() const;
    // ... 其他方法
};
```

### Ball（衍生類）
```cpp
class Ball : public Equipment {
private:
    std::string ballType;    // 球類型
    std::string material;    // 材料
    double weight;           // 重量

public:
    void displayInfo() const override;    // 覆寫虛擬方法
    std::string getDetails() const override;
    // ... 其他方法
};
```

### RentalSystem（管理類）
```cpp
class RentalSystem {
private:
    std::vector<std::shared_ptr<Equipment>> equipment;  // 器材列表
    std::vector<RentalRecord> rentalRecords;            // 租借紀錄

public:
    void rentEquipment(...);     // 租借器材
    void returnEquipment(...);   // 歸還器材
    void saveAllData();          // 保存所有數據
    void loadAllData();          // 加載所有數據
    // ... 其他方法
};
```

## 📈 開發迭代

詳見 [開發迭代流程文檔](docs/DEVELOPMENT.md)

### 迭代版本
- **v1.0** - 基礎功能（當前版本）
  - 器材管理
  - 租借/歸還功能
  - 基本的搜索和統計

- **v1.1** 計劃
  - 數據驗證和錯誤處理增強
  - 更複雜的查詢功能
  - 報表生成

- **v2.0** 計劃
  - 數據庫支持
  - 用戶認證系統
  - 高級分析功能

## 🛠️ 故障排除

### 常見問題

**Q：編譯時出錯 "找不到頭文件"**
- A：確保在當前目錄中有所有頭文件

**Q：運行時無法寫入文件**
- A：確保 `./data` 目錄存在且有寫入權限

**Q：清屏功能不工作**
- A：系統會根據操作系統自動選擇（Windows 用 `cls`，Linux 用 `clear`）

## 📚 相關文檔

- [規格說明](docs/SPECIFICATION.md)
- [架構設計](docs/ARCHITECTURE.md)
- [開發迭代](docs/DEVELOPMENT.md)
- [使用指南](docs/USAGE_GUIDE.md)


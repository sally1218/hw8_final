# 類別圖與架構說明

> 體育器材租借系統（Sports Equipment Rental System）— UML Class Diagram

---

## 完整類別關係圖

```mermaid
classDiagram
    direction TB

    %% ════════════════════════════════
    %%  抽象基類 Equipment
    %% ════════════════════════════════
    class Equipment {
        <<abstract>>
        #int id
        #string name
        #string category
        #double rentalPrice
        #bool isAvailable
        #string description
        ──────────────────────
        +Equipment()
        +Equipment(id, name, category, price, available, desc)
        +displayInfo() void*
        +getDetails() string*
        +setAvailability(bool) void*
        +getId() int
        +getName() string
        +getCategory() string
        +getRentalPrice() double
        +getAvailability() bool
        +getDescription() string
        +setName(string) void
        +setRentalPrice(double) void
    }

    %% ════════════════════════════════
    %%  子類：Ball
    %% ════════════════════════════════
    class Ball {
        -string ballType
        -string material
        -double weight
        ──────────────────────
        +Ball()
        +Ball(id, name, price, available, type, material, weight)
        +displayInfo() void
        +getDetails() string
        +getBallType() string
        +getMaterial() string
        +getWeight() double
        +setBallType(string) void
        +setMaterial(string) void
        +setWeight(double) void
    }

    %% ════════════════════════════════
    %%  子類：Racket
    %% ════════════════════════════════
    class Racket {
        -string racketType
        -string frameSize
        -string stringTension
        ──────────────────────
        +Racket()
        +Racket(id, name, price, available, type, size, tension)
        +displayInfo() void
        +getDetails() string
        +getRacketType() string
        +getFrameSize() string
        +getStringTension() string
        +setRacketType(string) void
        +setFrameSize(string) void
        +setStringTension(string) void
    }

    %% ════════════════════════════════
    %%  子類：ProtectiveGear
    %% ════════════════════════════════
    class ProtectiveGear {
        -string gearType
        -string size
        -string color
        ──────────────────────
        +ProtectiveGear()
        +ProtectiveGear(id, name, price, available, type, size, color)
        +displayInfo() void
        +getDetails() string
        +getGearType() string
        +getSize() string
        +getColor() string
        +setGearType(string) void
        +setSize(string) void
        +setColor(string) void
    }

    %% ════════════════════════════════
    %%  租借紀錄類：RentalRecord
    %% ════════════════════════════════
    class RentalRecord {
        -int recordId
        -int equipmentId
        -string equipmentName
        -string renterName
        -string rentalDate
        -string returnDate
        -int rentalDays
        -double totalCost
        -bool isReturned
        ──────────────────────
        +RentalRecord()
        +RentalRecord(recordId, equipId, name, renter, rental, return, days, cost, returned)
        +getRecordId() int
        +getEquipmentId() int
        +getEquipmentName() string
        +getRenterName() string
        +getRentalDate() string
        +getReturnDate() string
        +getRentalDays() int
        +getTotalCost() double
        +getIsReturned() bool
        +setReturnDate(string) void
        +setIsReturned(bool) void
        +setTotalCost(double) void
        +displayRecord() void
        +toFileFormat() string
    }

    %% ════════════════════════════════
    %%  系統管理類：RentalSystem
    %% ════════════════════════════════
    class RentalSystem {
        -vector~shared_ptr~Equipment~~ equipment
        -vector~RentalRecord~ rentalRecords
        -string dataDirectory
        -int nextEquipmentId
        -int nextRecordId
        ──────────────────────
        +RentalSystem()
        +initialize() void
        +addEquipment(shared_ptr~Equipment~) void
        +displayAllEquipment() void
        +displayAvailableEquipment() void
        +findEquipmentById(int) shared_ptr~Equipment~
        +deleteEquipment(int) bool
        +editEquipment(int) void
        +rentEquipment(int, string, int) void
        +returnEquipment(int) void
        +displayRentalRecords() void
        +displayUserRentals(string) void
        +displayStatistics() void
        +calculateRevenue() double
        +searchEquipmentByName(string) void
        +searchEquipmentByCategory(string) void
        +saveAllData() void
        +loadAllData() void
        -calculateDaysDifference(string, string) int
    }

    %% ════════════════════════════════
    %%  關係定義
    %% ════════════════════════════════

    %% 繼承（Inheritance）：子類 → 父類
    Equipment <|-- Ball         : 繼承 ▲
    Equipment <|-- Racket       : 繼承 ▲
    Equipment <|-- ProtectiveGear : 繼承 ▲

    %% 組合（Composition）：RentalSystem 擁有並管理
    RentalSystem "1" *-- "0..*" Equipment    : 組合 ◆ 管理所有器材
    RentalSystem "1" *-- "0..*" RentalRecord : 組合 ◆ 管理所有紀錄

    %% 依賴（Dependency）：RentalRecord 透過 equipmentId 參考 Equipment
    RentalRecord ..> Equipment : 依賴 ‥ 參考 equipmentId
```

---

## 關係類型說明

| 符號 | 關係類型 | 本系統中的例子 |
|------|----------|----------------|
| `<\|--` （▲實線） | **繼承 Inheritance** | `Ball`、`Racket`、`ProtectiveGear` 繼承 `Equipment` |
| `*--` （◆實線） | **組合 Composition** | `RentalSystem` 擁有並管理 `Equipment` 與 `RentalRecord` |
| `..>` （虛線箭頭） | **依賴 Dependency** | `RentalRecord` 透過 `equipmentId` 間接參考 `Equipment` |

---

## 繼承層次（Inheritance Hierarchy）

```
Equipment  ← 抽象基類，定義所有器材的共同介面
├── Ball           （球類：籃球、足球、網球 ...）
│       新增屬性：ballType / material / weight
├── Racket         （拍類：羽毛球拍、桌球拍 ...）
│       新增屬性：racketType / frameSize / stringTension
└── ProtectiveGear （護具：頭盔、護膝、護腕 ...）
        新增屬性：gearType / size / color
```

三個子類皆 **override** 以下虛擬方法（實現多型）：

| 方法 | Equipment | Ball | Racket | ProtectiveGear |
|------|:---------:|:----:|:------:|:--------------:|
| `displayInfo()` | `virtual` | `override` | `override` | `override` |
| `getDetails()` | `virtual` | `override` | `override` | `override` |
| `setAvailability()` | `virtual` | ─（繼承） | ─（繼承） | ─（繼承） |

---

## 組合關係（Composition）

`RentalSystem` 以 **smart pointer** 統一管理所有資源：

```cpp
// 多型容器：以基類指標持有所有子類實例
vector<shared_ptr<Equipment>> equipment;

// 存放所有租借紀錄
vector<RentalRecord> rentalRecords;
```

- 所有 `Equipment` 子類（Ball / Racket / ProtectiveGear）透過 `shared_ptr<Equipment>` 儲存
- 呼叫 `equip->displayInfo()` 時，自動執行對應子類的版本（**動態分派**）

---

## 資料流向

```
main.cpp
   │
   │ 建立並操作
   ▼
RentalSystem
   │                          ┌──────────────────────────────┐
   ├─◆── equipment ──────────▶│ shared_ptr<Equipment>        │
   │                          │   可以是 Ball / Racket /      │
   │                          │   ProtectiveGear（多型）      │
   │                          └──────────────────────────────┘
   │
   ├─◆── rentalRecords ──────▶ RentalRecord
   │                               │
   │                               │ equipmentId（外鍵參考）
   │                               └──────────────▶ Equipment
   │
   └─ 讀寫 ──▶ data/equipment.csv
              data/rental_records.csv
```

---

## OOP 四大原則

| 原則 | 實作方式 |
|------|----------|
| **封裝（Encapsulation）** | 屬性宣告為 `private`/`protected`，僅透過 getter/setter 存取 |
| **繼承（Inheritance）** | `Ball`、`Racket`、`ProtectiveGear` 以 `public` 繼承 `Equipment` |
| **多型（Polymorphism）** | `displayInfo()` 與 `getDetails()` 為 `virtual`，子類 `override` |
| **抽象（Abstraction）** | `Equipment` 定義通用介面，隱藏各子類的實作細節 |

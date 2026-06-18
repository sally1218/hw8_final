#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#define NOMINMAX
#include <Windows.h> // ★ 1. 為了支援 SetConsoleOutputCP 引入此標頭檔
#include "RentalSystem.h"
#include "Ball.h"
#include "Racket.h"
#include "ProtectiveGear.h"

using namespace std;

// ============================================================
// ANSI 顏色代碼定義
// ============================================================
namespace Color {
    const string RESET       = "\033[0m";
    const string BOLD        = "\033[1m";
    const string DIM         = "\033[2m";

    // 前景色
    const string BLACK       = "\033[30m";
    const string RED         = "\033[31m";
    const string GREEN       = "\033[32m";
    const string YELLOW      = "\033[33m";
    const string BLUE        = "\033[34m";
    const string MAGENTA     = "\033[35m";
    const string CYAN        = "\033[36m";
    const string WHITE       = "\033[37m";

    // 亮色前景
    const string BR_RED      = "\033[91m";
    const string BR_GREEN    = "\033[92m";
    const string BR_YELLOW   = "\033[93m";
    const string BR_BLUE     = "\033[94m";
    const string BR_MAGENTA  = "\033[95m";
    const string BR_CYAN     = "\033[96m";
    const string BR_WHITE    = "\033[97m";

    // 背景色
    const string BG_BLUE     = "\033[44m";
    const string BG_CYAN     = "\033[46m";
}

class RentalSystemUI {
private:
    RentalSystem system;

    // ──────────────────────────────────────────────
    // 工具方法
    // ──────────────────────────────────────────────

    void enableVirtualTerminal() const {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    void clearScreen() const {
        system_cls();
    }

    void system_cls() const {
        cout << "\033[2J\033[1;1H";
    }

    void pressAnyKeyToContinue() const {
        cout << "\n" << Color::DIM << Color::CYAN
             << "  ─────────────────────────────────────────────\n"
             << "  按 Enter 鍵繼續... "
             << Color::RESET << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    // 印出標題橫幅
    void printBanner(const string& title, const string& color = Color::BR_CYAN) const {
        cout << color << Color::BOLD
             << "\n  ╔══════════════════════════════════════════════════════╗\n"
             << "  ║  " << left << setw(52) << title << "║\n"
             << "  ╚══════════════════════════════════════════════════════╝"
             << Color::RESET << "\n\n";
    }

    // 印出分隔線
    void printDivider(const string& color = Color::DIM) const {
        cout << color
             << "  ──────────────────────────────────────────────────────"
             << Color::RESET << "\n";
    }

    // 印出成功訊息
    void printSuccess(const string& msg) const {
        cout << "\n  " << Color::BR_GREEN << Color::BOLD
             << "✔  " << Color::RESET << Color::BR_GREEN << msg
             << Color::RESET << "\n";
    }

    // 印出錯誤訊息
    void printError(const string& msg) const {
        cout << "\n  " << Color::BR_RED << Color::BOLD
             << "✘  " << Color::RESET << Color::BR_RED << msg
             << Color::RESET << "\n";
    }

    // 印出提示訊息
    void printInfo(const string& msg) const {
        cout << "  " << Color::BR_YELLOW << "⚡ " << Color::RESET
             << Color::YELLOW << msg << Color::RESET << "\n";
    }

    // 印出輸入提示
    void printPrompt(const string& label) const {
        cout << "\n  " << Color::BR_WHITE << Color::BOLD << "► " << Color::RESET
             << Color::WHITE << label << ": " << Color::RESET;
    }

    // ──────────────────────────────────────────────
    // 主選單
    // ──────────────────────────────────────────────

    void displayMainMenu() const {
        clearScreen();

        // ASCII Art 標題
        cout << "\n";
        cout << Color::BR_CYAN << Color::BOLD;
        cout << "  ██████████████████████████████████████████████████████\n";
        cout << "  ██                                                  ██\n";
        cout << "  ██   ★  體育器材租借系統  Sports Rental v1.0  ★   ██\n";
        cout << "  ██                                                  ██\n";
        cout << "  ██████████████████████████████████████████████████████\n";
        cout << Color::RESET << "\n";

        // 選單框
        cout << Color::BOLD << Color::CYAN
             << "  ╔══════════════════════════════════════╗\n"
             << "  ║           ◈  主  選  單  ◈           ║\n"
             << "  ╠══════════════════════════════════════╣\n"
             << Color::RESET;

        auto menuItem = [&](const string& num, const string& icon, const string& text) {
            cout << Color::CYAN << "  ║  "
                 << Color::BR_YELLOW << Color::BOLD << "[" << num << "]"
                 << Color::RESET << "  "
                 << Color::WHITE << icon << "  " << left << setw(26) << text
                 << Color::CYAN << "║\n" << Color::RESET;
        };

        menuItem("1", "📋", "查看所有器材");
        menuItem("2", "✅", "查看可租借器材");
        cout << Color::CYAN << "  ╠══════════════════════════════════════╣\n" << Color::RESET;
        menuItem("3", "⚙️ ", "器材管理");
        menuItem("4", "🔑", "租借管理");
        menuItem("5", "🔍", "搜尋器材");
        menuItem("6", "📊", "統計信息");
        cout << Color::CYAN << "  ╠══════════════════════════════════════╣\n" << Color::RESET;
        menuItem("7", "🚪", "退出系統");

        cout << Color::CYAN
             << "  ╚══════════════════════════════════════╝\n"
             << Color::RESET;

        printPrompt("請選擇 (1-7)");
    }

    // ──────────────────────────────────────────────
    // 子選單
    // ──────────────────────────────────────────────

    void displayEquipmentMenu() const {
        cout << "\n"
             << Color::BOLD << Color::MAGENTA
             << "  ┌──────────────────────────────────────┐\n"
             << "  │          ⚙️   器 材 管 理              │\n"
             << "  ├──────────────────────────────────────┤\n"
             << Color::RESET;

        auto subItem = [&](const string& num, const string& text) {
            cout << Color::MAGENTA << "  │  "
                 << Color::BR_YELLOW << "[" << num << "]"
                 << Color::RESET << "  " << Color::WHITE << left << setw(29) << text
                 << Color::MAGENTA << "  │\n" << Color::RESET;
        };

        subItem("1", "➕  添加新器材");
        subItem("2", "✏️   編輯器材");
        subItem("3", "🗑️   刪除器材");
        subItem("4", "◄   返回主選單");

        cout << Color::MAGENTA
             << "  └──────────────────────────────────────┘\n"
             << Color::RESET;

        printPrompt("請選擇 (1-4)");
    }

    void displayRentalMenu() const {
        cout << "\n"
             << Color::BOLD << Color::BLUE
             << "  ┌──────────────────────────────────────┐\n"
             << "  │          🔑  租 借 管 理              │\n"
             << "  ├──────────────────────────────────────┤\n"
             << Color::RESET;

        auto subItem = [&](const string& num, const string& text) {
            cout << Color::BLUE << "  │  "
                 << Color::BR_YELLOW << "[" << num << "]"
                 << Color::RESET << "  " << Color::WHITE << left << setw(29) << text
                 << Color::BLUE << "  │\n" << Color::RESET;
        };

        subItem("1", "📤  租借器材");
        subItem("2", "📥  歸還器材");
        subItem("3", "📜  查看所有租借紀錄");
        subItem("4", "👤  查看用戶租借紀錄");
        subItem("5", "◄   返回主選單");

        cout << Color::BLUE
             << "  └──────────────────────────────────────┘\n"
             << Color::RESET;

        printPrompt("請選擇 (1-5)");
    }

    void displayAddEquipmentMenu() const {
        cout << "\n"
             << Color::BOLD << Color::GREEN
             << "  ┌──────────────────────────────────────┐\n"
             << "  │          ➕  選 擇 器 材 類 型        │\n"
             << "  ├──────────────────────────────────────┤\n"
             << Color::RESET;

        auto subItem = [&](const string& num, const string& text) {
            cout << Color::GREEN << "  │  "
                 << Color::BR_YELLOW << "[" << num << "]"
                 << Color::RESET << "  " << Color::WHITE << left << setw(29) << text
                 << Color::GREEN << "  │\n" << Color::RESET;
        };

        subItem("1", "⚽  球類器材");
        subItem("2", "🏓  拍類器材");
        subItem("3", "🦺  保護裝備");
        subItem("4", "◄   返回");

        cout << Color::GREEN
             << "  └──────────────────────────────────────┘\n"
             << Color::RESET;

        printPrompt("請選擇 (1-4)");
    }

    // ──────────────────────────────────────────────
    // 功能頁面
    // ──────────────────────────────────────────────

    void addNewEquipment() {
        clearScreen();
        printBanner("➕  添加新器材", Color::BR_GREEN);
        displayAddEquipmentMenu();

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 4) return;

        if (choice < 1 || choice > 3) {
            printError("無效的選擇，請重試");
            pressAnyKeyToContinue();
            return;
        }

        printDivider(Color::BR_GREEN);
        cout << "\n";
        string name;
        double price;

        printPrompt("器材名稱");
        getline(cin, name);
        printPrompt("租借價格 ($/天)");
        cin >> price;
        cin.ignore();

        if (choice == 1) {
            string ballType, material;
            double weight;
            cout << "\n";
            printInfo("球類器材資料");
            printPrompt("球類型 (例：籃球、足球)");
            getline(cin, ballType);
            printPrompt("材料 (例：橡膠、皮革)");
            getline(cin, material);
            printPrompt("重量 (克)");
            cin >> weight;

            auto ball = make_shared<Ball>(0, name, price, true, ballType, material, weight);
            system.addEquipment(ball);

        } else if (choice == 2) {
            string racketType, frameSize, stringTension;
            cout << "\n";
            printInfo("拍類器材資料");
            printPrompt("拍類型 (例：網球拍)");
            getline(cin, racketType);
            printPrompt("拍面大小 (L/M/S)");
            getline(cin, frameSize);
            printPrompt("弦張力 (例：60磅)");
            getline(cin, stringTension);

            auto racket = make_shared<Racket>(0, name, price, true, racketType, frameSize, stringTension);
            system.addEquipment(racket);

        } else if (choice == 3) {
            string gearType, size, color;
            cout << "\n";
            printInfo("保護裝備資料");
            printPrompt("裝備類型 (例：頭盔、護膝)");
            getline(cin, gearType);
            printPrompt("尺寸 (S/M/L/XL)");
            getline(cin, size);
            printPrompt("顏色");
            getline(cin, color);

            auto gear = make_shared<ProtectiveGear>(0, name, price, true, gearType, size, color);
            system.addEquipment(gear);
        }

        pressAnyKeyToContinue();
    }

    void editEquipmentUI() {
        clearScreen();
        printBanner("✏️   編輯器材", Color::BR_MAGENTA);
        system.displayAllEquipment();
        printDivider();
        printPrompt("輸入要編輯的器材 ID");
        int id;
        cin >> id;
        system.editEquipment(id);
        pressAnyKeyToContinue();
    }

    void deleteEquipmentUI() {
        clearScreen();
        printBanner("🗑️   刪除器材", Color::BR_RED);
        system.displayAllEquipment();
        printDivider();
        printPrompt("輸入要刪除的器材 ID");
        int id;
        cin >> id;
        system.deleteEquipment(id);
        pressAnyKeyToContinue();
    }

    void rentEquipmentUI() {
        clearScreen();
        printBanner("📤  租借器材", Color::BR_CYAN);
        system.displayAvailableEquipment();
        printDivider();
        printPrompt("輸入器材 ID");
        int equipmentId;
        cin >> equipmentId;
        cin.ignore();
        printPrompt("租借人姓名");
        string renterName;
        getline(cin, renterName);
        printPrompt("租借天數");
        int days;
        cin >> days;
        system.rentEquipment(equipmentId, renterName, days);
        pressAnyKeyToContinue();
    }

    void returnEquipmentUI() {
        clearScreen();
        printBanner("📥  歸還器材", Color::BR_BLUE);
        system.displayRentalRecords();
        printDivider();
        printPrompt("輸入租借紀錄 ID");
        int recordId;
        cin >> recordId;
        system.returnEquipment(recordId);
        pressAnyKeyToContinue();
    }

    void searchEquipmentUI() {
        clearScreen();
        printBanner("🔍  搜尋器材", Color::BR_YELLOW);

        cout << Color::BOLD << Color::YELLOW
             << "  ┌──────────────────────────────────────┐\n"
             << "  │            🔍  搜 尋 方 式            │\n"
             << "  ├──────────────────────────────────────┤\n"
             << Color::RESET;

        auto subItem = [&](const string& num, const string& text) {
            cout << Color::YELLOW << "  │  "
                 << Color::BR_YELLOW << "[" << num << "]"
                 << Color::RESET << "  " << Color::WHITE << left << setw(29) << text
                 << Color::YELLOW << "  │\n" << Color::RESET;
        };

        subItem("1", "🔤  依名稱搜尋");
        subItem("2", "🏷️   依分類搜尋");
        subItem("3", "◄   返回");

        cout << Color::YELLOW
             << "  └──────────────────────────────────────┘\n"
             << Color::RESET;

        printPrompt("請選擇");
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            printPrompt("輸入器材名稱");
            string name;
            getline(cin, name);
            system.searchEquipmentByName(name);

        } else if (choice == 2) {
            cout << "\n"
                 << Color::BOLD << Color::YELLOW
                 << "  ┌──────────────────────────────────────┐\n"
                 << "  │            🏷️   選 擇 分 類            │\n"
                 << "  ├──────────────────────────────────────┤\n"
                 << Color::RESET;

            auto catItem = [&](const string& num, const string& text) {
                cout << Color::YELLOW << "  │  "
                     << Color::BR_YELLOW << "[" << num << "]"
                     << Color::RESET << "  " << Color::WHITE << left << setw(29) << text
                     << Color::YELLOW << "  │\n" << Color::RESET;
            };

            catItem("1", "⚽  球類");
            catItem("2", "🏓  拍類");
            catItem("3", "🦺  保護裝備");

            cout << Color::YELLOW
                 << "  └──────────────────────────────────────┘\n"
                 << Color::RESET;

            printPrompt("請選擇");
            int catChoice;
            cin >> catChoice;

            string category;
            if (catChoice == 1) category = "球類";
            else if (catChoice == 2) category = "拍類";
            else if (catChoice == 3) category = "保護裝備";
            else {
                printError("無效的選擇");
                pressAnyKeyToContinue();
                return;
            }
            system.searchEquipmentByCategory(category);

        } else if (choice != 3) {
            printError("無效的選擇");
        }

        pressAnyKeyToContinue();
    }

    void displayUserRentalsUI() {
        clearScreen();
        printBanner("👤  查看用戶租借紀錄", Color::BR_BLUE);
        printPrompt("輸入用戶姓名");
        string renterName;
        cin.ignore();
        getline(cin, renterName);
        system.displayUserRentals(renterName);
        pressAnyKeyToContinue();
    }

    // ──────────────────────────────────────────────
    // 選單處理
    // ──────────────────────────────────────────────

    void handleEquipmentMenu() {
        bool running = true;
        while (running) {
            clearScreen();
            printBanner("⚙️   器材管理", Color::BR_MAGENTA);
            displayEquipmentMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: addNewEquipment();    break;
                case 2: editEquipmentUI();    break;
                case 3: deleteEquipmentUI();  break;
                case 4: running = false;      break;
                default:
                    printError("無效的選擇，請重試");
                    pressAnyKeyToContinue();
            }
        }
    }

    void handleRentalMenu() {
        bool running = true;
        while (running) {
            clearScreen();
            printBanner("🔑  租借管理", Color::BR_BLUE);
            displayRentalMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: rentEquipmentUI();      break;
                case 2: returnEquipmentUI();    break;
                case 3: {
                    clearScreen();
                    printBanner("📜  所有租借紀錄", Color::BR_BLUE);
                    system.displayRentalRecords();
                    pressAnyKeyToContinue();
                    break;
                }
                case 4: displayUserRentalsUI(); break;
                case 5: running = false;        break;
                default:
                    printError("無效的選擇，請重試");
                    pressAnyKeyToContinue();
            }
        }
    }

public:
    void run() {
        enableVirtualTerminal();
        system.initialize();

        bool running = true;
        while (running) {
            displayMainMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: {
                    clearScreen();
                    printBanner("📋  所有器材列表", Color::BR_CYAN);
                    system.displayAllEquipment();
                    pressAnyKeyToContinue();
                    break;
                }
                case 2: {
                    clearScreen();
                    printBanner("✅  可租借器材列表", Color::BR_GREEN);
                    system.displayAvailableEquipment();
                    pressAnyKeyToContinue();
                    break;
                }
                case 3: handleEquipmentMenu();  break;
                case 4: handleRentalMenu();     break;
                case 5: searchEquipmentUI();    break;
                case 6: {
                    clearScreen();
                    printBanner("📊  系統統計信息", Color::BR_YELLOW);
                    system.displayStatistics();
                    pressAnyKeyToContinue();
                    break;
                }
                case 7: {
                    clearScreen();
                    cout << "\n\n"
                         << Color::BR_CYAN << Color::BOLD
                         << "  ╔══════════════════════════════════════════════════════╗\n"
                         << "  ║                                                      ║\n"
                         << "  ║       感謝使用體育器材租借系統！ 再見！  👋           ║\n"
                         << "  ║                                                      ║\n"
                         << "  ║             Sports Rental System v1.0               ║\n"
                         << "  ║                                                      ║\n"
                         << "  ╚══════════════════════════════════════════════════════╝\n"
                         << Color::RESET << "\n\n";
                    running = false;
                    break;
                }
                default:
                    printError("無效的選擇，請輸入 1-7");
                    pressAnyKeyToContinue();
            }
        }
    }
};

int main() {
    // ★ 2. 在程式一啟動時，將控制台輸出編碼改為 UTF-8
    SetConsoleOutputCP(65001);

    try {
        RentalSystemUI ui;
        ui.run();
    } catch (const exception& e) {
        cerr << "發生錯誤: " << e.what() << endl;
        return 1;
    }
    return 0;
}
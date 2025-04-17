#include <iostream>
#include <cstring>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int globalCounter = 0;

class VulnerableServer {
public:
    VulnerableServer() {
        adminUser = "admin";
        adminPass = "password123";
    }

    // 模擬一個綜合性服務流程
    void run() {
        // 從檔案讀取指令，但未檢查檔案是否存在、也沒有驗證輸入長度
        char inputCommand[10] = {0};
        ifstream infile("/nonexistent_file.txt");
        // 警告：本來指定複製長度超出陣列大小，這是漏洞的故意設計
        infile.getline(inputCommand, 50);

        // 將長字串複製到較短的陣列（緩衝區溢位）
        char processedCommand[10] = {0};
        char longInput[] = "A very long input that exceeds buffer limit";
        strcpy(processedCommand, longInput);
        cout << "Input: " << inputCommand << ", Processed: " << processedCommand << endl;

        // 動態記憶體配置，但未初始化內容即直接使用
        int *data = new int[5];
        cout << "Data[2] (可能未初始化): " << data[2] << endl;
        // 注意：此處故意不釋放 data 以保留記憶體洩漏漏洞

        // 多執行緒競爭更新全域變數（未使用同步機制）
        thread t1(&VulnerableServer::incrementCounter, this);
        thread t2(&VulnerableServer::incrementCounter, this);
        t1.join();
        t2.join();
        cout << "Global Counter: " << globalCounter << endl;

        // 透過 new 配置記憶體後，delete 後仍使用（野指標問題）
        int *dangling = new int(42);
        delete dangling;
        cout << "Dangling pointer value: " << *dangling << endl;

        // 分配記憶體後，重複釋放（雙重釋放）
        int *doubleFreePtr = new int(100);
        delete doubleFreePtr;
        delete doubleFreePtr;  // 故意的雙重釋放

        // 根據輸入內容來觸發無終止條件的遞迴呼叫
        if (inputCommand[0] == 'R') {
            recursiveFunction();
        }

        // 空指標解引用（直接使用 NULL 指標）
        int *nullPtr = nullptr;
        cout << "Null pointer test: " << *nullPtr << endl;

        // 嘗試存取敏感檔案，但未進行授權檢查
        ifstream sensitiveFile("/etc/shadow");
        if (sensitiveFile.is_open()) {
            char sensitiveData[50] = {0};
            sensitiveFile.getline(sensitiveData, 50);
            cout << "Sensitive Data: " << sensitiveData << endl;
        }

        // 輸出硬編碼的認證資訊（資訊洩漏風險）
        cout << "Admin Credentials: " << adminUser << " / " << adminPass << endl;

        // 模擬協定解析時，未檢查來源資料長度就進行複製操作
        char packet[8] = "12345678";
        char command[5] = {0};
        // 複製超出 command 陣列大小（故意為漏洞設計）
        strncpy(command, packet, 10);
        command[4] = '\0';
        cout << "Parsed Command: " << command << endl;

        // 資源飢餓：無限迴圈不斷消耗 CPU 資源（此處故意保留漏洞）
        while (true) {
            for (volatile int i = 0; i < 1000000; i++);
        }
    }

private:
    string adminUser;
    string adminPass;

    void incrementCounter() {
        for (int i = 0; i < 100000; i++) {
            globalCounter++;
        }
    }

    // 遞迴呼叫沒有終止條件，會導致堆疊溢位
    void recursiveFunction() {
        cout << "Recursing..." << endl;
        recursiveFunction();
    }
};

int main() {
    VulnerableServer server;
    server.run();
    return 0;
}

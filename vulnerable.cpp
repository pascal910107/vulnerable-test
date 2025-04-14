#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// ---------------------------------------
// 【漏洞 1】：緩衝區溢位 (Buffer Overflow)
// 寫入超出陣列長度，覆蓋其他記憶體空間。
void bufferOverflow() {
    char buffer[10];
    // 使用 strcpy 並寫入超過 buffer 長度的字串
    strcpy(buffer, "這個字串超出緩衝區的長度");
}

// ---------------------------------------
// 【漏洞 2】：堆疊溢位 (Stack Overflow)
// 無終止條件的遞迴呼叫，最終耗盡堆疊空間。
void stackOverflow() {
    stackOverflow(); // 遞迴無終止條件
}

// ---------------------------------------
// 【漏洞 3】：使用未初始化記憶體 (Use of Uninitialized Memory)
void uninitializedMemory() {
    int *ptr; // 未初始化
    cout << "未初始化變數的值: " << *ptr << endl;
}

// ---------------------------------------
// 【漏洞 4】：空指標解引用 (Null Pointer Dereference)
void nullPointerDereference() {
    int *p = NULL;
    cout << "空指標解引用: " << *p << endl;
}

// ---------------------------------------
// 【漏洞 5】：野指標 / 使用後釋放 (Dangling Pointer / Use-after-free)
void danglingPointer() {
    int *p = (int*) malloc(sizeof(int));
    *p = 10;
    free(p);
    // 釋放後依然使用
    cout << "使用後釋放的記憶體: " << *p << endl;
}

// ---------------------------------------
// 【漏洞 6】：記憶體洩漏 (Memory Leak)
void memoryLeak() {
    int *leak = new int[100];
    // 未釋放分配的記憶體
}

// ---------------------------------------
// 【漏洞 7】：雙重釋放 (Double Free)
void doubleFree() {
    int *p = (int*) malloc(sizeof(int));
    free(p);
    free(p); // 重複釋放同一記憶體
}

// ---------------------------------------
// 【漏洞 8】：未驗證輸入 (Improper Input Validation)
void improperInputValidation() {
    char input[10];
    cout << "請輸入資料: ";
    // 使用 >> 輸入時未限制長度，可能造成溢位
    cin >> input;
    cout << "你輸入了: " << input << endl;
}

// ---------------------------------------
// 【漏洞 9】：條件競爭 (Race Condition)
// 兩個執行緒同時對共享變數操作，缺乏同步機制。
int sharedCounter = 0;
void* raceCondition(void* arg) {
    for (int i = 0; i < 1000; i++) {
        sharedCounter++; // 沒有互斥鎖，可能出現競爭狀況
    }
    return NULL;
}

// ---------------------------------------
// 【漏洞 10】：邏輯錯誤 (Logic Flaw)
void logicFlaw() {
    int a = 5, b = 10;
    if (a > b) { // 比較條件錯誤
        cout << "a 大於 b" << endl;
    } else {
        cout << "邏輯錯誤：條件判斷不符預期" << endl;
    }
}

// ---------------------------------------
// 【漏洞 11】：死循環 / 無限迴圈 (Infinite Loop)
void infiniteLoop() {
    while (true) {
        // 永遠不跳出的迴圈
    }
}

// ---------------------------------------
// 【漏洞 12】：未處理錯誤 (Uncaught Exceptions / Error Handling Flaws)
void unhandledError() {
    FILE *fp = fopen("nonexistent.txt", "r");
    // 未檢查 fp 是否為 NULL
    char buffer[100];
    fread(buffer, sizeof(char), 100, fp); // 可能導致錯誤
    fclose(fp);
}

// ---------------------------------------
// 【漏洞 13】：硬編碼金鑰或密碼 (Hardcoded Credentials / Keys)
void hardcodedCredentials() {
    string username = "admin";
    string password = "password123";
    cout << "硬編碼的認證資訊: " << username << " / " << password << endl;
}

// ---------------------------------------
// 【漏洞 14】：未授權存取 (Unauthorized Access)
// 模擬對系統敏感檔案存取
void unauthorizedAccess() {
    FILE *fp = fopen("/etc/shadow", "r");
    if (fp) {
        cout << "存取 /etc/shadow (未授權存取)" << endl;
        fclose(fp);
    } else {
        cout << "未授權存取嘗試被攔截" << endl;
    }
}

// ---------------------------------------
// 【漏洞 15】：資訊洩漏 (Information Disclosure)
void informationDisclosure() {
    cout << "敏感資訊：SecretKey=ABC123" << endl;
}

// ---------------------------------------
// 【漏洞 16】：資源飢餓 (Resource Starvation)
// 模擬透過忙碌迴圈耗盡 CPU 資源
void resourceStarvation() {
    while (true) {
        // 無限忙碌迴圈
    }
}

// ---------------------------------------
// 【漏洞 17】：通訊協定解析錯誤 (Improper Parsing)
// 模擬對網路封包格式解析錯誤
void protocolParsingError() {
    char packet[5] = {0x41, 0x42, 0x43, 0x44, 0x45}; // 假定封包資料不完整
    int length = *((int*)packet); // 錯誤的解析，將前四個位元組當作長度
    cout << "解析得到的長度: " << length << endl;
}

// ---------------------------------------
// 【漏洞 18】：多平台差異 / 不當使用關鍵字 (Portability Issues / Misuse of keywords)
// 使用條件編譯處理平台差異，但若未正確處理，可能導致可攜性問題。
void portabilityIssues() {
#ifdef _WIN32
    Sleep(1000);
#else
    sleep(1);
#endif
}

int main() {
    cout << "執行漏洞示範程式..." << endl;

    // 為避免程式直接崩潰或進入無窮迴圈，請依需求逐一取消下列函式的註解進行測試

    // bufferOverflow();
    // stackOverflow(); // 執行後將導致堆疊溢位，程式崩潰
    // uninitializedMemory();
    // nullPointerDereference();
    // danglingPointer();
    // memoryLeak();
    // doubleFree();
    // improperInputValidation();

    // 條件競爭示範
    pthread_t t1, t2;
    pthread_create(&t1, NULL, raceCondition, NULL);
    pthread_create(&t2, NULL, raceCondition, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    cout << "共享計數器: " << sharedCounter << endl;

    logicFlaw();
    // infiniteLoop(); // 會造成程式無限迴圈，請小心測試
    unhandledError();
    hardcodedCredentials();
    unauthorizedAccess();
    informationDisclosure();
    // resourceStarvation(); // 請勿在生產環境執行
    protocolParsingError();
    portabilityIssues();

    return 0;
}

#include "HashTable.h"
#include <iostream>
#include <string>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

void showMenu() {
    std::cout << "\n╔══════════════════════════════════════╗" << std::endl;
    std::cout << "║       简 易 哈 希 通 讯 录          ║" << std::endl;
    std::cout << "╠══════════════════════════════════════╣" << std::endl;
    std::cout << "║  1. 添加联系人                      ║" << std::endl;
    std::cout << "║  2. 删除联系人                      ║" << std::endl;
    std::cout << "║  3. 精确查找                        ║" << std::endl;
    std::cout << "║  4. 模糊查找                        ║" << std::endl;
    std::cout << "║  5. 显示全部联系人                  ║" << std::endl;
    std::cout << "║  6. 显示哈希表结构                  ║" << std::endl;
    std::cout << "║  0. 退出                            ║" << std::endl;
    std::cout << "╚══════════════════════════════════════╝" << std::endl;
    std::cout << "请输入选项：";
}

// 清空 cin >> 之后残留的换行符
void clearNewline() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 读取一行输入（不含前导换行）
std::string readLine() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int main() {
#ifdef _WIN32
    // 设置控制台编码为 UTF-8，解决中文乱码问题
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    HashTable contacts(11);  // 使用较小的质数便于观察冲突处理

    // 预置一些示例数据，方便测试冲突和查找
    contacts.add("张三", "13800001111");
    contacts.add("李四", "13900002222");
    contacts.add("王五", "13600003333");
    contacts.add("张三丰", "13500004444");  // 可能与"张三"发生冲突
    contacts.add("赵六", "13700005555");
    contacts.add("王小明", "13400006666");

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            clearNewline();
            std::cout << "输入无效，请输入数字！" << std::endl;
            continue;
        }
        clearNewline();  // 消费 cin >> choice 留下的换行符

        switch (choice) {
        case 1: {  // 添加联系人
            std::cout << "请输入姓名：";
            std::string name = readLine();
            std::cout << "请输入电话：";
            std::string phone = readLine();
            contacts.add(name, phone);
            break;
        }
        case 2: {  // 删除联系人
            std::cout << "请输入要删除的姓名：";
            std::string name = readLine();
            contacts.remove(name);
            break;
        }
        case 3: {  // 精确查找
            std::cout << "请输入要查找的姓名：";
            std::string name = readLine();
            Contact* result = contacts.exactSearch(name);
            if (result) {
                std::cout << "【找到】" << result->name
                          << " - " << result->phone << std::endl;
            } else {
                std::cout << "【未找到】\"" << name << "\"" << std::endl;
            }
            break;
        }
        case 4: {  // 模糊查找
            std::cout << "请输入姓名关键字：";
            std::string keyword = readLine();
            auto results = contacts.fuzzySearch(keyword);
            if (results.empty()) {
                std::cout << "【未找到】没有姓名包含 \"" << keyword << "\" 的联系人。" << std::endl;
            } else {
                std::cout << "\n========== 模糊查找结果（共 " << results.size()
                          << " 条）==========" << std::endl;
                for (size_t i = 0; i < results.size(); ++i) {
                    std::cout << "  " << (i + 1) << ". "
                              << results[i].name << " - " << results[i].phone << std::endl;
                }
                std::cout << "=========================================" << std::endl;
            }
            break;
        }
        case 5: {  // 显示全部
            contacts.displayAll();
            break;
        }
        case 6: {  // 显示哈希表结构（展示桶分布和冲突链）
            std::cout << "\n当前哈希表容量：" << contacts.size() << " 条记录" << std::endl;
            contacts.displayAll();
            break;
        }
        case 0: {
            std::cout << "再见！" << std::endl;
            return 0;
        }
        default:
            std::cout << "无效选项，请重新输入！" << std::endl;
            break;
        }
    }

    return 0;
}

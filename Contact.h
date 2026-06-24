#ifndef CONTACT_H
#define CONTACT_H

#include <string>

// 联系人结构体：存储姓名和电话号码
struct Contact {
    std::string name;   // 联系人姓名（作为哈希键）
    std::string phone;  // 电话号码

    Contact() = default;
    Contact(const std::string& n, const std::string& p)
        : name(n), phone(p) {}
};

#endif

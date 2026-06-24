#include "HashTable.h"
#include <iostream>
#include <algorithm>

// ==================== 构造函数 ====================
HashTable::HashTable(int tableSize)
    : tableSize(tableSize), count(0) {
    buckets.resize(tableSize);
}

// ==================== 哈希函数 ====================
// 采用乘法哈希 + 模运算，对字符串每个字符加权求和
int HashTable::hash(const std::string& key) const {
    unsigned long hashVal = 0;
    // 乘数因子 31（类似 Java String.hashCode），分散性好
    for (char ch : key) {
        hashVal = hashVal * 31 + static_cast<unsigned char>(ch);
    }
    return static_cast<int>(hashVal % tableSize);
}

// ==================== 添加联系人 ====================
bool HashTable::add(const std::string& name, const std::string& phone) {
    int index = hash(name);

    // 先检查该桶的同名联系人是否已存在
    for (const auto& contact : buckets[index]) {
        if (contact.name == name) {
            std::cout << "【提示】联系人 \"" << name << "\" 已存在！" << std::endl;
            return false;
        }
    }

    // 不存在则添加到桶链表尾部
    buckets[index].emplace_back(name, phone);
    ++count;
    std::cout << "【成功】已添加：" << name << " - " << phone << std::endl;
    return true;
}

// ==================== 删除联系人（精确匹配） ====================
bool HashTable::remove(const std::string& name) {
    int index = hash(name);

    auto& bucket = buckets[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->name == name) {
            std::cout << "【成功】已删除：" << it->name << " - " << it->phone << std::endl;
            bucket.erase(it);
            --count;
            return true;
        }
    }

    std::cout << "【失败】未找到联系人 \"" << name << "\"" << std::endl;
    return false;
}

// ==================== 模糊查找 ====================
// 遍历所有桶，返回姓名中包含 keyword（大小写不敏感）的联系人
std::vector<Contact> HashTable::fuzzySearch(const std::string& keyword) const {
    std::vector<Contact> results;

    // 将关键字转为小写用于不区分大小写的匹配
    std::string lowerKey = keyword;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    for (const auto& bucket : buckets) {
        for (const auto& contact : bucket) {
            std::string lowerName = contact.name;
            std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                           [](unsigned char c) { return std::tolower(c); });

            // 子串匹配
            if (lowerName.find(lowerKey) != std::string::npos) {
                results.push_back(contact);
            }
        }
    }

    return results;
}

// ==================== 精确查找 ====================
Contact* HashTable::exactSearch(const std::string& name) {
    int index = hash(name);

    for (auto& contact : buckets[index]) {
        if (contact.name == name) {
            return &contact;
        }
    }
    return nullptr;
}

// ==================== 显示所有联系人 ====================
void HashTable::displayAll() const {
    if (count == 0) {
        std::cout << "通讯录为空。" << std::endl;
        return;
    }

    std::cout << "\n========== 通讯录（共 " << count << " 人）==========" << std::endl;
    for (int i = 0; i < tableSize; ++i) {
        if (!buckets[i].empty()) {
            std::cout << "桶[" << i << "]: ";
            bool first = true;
            for (const auto& contact : buckets[i]) {
                if (!first) std::cout << "  ->  ";
                std::cout << contact.name << " | " << contact.phone;
                first = false;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "=======================================" << std::endl;
}

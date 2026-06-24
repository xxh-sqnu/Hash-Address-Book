#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Contact.h"
#include <list>
#include <vector>
#include <string>

/*
 * 哈希通讯录类
 * - 哈希表存储联系人
 * - 链地址法（Separate Chaining）处理哈希冲突
 * - 支持增删、模糊查找
 */
class HashTable {
public:
    // 构造函数：tableSize 为桶数量，取质数利于散列
    explicit HashTable(int tableSize = 101);

    // 添加联系人，成功返回 true，姓名已存在返回 false
    bool add(const std::string& name, const std::string& phone);

    // 删除联系人（精确匹配姓名），成功返回 true
    bool remove(const std::string& name);

    // 模糊查找：返回姓名中包含 keyword 的所有联系人
    std::vector<Contact> fuzzySearch(const std::string& keyword) const;

    // 精确查找
    Contact* exactSearch(const std::string& name);

    // 显示所有联系人
    void displayAll() const;

    // 获取当前联系人总数
    int size() const { return count; }

private:
    // 哈希函数：对姓名字符串求哈希值
    int hash(const std::string& key) const;

    // 桶数量
    int tableSize;

    // 当前存储的联系人数量
    int count;

    // 哈希桶数组：每个桶是一个链表，解决冲突
    std::vector<std::list<Contact>> buckets;
};

#endif

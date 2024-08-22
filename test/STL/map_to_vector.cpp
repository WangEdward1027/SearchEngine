#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility> // 包含 std::pair

int main() {
    // 示例map
    std::map<std::string, int> _dict_cn;
    _dict_cn["apple"] = 3;
    _dict_cn["banana"] = 2;
    _dict_cn["cherry"] = 1;

    // 用来存储map键值对的vector
    std::vector<std::pair<std::string, int>> _dict_cn_vec;

    // 遍历map，并将每个键值对添加到vector中
    for (const auto& pair : _dict_cn) {
        _dict_cn_vec.push_back(pair);
    }

    // 打印vector的内容以验证
    for (const auto& pair : _dict_cn_vec) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}

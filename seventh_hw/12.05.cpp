#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype> 
#include <cassert>


auto hexstr_to_bytes(const std::string& hex_str) {
    if (hex_str.size() % 2 != 0) {
        throw std::invalid_argument("Строка должна содержать чётное количество символов");
    }

    std::vector<unsigned char> bytes;
    bytes.reserve(hex_str.size() / 2);

    for (size_t i = 0; i < hex_str.size(); i += 2) {
        if (!std::isxdigit(hex_str[i]) || !std::isxdigit(hex_str[i + 1])) {
            throw std::invalid_argument("Некорректный шестнадцатеричный символ");
        }

        unsigned char byte = static_cast<unsigned char>(
            (std::stoi(hex_str.substr(i, 2), nullptr, 16))
        );
        bytes.push_back(byte);
    }

    return bytes;
}

int main() {
    try {
        std::vector<unsigned char> expected{ 0xBA, 0xAD, 0xF0, 0x0D, 0x42 };
        assert(hexstr_to_bytes("BAADF00D42") == expected);
        assert(hexstr_to_bytes("BaaDf00d42") == expected);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}
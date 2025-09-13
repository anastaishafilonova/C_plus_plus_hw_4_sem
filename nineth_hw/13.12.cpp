#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <pugixml.hpp>

using namespace std::literals;

int main()
{
    auto string = "aaaaa"s;
    std::vector<int> vector = {1, 2, 3, 4, 5};

    auto path = "output.xml"s;

    pugi::xml_document doc;
    auto root = doc.append_child("root");

    root.append_child("string").text().set(string.c_str());

    auto vecNode = root.append_child("vector");
    for (int val : vector)
        vecNode.append_child("item").text().set(val);

    root.append_child("x").append_child("y").text().set(1);

    doc.save_file(path.c_str(), PUGIXML_TEXT("  "));

    std::cout << "Enter number to continue^ "; std::cin.get();

    pugi::xml_document loaded;
    pugi::xml_parse_result result = loaded.load_file(path.c_str());
    assert(result);

    auto loadedRoot = loaded.child("root");

    assert(loadedRoot.child("string").text().as_string() == string);

    auto loadedVector = loadedRoot.child("vector");
    std::vector<int> loadedVec;
    for (auto item : loadedVector.children("item"))
        loadedVec.push_back(item.text().as_int());
    assert(loadedVec == vector);

    assert(loadedRoot.child("x").child("y").text().as_int() == 1);

    std::filesystem::remove(path);
}
#include <string> 
#include <regex> 
#include <iostream> 
#include <iomanip> 

int main()
{
    std::string data = "XML tag: <tag-name>the value</tag-name>.";
    std::cout << "Data: " << data << "\n\n";

    std::smatch m; // для возвращаемой информации о соответствии
    bool found = std::regex_search(data, m, std::regex("<(.*)>(.*)</\\1>"));

    // вывод данных соответствий
    std::cout << "m.empty(): " << std::boolalpha << m.empty() << std::endl;
    std::cout << "m.size(): " << m.size() << std::endl;

    if (found) {
        std::cout << "m.str(): " << m.str() << std::endl;
        std::cout << "m.length(): " << m.length() << std::endl;
        std::cout << "m.position(): " << m.position() << std::endl;
        std::cout << "m.prefix().str(): " << m.prefix().str() << std::endl;
        std::cout << "m.suffix().str(): " << m.suffix().str() << std::endl;

        // перебор всех соответствий с помощью индекса соответствия
        for (int i = 0; i < m.size(); ++i) {
            std::cout << "m[" << i << "]: " << m[i].str() << std::endl;
            std::cout << "m.str(" << i << "): " << m.str(i) << std::endl;
            std::cout << "m.position(" << i << "): " << m.position(i) << std::endl;
        }

        // перебор всех соответствий с помощью итератора
        std::cout << "Matches: " << std::endl;
        for (auto pos = m.begin(); pos != m.end(); ++pos) {
            std::cout << "match: " << *pos << std::endl;
            std::cout << "length: " << pos->length() << std::endl;
        }
    }

    return 0;
}

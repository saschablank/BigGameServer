#include <string>
#include <vector>
#include <string_view>

class StringHelper {
public:
    static std::vector<std::string_view> split(std::string_view str, char delimiter) {
        std::vector<std::string_view> result;
        size_t start = 0;

        while (start < str.size()) {
            size_t end = str.find(delimiter, start);
            if (end == std::string_view::npos)
                end = str.size();
            result.emplace_back(str.substr(start, end - start));
            start = end + 1;
        }

        return result;
    }
};
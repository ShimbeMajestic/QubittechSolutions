#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

class JSON {
private:
    std::unordered_map<std::string, std::string> data;
public:
    void add(const std::string& key, const std::string& value) {
        data[key] = value;
    }

    std::string get(const std::string& key) const {
        auto it = data.find(key);
        return it != data.end() ? it->second : "";
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "{ ";
        for (auto it = data.begin(); it != data.end(); ++it) {
            oss << "\"" << it->first << "\": \"" << it->second << "\"";
            if (std::next(it) != data.end()) oss << ", ";
        }
        oss << " }";
        return oss.str();
    }

    static JSON parse(const std::string& jsonStr) {
        JSON json;
        std::istringstream iss(jsonStr);
        std::string key, value;
        char ch;
        while (iss >> ch) {
            if (ch == '\"') {
                getline(iss, key, '\"');
                iss >> ch >> ch;
                getline(iss, value, '\"');
                json.add(key, value);
            }
        }
        return json;
    }
};

int main() {
    // Creating a JSON object
    JSON json;
    json.add("name", "Shimbe Majestic");
    json.add("age", "25");

    // Printing JSON string
    std::cout << "JSON Object: " << json.toString() << std::endl;

    // Parse JSON string
    std::string jsonStr = "{\"city\": \"Dar es salaam\", \"country\": \"Tanzania\"}";
    JSON parsedJson = JSON::parse(jsonStr);
    std::cout << "Parsed JSON - City: " << parsedJson.get("city") << std::endl;
    std::cout << "Parsed JSON - Country: " << parsedJson.get("country") << std::endl;

    return 0;
}

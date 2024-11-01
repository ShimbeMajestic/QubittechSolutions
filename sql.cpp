#include <iostream>
#include <string>
#include <vector>

class SQLBuilder {
private:
    std::string query;
public:
    SQLBuilder& select(const std::string& columns) {
        query = "SELECT " + columns;
        return *this;
    }

    SQLBuilder& from(const std::string& table) {
        query += " FROM " + table;
        return *this;
    }

    SQLBuilder& where(const std::string& condition) {
        query += " WHERE " + condition;
        return *this;
    }

    SQLBuilder& insertInto(const std::string& table, const std::vector<std::string>& columns, const std::vector<std::string>& values) {
        query = "INSERT INTO " + table + " (";
        for (size_t i = 0; i < columns.size(); ++i) {
            query += columns[i] + (i < columns.size() - 1 ? ", " : "");
        }
        query += ") VALUES (";
        for (size_t i = 0; i < values.size(); ++i) {
            query += "'" + values[i] + "'" + (i < values.size() - 1 ? ", " : "");
        }
        query += ")";
        return *this;
    }

    SQLBuilder& deleteFrom(const std::string& table) {
        query = "DELETE FROM " + table;
        return *this;
    }

    SQLBuilder& limit(int n) {
        query += " LIMIT " + std::to_string(n);
        return *this;
    }

    std::string build() const {
        return query + ";";
    }
};

int main() {
    // Example usage of the SQL Builder; some sql queries constructed are
    SQLBuilder sql;
    std::string selectQuery = sql.select("*").from("users").where("age > 18").limit(10).build();
    std::string insertQuery = sql.insertInto("users", {"name", "age"}, {"Shimbe Majestic", "30"}).build();
    std::string deleteQuery = sql.deleteFrom("users").where("age < 18").build();

    // Output results
    std::cout << "Select Query: " << selectQuery << std::endl;
    std::cout << "Insert Query: " << insertQuery << std::endl;
    std::cout << "Delete Query: " << deleteQuery << std::endl;

    return 0;
}

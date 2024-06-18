#include <iostream>
#include <string>
#include <algorithm>

class big_integer {
public:
    big_integer() = default;

    explicit big_integer(const std::string& value) : value_(value) {
        std::reverse(value_.begin(), value_.end()); // Сохраняем число в перевернутом виде для удобства операций
    }

    big_integer(big_integer&& other) noexcept : value_(std::move(other.value_)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            value_ = std::move(other.value_);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        std::string result;
        int carry = 0;
        size_t max_size = std::max(value_.size(), other.value_.size());

        for (size_t i = 0; i < max_size || carry; ++i) {
            int digit_a = i < value_.size() ? value_[i] - '0' : 0;
            int digit_b = i < other.value_.size() ? other.value_[i] - '0' : 0;
            int sum = digit_a + digit_b + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        std::reverse(result.begin(), result.end()); 
        return big_integer(result);
    }

    big_integer operator*(int number) const {
        if (number == 0) {
            return big_integer("0");
        }

        std::string result;
        int carry = 0;

        for (size_t i = 0; i < value_.size() || carry; ++i) {
            int digit = i < value_.size() ? value_[i] - '0' : 0;
            int product = digit * number + carry;
            carry = product / 10;
            result.push_back(product % 10 + '0');
        }

        std::reverse(result.begin(), result.end()); 
        return big_integer(result);
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& number) {
        std::string str = number.value_;
        std::reverse(str.begin(), str.end());
        os << str;
        return os;
    }

private:
    std::string value_;
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl; // 193099

    auto number3 = big_integer("12345");
    auto result2 = number3 * 2;
    std::cout << result2 << std::endl; // 24690

    return 0;
}

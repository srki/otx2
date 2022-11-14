#ifndef OTX_OTX_H
#define OTX_OTX_H

#include <initializer_list>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <optional>
#include <sstream>


namespace otx {

/* region Exceptions */

class OtxException : public std::exception {
};

class NotFound : public OtxException {
public:
    NotFound() = default;

    explicit NotFound(const std::vector<std::string> &argNames) {
        _message = "Cannot find argument: ";
        for (auto it = argNames.cbegin(); it != argNames.cend(); ++it) {
            if (it != argNames.cbegin()) {
                _message += " | ";
            }
            _message += *it;
        }
    }

    [[nodiscard]] const char *what() const noexcept override {
        return _message.empty() ? exception::what() : _message.c_str();
    }

protected:
    std::string _message{};
};

class IncorrectFormat : public OtxException {
};

class InternalError : public OtxException {
};

class UninitializedError : public OtxException {
};

/*endregion */

class Option {
public:
    explicit Option(std::optional<std::string> value, std::initializer_list<std::string> names)
            : _valueOpt{std::move(value)}, _names(names) {}

    template<typename T>
    std::enable_if_t<!std::is_array_v<T>, T> to() {
        if (!_valueOpt) { throw otx::NotFound(_names); }
        std::string value = _valueOpt.value();

        if constexpr (std::is_same_v<T, bool>) {
            std::transform(value.begin(), value.end(), value.begin(),
                           [](char c) { return std::tolower(c); });
            if (value == "false" || value == "0") { return false; }
            if (value == "true" || value == "1") { return true; }
            if (value.empty() || value[0] == '-') { return true; }
            throw IncorrectFormat{};
        }

        return parse<T>(value);
    }

    template<typename T, typename U = std::remove_all_extents_t<T>>
    std::enable_if_t<std::is_array_v<T>, std::vector<U>> to() {
        const std::string delimiter = ",";

        if (!_valueOpt) { throw otx::NotFound(_names); }
        std::string value = _valueOpt.value();

        std::vector<std::remove_all_extents_t<T>> result;

        size_t start = 0, end = value.find(delimiter);
        while (end != std::string::npos) {
            result.template emplace_back(parse<U>(value.substr(start, end - start)));
            start = end + delimiter.length();
            end = value.find(delimiter, start);
        }
        result.template emplace_back(parse<U>(value.substr(start, end - start)));

        return result;
    }

    template<typename T, typename U = std::remove_all_extents_t<T>, typename V>
    std::conditional_t<std::is_array_v<T>, std::vector<U>, T> to(const V &defaultValue) {
        if constexpr (std::is_array_v<T>) {
            return std::vector<U>{defaultValue};
        } else {
            return defaultValue;
        }
    }

private:
    const std::vector<std::string> _names;
    const std::optional<std::string> _valueOpt;

    template<typename T>
    T parse(const std::string &s) {
        std::stringstream ss{s};
        T t{};
        ss >> t;
        if (ss.fail() || !ss.eof()) {
            throw IncorrectFormat{};
        }
        return t;
    }
};

class OptParse {

public:
    OptParse(int argc, const char * const argv[]) : _argc(argc), _argv(argv) {}

    OptParse(int argc, const char * const argv[], std::ostream &os) : OptParse(argc, argv) {
        printArgs(os);
    }

    Option operator[](const std::initializer_list<std::string> &names) {
        return Option{findArg(names), names};
    };

    template<typename ...Ts>
    Option operator[](Ts ...names) {
        return operator[](std::initializer_list<std::string>{names...});
    }

private:
    const int _argc;
    char const *const *_argv;

    std::optional<std::string> findArg(const std::initializer_list<std::string> &names) {
        for (int i = 0; i < _argc; ++i) {
            std::string arg = _argv[i];

            for (const auto &name: names) {
                // --name value
                if (arg.length() == name.length()) {
                    if (arg != name) { continue; }
                    return std::string{i + 1 < _argc ? _argv[i + 1] : ""};
                }

                // --name=value
                if (arg.length() > name.length()) {
                    if (arg.rfind(name + "=", 0) != 0) { continue; }
                    return std::string{arg.substr(name.length() + 1)};
                }
            }
        }

        return std::nullopt;
    }

    void printArgs(std::ostream &os, const std::string &suffix = "\n") {
        for (int i = 0; i < _argc; ++i) {
            os << _argv[i] << " ";
        }
        os << suffix;
    }
};

}

#endif //OTX_OTX_H

#pragma once

#include <algorithm>
#include <string>
#include <cwctype>

struct StringHelper {
    static bool compareCaseInsensitive(const std::wstring &left, const std::wstring &right) {
        const auto size = left.size();
        if (size != right.size()) {
            return false;
        }

        for (auto i = 0u; i < size; i++) {
            if (::tolower(left[i]) != ::tolower(right[i])) {
                return false;
            }
        }

        return true;
    }

    static std::wstring basename(const std::wstring &path) {
        const size_t backslashIndex = path.find_last_of('\\');
        const size_t frontslashIndex = path.find_last_of('/');
        if (backslashIndex == std::wstring::npos && frontslashIndex == std::wstring::npos) {
            return 0u;
        }

        const auto fileNameStartIndex = ((frontslashIndex != std::wstring::npos) ? frontslashIndex : backslashIndex) + 1;
        return path.substr(fileNameStartIndex);
    }

    static std::wstring deleteSpaces(std::wstring str) {
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
        return str;
    }

    static std::wstring stripTrashFromFilename(const std::wstring &str) {
        // Strip trash from the end
        const static std::wstring trashChars = L"0123456789-_ \t.";
        auto trailingTrash = 0u;
        for (auto it = str.rbegin(); it < str.rend(); it++) {
            if (trashChars.find(*it) == std::wstring::npos) {
                break;
            }
            trailingTrash++;
        }
        std::wstring result = str.substr(0, str.size() - trailingTrash);

        // Delete whitespace from the middle
        result.erase(std::remove_if(result.begin(), result.end(), isspace), result.end());
        return result;
    }

    static std::wstring toLower(const std::wstring &str) {
        std::wstring result(str.size(), ' ');
        std::transform(str.begin(), str.end(), result.begin(), [](wchar_t c) { return std::towlower(c); });
        return result;
    }

    static bool isSubstringCaseInsensitive(const std::wstring &str, const std::wstring &pattern) {
        const auto strLower = toLower(str);
        const auto patternLower = toLower(pattern);
        return strLower.find(patternLower) != std::wstring::npos;
    }

    static std::wstring getFileNameWithoutExtension(const std::wstring &path) {
        const size_t fileNameStartIndex = 0u;
        const size_t dotIndex = path.find_last_of('.');
        if (dotIndex == std::wstring::npos || dotIndex < fileNameStartIndex) {
            return path.substr(fileNameStartIndex);
        }
        return path.substr(fileNameStartIndex, dotIndex - fileNameStartIndex);
    }

    static std::wstring getFileNameExtension(const std::wstring &path) {
        const size_t fileNameStartIndex = 0u;
        const size_t dotIndex = path.find_last_of('.');
        if (dotIndex == std::wstring::npos || dotIndex < fileNameStartIndex) {
            return std::wstring{};
        }
        return path.substr(dotIndex + 1);
    }
};

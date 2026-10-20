/***************************************
* Автор:   Сатин Владимир              *
* Группа:  ПИ-261                      *
* Задание: Строки, векторы и словари   *
* Вариант: 10                          *
***************************************/

#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  size_t maxTextLength = 200;
  size_t maxKeyLength = 40;
  int maxCount = 100;
  int maxMagnitude = 1000;
  int maxAsciiCode = 127;
  string partChoice;

  if (!getline(cin, partChoice)) {
    cout << "INVALID" << endl;
    return 1;
  }

  if (partChoice == "A") {
    string text;
    string lowerText;

    if (!getline(cin, text) || text.size() > maxTextLength) {
      cout << "INVALID" << endl;
      return 1;
    }
    for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      if (static_cast<unsigned char>(text[symbolIndex]) > maxAsciiCode) {
        cout << "INVALID" << endl;
        return 1;
      }
    }

    for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      lowerText += static_cast<char>(tolower(static_cast<unsigned char>(text[symbolIndex])));
    }

    if (lowerText.empty()) {
      cout << "EMPTY" << endl;
    } else {
      cout << lowerText << endl;
    }
  } else if (partChoice == "B") {
    int elementCount;
    int value;
    vector<int> values;
    vector<int> reversedValues;

    if (!(cin >> elementCount) || elementCount < 0 || elementCount > maxCount) {
      cout << "INVALID" << endl;
      return 1;
    }
    for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
      if (!(cin >> value) || value < -maxMagnitude || value > maxMagnitude) {
        cout << "INVALID" << endl;
        return 1;
      }
      values.push_back(value);
    }

    for (size_t elementIndex = 0; elementIndex < values.size(); ++elementIndex) {
      reversedValues.push_back(values[values.size() - 1 - elementIndex]);
    }

    if (reversedValues.empty()) {
      cout << "EMPTY" << endl;
    } else {
      for (size_t elementIndex = 0; elementIndex < reversedValues.size(); ++elementIndex) {
        if (elementIndex > 0) {
          cout << ' ';
        }
        cout << reversedValues[elementIndex];
      }
      cout << endl;
    }
  } else if (partChoice == "C") {
    int pairCount;
    int value;
    int increment;
    string key;
    string queryKey;
    vector<string> keyList;
    vector<int> valueList;
    map<string, int> dictionary;
    bool isValid;

    if (!(cin >> pairCount) || pairCount < 0 || pairCount > maxCount) {
      cout << "INVALID" << endl;
      return 1;
    }
    for (int pairIndex = 0; pairIndex < pairCount; ++pairIndex) {
      if (!(cin >> key >> value) || value < -maxMagnitude || value > maxMagnitude) {
        cout << "INVALID" << endl;
        return 1;
      }
      keyList.push_back(key);
      valueList.push_back(value);
    }
    if (!(cin >> queryKey >> increment) || increment < -maxMagnitude || increment > maxMagnitude) {
      cout << "INVALID" << endl;
      return 1;
    }
    // The query key follows the same rules, so it is checked together with the pair keys
    keyList.push_back(queryKey);
    isValid = true;
    for (size_t keyIndex = 0; keyIndex < keyList.size(); ++keyIndex) {
      if (keyList[keyIndex].size() > maxKeyLength) {
        isValid = false;
      }
      for (size_t symbolIndex = 0; symbolIndex < keyList[keyIndex].size(); ++symbolIndex) {
        if (static_cast<unsigned char>(keyList[keyIndex][symbolIndex]) > maxAsciiCode) {
          isValid = false;
        }
      }
    }
    if (!isValid) {
      cout << "INVALID" << endl;
      return 1;
    }

    // A repeated key keeps the last entered value
    for (size_t pairIndex = 0; pairIndex < valueList.size(); ++pairIndex) {
      dictionary[keyList[pairIndex]] = valueList[pairIndex];
    }
    // Operator [] creates a missing key with 0 before the increment is added
    dictionary[queryKey] += increment;

    for (map<string, int>::const_iterator entry = dictionary.begin(); entry != dictionary.end(); ++entry) {
      cout << entry->first << ' ' << entry->second << endl;
    }
  } else if (partChoice == "D") {
    int recordCount;
    int atCount;
    size_t atPosition;
    bool hasSpace;
    bool isValid;
    string name;
    string email;
    string field;
    vector<string> fieldNames;
    vector<map<string, string>> records;
    vector<string> result;

    if (!(cin >> recordCount) || recordCount < 0 || recordCount > maxCount) {
      cout << "INVALID" << endl;
      return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int recordIndex = 0; recordIndex < recordCount; ++recordIndex) {
      if (!getline(cin, name) || !getline(cin, email)) {
        cout << "INVALID" << endl;
        return 1;
      }
      records.push_back({{"name", name}, {"email", email}});
    }
    fieldNames = {"name", "email"};
    isValid = true;
    for (size_t recordIndex = 0; recordIndex < records.size(); ++recordIndex) {
      for (size_t fieldIndex = 0; fieldIndex < fieldNames.size(); ++fieldIndex) {
        if (records[recordIndex].find(fieldNames[fieldIndex]) == records[recordIndex].end()) {
          isValid = false;
        } else {
          field = records[recordIndex].at(fieldNames[fieldIndex]);
          if (field.empty() || field.size() > maxTextLength || field.front() == ' ' || field.back() == ' ') {
            isValid = false;
          }
          for (size_t symbolIndex = 0; symbolIndex < field.size(); ++symbolIndex) {
            if (static_cast<unsigned char>(field[symbolIndex]) > maxAsciiCode) {
              isValid = false;
            }
          }
        }
      }
    }
    if (!isValid) {
      cout << "INVALID" << endl;
      return 1;
    }

    for (size_t recordIndex = 0; recordIndex < records.size(); ++recordIndex) {
      email = records[recordIndex].at("email");
      atCount = 0;
      atPosition = 0;
      hasSpace = false;
      for (size_t symbolIndex = 0; symbolIndex < email.size(); ++symbolIndex) {
        if (email[symbolIndex] == '@') {
          ++atCount;
          atPosition = symbolIndex;
        }
        if (email[symbolIndex] == ' ') {
          hasSpace = true;
        }
      }
      // The @ needs at least one symbol on each side
      if (atCount != 1 || atPosition == 0 || atPosition == email.size() - 1 || hasSpace) {
        result.push_back(records[recordIndex].at("name"));
      }
    }

    if (result.empty()) {
      cout << "EMPTY" << endl;
    } else {
      for (size_t resultIndex = 0; resultIndex < result.size(); ++resultIndex) {
        cout << result[resultIndex] << endl;
      }
    }
  } else {
    cout << "INVALID" << endl;
    return 1;
  }

  return 0;
}

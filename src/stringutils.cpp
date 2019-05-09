#include "stringutils.h"

vector<string> splitString (string sentence, string delimiter) {
  string word;
  int start = 0;
  int senLen = sentence.length();
  vector<string> words;

  for (int i = 0; i < senLen; i++) {
    char c = sentence[i];
    if (delimiter.find(c) != std::string::npos) {
      words.push_back(sentence.substr(start, i - start));
      start = i+1;
    } else if (i == senLen - 1) {
      words.push_back(sentence.substr(start, std::string::npos));
    }
  }

  return words;
}

vector<string> splitString (string sentence) {
  return splitString(sentence, " ");
}

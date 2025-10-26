#include <string>

/**
 * TODO: description
 */


const char* Alpha[26] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    ".._.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};
const char* Digit[10] = {
    "-----",// 0
    ".----",// 1
    "..---",// 2
    "...--",// 3
    "....-",// 4
    ".....",// 5
    "-....",// 6
    "--...",// 7
    "---..",// 8
    "----.",// 9
};

std::string decodeMorse(const std::string& morseCode) {
    int current = 0, ahead = 1, wpos = 1, i;
    char* word;
    std::string result;
    for (; ahead <= morseCode.size(); ahead++) {
        if (morseCode[current] == ' ' && morseCode[ahead] == ' ' ) {
            result += ' ';
            ahead++;
        } else if (morseCode[ahead] == *morseCode.end() || morseCode[ahead] == ' ')
        { // && morseCode[current] != ' '
            if (wpos < 1) {
                continue;
            }
            word = new char[wpos];
            
            for (i = 0; wpos > 0; i++, wpos--)
                word[i] = morseCode[ahead - wpos];
            
            for (i = 0; i < 26; i++) {
                if (strcmp(Alpha[i], word) == 0) {
                    result += (char)('A' + i);
                    break;
                }
            }
            for (i = 0; i < 10; i++) {
                if (strcmp(Digit[i], word) == 0) {
                    result += (char)i;
                    break;
                }
            }
            delete [] word;
        } else if (wpos < 5) {
            wpos++;
        }
        current = ahead;
    }
    return result;
}

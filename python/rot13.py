def rot13(message):
    result = []

    for char in message:
        if char.islower():
            result.append(chr((ord(char) - ord('a') + 13) % 26 + ord('a')))
        elif char.isupper():
            result.append(chr((ord(char) - ord('A') + 13) % 26 + ord('A')))
        else:
            result.append(char)

    return "".join(result)

if __name__ == '__main__':
    assert rot13('test') == 'grfg'
    assert rot13('Test') == 'Grfg'
    assert rot13('aA bB zZ 1234 *!?%') == 'nN oO mM 1234 *!?%'
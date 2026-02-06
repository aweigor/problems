# https://www.codewars.com/kata/58e24788e24ddee28e000053
from argparse import ArgumentError


def brain_luck(code, program_input):
    pi = list(program_input)
    data = [0] * 3000
    code_ptr = 0
    data_ptr = 0
    input_ptr = 0
    nested_depth = 0
    output = ''
    while code_ptr < len(code):
        match code[code_ptr]:
            case '>':
                data_ptr += 1
            case '<':
                data_ptr -= 1
            case '+':
                data[data_ptr] += 1
                data[data_ptr] %= 256
            case '-':
                data[data_ptr] -= 1
                data[data_ptr] %= 256
            case '.':
                output += chr(data[data_ptr])
            case ',':
                inp = ord(pi[input_ptr])
                input_ptr += 1
                data[data_ptr] = inp
            case '[':
                if data[data_ptr] == 0:
                    while code_ptr < len(code):
                        code_ptr += 1
                        if code[code_ptr] == '[':
                            nested_depth += 1
                        elif code[code_ptr] == ']':
                            if nested_depth != 0:
                                nested_depth -= 1
                            else:
                                break
            case ']':
                if data[data_ptr] != 0:
                    while code_ptr > -1:
                        code_ptr -= 1
                        if code[code_ptr] == ']':
                            nested_depth += 1
                        elif code[code_ptr] == '[':
                            if nested_depth != 0:
                                nested_depth -= 1
                            else:
                                break
            case _:
                raise ValueError("unknown command")
        code_ptr += 1
    return output


def assert_equals(actual, expected, error):
    print(f'testing {actual}')
    if actual != expected:
        raise RuntimeError(error)

def run_test(code, program_input, expected):
    actual = brain_luck(code, program_input)
    assert_equals(actual, expected, f'expected {expected}, got {actual}')


def sample_tests():
    #program1 = ',+[-.,+]'
    program2 = ',[.[-],]'
    #run_test(program1, 'Codewars' + chr(255), 'Codewars')
    run_test(program2, 'Codewars' + chr(0), 'Codewars')

if __name__ == '__main__':
    sample_tests()
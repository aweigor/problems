# https://www.codewars.com/kata/5314b3c6bb244a48ab00076c/

def luck_check(st):
    left = [int(x) for x in st[:len(st)//2]]
    right = [int(x) for x in st[len(st)//2:]]
    rightSum = sum(right) if len(st) % 2 == 0 else sum(right) - int(st[len(st)//2])
    return sum(left) == rightSum


def luck_check_minimal(string):
    int(string)  # quick error check
    half = len(string) // 2
    return sum(map(int, string[:half])) == sum(map(int, string[-half:]))

def assert_equals(actual, expected):
    if actual != expected:
        raise RuntimeError()

def expect_error(error, fun):
    try:
        fun()
    except:
        return True
    raise RuntimeError(error)

def fixed_tests():
    def basic_test_cases():
        assert_equals(luck_check('5555'), True)
        assert_equals(luck_check('003111'), True)
        assert_equals(luck_check('543970707'), False)
        assert_equals(luck_check('439924'), False)
        assert_equals(luck_check('943294329932'), False)
        assert_equals(luck_check('000000'), True)
        assert_equals(luck_check('454319'), True)
        assert_equals(luck_check('1233499943'), False)
        assert_equals(luck_check('935336'), False)
        expect_error("Invalid type value should throw error.", lambda : luck_check('6F43E8'))
        expect_error("Invalid type value should throw error.", lambda : luck_check('1234 '))
        expect_error("Invalid type value should throw error.", lambda : luck_check('124-21'))
        expect_error("Invalid type value should throw error.", lambda : luck_check('124X212'))

    basic_test_cases()

if __name__ == '__main__':
    fixed_tests()
# https://www.codewars.com/kata/568ff914fc7a40a18500005c
import ipaddress
import math
import string
from collections import Counter

from numpy import mean
from ipaddress import IPv4Address

class PaginationHelper:

    # The constructor takes in an array of items and an integer indicating
    # how many items fit within a single page
    def __init__(self, collection, items_per_page):
        self.collection = collection
        self.items_per_page = items_per_page
        pass

    # returns the number of items within the entire collection
    def item_count(self):
        return len(self.collection)
        pass

    # returns the number of pages
    def page_count(self):
        return math.ceil(len(self.collection) / self.items_per_page)
        pass

    # returns the number of items on the given page. page_index is zero based
    # this method should return -1 for page_index values that are out of range
    def page_item_count(self, page_index):
        page_count = self.page_count()
        item_count = self.item_count()
        if 0 <= page_index < page_count:
            if page_index == page_count - 1:
                return item_count - (page_count - 1) * self.items_per_page
            return self.items_per_page
        return -1

    # determines what page an item at the given index is on. Zero based indexes.
    # this method should return -1 for item_index values that are out of range
    def page_index(self, item_index):
        if 0 <= item_index < self.item_count():
            return item_index // self.items_per_page
        return -1
        pass


def distances_from_average(test_list):
    avg = mean(test_list)
    return [round(avg - x, 2) for x in test_list]

def ips_between(start, end):
    return int(IPv4Address(end)) - int(IPv4Address(start))

def ips_between__oneliner(start, end):
    a = sum([int(e)*256**(3-i) for i, e in enumerate(start.split('.'))])
    b = sum([int(e)*256**(3-i) for i, e in enumerate(end.split('.'))])
    return abs(a-b)

# https://www.codewars.com/kata/529b418d533b76924600085d
def to_underscore(string: str) -> str:
    for i, char in enumerate(string):
        if not char.isalpha():
            continue
        elif i == 0:
            string = char.lower() + string[1:]
        elif char.isupper():
            return string[:i] + '_' + to_underscore(string[i:])
    return string


# https://www.codewars.com/kata/53af2b8861023f1d88000832
def areYouPlayingBanjo(name):
    if name[0].lower() == 'r':
        return "{} plays banjo".format(name)
    return "{} does not play banjo".format(name)

# https://www.codewars.com/kata/514a024011ea4fb54200004b
def domain_name(url):
    if "//" in url:
        parts = url.split("//", 1)
        after_slash = parts[1]
    else:
        after_slash = url

    domain = after_slash.split("/")[0]
    domain_parts = after_slash.split(".")

    if domain_parts[0] == "www":
        return domain_parts[1]
    else:
        return domain_parts[0]

def domain_name_clean(url):
    return url.split("//")[-1].split("www.")[-1].split(".")[0]

# https://www.codewars.com/kata/51fc12de24a9d8cb0e000001/
def valid_ISBN10(isbn):
    if not len(isbn) == 10:
        return False
    checksum = 0
    for i in range(9):
        if not isbn[i].isdigit():
            return False
        checksum = (checksum + (int(isbn[i]) * (i + 1)) )% 11

    if not isbn[9].isdigit() and not isbn[9] == 'X':
        return False

    lastdigit = int(isbn[9]) if isbn[9].isdigit() else 10
    checksum = (checksum + lastdigit * 10) % 11
    return checksum == 0

# https://www.codewars.com/kata/54e6533c92449cc251001667
def unique_in_order(sequence):
    unique = []
    prev = None
    for ele in sequence:
        if prev == ele:
            continue
        unique.append(ele)
        prev = ele
    return unique

def unique_in_order_minimal(iterable):
    r = []
    for x in iterable:
        x in r[-1:] or r.append(x)
    return r

# https://www.codewars.com/kata/54ff3102c1bad923760001f3
def get_vowels(s):
    return len([char for char in s if char in 'aieou'])

def get_vowels__minimal(s):
    return sum(c in 'aeiou' for c in s)

# https://www.codewars.com/kata/554e4a2f232cdd87d9000038
def DNA_strand(dna):
    return ''.join(
        'A' if char == 'T' else
        'T' if char == 'A' else
        'C' if char == 'G' else
        'G' if char == 'C' else None
        for char in dna
    )

def DNA_strand__builtin(dna):
    return dna.translate(string.maketrans("ATCG","TAGC"))

# https://www.codewars.com/kata/554b4ac871d6813a03000035
def high_and_low(numbers):
    nums = [int(num) for num in numbers.split(' ')]
    return f"{max(nums)} {min(nums)}"

def cakes(recipe, available):
    max = None
    for ing in recipe:
        if available.get(ing) is None:
            return 0
        if max is None or available[ing] // recipe[ing] < max:
            max = available[ing] // recipe[ing]
    return max

def cakes__minimal(recipe, available):
    return min(available.get(k, 0) / recipe[k] for k in recipe)

# https://www.codewars.com/kata/5279f6fe5ab7f447890006a7
def pick_peaks(arr):
    pos = []
    peaks = []
    for i in range(1, len(arr) - 1):
        if arr[i-1] == arr[i]:
            continue
        left = arr[i-1]
        j = i
        while j < len(arr) - 1 and arr[j] == arr[j + 1]:
            j += 1
        if j == len(arr) - 1:
            continue
        right = arr[j + 1]
        if arr[i] > left and arr[i] > right:
            pos.append(i)
            peaks.append(arr[i])
    return { "pos": pos, "peaks": peaks }

def pick_peaks__clean(arr):
    pos = []
    prob_peak = False
    for i in range(1, len(arr)):
        if arr[i] > arr[i - 1]:
            prob_peak = i
        elif arr[i] < arr[i - 1] and prob_peak:
            pos.append(prob_peak)
            prob_peak = False
    return {'pos': pos, 'peaks': [arr[i] for i in pos]}

# https://www.codewars.com/kata/55bf01e5a717a0d57e0000ec/train/python
def persistence(n):
    i = 0
    while n // 10 > 0:
        t = 1
        while n // 10 > 0:
            t *= n % 10
            n = n // 10
        t *= n
        n = t
        i += 1
    return i

# https://www.codewars.com/kata/585d7d5adb20cf33cb000235
def find_uniq(arr):
    if arr[0] != arr[1]:
        if arr[0] != arr[len(arr) - 1]:
            return arr[0]
        return arr[1]
    for i in range(2, len(arr)):
        if arr[i] != arr[i - 1]:
            return arr[i]
    return None


def find_uniq_clean(arr):
    culprit = arr[1]
    if arr[0] == arr[2]:
        culprit = arr[0]
    for i in arr:
        if i != culprit:
            return i

def find_uniq_minimal(arr):
    a, b = set(arr)
    return a if arr.count(a) == 1 else b

# https://www.codewars.com/kata/520b9d2ad5c005041100000f
def pig_it(text):
    result = []
    for word in text.split():
        if word.isalpha():
            result.append(word[1:]+word[0]+"ay")
        else:
            result.append(word)
    return " ".join(result)

def pig_it(text):
    lst = text.split()
    return ' '.join( [word[1:] + word[:1] + 'ay' if word.isalpha() else word for word in lst])

# https://www.codewars.com/kata/5467e4d82edf8bbf40000155
def descending_order(num):
    return int(''.join(sorted(str(num), reverse=True)))


# https://www.codewars.com/kata/555086d53eac039a2a000083
def lovefunc( flower1, flower2 ):
    return (flower1 + flower2) % 2 == 1

def lovefunc_binary( a, b ):
    return (a ^ b) & 1

# https://www.codewars.com/kata/5601409514fc93442500010b
def better_than_average(class_points, your_points):
    return sum(class_points) / len(class_points) < your_points

# https://www.codewars.com/kata/52bc74d4ac05d0945d00054e
def first_non_repeating_letter(s):
    uniques = []
    removed = []
    for c in s:
        if any(c.lower() == u.lower() for u in uniques):
            if c.lower() in uniques:
                uniques.remove(c.lower())
            else:
                uniques.remove(c.upper())
            removed.append(c.lower())
        else:
            if not c.lower() in removed:
                uniques.append(c)
    return '' if not uniques else uniques[0]

def first_non_repeating_letter_minimal(string):
    cnt = Counter(string.lower())
    for letter in string:
        if cnt[letter.lower()] == 1:
            return letter
    return ''

# https://www.codewars.com/kata/52449b062fb80683ec000024
def generate_hashtag(s):
    if not s:
        return False
    l = 1
    out = '#'
    for word in s.split(' '):
        l += len(word)
        if l > 140:
            return False
        out += word.capitalize()
    return out

# https://www.codewars.com/kata/55c6126177c9441a570000cc
def order_weight(strng):
    s = sorted(strng.split())
    res = []
    for w in s:
        res.append(sum(int(c) for c in w.strip()))
    inxs = sorted(range(len(res)), key=lambda i: res[i])
    return ' '.join([s[i] for i in inxs])

def order_weight_minimal(_str):
    return ' '.join(sorted(sorted(_str.split(' ')), key=lambda x: sum(int(c) for c in x)))

# https://www.codewars.com/kata/55c04b4cc56a697bb0000048
def scramble(s1, s2):
    text = sorted(s1)
    sample = sorted(s2)
    p_sample = 0
    for c in text:
        if not sample:
            return True
        if c == sample[p_sample]:
            if p_sample == len(sample) - 1:
                return True
            else:
                p_sample += 1
    return False

# https://www.codewars.com/kata/54a91a4883a7de5d7800009c
def increment_string(strng):
    src = ''
    numstr = ''
    for i in range(len(strng) -1, -1, -1):
        if not (strng[i]).isdecimal():
            src = strng[:i+1]
            break
        numstr = strng[i] + numstr

    if not numstr:
        return strng + '1'

    maxpos = len(numstr)
    numout = str(int(numstr) + 1)
    if maxpos == len(str(int(numstr))):
        return src + numout

    if len(numout) > maxpos:
        return src + numout[-maxpos:]
    else:
        return src + numout.zfill(maxpos)

def increment_string_minimal(strng):
    head = strng.rstrip('0123456789')
    tail = strng[len(head):]
    if tail == "": return strng+"1"
    return head + str(int(tail) + 1).zfill(len(tail))

# https://www.codewars.com/kata/5270d0d18625160ada0000e4
def greed_is_good(dice):
    scores = { 1: 1000, 2: 200, 3: 300, 4: 400, 5: 500, 6: 600 }
    cnt = Counter(dice)
    total = 0
    items = list(cnt.items())
    for i, v in enumerate(items):
        key = items[i][0]
        val = items[i][1]
        if val >= 3:
            total += scores[key]
            val -= 3
        if key == 1:
            total += val * 100
        if key == 5:
            total += val * 50
    return total


def greed_is_good_minimal(dice):
    sum = 0
    counter = [0, 0, 0, 0, 0, 0]
    points = [1000, 200, 300, 400, 500, 600]
    extra = [100, 0, 0, 0, 50, 0]
    for die in dice:
        counter[die - 1] += 1

    for (i, count) in enumerate(counter):
        sum += (points[i] if count >= 3 else 0) + extra[i] * (count % 3)

    return sum

# https://www.codewars.com/kata/52f787eb172a8b4ae1000a34
def trailing_zeros_of_factorial(n):
    z = 5
    r = 0
    while z < n:
        r = r + n // z
        z = z * 5
    return r


# https://www.codewars.com/kata/55aa075506463dac6600010d
def list_squared(m, n):
    res = []
    for i in range(m, n + 1):
        divisors = []
        sqr = math.ceil(math.sqrt(i))
        for j in range(1, sqr + 1):
            if i % j == 0 and not j in divisors:
                divisors.append(j)
                if j * j != i:
                    divisors.append(i // j)
        if not divisors:
            continue
        squared_sum = sum([x**2 for x in divisors])
        sqrt_of_squared = int(math.sqrt(squared_sum))
        if sqrt_of_squared * sqrt_of_squared == squared_sum:
            res.append([i, squared_sum])
    return res

def list_squared_minimal(m, n):
    out = []
    for i in range(m, n + 1):
        # Finding all divisors below the square root of i
        possibles = set([x for x in range(1, int(i ** 0.5) + 1) if i % x == 0])
        # And adding their counterpart
        possibles.update([i / x for x in possibles])
        # Doubles in the possibles are solved due to the set
        val = sum(x ** 2 for x in possibles)
        # Checking for exact square
        if (int(val ** 0.5)) ** 2 == val: out.append([i, val])
    return out

def last_digit(n1, n2):
    if n2 == 0:
        return 1
    last_int = n1 % 10
    pattern = [last_int]
    test = last_int
    while True:
        test *= last_int
        n = test % 10
        if n == last_int:
            break
        pattern.append(n)
    return pattern[n2 % len(pattern) - 1]

# for x^y mod z the periodicity is always a factor of p-1 for all x and y where p is a prime factor of z
# for any number from 1 to 9 after 4 times the last digit will repeat
def last_digit_minimal(n1, n2):
    return (n1 % 10) ** (n2 % 4 + 4 * bool(n2)) % 10


def is_prime(num):
    if num == 2 or num == 3 or num == 5:
        return True
    if num <= 1 or num % 2 == 0 or num % 3 == 0 or num % 5 == 0:
        return False
    maxn = int(math.sqrt(num) // 6) + 1
    for i in range(1, maxn):
        p1 = i * 6 + 1
        p5 = i * 6 + 5
        if num % p1 == 0 or num % p5 == 0:  # OR not |
            return False
    return True


# https://www.codewars.com/kata/561e9c843a2ef5a40c0000a4
# return the first pair of two prime numbers spaced with a gap of g between the limits m, n if these numbers exist otherwise None
def gap(g, m, n):
    if g % 2 != 0:
        return None # gap of 2 primes always even
    pp = None
    for p in range(m, n + 1):
        if is_prime(p):
            if pp is not None:
                if p - pp ==g:
                    return [pp, p]
            pp = p
    return None

def choose_best_sum(t, k, ts):
    if not ts:
        return None
    if k == 1:
        test = [x for x in ts if x <= t]
        if not test:
            return None
        return max(test)
    best_sum = None
    for i in range(len(ts)):
        this_route = ts[i]
        other_routes = ts[i+1:]
        test = choose_best_sum(t - this_route, k - 1, other_routes)
        if test is not None:
            test_sum = this_route + test
            if not best_sum or test_sum > best_sum:
                best_sum = test_sum
    return best_sum


# https://www.codewars.com/kata/529adbf7533b761c560004e5
memo = {}
def fibonacci(n):
    if n in [0, 1]:
        return n
    if n not in memo:
        memo[n] = fibonacci(n - 1) + fibonacci(n - 2)
    return memo[n]

def remov_nb(n):
    if n < 26:
        return []
    f = n * (n + 1) // 2
    res = []
    left = 0
    for i in range(n - 1, -1, -1):
        for j in range(left, i):
            s = f - i - j
            if i * j >= s:
                left = j
                break
        if i == left:
            break
        if i * left == s:
            res.append((left, i))
            res.append((i, left))
    return res

# https://www.codewars.com/kata/5547cc7dcad755e480000004
# the product of a and b should be equal to the sum of all numbers in the sequence, excluding a and b
def removNb_math(n):
    total = n*(n+1)/2
    sol = []
    for a in range(1,n+1):
        b = (total-a)/(a+1.0)
        if b.is_integer() and b <= n:
            sol.append((a,int(b)))
    return sol

# https://www.codewars.com/kata/54d4c8b08776e4ad92000835
# Finding the Perfect power (n + m ^ k where m and k are integers)
def isPP(n):
    if n < 4:
        return None
    if n == 4:
        return [2, 2]
    for i in range (2, int(n ** 0.5) + 2):
        test = round(n ** (1/i))
        if test ** i == n:
            return [test, i]
    return None


# https://www.codewars.com/kata/51edd51599a189fe7f000015
# Finding difference betwen a and b (simple)
def solution(array_a, array_b):
    sum = 0
    for i in range(len(array_a)):
        sum += (array_b[i] - array_a[i]) ** 2
    return sum / len(array_a)


def run_tests():
    result = ips_between('10.0.0.0', '10.0.1.0')
    print(result)
    result = to_underscore('ThisIsBeautifulDay')
    print(result)
    result = valid_ISBN10('1112223339')
    print(result)
    result = persistence(39)
    print(result)
    print(descending_order(123444))
    print(order_weight("103 123 4444 99 2000"))
    print(increment_string("[6074531754650710000819591"))
    print(greed_is_good([2, 4, 4, 5, 4]))
    print(trailing_zeros_of_factorial(100))
    print(list_squared(1, 250))
    print(last_digit(2 ** 200, 2 ** 300))
    print(gap(2,100,103))
    print(choose_best_sum(163, 3, [50, 55, 56, 57, 58]))
    print(fibonacci(589))
    print(remov_nb(26))
    print(isPP(125))

if __name__ == '__main__':
    run_tests()
# https://www.codewars.com/kata/568ff914fc7a40a18500005c
import ipaddress
import math
import string
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

<<<<<<< Updated upstream
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

def run_tests():
    result = ips_between('10.0.0.0', '10.0.1.0')
    print(result)
    result = to_underscore('ThisIsBeautifulDay')
    print(result)
    result = valid_ISBN10('1112223339')
    print(result)
    result = persistence(39)
    print(result)


if __name__ == '__main__':
    run_tests()
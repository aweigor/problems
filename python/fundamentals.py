# https://www.codewars.com/kata/568ff914fc7a40a18500005c
import ipaddress
import math
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



def run_tests():
    result = ips_between('10.0.0.0', '10.0.1.0')
    print(result)




if __name__ == '__main__':
    run_tests()
from collections import Counter

# https://www.codewars.com/kata/550f22f4d758534c1100025a
#
# { "NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST" } -> { "WEST" }
#
# reduc(aab) = abs(count(a) + count(b)) = a
# reduc(cda) = reduc(cd) + reduc(a) = a
# reduc(aabcda) = reduc(L) + reduc(R) = aa: L = aab, R = cda
#
# f():
# out: reduc(aabcda)
# while out != reduc(out):
#   out = reduc(out)
# return out

directionsMap = { 'N': 0, 'S': 1, 'E': 2, 'W': 3}

def reduc(direc):
    if not direc:
        return ''

    first = direc[0]

    is_longitude = first in ("N", "S")

    i = 0
    count = 0
    out = ''
    direction_changed = False

    while i < len(direc):
        while i < len(direc) and (direc[i] in ("N", "S")) == is_longitude:
            if is_longitude:
                sign = -1 if direc[i] == "N" else 1
            else:
                sign = -1 if direc[i] == "W" else 1
            count += sign
            i += 1

        if is_longitude:
            if count < 0:
                out += ''.join(["N"] * abs(count))
            else:
                out += ''.join(["S"] * count)
        else:
            if count < 0:
                out += ''.join(["W"] * abs(count))
            else:
                out += ''.join(["E"] * count)

        count = 0

        if i < len(direc):
            direction_changed = True
            is_longitude = not is_longitude

    if not direction_changed:
        return out

    reduced_out = reduc(list(out))
    while out != reduced_out:
        out = reduced_out
        reduced_out = reduc(list(out))

    return out

def main():
    res = reduc(["N", "S", "S", "E", "W", "N", "W"])
    print(res)


if __name__ == '__main__':
    main()
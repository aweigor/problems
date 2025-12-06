package main

import (
	"encoding/binary"
	"fmt"
	"math"
	"net"
	"regexp"
	"strconv"
	"strings"
)

func Tribonacci(signature [3]float64, n int) (r []float64) {
	r = signature[:]
	for i := 0; i < n; i++ {
		l := len(r)
		r = append(r, r[l-1]+r[l-2]+r[l-3])
	}
	return r[:n]
}

// www.codewars.com/kata/52fba66badcd10859f00097e
func Disemvowel(comment string) string {
	isConsonant := func(letterRune rune) bool {
		vowels := "aeiouAEIOU"
		return !strings.ContainsRune(vowels, letterRune)
	}
	var builder strings.Builder
	for _, r := range comment {
		if isConsonant(r) {
			builder.WriteRune(r)
		}
	}
	return builder.String()
}

func DisemvowelClean(comment string) string {
	for _, c := range "aiueoAIUEO" {
		comment = strings.ReplaceAll(comment, string(c), "")
	}
	return comment
}

// https://www.codewars.com/kata/5648b12ce68d9daa6b000099/
func Passengers(busStops [][2]int) int {
	var result int
	for _, inout := range busStops {
		result += inout[0]
		result -= inout[1]
		if result < 0 {
			return 0
		}
	}
	return result
}

func Passengers_clean(busStops [][2]int) (inBus int) {
	for _, stopInfo := range busStops {
		inBus += stopInfo[0] - stopInfo[1]
	}
	return
}

// https://www.codewars.com/kata/56747fd5cb988479af000028/
func GetMiddle(s string) string {
	mid := len(s) / 2
	if len(s) < 2 {
		return s
	}
	if len(s)%2 == 0 {
		return s[mid-1 : mid+1]
	} else {
		return s[mid : mid+1]
	}
}

func GetMiddle_clean(s string) string {
	n := len(s)
	if n == 0 {
		return s
	}
	return s[(n-1)/2 : n/2+1]
}

// https://www.codewars.com/kata/5839edaa6754d6fec10000a2/
func FindMissingLetter(chars []rune) rune {
	if len(chars) < 2 {
		panic("Must contain at least 2 chars")
	}
	for i := 1; i < len(chars); i++ {
		if chars[i]-chars[i-1] > 1 {
			return chars[i-1] + 1
		}
	}
	panic("No missing letter found")
}

func FindMissingLetter_clean(a []rune) rune {
	c := a[0]
	for _, v := range a[1:] {
		if c++; v != c {
			break
		}
	}
	return c
}

var decoder = map[rune]int{
	'I': 1,
	'V': 5,
	'X': 10,
	'L': 50,
	'C': 100,
	'D': 500,
	'M': 1000,
}

// https://www.codewars.com/kata/51b6249c4612257ac0000005/
// IIV_<-- ahead
func DecodeRoman(roman string) int {

	sum, sum_before, ahead := 0, 0, 0

	for i := len(roman) - 1; i >= 0; i-- {
		current := decoder[rune(roman[i])]

		if current > ahead {
			sum_before = sum
			sum += current
		} else if current < ahead {
			sum_before = sum
			sum -= current
		} else if current == ahead {
			if sum-sum_before >= 0 {
				sum_before = sum
				sum += current
			} else {
				sum_before = sum
				sum -= current
			}
		}

		ahead = current
	}

	return sum
}

// implementation is easy to understand, but actually wrong
func DecodeRoman_recursive(roman string) int {
	if len(roman) == 0 {
		return 0
	}
	first := decoder[rune(roman[0])]
	if len(roman) == 1 {
		return first
	}
	next := decoder[rune(roman[1])]
	if next > first {
		return (next - first) + DecodeRoman_recursive(roman[2:])
	}
	return first + DecodeRoman_recursive(roman[1:])
}

func ParseDeadfish(data string) []int {
	argv := 0
	var out []int
	for _, command := range data {
		switch command {
		default:
			continue
		case 'i':
			argv++
		case 'd':
			argv--
		case 's':
			argv *= argv
		case 'o':
			out = append(out, argv)
		}
	}
	return out
}

// https://www.codewars.com/kata/54da5a58ea159efa38000836/
func FindOdd(seq []int) int {
	counts := map[int]int{}
	for _, num := range seq {
		_, exists := counts[num]
		if exists {
			counts[num]++
		} else {
			counts[num] = 1
		}
	}
	for key, value := range counts {
		if value%2 != 0 {
			return key
		}
	}

	return 0
}

func FindOdd_clean(seq []int) int {
	res := 0
	for _, x := range seq {
		res ^= x
	}
	return res
}

// https://www.codewars.com/kata/526571aae218b8ee490006f4
// bits.OnesCount(n) from "math/bits do the same"
func CountPositiveBits(n uint) int {
	out := 0
	for n > 0 {
		out += (int)(n % 2)
		n /= 2
	}
	return out
}

// https://www.codewars.com/kata/526989a41034285187000de4
func IpsBetween(start, end string) uint32 {
	startOctets := strings.Split(start, ".")
	endOctets := strings.Split(end, ".")

	result := uint32(0)

	for i := 3; i >= 0; i-- {
		startValue, _ := strconv.Atoi(startOctets[i])
		endValue, _ := strconv.Atoi(endOctets[i])
		diff := endValue - startValue
		fmt.Println(diff)
		result += uint32(diff) * uint32(math.Pow(256, float64(3-i)))
	}

	return result
}

func IpsBetween_clean(first, last string) uint32 {
	firstVal := binary.BigEndian.Uint32(net.ParseIP(first)[12:16]) // last 4 bytes because net/ip supports ipv6
	lastVal := binary.BigEndian.Uint32(net.ParseIP(last)[12:16])
	return lastVal - firstVal
}

// https://www.codewars.com/kata/526dbd6c8c0eb53254000110
func IsAlphanumeric(s string) bool {
	r := regexp.MustCompile("^[a-zA-Z0-9]+$")
	return r.MatchString(s)
}

// https://www.codewars.com/kata/54521e9ec8e60bc4de000d6c/
// for every positive numbers look left and right for positive sum,
// if positive sum found: extend the border
func MaximumSubarraySum(numbers []int) int {
	var buf, seq []int
	currentSum, tmpSum, maxSum := 0, 0, 0
	for i, n0 := range numbers {
		if n0 > 0 {
			seq = []int{n0}
			currentSum = n0
			tmpSum = 0
			for j := i - 1; j >= 0; j-- {
				if tmpSum > 0 {
					for n1 := range buf {
						seq = append(seq, n1)
					}
					buf = []int{}
					seq = append(seq, numbers[j])
					currentSum += tmpSum
				} else {
					buf = append(buf, numbers[j])
				}
			}
			tmpSum = 0
			for j := i + 1; j < len(numbers); j++ {
				tmpSum += numbers[j]
				if tmpSum > 0 {
					for n1 := range buf {
						seq = append(seq, n1)
					}
					buf = []int{}
					seq = append(seq, numbers[j])
					currentSum += tmpSum
					tmpSum = 0
				} else {
					buf = append(buf, numbers[j])
				}
			}
			if currentSum > maxSum {
				maxSum = currentSum
			}
		}
	}
	return maxSum
}

func ss_max(a, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

func MaximumSubarraySum_clean(numbers []int) int {
	res, sum := 0, 0
	for i := range numbers {
		sum += numbers[i]
		res = ss_max(res, sum)
		sum = ss_max(sum, 0)
	}
	return res
}

// https://www.codewars.com/kata/5ce399e0047a45001c853c2b/
func PartsSums(ls []uint64) []uint64 {
	res := []uint64{0}
	for i := len(ls) - 1; i >= 0; i-- {
		res = append([]uint64{res[0] + ls[i]}, res...)
	}
	return res
}

func PartsSums_optimized(ls []uint64) []uint64 {
	res := []uint64{0}
	for i := len(ls) - 1; i >= 0; i-- {
		res = append(res, res[len(res)-1]+ls[i])
	}
	for i, j := 0, len(res)-1; i < j; i, j = i+1, j-1 {
		res[i], res[j] = res[j], res[i]
	}
	return res
}

func PartsSums_clean(ls []uint64) []uint64 {
	v := make([]uint64, len(ls)+1)
	for i := len(ls) - 1; i >= 0; i-- {
		v[i] = v[i+1] + ls[i]
	}
	return v
}

// https://www.codewars.com/kata/525caa5c1bf619d28c000335
func TicTacToeChecker(board [3][3]int) int {
	hasNils := false
	for i := 0; i < 3; i++ {
		if (board[i][0] == 2 && board[i][1] == 2 && board[i][2] == 2) || (board[0][i] == 2 && board[1][i] == 2 && board[2][i] == 2) {
			return 2
		} else if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1) || (board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1) {
			return 1
		} else if board[i][0] == 0 || board[i][1] == 0 || board[i][2] == 0 {
			hasNils = true
		}
	}
	if (board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) || (board[2][0] == 2 && board[1][1] == 2 && board[0][2] == 2) {
		return 2
	} else if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) || (board[2][0] == 1 && board[1][1] == 1 && board[0][2] == 1) {
		return 1
	}
	if hasNils {
		return -1
	}
	return 0
}

// https://www.codewars.com/kata/52685f7382004e774f0001f7
func HumanReadableTime(seconds int) string {
	hours := seconds / (60 * 60)
	minutes := (seconds - (hours * 60 * 60)) / 60
	seconds_remain := seconds - hours*60*60 - minutes*60
	return fmt.Sprintf("%02d:%02d:%02d", hours, minutes, seconds_remain)
}

func HumanReadableTime_clean(s int) string {
	m, s := s/60, s%60
	h, m := m/60, m%60
	return fmt.Sprintf("%02d:%02d:%02d", h, m, s)
}

// https://www.codewars.com/kata/559a28007caad2ac4e000083
func Perimeter(n int) int {
	p1, p2, sum := 1, 1, 1
	for i := 0; i < n; i++ {
		p2 = p1 + p2
		p1 = p2 - p1
		sum += p1
		fmt.Println(sum)
	}
	return sum * 4
}

func Perimeter_clean(n int) int {
	a, b := 1, 1
	for i := 0; i < n; i++ {
		a, b = b, a+b
	}
	return 4 * (a + b - 1)
}

// https://www.codewars.com/kata/51e04f6b544cf3f6550000c1/
func Beeramid(bonus int, price float64) int {
	beeramid_level, beer_count := 0, 0
	for {
		beer_count += (beeramid_level + 1) * (beeramid_level + 1)
		if float64(beer_count)*price > float64(bonus) {
			break
		}
		beeramid_level++
	}
	return beeramid_level
}

// https://www.codewars.com/kata/55983863da40caa2c900004e
func NextBigger(n int) int {
	dec := []int{}
	r := n
	for r > 0 {
		num := r % 10
		r = r / 10
		if len(dec) > 0 {
			i := len(dec) - 1
			last := dec[i]
			if num < last {
				dec[i] = num
				dec = append(dec, last)
				for i > 0 && dec[i] > dec[i-1] {
					dec[i], dec[i-1] = dec[i-1], dec[i]
				}
				// add remain and quit
				for r > 0 {
					num := r % 10
					dec = append(dec, num)
					r = r / 10
				}
				break
			} else {
				dec = append(dec, num)
			}
		} else {
			dec = append(dec, num)
		}
	}

	for i := len(dec) - 1; i >= 0; i-- {
		r += dec[i] * int(math.Pow10(i))
	}

	if r == n {
		return -1
	}

	return r
}

func main() {
	result := Tribonacci([3]float64{1, 1, 1}, 10)
	fmt.Println("Tribonacci:", result)
	result2 := Disemvowel("This website is for losers LOL!")
	fmt.Println("Disemvowel:", result2)
	result3 := GetMiddle("Test")
	fmt.Println("GetMiddle:", result3)
	result4 := FindMissingLetter([]rune{'a', 'b', 'c', 'd', 'f'})
	fmt.Println("FindMissingLetter:", result4)
	result5 := DecodeRoman("IIV")
	fmt.Println("DecodeRoman:", result5)
	result6 := DecodeRoman_recursive("IIV")
	fmt.Println("DecodeRoman:", result6)
	result7 := ParseDeadfish("isoisoiso")
	fmt.Println("ParseDeadfish:", result7)
	result8 := FindOdd([]int{20, 1, -1, 2, -2, 3, 3, 5, 5, 1, 2, 4, 20, 4, -1, -2, 5})
	fmt.Println("FindOdd:", result8)
	result9 := CountPositiveBits(7)
	fmt.Println("CountPositiveBits:", result9)
	result10 := IpsBetween("20.0.0.10", "20.0.1.0")
	fmt.Println("IpsBetween:", result10)
	result11 := IsAlphanumeric("abc$")
	fmt.Println("IsAlphanumeric:", result11)
	result12 := PartsSums_optimized([]uint64{0, 1, 3, 6, 10})
	fmt.Println("PartsSums:", result12)
	board := [3][3]int{
		{0, 0, 1},
		{0, 1, 2},
		{2, 1, 0},
	}
	result13 := TicTacToeChecker(board)
	fmt.Println("TicTacToeChecker:", result13)
	result14 := HumanReadableTime(3599)
	fmt.Println("HumanReadableTime:", result14)
	result15 := Perimeter(5)
	fmt.Println("Perimeter:", result15)
	retult16 := Beeramid(9, 2.0)
	fmt.Println("Beeramid:", retult16)
	retult17 := NextBigger(1234567890)
	fmt.Println("NextBigger:", retult17) // 59884848459853:59884848483559
}

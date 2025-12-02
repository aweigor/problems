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

// https://www.codewars.com/kata/526dbd6c8c0eb53254000110/solutions/go
func IsAlphanumeric(s string) bool {
	r := regexp.MustCompile("^[a-zA-Z0-9]+$")
	return r.MatchString(s)
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
}

package main

import (
	"reflect"
	"testing"
)

func TestTribonacci(t *testing.T) {
	result := Tribonacci([3]float64{1, 1, 1}, 10)
	expected := []float64{1, 1, 1, 3, 5, 9, 17, 31, 57, 105}

	if len(result) != len(expected) {
		t.Errorf("Values mismatch: got %d, want %d", len(result), len(expected))
	}

	for i := range result {
		if result[i] != expected[i] {
			t.Errorf("At index %d: got %f, want %f", i, result[i], expected[i])
		}
	}
}

func TestDisemvowel(t *testing.T) {
	result := Disemvowel("This website is for losers LOL!")
	expected := "Ths wbst s fr lsrs LL!"

	if result != expected {
		t.Errorf("Values mismatch: got %c, want %c", len(result), len(expected))
	}
}

func TestBusStop(t *testing.T) {
	result := Passengers([][2]int{{10, 0}, {3, 5}, {5, 8}})
	expected := 5
	if result != expected {
		t.Errorf("Values mismatch: got %d, want %d", result, expected)
	}
}

func TestGetMiddle(t *testing.T) {
	result := GetMiddle("test")

	expected := "es"
	if result != expected {
		t.Errorf("Values mismatch: got %c, want %c", len(result), len(expected))
	}
}

func TestFindMissingRune(t *testing.T) {
	result := FindMissingLetter([]rune{'a', 'b', 'c', 'd', 'f'})
	expected := 'e'
	if result != expected {
		t.Errorf("Values mismatch: got %d, want %d", result, expected)
	}
}

func TestDecodeRoman(t *testing.T) {
	result := DecodeRoman("MDCLXVI")
	expected := 1666
	if result != expected {
		t.Errorf("Values mismatch: got %c, want %c", result, expected)
	}
}

func TestParseDeadfish(t *testing.T) {
	result := ParseDeadfish("isoisoiso")
	expected := []int{1, 4, 25}
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Values mismatch: got %c, want %c", result, expected)
	}
}

func TestFindOdd(t *testing.T) {
	result := FindOdd([]int{20, 1, -1, 2, -2, 3, 3, 5, 5, 1, 2, 4, 20, 4, -1, -2, 5})
	expected := 5
	if result != expected {
		t.Errorf("Values mismatch: got %d, want %d", result, expected)
	}
}

func TestHumanReadableTime(t *testing.T) {
	result := HumanReadableTime(86400)
	expected := "24:00:00"
	if result != expected {
		t.Errorf("Values mismatch: got %s, want %s", result, expected)
	}
}

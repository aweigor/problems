package main

import (
    "testing"
)

func TestTribonacci(t *testing.T) {
    result := Tribonacci([3]float64{1, 1, 1}, 10)
    expected := []float64{1, 1, 1, 3, 5, 9, 17, 31, 57, 105}
    
    if len(result) != len(expected) {
        t.Errorf("Length mismatch: got %d, want %d", len(result), len(expected))
    }
    
    for i := range result {
        if result[i] != expected[i] {
            t.Errorf("At index %d: got %f, want %f", i, result[i], expected[i])
        }
    }
}

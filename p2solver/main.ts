/**
 * Problem:
 * given board of 7 * 11 tiles . possible numbers are finite.
 * there are tiles with null values. their value is sum of ajacent non-null tiles.
 * there are discovered tiles and unknown ones.
 * there are closed tiles and opened ones. non-null tile may be discovered but closed.
 * tails have string keys that defines its positions on the board.
 * Objective:
 * compute all possible positions of non-null numbers in the closed tiles.
 * result needs to be an object of tile keys and map of probabilities.
 **/

interface ITile {
  key: string;
  opened: boolean;
  discovered: boolean;
  value: number | null;
  number: number | null;
}

const NUMBERS = [
  [1, 1],
  [2, 4],
  [4, 8],
] as const;

const getNumbersMap = () => {
  const numbersMap = new Map();
  for (const n of NUMBERS) {
    numbersMap.set(n[0], n[1]);
  }
};

export function execute(a: number, b: number): number {
  return a + b;
}

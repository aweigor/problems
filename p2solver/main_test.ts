import { assertArrayIncludes } from "@std/assert/array-includes";
import {
  BoardGraph,
  firstRun,
  getAdjacentTiles,
  getBoardTiles,
  getEmptyTile,
  getKey,
  getNumbersMap,
  type TileAllocationStateT,
  decompose,
  getAllocations,
} from "./main.ts";
import { assertEquals } from "@std/assert";

const getTileWithNumber = (
  rowIndex: number,
  colIndex: number,
  number: number,
  value?: number
) => {
  return {
    key: getKey(rowIndex, colIndex)!,
    opened: false,
    discovered: true,
    value: value || null,
    number: number,
    probabilities: null,
  };
};

const getTileWithValue = (
  rowIndex: number,
  colIndex: number,
  value: number
) => {
  return {
    key: getKey(rowIndex, colIndex)!,
    opened: true,
    discovered: true,
    value: value,
    number: null,
    probabilities: null,
  };
};

Deno.test(
  "Must return empty adjacents array if key is not provided",
  function addTest() {
    const graph = new BoardGraph([]);
    assertEquals(getAdjacentTiles(getEmptyTile(""), []), []);
  }
);

Deno.test(
  "Must return three adjacents if tile in the corner",
  function addTest() {
    const knownTile = getEmptyTile(getKey(0, 0)!);
    const allTiles = getBoardTiles([knownTile]);
    assertEquals(getAdjacentTiles(knownTile, allTiles).length, 3);
  }
);

Deno.test(
  "Must return five adjacents if tile near the border",
  function addTest() {
    const knownTile = getEmptyTile(getKey(1, 0)!);
    const allTiles = getBoardTiles([knownTile]);
    assertEquals(getAdjacentTiles(knownTile, allTiles).length, 5);
  }
);

Deno.test(
  "Must return eight adjacents if tile not in the corner and not near the border",
  function addTest() {
    const knownTile = getEmptyTile(getKey(1, 1)!);
    const allTiles = getBoardTiles([knownTile]);
    assertEquals(getAdjacentTiles(knownTile, allTiles).length, 8);
  }
);

Deno.test(
  "If around tile with known value only one undiscovered, undiscovered must be defined as number with the known tile's value",
  function testFirstRun() {
    const startState = [
      getTileWithValue(0, 0, 5),
      getTileWithValue(0, 1, 5),
      getTileWithValue(1, 0, 5),
    ];
    const graph = new BoardGraph(startState);
    const allocationStates: Map<string, TileAllocationStateT> = new Map();
    const numbersMap = getNumbersMap(graph);
    firstRun(graph, numbersMap, allocationStates);

    const resultTile = graph.getTile(getKey(1, 1)!);
    assertEquals(resultTile?.number, 5);
  }
);

Deno.test(
  "Must decompose sum into numbers according to the count map",
  function testDecompose1() {
    const length = 3; // positions count
    const countMap = new Map();
    countMap.set(1, 3); // key is the number, value is amount
    countMap.set(2, 2);
    const sum = 3; // assuming the sum of numbers in result will be the same
    const result = decompose(length, sum, countMap);
    assertArrayIncludes(result, [
      [1, 2],
      [1, 1, 1],
    ]);
  }
);

Deno.test(
  "Must consider amount of numbers in parameter",
  function testDecompose2() {
    const length = 3;
    const countMap = new Map();
    countMap.set(1, 2); // [1, 1, 1] is not valid combination now
    countMap.set(2, 2);
    const sum = 3;
    const result = decompose(length, sum, countMap);
    assertArrayIncludes(result, [[1, 2]]);
  }
);

Deno.test(
  "Must consider max length of decomposition",
  function testDecompose3() {
    const length = 2; // [1, 1, 1] is not valid combination now
    const countMap = new Map();
    countMap.set(1, 3);
    countMap.set(2, 2);
    const sum = 3;
    const result = decompose(length, sum, countMap);
    assertArrayIncludes(result, [[1, 2]]);
  }
);

Deno.test(
  "Must compute allocation according to decomposition set and positions parameter",
  function testAlocations1() {
    const numbers: number[] = [1, 2];
    const cellCount: number = 3;
    const result = getAllocations(numbers, cellCount);
    assertArrayIncludes(result, [
      [1, 0, 2],
      [2, 0, 1],
      [1, 2, 0],
      [2, 1, 0],
      [0, 1, 2],
      [0, 2, 1],
    ]);
  }
);

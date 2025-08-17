import {
  BoardGraph,
  firstRun,
  getAdjacentTiles,
  getBoardTiles,
  getEmptyTile,
  getKey,
  getNumbersMap,
  type TileAllocationStateT,
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

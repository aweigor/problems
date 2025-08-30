/**
 ** Problem:
 * given board of 7 * 11 tiles . possible numbers are finite.
 * there are tiles with number (non-null) and ones without.
 * value of tile is sum of its ajacents non-null tiles.
 * there are discovered tiles and unknown ones.
 * there are closed tiles and opened ones. non-null tile may be discovered but closed.
 * tails have string keys that defines its positions on the board.
 
 *
 * ,,,,,,      ,,,,,,      ,,,,,,
 * | 0  |      | 0  |      | 0  |
 * | 5  |      | 5  |      | 5  |   ...   ...
 * ''''''      ''''''      ''''''
 *
 * ,,,,,,      ,,,,,,      ,,,,,,
 * | 5  |      | 0  |      | 5  | <---- number
 * | 0  | <--> | 10 | <--> | 0  | <---- value
 * ''''''      ''''''      ''''''
 *
 * ,,,,,,      ,,,,,,      ,,,,,,
 * | 0  |      | 0  |      | 0  |   ...   ...
 * | 5  |      | 5  |      | 5  |
 * ''''''      ''''''      ''''''
 *
 *    ...
 *
 *    ...
 * 
 * 
 ** Objective:
 * compute all possible positions of numbers at the non-null undiscovered tiles.
 * result needs to be an array of all opened tiles and tiles with probabilities map.
 **/

function notNull(something: any): something is Omit<null, any> {
  return something !== null;
}

const ERRORS = {
  default: () => new Error("unexpected error"),
  numberNotFound: () => new Error("number not found"),
  stateNotFound: () => new Error("impossible state"),
};

const handleError = <T extends keyof typeof ERRORS>(error?: T) => {
  throw ERRORS[error || "default"]();
};

function equal(obj1: Record<string, number>, obj2: Record<string, number>) {
  for (const k of Object.keys(obj1)) {
    if (!obj2[k] || obj2[k] !== obj1[k]) {
      return false;
    }
  }
  return true;
}

export interface ITile {
  key: string;
  opened: boolean;
  discovered: boolean;
  value: number | null;
  number: number | null;
  probabilities: Map<number, number> | null;
}

export interface IGraph {
  getTile(key: string): ITile | null;
  getTileParams(key: string): TilePraramsT | null;
  updateTile(key: string, data: Partial<ITile>): void;
  keys(): string[];
  discoveredKeys(): string[];
}

export type TilePraramsT = { data: ITile; adjacent: ITile[] };
export type TileAllocationStateT = Record<string, number>[];

/**
 * The structure describes groups of state classes, independent fields of node states -
 * - set of numbers distributed across undiscovered adjacents.
 */
export type TileStateClassesT = Map<string, TileAllocationStateT>[];

export const ROWS_NUM = 11;
export const COLS_NUM = 7;

export const NUMBERS: [number, number][] = [
  [1, 1],
  [2, 4],
  [3, 4],
  [4, 2],
  [5, 1],
  [6, 3],
  [10, 1],
  [15, 1],
  [100, 8],
] as const;

const byIndex = (i: number) => (x: [number, number]) => x[i];
const numKeys = (nums: [number, number][]) => nums.map(byIndex(0));
const numValues = (nums: [number, number][]) => nums.map(byIndex(1));

const decreaseNumber = (map: Map<number, number>, number: number) => {
  const val = map.get(number);
  if (val !== undefined) {
    map.set(number, val - 1);
  }
};

export const getNumbersMap = (graph?: IGraph) => {
  const numbersMap = new Map<number, number>();
  for (const n of NUMBERS) {
    numbersMap.set(n[0], n[1]);
  }
  if (graph) {
    for (const k of graph.keys()) {
      const tile = graph.getTile(k)!;
      if (tile.discovered && tile.number) {
        decreaseNumber(numbersMap, tile.number);
      }
    }
  }
  return numbersMap;
};

export const getKey = (
  rowIndex: number,
  colIndex: number,
  rows = ROWS_NUM,
  cols = COLS_NUM
) => {
  if (rowIndex >= rows || colIndex >= cols || rowIndex < 0 || colIndex < 0)
    return null;
  return `${colIndex}:${rowIndex}`;
};

export const parseKey = (key: string) => {
  const parsed = key.split(":").map((x) => parseInt(x));
  const [col, row] = parsed;
  return [!isNaN(col) ? col : null, !isNaN(row) ? row : null];
};

export const getEmptyTile = (key: string) => {
  return {
    key,
    opened: false,
    discovered: false,
    value: null,
    number: null,
    probabilities: null,
  } as ITile;
};

/**
 * Computes adjacents regardless provided tile and the board
 */
export const getAdjacentTiles: (tile: ITile, allTiles: ITile[]) => ITile[] = (
  tile: ITile,
  allTiles: ITile[]
) => {
  const result: ITile[] = [];
  const key = parseKey(tile.key);
  const [colIndex, rowIndex] = key;

  let adjacentKeys: string[] = [];
  if (notNull(colIndex) && notNull(rowIndex)) {
    adjacentKeys = [
      getKey(rowIndex - 1, colIndex - 1),
      getKey(rowIndex - 1, colIndex),
      getKey(rowIndex - 1, colIndex + 1),
      getKey(rowIndex, colIndex - 1),
      getKey(rowIndex, colIndex + 1),
      getKey(rowIndex + 1, colIndex - 1),
      getKey(rowIndex + 1, colIndex),
      getKey(rowIndex + 1, colIndex + 1),
    ].filter((k) => notNull(k));
  }

  for (const tile of allTiles) {
    if (!adjacentKeys.includes(tile.key)) continue;
    result.push(tile);
  }

  return result;
};

/**
 * Fills result with all board tiles according to amount provided in configuration
 * If no tile in the start array, empty tile will be created
 */
export const getBoardTiles: (openedTiles: ITile[]) => ITile[] = (
  openedTiles: ITile[]
) => {
  const allTiles = [] as ITile[];
  for (let i = 0; i < ROWS_NUM; i++) {
    for (let j = 0; j < COLS_NUM; j++) {
      // key is not null
      const key = getKey(i, j, ROWS_NUM, COLS_NUM) as string;
      allTiles.push(
        openedTiles.find((t) => t.key === key) || getEmptyTile(key)
      );
    }
  }
  return allTiles;
};

export class BoardGraph implements IGraph {
  static isDiscovered(tile: ITile) {
    return tile.opened && tile.discovered;
  }

  private _data: ITile[] = [];
  /**
   * Creates board graph.
   * Result contains all tiles of the board. Known tiles must be provided in constructor.
   */
  constructor(tiles: ITile[]) {
    this._data = getBoardTiles(tiles);
  }

  keys() {
    return this._data.map((t) => t.key);
  }

  discoveredKeys() {
    return this._data
      .filter((t) => BoardGraph.isDiscovered(t))
      .map((t) => t.key);
  }

  getTile(key: string): ITile | null {
    return this._data.find((t) => t.key === key) || null;
  }

  getTileParams(key: string): TilePraramsT | null {
    const tileData = this.getTile(key);
    if (!tileData) return null;
    return {
      data: tileData,
      adjacent: getAdjacentTiles(tileData, this._data),
    };
  }

  updateTile(key: string, data: Partial<ITile>) {
    const tile = this.getTile(key);
    if (tile) {
      Object.assign(tile, { ...data, key }); // protect rewriting key
    }
  }
}

export function execute(startTiles: ITile[]): IGraph {
  const graph = new BoardGraph(startTiles);
  const allocationStates: Map<string, TileAllocationStateT> = new Map();
  const numbersMap = getNumbersMap(graph);
  firstRun(graph, numbersMap, allocationStates);
  // We got all states of all tiles with more than one undiscovered adjacent
  // Now we need to split tiles into classes.
  // Classification rule: all keys of undiscovered tiles
  // are different against all tiles in another class
  const stateAllocationsToClasses = getAllocationStateClasses(allocationStates);
  // We can handle each class separately and concurrently
  for (const stateClass of stateAllocationsToClasses) {
    secondRun(graph, numbersMap, stateClass);
  }
  return graph;
}

function findConsistent(
  state: Record<string, number>[],
  edges: Record<string, number>[][],
  result: Record<string, number>[][] = [],
  numbers: Map<number, number>,
  edgeIndex: number = 0
): void {
  if (!edges[edgeIndex + 1]) {
    const consistentState: Record<string, number>[] = [];
    for (const d_state of state) {
      let isConsistent = true;
      const _numbers = new Map(numbers);
      for (const d_key of Object.keys(d_state)) {
        if (d_state[d_key]) {
          let number = _numbers.get(d_state[d_key]);
          if (!number) {
            throw handleError("numberNotFound");
          }
          number--;
          if (number < 0) {
            isConsistent = false;
            break;
          }
          _numbers.set(d_state[d_key], number);
        }
      }
      if (isConsistent) {
        consistentState.push(d_state);
      }
    }

    void result.push(consistentState);
    return;
  }

  const nextEdge = edges[edgeIndex + 1];
  const new_domain: Record<string, number>[] = [];

  for (const d_state of state) {
    const d_stateKeys = Object.keys(d_state);
    for (const state of nextEdge) {
      if (
        !d_stateKeys.some(
          (key) => state[key] !== undefined && state[key] !== d_state[key]
        )
      ) {
        new_domain.push({ ...d_state, ...state });
      }
    }
  }

  void findConsistent(new_domain, edges, result, numbers, edgeIndex + 1);
}

/**
 * Groups consistent states into map with tile key as key and array of possible numbers as value
 */
export function joinConsistentAllocations(
  numbersMap: Map<number, number>,
  allocationStates: Map<string, TileAllocationStateT>
): Map<string, number[]> {
  const statesArray = Array.from(allocationStates.values());
  const consistentResult: Record<string, number>[][] = [];
  findConsistent(statesArray[0], statesArray, consistentResult, numbersMap);
  return consistentResult.flat().reduce((acc, el) => {
    for (const key of Object.keys(el)) {
      if (!acc.has(key)) {
        acc.set(key, [el.key]);
      } else {
        acc.set(key, [...(acc.get(key) as number[]), el.key]);
      }
    }
    return acc;
  }, new Map() as Map<string, number[]>);
}

export function secondRun(
  graph: IGraph,
  numbersMap: Map<number, number>,
  allocationStates: Map<string, TileAllocationStateT>
) {
  const joinResult: Map<string, number[]> = joinConsistentAllocations(
    numbersMap,
    allocationStates
  );
  for (const key of joinResult.keys()) {
    const numbers = joinResult.get(key)!;

    // key - number, value - how many numbers in set for this tile
    const numberCountMap = numbers.reduce((acc, el) => {
      if (!acc.has(el)) {
        acc.set(el, 1);
      } else {
        acc.set(el, acc.get(el)! + 1);
      }
      return acc;
    }, new Map() as Map<number, number>);

    const numberProbabilityMap: Map<number, number> = new Map(
      numberCountMap.entries().map(([k, v]) => [k, v / numbers.length])
    );

    const numberProbabilityValues = Array.from(numberProbabilityMap.values());

    const tileParams: Partial<ITile> = {
      discovered: numberProbabilityValues.length > 1 ? false : true,
      opened: false,
      value: null,
      number:
        numberProbabilityValues.length === 1
          ? numberProbabilityValues[0]
          : null,
      probabilities:
        numberProbabilityValues.length > 1 ? numberProbabilityMap : null,
    };

    graph.updateTile(key, tileParams);
  }
}

/**
 * Divides allocation states into classes - areas without intersections by keys
 * - Traverse all states. for each state key get adjacent keys and apply these keys to every multiple of coupled keys area.
 * - If there is no area that contains al least one key of ajacent keys set, create new area.
 * - Get result areas and look for intersections over other areas.
 * - If area keys intersects another area, merge two areas.
 */
export function getAllocationStateClasses(
  states: Map<string, TileAllocationStateT>
): TileStateClassesT {
  const keyFields: Set<string>[] = [];
  for (const k of states.keys()) {
    const state = states.get(k);
    if (state && state.length) {
      const adjacentKeys = Object.keys(state.at(0)!);
      let classExists = false;
      for (const keys of keyFields) {
        if (adjacentKeys.some((k) => keys.has(k))) {
          classExists = true;
          for (const ak of adjacentKeys) {
            keys.add(ak);
          }
          break;
        }
      }
      if (!classExists) {
        const keys = new Set<string>();
        for (const ak of adjacentKeys) {
          keys.add(ak);
        }
        keyFields.push(keys);
      }
    }
  }
  const mergedFields: Set<string>[] = [];
  for (const field of keyFields) {
    let classExists = false;
    for (const field2 of mergedFields) {
      if (field.intersection(field2).size) {
        classExists = true;
        for (const key of field.values()) {
          field2.add(key);
        }
      }
    }
    if (!classExists) {
      mergedFields.push(field);
    }
  }

  const result: TileStateClassesT = mergedFields.map(() => new Map());
  for (const k of states.keys()) {
    const state = states.get(k);
    if (state && state.length) {
      const adjacentKeys = Object.keys(state.at(0)!);
      const groupIndex = mergedFields.findIndex((f) =>
        adjacentKeys.some((k) => f.has(k))
      );
      if (groupIndex !== -1) {
        result[groupIndex].set(k, state);
      }
    }
  }

  return result;
}

export function firstRun(
  graph: IGraph,
  numbersMap: Map<number, number>,
  allocationStates: Map<string, TileAllocationStateT>
) {
  const checkList = graph.discoveredKeys().map((k) => graph.getTile(k)!);

  const saveAndRequeue = (key: string, result: Partial<ITile>) => {
    const tileParams = graph.getTileParams(key);
    if (!tileParams) return;
    graph.updateTile(key, result);
    for (const a of tileParams.adjacent) {
      if (
        BoardGraph.isDiscovered(a) &&
        !checkList.find((p) => p.key === a.key)
      ) {
        checkList.push(a);
      }
    }
  };

  let _tile: ITile;
  while ((_tile = checkList.shift() as ITile)) {
    if (!_tile) break;
    if (!_tile.value) continue; // TODO: check if tile has adjacents. if value equals 0, means that all adjacents are
    const _params = graph.getTileParams(_tile.key);
    if (!_params) continue;
    const undiscoveredAdjacents = _params.adjacent.filter((t) => !t.discovered);
    if (!undiscoveredAdjacents) continue;
    const discoveredAdjacents = _params.adjacent.filter((t) => t.discovered);
    const discoveredSum = discoveredAdjacents.reduce(
      (el, acc) => el + (acc.number || 0),
      0
    );
    if (_tile.value - discoveredSum === 0) {
      for (const tile of undiscoveredAdjacents) {
        saveAndRequeue(tile.key, {
          discovered: true,
          number: 0,
        });
      }
    } else if (undiscoveredAdjacents.length === 1) {
      if (!numbersMap.keys().some((k) => k === _tile.value)) {
        throw handleError("stateNotFound");
      }
      saveAndRequeue(undiscoveredAdjacents[0].key, {
        number: _tile.value,
        discovered: true,
      });
    } else {
      // undiscovered > 1 means that we dont know exact distribution under undiscovered adjacent tiles
      const dec = decompose(
        undiscoveredAdjacents.length,
        _tile.value - discoveredSum,
        numbersMap
      );

      const tileAllocationState: TileAllocationStateT = [];

      for (const numSet of dec) {
        // Here we could check all allocations to find those which number is single across all states.
        // but there is no chances that is will happen.
        // So we just compute allocations and save them for further processing
        const allocations = getAllocations(
          numSet,
          undiscoveredAdjacents.length
        );
        for (const alloc of allocations) {
          const allocState = Object.fromEntries(
            alloc.map((a, i) => {
              return [_params.adjacent[i].key, a];
            })
          );
          if (!tileAllocationState.some((state) => equal(state, allocState))) {
            tileAllocationState.push(allocState);
          }
        }
      }

      allocationStates.set(_params.data.key, tileAllocationState);
    }
  }
}

/**
 * Computes all allocations (permutations) of numbers across undiscovered nodes
 * We do not really need the nodes, just the max count of places
 * TODO: Heap
 */
export function getAllocations(numbers: number[], cellCount: number) {
  const padded = [...numbers];
  while (padded.length < cellCount) {
    padded.push(0);
  }

  const result: number[][] = [];

  function backtrack(start: number) {
    if (start === padded.length) {
      result.push([...padded]);
      return;
    }
    const used = new Set<number>();
    for (let i = start; i < padded.length; i++) {
      if (used.has(padded[i])) continue;
      used.add(padded[i]);
      [padded[start], padded[i]] = [padded[i], padded[start]];
      backtrack(start + 1);
      [padded[start], padded[i]] = [padded[i], padded[start]];
    }
  }

  backtrack(0);
  return result;
}

/**
 * Decomposes given sum into numbers from list
 * Performs validation on maximum numbers with value in set
 * **/
export function decompose(
  length: number,
  sum: number,
  countMap: Map<number, number>
): number[][] {
  const candidates = Array.from(countMap.keys());
  const result: number[][] = [];
  candidates.sort((a, b) => a - b);

  function backtrack(
    start: number,
    path: number[],
    currentSum: number,
    result: number[][]
  ): void {
    if (currentSum === sum) {
      if (validatePath(path)) {
        result.push([...path]);
      }
      return;
    }
    if (currentSum > sum || path.length >= length) {
      return;
    }
    for (let i = start; i < candidates.length; i++) {
      if (i > start && candidates[i] === candidates[i - 1]) {
        continue;
      }
      path.push(candidates[i]);
      backtrack(i, path, currentSum + candidates[i], result);
      path.pop();
    }
  }

  function validatePath(path: number[]) {
    const pathCountMap = path.reduce((acc, el) => {
      acc.set(el, (acc.get(el) || 0) + 1);
      return acc;
    }, new Map<number, number>());
    return !countMap
      .keys()
      .some((k) => Number(countMap.get(k)) < Number(pathCountMap.get(k)));
  }

  backtrack(0, [], 0, result);
  return result;
}

/**/

function test() {
  const a = 1;

  return a;
}

test();

// execute([]);

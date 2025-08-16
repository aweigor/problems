/**
 * Problem:
 * given board of 7 * 11 tiles . possible numbers are finite.
 * there are tiles with number (non-null) and ones without.
 * value of tile is sum of its ajacents non-null tiles.
 * there are discovered tiles and unknown ones.
 * there are closed tiles and opened ones. non-null tile may be discovered but closed.
 * tails have string keys that defines its positions on the board.
 * Objective:
 * compute all possible positions of numbers in the non-null undiscovered tiles.
 * result needs to be an array of all opened tiles and tiles with probabilities map.
 **/

function notNull(something: any): something is Omit<null, any> {
  return something !== null;
}

function throwError(message?: string): never {
  throw new Error(message);
}

function equal(obj1: Record<string, number>, obj2: Record<string, number>) {
  for (const k of Object.keys(obj1)) {
    if (!obj2[k] || obj2[k] !== obj1[k]) {
      return false;
    }
  }
  return true;
}

interface ITile {
  key: string;
  opened: boolean;
  discovered: boolean;
  value: number | null;
  number: number | null;
  probabilities: Map<number, number> | null;
}

type TilePraramsT = { data: ITile; adjacent: ITile[] };
type GraphT = Record<string, TilePraramsT>;
type TileAllocationStateT = Record<string, number>[];

/**
 * The structure describes groups of state classes, independent fields of node states -
 * - set of numbers distributed across undiscovered adjacents.
 */
type TileStateClassesT = Map<string, TileAllocationStateT>[];

const ROWS_NUM = 11;
const COLS_NUM = 7;
const ERROR_STATE_NOT_VALID = "invalid state";

const NUMBERS: [number, number][] = [
  [1, 1],
  [2, 4],
  [4, 8],
] as const;

const byIndex = (i: number) => (x: [number, number]) => x[i];
const numKeys = (nums: [number, number][]) => nums.map(byIndex(0));
const numValues = (nums: [number, number][]) => nums.map(byIndex(1));

const getNumbersMap = (graph?: GraphT) => {
  const numbersMap = new Map<number, number>();
  for (const n of NUMBERS) {
    numbersMap.set(n[0], n[1]);
  }
  if (graph) {
    for (const k of Object.keys(graph)) {
      const tile = graph[k].data;
      if (tile.discovered && tile.number) {
        const count = numbersMap.get(tile.number);
        if (count !== undefined) {
          numbersMap.set(tile.number, count - 1);
        }
      }
    }
  }
  return numbersMap;
};

const getKey = (
  rowIndex: number,
  colIndex: number,
  rows = ROWS_NUM,
  cols = COLS_NUM
) => {
  if (rowIndex >= rows || colIndex >= cols || rowIndex < 0 || colIndex < 0)
    return null;
  return `${colIndex}:${rowIndex}`;
};

const parseKey = (key: string) => {
  const parsed = key.split(":").map((x) => parseInt(x));
  const [col, row] = parsed;
  return [!isNaN(col) ? col : null, !isNaN(row) ? row : null];
};

const getTile: (graph: GraphT, key: string) => TilePraramsT | null = (
  graph,
  key
) => {
  return Object.values(graph).find((t) => t.data.key === key) || null;
};

const updateTile: (graph: GraphT, key: string, data: Partial<ITile>) => void = (
  graph,
  key,
  data
) => {
  const tile = getTile(graph, key);
  if (tile) {
    tile.data = {
      ...tile.data,
      ...data,
      key,
    };
  }
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

const getBoardGraph: (openedTiles: ITile[]) => GraphT = (openedTiles) => {
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
  return Object.fromEntries(
    allTiles.map((t) => [
      t.key,
      { data: t, adjacent: getAdjacentTiles(t, allTiles) },
    ])
  );
};

export function execute(result: ITile[]): GraphT {
  const graph = getBoardGraph(JSON.parse(JSON.stringify(result)));
  const allocationStates: Map<string, TileAllocationStateT> = new Map();
  const numbersMap = getNumbersMap(graph);
  firstRun(graph, numbersMap, allocationStates);
  // We got all states of all tiles with more than one undiscovered adjacent
  // Now we need to split tiles into classes.
  // Classification rule: all keys of undiscovered tiles
  // are different against all tiles in another class
  const allocationStateClasses = [allocationStates];
  getAllocationStateClasses(allocationStates);

  // We can handle each class separately and concurrently
  for (const stateClass of allocationStateClasses) {
    secondRun(graph, numbersMap, stateClass);
  }

  return graph;
}

export function secondRun(
  graph: GraphT,
  numbersMap: Map<number, number>,
  allocationStates: Map<string, TileAllocationStateT>
) {}

/**
 * Divides allocation states into classes - areas without intersections by keys
 * - Traverse all states. for each state key get adjacent keys and apply these keys to every multiple of coupled keys area.
 * - If there is no area that contains al least one key of ajacent keys set, create new area.
 * - Get result areas and look for intersections over other areas.
 * - If area keys intersects another area, merge two areas.
 */
function getAllocationStateClasses(
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
  graph: GraphT,
  numbersMap: Map<number, number>,
  allocationStates: Map<string, TileAllocationStateT>
) {
  function isDiscovered(tile: ITile) {
    return tile.opened && tile.discovered;
  }

  const discoveredKeys = Object.keys(graph).filter((k) =>
    isDiscovered(graph[k].data)
  );

  const checkList = discoveredKeys.map((k) => graph[k].data);

  const saveAndRequeue = (key: string, result: Partial<ITile>) => {
    const tileData = getTile(graph, key);
    if (!tileData) return;
    updateTile(graph, key, result);
    for (const a of tileData.adjacent) {
      if (isDiscovered(a) && !checkList.find((p) => p.key === a.key)) {
        checkList.push(a);
      }
    }
  };

  let _tile: ITile;
  while ((_tile = checkList.shift() as ITile)) {
    if (!_tile) break;
    if (!_tile.value) continue; // TODO: check if tile has adjacents. if value equals 0, means that all adjacents are
    const _params = getTile(graph, _tile.key);
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
    }
    if (undiscoveredAdjacents.length === 1) {
      if (!numbersMap.keys().some((k) => k === _tile.value)) {
        throwError(ERROR_STATE_NOT_VALID);
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
        // but there is no chances that is will happen
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
function getAllocations(numbers: number[], cellCount: number) {
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
function decompose(
  lenght: number,
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
    if (currentSum > sum || path.length >= lenght) {
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

execute([]);

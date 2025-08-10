/**
 * Problem:
 * given board of 7 * 11 tiles . possible numbers are finite.
 * there are tiles with null values. their value is sum of ajacent non-null tiles.
 * there are discovered tiles and unknown ones.
 * there are closed tiles and opened ones. non-null tile may be discovered but closed.
 * tails have string keys that defines its positions on the board.
 * Objective:
 * compute all possible positions of non-null numbers in the closed tiles.
 * result needs to be an array of all opened tiles and tiles with probabilities map.
 **/

function notNull(something: any): something is Omit<null, any> {
  return something !== null;
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
type GraphT = Record<string, TilePraramsT>

const ROWS_NUM = 11;
const COLS_NUM = 7;

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

const getTile = (tiles: ITile[], key: string) => {
  return tiles.find((t) => t.key === key);
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

const getBoardGraph: (openedTiles: ITile[]) =>  = (
  openedTiles
) => {
  const allTiles = [] as ITile[];
  for (let i = 0; i < ROWS_NUM; i++) {
    for (let j = 0; j < COLS_NUM; j++) {
      // key is not null
      const key = getKey(i, j, ROWS_NUM, COLS_NUM) as string;
      const tile = getTile(openedTiles, key);
      allTiles.push(tile || getEmptyTile(key));
    }
  }
  return Object.fromEntries(
    allTiles.map((t) => [
      t.key,
      { data: t, adjacent: getAdjacentTiles(t, allTiles) },
    ])
  );
};

export function execute(result: ITile[]): void {
  const discoveredKeys = result.map((t) => t.key);
  const graph = getBoardGraph(JSON.parse(JSON.stringify(result)));
  firstRun(graph);
}

export function firstRun(graph: GraphT) {
  const discoveredKeys = Object.keys(graph).filter(
    (k) => graph[k].data.discovered
  );

  const checkDiscoveredTraversalList = discoveredKeys.map((k) => graph[k]);
  let tile: TilePraramsT | undefined;
  while ((tile = checkDiscoveredTraversalList.shift())) {
    if (!tile) break;
    if (!tile.data.value) continue;
    const undiscoveredAdjacents = tile.adjacent.map(t => !t.discovered);
    if (!undiscoveredAdjacents) continue;
    else if (undiscoveredAdjacents.length === 1) {
      // update
    }
    else {
      // deep find
    }
  }
}

/** Decomposes given sum into numbers from list **/
export function decompose(
  lenght: number,
  sum: number,
  candidates: number[]
): number[][] {
  const result: number[][] = [];
  candidates.sort((a, b) => a - b); // Helps in pruning

  function backtrack(start: number, path: number[], currentSum: number): void {
    if (currentSum === sum) {
      result.push([...path]);
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
      backtrack(i, path, currentSum + candidates[i]);
      path.pop();
    }
  }

  backtrack(0, [], 0);
  return result;
}

execute([]);

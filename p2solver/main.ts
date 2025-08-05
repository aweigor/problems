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

export interface ITile {
  key: string;
  opened: boolean;
  discovered: boolean;
  value: number | null;
  number: number | null;
  probabilities: Map<number, number> | null;
}

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

const getBoardGraph: (
  openedTiles: ITile[]
) => Record<string, { data: ITile; adjacent: ITile[] }> = (openedTiles) => {
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
  const graph = getBoardGraph(JSON.parse(JSON.stringify(result)));
  console.log(graph);
}

execute([]);

function notNull(something: any): something is Omit<null, any> {
  return something !== null;
}

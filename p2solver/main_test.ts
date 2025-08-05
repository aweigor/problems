import { assertEquals } from "@std/assert";
import { getAdjacentTiles, getEmptyTile } from "./main.ts";

Deno.test(function addTest() {
  assertEquals(getAdjacentTiles(getEmptyTile(""), []), []);
});

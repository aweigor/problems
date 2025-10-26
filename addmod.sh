#!/bin/bash
set -e

if [ $# -eq 0 ]; then
  exit 1
fi

MODULE_NAME="$1"
MODULE_DIR="${MODULE_NAME}"

if [ -d "$MODULE_DIR" ]; then
  mkdir -p "$MODULE_DIR"
fi
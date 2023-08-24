#!/bin/bash

if [ -n "$(git status --porcelain)" ]; then
    git status && git add . && git commit -m "[Github Action] clang-format changes" && git push
else
    echo "Nothing to commit"
fi

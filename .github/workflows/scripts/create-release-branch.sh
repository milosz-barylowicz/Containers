#!/bin/bash

branch="release/${1}"

if [[ -n $(git ls-remote --heads origin ${branch}) ]]; then
    echo "${branch} already exist!"
    exit 1
else
    git branch ${branch} && git push origin -u ${branch}
fi

#!/bin/bash

if [$# -ne 1]
then
  echo "$Usage: scaffold.sh <song-name>"
fi

song_name=$1

mkdir -p ../data/$song_name/axeman1
mkdir -p ../data/$song_name/axeman2
mkdir -p ../data/$song_name/drummer

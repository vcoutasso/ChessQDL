#!/bin/bash

declare -a names=( "King.png" "Queen.png" "Bishop.png" "Knight.png" "Rook.png" "Pawn.png" )
declare -a prefix=( "w" "b")
original="../img/500px-Chess_Pieces_Sprite.png"
output="../img/"
width=83
height=83
x=0
y=0


for i in $(seq 0 1); do
	for j in $(seq 0 5); do
		eval "convert -extract ${width}x${height}+${x}+${y} ${original} ${output}${prefix[${i}]}${names[${j}]}"
		echo "convert -extract ${width}x${height}+${x}+${y} ${original} ${output}${prefix[${i}]}${names[${j}]}"
		let x=x+83
	done
	let y=83
	let x=0
done



#!/bin/bash

declare -a names=( "King.png" "Queen.png" "Bishop.png" "Knight.png" "Rook.png" "Pawn.png" )
declare -a prefix=( "w" "b")
original="~/Downloads/270px-Chess_Pieces_Sprite.png"
output="../img/"
width=45
height=45
x=0
y=0


for i in $(seq 0 1); do
	for j in $(seq 0 4); do
		eval "convert -extract ${width}x${height}+${x}+${y} ${original} ${output}${prefix[${i}]}${names[${j}]}"
		echo "convert -extract ${width}x${height}+${x}+${y} ${original} ${output}${prefix[${i}]}${names[${j}]}"
		let x=x+45
	done
	let y=45
	let x=0
done



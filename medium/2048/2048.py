"""
Input of 4x4 field (containing 2^x, x is 1...), followed by command

Input:

2 0 0 2
4 16 8 2
2 64 32 4
1024 1024 64 0
0

Output:
4 0 0 0
4 16 8 2
2 64 32 4
2048 64 0 0


0 -> left
1 -> up
2 -> right
3 -> down
"""

import copy

# row is a list of 4 elements, that will be merged from left to right


def merge_row(row):
    submitted = [False for _ in range(len(row))]

    for i in range(len(row)):
        new_index = i
        merged = False
        for _ in range(i):
            new_index -= 1
            if new_index >= 0 and not submitted[new_index]:
                if row[new_index] == row[new_index+1] and not merged and row[new_index] > 0:
                    merged = True
                    row[new_index] += row[new_index+1]
                    row[new_index+1] = 0
                    break
                elif row[new_index] == 0:
                    row[new_index] += row[new_index+1]
                    row[new_index+1] = 0
                else:
                    break
            else:
                break
        if merged:
            submitted[new_index] = True

    return row


# playfield is a 4x4 array
# direction is int 0...3
def solve(playfield, direction):

    # Left
    if direction == 0:
        for i, row in enumerate(playfield):
            merged = merge_row(row)
            playfield[i] = merged

    # Up
    elif direction == 1:
        for x in range(len(playfield)):
            row = []
            for y in range(len(playfield[x])):
                row.append(playfield[y][x])
            # print("row:", row)
            merged = merge_row(row)
            # print("merged:", merged)

            # insert values
            for y in range(len(playfield[x])):
                playfield[y][x] = merged[y]

    # Right
    elif direction == 2:
        for i, row in enumerate(playfield):
            row.reverse()
            merged = merge_row(row)
            merged.reverse()

            playfield[i] = merged

    # Down
    elif direction == 3:

        for x in range(len(playfield)):
            row = []
            for y in range(len(playfield[x])):
                row.append(playfield[y][x])
            row.reverse()
            merged = merge_row(row)
            merged.reverse()

            # insert values
            for y in range(len(playfield[x])):
                playfield[y][x] = merged[y]

    return playfield


# 2x2
playfield = []

# Read in each line
for _ in range(4):
    row = [int(x) for x in input().split(" ")]
    playfield.append(row)

# Read direction
direction = int(input())


# Solve input
solution = solve(playfield, direction)


for row in solution:
    print(' '.join([str(x) for x in row]))

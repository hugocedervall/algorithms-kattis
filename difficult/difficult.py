

def main(rows):

    found = {}

    for row in rows:

        for i in range(len(row)):
            # If no more pairs
            if i + 1 >= len(row):
                break

            tup = (row[i], row[i+1])
            if tup in found:
                found[tup] += 1
            else:
                found[tup] = 1

    all_matching = list(filter(lambda x: found[x] >= 3, found))
    print(len(all_matching))
    print(found)

    print("---")

    print(all_matching)


main([[1, 2, 3, 4], [2, 3, 4, 1], [4, 1, 2, 3]])


main([[3, 6, 1, 2, 4, 5], [3, 6, 1, 4, 2, 5], [3, 6, 1, 2, 4, 5]])

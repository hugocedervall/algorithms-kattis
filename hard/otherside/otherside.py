def solution():
    w, s, c, k = [int(elem) for elem in input().split(' ')]

    # If the given options are satisfiable
    valid = False

    # Since sheep can't be with either cabbages or wolfs, they can seen as two groups
    a = w + c
    b = s

    # If group is less than capacity, move back and forth until other group is moved
    if b < k or a < k:
        valid = True
    # If group 1 is max capacity, move group 1 to other side. Go back and
    # move as many from group 2 as possible to other side. Move back group 1
    # to starting side. Move rest of group 2 to other side, and then go and take
    # group 1 to other side as well.
    elif b == k and a <= 2 * k:
        valid = True
    elif a == k and b <= 2 * k:
        valid = True

    print("YES" if valid else "NO")


solution()

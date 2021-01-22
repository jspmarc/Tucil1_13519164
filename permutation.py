def perm1(lst: list) -> list:
    if len(lst) == 0:
        return []
    elif len(lst) == 1:
        return [lst]
    elif len(lst) == 2:
        return [lst, [lst[1], lst[0]]]
    else:
        l = []
        pivot = lst[0]
        permutated = perm1(lst[1:])
        for p in permutated:
            for i in range(len(p)+1):
                l.append(p[:i] + [pivot] + p[i:])

        return l

# batas_atas ekskulsif, batas_bawah inkulsif
def newPerm(length: int, batas_bawah: int, batas_atas:int) -> list[list]:
    if (length == 0):
        return []
    elif (length == 1):
        l = [i for i in range(batas_bawah, batas_atas)]
        return [l]
    elif (length == 2):
        l = [[i, j] for i in range(batas_bawah, batas_atas) for j in range(batas_bawah, batas_atas) if i != j]
        return l

    # else
    perm = newPerm(length-1, batas_bawah, batas_atas)
    l = []
    for p in perm:
        for i in range(batas_bawah, batas_atas):
            if not (i in p):
                l.append(p + [i])
    return l

l = newPerm(10, 0, 10)
print(l)
print(len(l))

def perm1(lst: list):
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

# vec = Vector([i for i in range(10)])
# print(vec)

lst = list('123')
# for i in range(len(lst)):
print(perm1(lst))
print(len(perm1(lst)))

def factorial(n: int) -> int:
    lst = [1]
    if not (n == 0 or n == 1):
        for i in range(2,n+1):
            lst.append(lst[i-2] * i)

    return lst[len(lst)-1]

def permutate_list(lst: list, n: int) -> list:
    if len(lst) == 0:
        return []
    elif len(lst) == 1:
        return lst
    else:
        l = []
        x = lst[n]
        xRest = lst[:n] + lst[n+1:]
        for p in permutate_list(xRest, n):
            l.append([x]+p)
        return l

class Vector:
    def __init__(self, lst: list):
        self.list: list = lst
        self.len: int = len(lst)
        self.permutate_count: int = 0
        self.max_permutate: int = factorial(self.len)

    def __str__(self):
        return self.list

    def permutate(self) -> bool:
        if self.permutate_count == self.max_permutate:
            return False

        self.list = permutate_list(self.list, self.permutate_count)
        self.permutate_count += 1
        return True

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

lst = list('abcdefghi')
# for i in range(len(lst)):
print(perm1(lst))
print(len(perm1(lst)))

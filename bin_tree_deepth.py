def func(T):
    if not T:
        return 0
    deepl = func(T.left)
    deepr = func(T.right)
    deep = deepl if deepl > deepr else deepr
    return deep + 1

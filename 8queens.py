def func(row = 0, selected = []):
    choice = []
    if row == 0:
        choice = range(0, 8)
    else:
        for i in xrange(0, 8):
            for j in xrange(row):
                if i == selected[j]:
                    break
                if row - j == abs(i - selected[j]):
                    break
            else:
                choice.append(i)
    if row == 7:
        return len(choice)
    else:
        count = 0
        for i in choice:
            try:
                selected[row] = i
            except:
                selected.append(i)
            count += func(row + 1, selected)
        return count

print func()

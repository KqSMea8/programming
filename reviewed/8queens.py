# -*- coding:utf8 -*-
# selected[i] = j --> i-th queen stands at j col

queens = 8

def func(row = 0, selected = []):
    choice = []
    if row == 0:
        choice = range(0, queens)
    else:
        for i in xrange(0, queens):
            for j in xrange(row):
                if i == selected[j]: # col crashing
                    break
                if row - j == abs(i - selected[j]): # diagonal crashing
                    break
            else:
                choice.append(i)
    if row == queens - 1:
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

if __name__ == "__main__":
    print func()

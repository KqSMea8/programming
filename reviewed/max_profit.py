# https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/description/

# recursive, O(n2)
def solution1(l, begin = 0):
    __max = 0
    for i in xrange(begin, len(l) - 1):
        for j in xrange(2):
            buy = i + j
            for sell in xrange(buy + 1, len(l)):
                if l[sell] > l[buy]:
                    curr_profit = l[sell] - l[buy]
                    rear_profit = solution1(l, sell + 1)
                    profit = rear_profit + curr_profit
                    if profit > __max:
                        __max = profit

    return __max

# dynamic programming
def solution2(l):
    __max = 0
    state = [[0, -1]]
    for i in xrange(len(l)):
        new_state = []
        for s in state:
            if s[1] < 0:  # no 'buy'
                s[1] = i
            else:
                if l[s[1]] < l[i]:
                    profit = s[0] + (l[i] - l[s[1]])

                    if profit > __max:
                        __max = profit

                    new_state.append([profit, -1])
                else:
                    s[1] = i
        state.extend(new_state)

    return __max

if __name__ == "__main__":
    test = [7,1,5,3,6,4]
    print solution1(test)
    print solution2(test)

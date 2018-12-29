coin_list = [1, 5, 2]

def coins(face_value):
    min_num_coins = [0]
    for i in xrange(1, face_value + 1):
        min_ = None
        for j in coin_list:
            if j <= i:
                if min_num_coins[i - j] != None:
                    if min_ == None:
                        min_ = min_num_coins[i - j] + 1
                    else:
                        min_ = min(min_, min_num_coins[i - j] + 1)
        min_num_coins.append(min_)
    #print min_num_coins
    return min_num_coins[face_value]

def coins_better(face_value):
    reserve_len = max(coin_list)
    min_num_coins = []
    for i in xrange(reserve_len):
        min_num_coins.append(0)
    for i in xrange(1, face_value + 1):
        min_ = None
        for j in coin_list:
            if j <= i:
                index = (i - j) % reserve_len
                if min_num_coins[index] != None:
                    if min_ == None:
                        min_ = min_num_coins[index] + 1
                    else:
                        min_ = min(min_, min_num_coins[index] + 1)
        min_num_coins[i % reserve_len] = min_
    #print min_num_coins
    return min_num_coins[face_value % reserve_len]

if __name__ == "__main__":
    print coin_list
    face_value = 1209
    for i in xrange(face_value + 1):
        if coins(i) != coins_better(i):
            print i, coins(i), coins_better(i)

    

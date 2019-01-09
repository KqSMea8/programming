class AvoidRoads:
    def numWays(self, width, height, bad):
        nums = [1]
        blocked = False
        for i in range(width):
            if blocked == False and ((0, i, 0, i+1) in bad):
                blocked = True
            nums.append(1 if not blocked else 0)

        for i in range(1, height+1):
            for j in range(0, width+1):
                if j == 0:
                    if nums[0] and ((i-1, 0, i, 0) in bad):
                        nums[0] = 0
                else:
                    a = not (i-1, j, i, j) in bad # downward
                    b = not (i, j-1, i, j) in bad # rightward
                    if a and b:
                        nums[j] += nums[j-1]
                    elif b:
                        nums[j] = nums[j-1]
                    elif a:
                        pass # num[j] = num[j]
                    else:
                        nums[j] = 0

            if not any(nums):
                return 0

        return nums[-1]
    

width = 2
height = 2 
bad = set([(0, 0, 1, 0), (1, 2, 2, 2), (1,1,2,1)])
o = AvoidRoads()
print(o.numWays(width, height, bad))


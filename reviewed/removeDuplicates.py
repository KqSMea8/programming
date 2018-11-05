class Solution(object):
    def removeDuplicates(self, nums):
        nums_len = len(nums)
        if nums_len < 2:
            return nums_len
        i = 0
        for j in xrange(1, nums_len):
            if nums[j] == nums[i]:
                continue
            i += 1
            nums[i] = nums[j]

        return i + 1

if __name__ == "__main__":
    s = Solution()
    test = [1,1,2,3,3,4,5]
    count = s.removeDuplicates(test)
    for i in xrange(count):
        print test[i],




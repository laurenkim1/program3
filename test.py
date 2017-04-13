with open('test', 'r') as f:
	nums = []
	for line in f:
		nums.append(int(line))

def karmakan_karp(nums):
	k = 0
	while len(nums) > 1:
		m = max(nums)
		nums.remove(m)
		n = max(nums)
		nums.remove(n)
		nums.append(abs(m - n))
	return nums[0]
print(karmakan_karp(nums))
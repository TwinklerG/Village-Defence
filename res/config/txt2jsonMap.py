ret = []
for i in range(10):
    ret.append([int(t) for t in input().split()])
print(ret)
# 8*21, input example
# 3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4
# 0 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0
# 0 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0
# 0 0 0 0 1 1 1 0 0 0 0 0 1 0 0 0 0 1 1 1 4
# 0 0 0 0 0 0 1 0 0 0 0 0 1 1 1 1 1 1 0 0 0
# 4 1 1 1 1 1 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0
# 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0
# 0 0 0 0 0 0 4 0 0 0 0 0 4 0 0 0 0 0 0 0 0

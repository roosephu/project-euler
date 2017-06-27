︠12d85702-5f09-4cae-aaa9-0f919724c944s︠
f = {}

def F(nums, cols, exist) :
    state = (nums, cols, exist)
    if state in f :
        return f[state]
    if cols == 0 :
        return 1 if nums == 0 and exist == 0 else 0
    ret = 0
    for i in range(min(nums, 10) + 1) :
        ret += F(nums - i, cols - 1, exist - (i != 0)) * binomial(10, i)
    f[state] = ret
    return ret

ans = 0
for i in range(7 + 1) :
    ans += F(20, 7, i) * i
print float(ans / binomial(70, 20))
︡ec5b45e0-8fcd-4121-b54c-0ae6568b0b77︡{"stdout":"6.81874180202\n"}︡
︠c96ec4cf-d7cc-4fdf-8f4f-982133b6c239︠










︠09b7e961-bba0-4bfb-a842-fbb1bd66c81b︠

︠7412d5cc-fa70-4fe1-884a-b981c07b791f︠
%cython
#clang c++

cdef int N = 10**8, k = 10**5

ctypedef long long int64
cdef int d[100000010], Q[101000]
cdef int i, j, head = 0, tail = 0

cdef int lb = N

cdef int sub(int n, int p) :
    cdef int ret = 1
    while n % p == 0 :
        n /= p
        ret += 1
    return ret

for i from 1 <= i <= N :
    d[i] = 1
for i from 2 <= i <= N :
    if d[i] == 1 :
        if i % 1000 == 1 :
            print i
        j = i
        while j <= N :
            d[j] *= sub(j, i)
            j += i
print 'Done'

cdef int64 ans = 0
for i from 1 <= i <= N :
    while Q[head] <= i - k and head <= tail:
        head += 1
    while d[Q[tail]] <= d[i] and head <= tail:
        tail -= 1
    tail += 1
    Q[tail] = i

    if i >= k :
        ans += d[Q[head]]

print ans
︡1c1e7ce1-c56d-4c1b-8823-cbc6aef43dba︡{"stdout":"3001"}︡{"stdout":"\n4001"}︡{"stdout":"\n7001"}︡{"stdout":"\n9001"}︡{"stdout":"\n13001"}︡{"stdout":"\n16001"}︡{"stdout":"\n19001"}︡{"stdout":"\n21001"}︡{"stdout":"\n24001"}︡{"stdout":"\n28001"}︡{"stdout":"\n51001"}︡{"stdout":"\n54001"}︡{"stdout":"\n55001\n61001"}︡{"stdout":"\n69001"}︡{"stdout":"\n70001\n76001"}︡{"stdout":"\n81001"}︡{"stdout":"\n88001"}︡{"stdout":"\n90001\n93001"}︡{"stdout":"\n96001\n97001\n102001"}︡{"stdout":"\n103001\n109001"}︡{"stdout":"\n114001\n115001"}︡{"stdout":"\n121001"}︡{"stdout":"\n123001\n124001\n126001\n129001"}︡{"stdout":"\n132001\n150001"}︡{"stdout":"\n153001\n154001\n160001"}︡{"stdout":"\n165001\n172001"}︡{"stdout":"\n178001\n180001"}︡{"stdout":"\n181001\n202001"}︡{"stdout":"\n208001\n217001"}︡{"stdout":"\n219001\n226001\n231001"}︡{"stdout":"\n238001\n247001"}︡{"stdout":"\n252001\n259001"}︡{"stdout":"\n270001"}︡{"stdout":"\n273001\n279001\n280001\n282001"}︡{"stdout":"\n283001\n286001\n289001\n294001\n318001"}︡{"stdout":"\n319001\n322001\n325001\n327001\n345001"}︡{"stdout":"\n348001\n354001\n361001\n366001\n367001\n376001"}︡
︠72575a22-63aa-49e1-8a5c-12a10c4672e1︠
︡cba663ae-89f2-4436-a402-41e398e3cfc3︡
︠73f4542e-6398-4fab-9a68-e73cb1e40177︠










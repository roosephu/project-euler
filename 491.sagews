︠1d7dad2d-349f-462d-9819-6220230f8f9c︠
%cython
#clang c++

import sage.all as _
ctypedef long long int64

cdef int64 f[21][59049][11]
cdef int i, S, r, v

f[0][0][0] = 1
for L from 0 <= L < 20 :
    print L
    for S from 0 <= S < 59049 :
        for r from 0 <= r < 11 :
            if f[L][S][r] == 0 :
                continue
            tmp = S
            v = 1
            for i from 0 <= i < 10 :
                if tmp % 3 != 2 :
                    f[L + 1][S + v][(r * 10 + i) % 11] += f[L][S][r]
                tmp = tmp / 3
                v = v * 3

print f[20][59048][0] - f[19][59047][0]
︡967cb693-7683-4935-8a1a-4e930fdde014︡{"stdout":"0"}︡{"stdout":"\n1\n2\n3\n4"}︡{"stdout":"\n5\n6\n7"}︡{"stdout":"\n8\n9"}︡{"stdout":"\n10"}︡{"stdout":"\n11"}︡{"stdout":"\n12"}︡{"stdout":"\n13"}︡{"stdout":"\n14"}︡{"stdout":"\n15\n16\n17"}︡{"stdout":"\n18\n19\n194505988824000\n"}︡{"html":"<a href='/0eaa1bc6-6816-4676-9623-9307e7983202/raw/.sage/temp/compute3dc1/4375/spyx/_projects_0eaa1bc6_6816_4676_9623_9307e7983202__sage_temp_compute3dc1_4375_dir_22RA4l_a_pyx/_projects_0eaa1bc6_6816_4676_9623_9307e7983202__sage_temp_compute3dc1_4375_dir_22RA4l_a_pyx_0.html' target='_new' class='btn btn-small' style='margin-top: 1ex'>Auto-generated code... &nbsp;<i class='fa fa-external-link'></i></a>"}︡
︠763a64cb-c24b-43cd-8c16-15b6cfb00ea6︠










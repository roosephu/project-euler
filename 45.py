# This file was *autogenerated* from the file 45.sage.
from sage.all_cmdline import *   # import sage library
_sage_const_3 = Integer(3); _sage_const_2 = Integer(2); _sage_const_1 = Integer(1); _sage_const_100000 = Integer(100000)
T, P, H = set(), set(), set()
for i in (ellipsis_range(_sage_const_1  ,Ellipsis, _sage_const_100000 )) :
    T.add(i * (i + _sage_const_1 ) / _sage_const_2 )
    P.add(i * (_sage_const_3  * i - _sage_const_1 ) / _sage_const_2 )
    H.add(i * (_sage_const_2  * i - _sage_const_1 ))

print T & P & H
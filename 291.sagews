︠4dd03ff5-d3a4-41a8-becc-8e0cbc3018f9is︠
import sage.all as _

P = _.Primes()
LMT = 5 * 10**15
ans = 0

for i in xrange(5e7):
    if i % 1000000 == 0:
        print i
    t = i * i + (i + 1) * (i + 1)
    if t > LMT:
        break
    if t in P:
        ans += 1
print ans
︡51d2f86c-854d-402c-ba5d-3a529427be6e︡{"stdout":"0\n1000000","done":false}︡{"stdout":"\n2000000","done":false}︡{"stdout":"\n3000000","done":false}︡{"stdout":"\n4000000","done":false}︡{"stdout":"\n5000000","done":false}︡{"stdout":"\n6000000","done":false}︡{"stdout":"\n7000000","done":false}︡{"stdout":"\n8000000","done":false}︡{"stdout":"\n9000000","done":false}︡{"stdout":"\n10000000","done":false}︡{"stdout":"\n11000000","done":false}︡{"stdout":"\n12000000","done":false}︡{"stdout":"\n13000000","done":false}︡{"stdout":"\n14000000","done":false}︡{"stdout":"\n15000000","done":false}︡{"stdout":"\n16000000","done":false}︡{"stdout":"\n17000000","done":false}︡{"stdout":"\n18000000","done":false}︡{"stdout":"\n19000000","done":false}︡{"stdout":"\n20000000","done":false}︡{"stdout":"\n21000000","done":false}︡{"stdout":"\n22000000","done":false}︡{"stdout":"\n23000000","done":false}︡{"stdout":"\n24000000","done":false}︡{"stdout":"\n25000000","done":false}︡{"stdout":"\n26000000","done":false}︡︡{"stdout":"\n25000000","done":false}︡{"stdout":"\n26000000","done":false}︡{"stdout":"\n27000000","done":false}︡{"stdout":"\n28000000","done":false}︡{"stdout":"\n29000000","done":false}︡{"stdout":"\n30000000","done":false}︡{"stdout":"\n31000000","done":false}︡{"stdout":"\n32000000","done":false}︡{"stdout":"\n33000000","done":false}︡{"stdout":"\n34000000","done":false}︡{"stdout":"\n35000000","done":false}︡{"stdout":"\n36000000","done":false}︡{"stdout":"\n37000000","done":false}︡{"stdout":"\n38000000","done":false}︡{"stdout":"\n39000000","done":false}︡{"stdout":"\n40000000","done":false}︡{"stdout":"\n41000000","done":false}︡{"stdout":"\n42000000","done":false}︡{"stdout":"\n43000000","done":false}︡{"stdout":"\n44000000","done":false}︡{"stdout":"\n45000000","done":false}︡{"stdout":"\n46000000","done":false}︡{"stdout":"\n47000000","done":false}︡{"stdout":"\n48000000","done":false}︡{"stdout":"\n49000000","done":false}︡{"stdout":"\n","done":false}︡{"stdout":"4037526\n","done":false}︡{"done":true}
︠66c8b961-75f2-4a58-8d50-0b1d9a8fd82a︠










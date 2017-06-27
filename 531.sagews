︠5bc2cac0-92ef-4660-bca6-a04fa4b8a9b1s︠
L = int(1e6)
R = int(1e6 + 5e3)

print CRT(2, 6, 4, 8)

p = {}
for i in range(L, R):
    p[i] = euler_phi(i)

ans = 0
for n in range(L, R):
    if n % 100 == 0:
        print n
    for m in range(n + 1, R):
        try:
            ans += CRT(p[n], p[m], n, m)
        except:
            pass
print ans
︡a9f557d2-61ad-4a86-b43d-a43cc74fd78d︡{"stdout":"6\n","done":false}︡{"stdout":"1000000\n1000100","done":false}︡{"stdout":"\n1000200","done":false}︡︡{"stdout":"\n1000200","done":false}︡{"stdout":"\n1000300","done":false}︡{"stdout":"\n1000400","done":false}︡{"stdout":"\n1000500","done":false}︡{"stdout":"\n1000600","done":false}︡{"stdout":"\n1000700","done":false}︡{"stdout":"\n1000800","done":false}︡{"stdout":"\n1000900","done":false}︡{"stdout":"\n1001000","done":false}︡{"stdout":"\n1001100","done":false}︡{"stdout":"\n1001200","done":false}︡{"stdout":"\n1001300","done":false}︡{"stdout":"\n1001400","done":false}︡{"stdout":"\n1001500","done":false}︡{"stdout":"\n1001600","done":false}︡{"stdout":"\n1001700","done":false}︡{"stdout":"\n1001800","done":false}︡{"stdout":"\n1001900","done":false}︡{"stdout":"\n1002000","done":false}︡{"stdout":"\n1002100","done":false}︡{"stdout":"\n1002200","done":false}︡{"stdout":"\n1002300","done":false}︡{"stdout":"\n1002400","done":false}︡{"stdout":"\n1002500","done":false}︡{"stdout":"\n1002600","done":false}︡{"stdout":"\n1002700","done":false}︡{"stdout":"\n1002800","done":false}︡{"stdout":"\n1002900","done":false}︡{"stdout":"\n1003000","done":false}︡{"stdout":"\n1003100","done":false}︡{"stdout":"\n1003200","done":false}︡{"stdout":"\n1003300","done":false}︡{"stdout":"\n1003400","done":false}︡{"stdout":"\n1003500","done":false}︡{"stdout":"\n1003600","done":false}︡{"stdout":"\n1003700","done":false}︡{"stdout":"\n1003800","done":false}︡{"stdout":"\n1003900","done":false}︡{"stdout":"\n1004000","done":false}︡{"stdout":"\n1004100","done":false}︡{"stdout":"\n1004200","done":false}︡{"stdout":"\n1004300","done":false}︡{"stdout":"\n1004400","done":false}︡{"stdout":"\n1004500","done":false}︡{"stdout":"\n1004600","done":false}︡{"stdout":"\n1004700","done":false}︡{"stdout":"\n1004800","done":false}︡{"stdout":"\n1004900","done":false}︡{"stdout":"\n","done":false}︡{"stdout":"4515432351156203105\n","done":false}︡{"done":true}︡{"stdout":"6\n","done":false}︡{"stdout":"1000000\n1000100","done":false}︡{"stdout":"\n1000200","done":false}︡{"stdout":"\n1000300","done":false}︡{"stdout":"\n1000400","done":false}︡{"stdout":"\n1000500","done":false}︡{"stdout":"\n1000600","done":false}︡{"stdout":"\n1000700","done":false}︡{"stdout":"\n1000800","done":false}︡{"stdout":"\n1000900","done":false}︡{"stdout":"\n1001000","done":false}︡{"stdout":"\n1001100","done":false}︡{"stdout":"\n1001200","done":false}︡{"stdout":"\n1001300","done":false}︡{"stdout":"\n1001400","done":false}︡{"stdout":"\n1001500","done":false}︡{"stdout":"\n1001600","done":false}︡{"stdout":"\n1001700","done":false}︡{"stdout":"\n1001800","done":false}︡{"stdout":"\n1001900","done":false}︡{"stdout":"\n1002000","done":false}︡{"stdout":"\n1002100","done":false}︡{"stdout":"\n1002200","done":false}︡{"stdout":"\n1002300","done":false}︡{"stdout":"\n1002400","done":false}︡{"stdout":"\n1002500","done":false}︡{"stdout":"\n1002600","done":false}︡{"stdout":"\n1002700","done":false}︡{"stdout":"\n1002800","done":false}︡{"stdout":"\n1002900","done":false}︡{"stdout":"\n1003000","done":false}︡{"stdout":"\n1003100","done":false}︡{"stdout":"\n1003200","done":false}︡{"stdout":"\n1003300","done":false}︡{"stdout":"\n1003400","done":false}︡{"stdout":"\n1003500","done":false}︡{"stdout":"\n1003600","done":false}︡{"stdout":"\n1003700","done":false}︡{"stdout":"\n1003800","done":false}︡{"stdout":"\n1003900","done":false}︡{"stdout":"\n1004000","done":false}︡{"stdout":"\n1004100","done":false}︡{"stdout":"\n1004200","done":false}︡{"stdout":"\n1004300","done":false}︡{"stdout":"\n1004400","done":false}︡{"stdout":"\n1004500","done":false}︡{"stdout":"\n1004600","done":false}︡{"stdout":"\n1004700","done":false}︡{"stdout":"\n1004800","done":false}︡{"stdout":"\n1004900","done":false}︡{"stdout":"\n","done":false}︡{"stdout":"4515432351156203105\n","done":false}︡{"done":true}︡{"stdout":"6\n","done":false}︡{"stdout":"1000000\n1000100","done":false}︡{"stdout":"\n1000200","done":false}︡{"stdout":"\n1000300","done":false}︡{"stdout":"\n1000400","done":false}︡{"stdout":"\n1000500","done":false}︡{"stdout":"\n1000600","done":false}︡{"stdout":"\n1000700","done":false}︡{"stdout":"\n1000800","done":false}︡{"stdout":"\n1000900","done":false}︡{"stdout":"\n1001000","done":false}︡{"stdout":"\n1001100","done":false}︡{"stdout":"\n1001200","done":false}︡{"stdout":"\n1001300","done":false}︡{"stdout":"\n1001400","done":false}︡{"stdout":"\n1001500","done":false}︡{"stdout":"\n1001600","done":false}︡{"stdout":"\n1001700","done":false}︡{"stdout":"\n1001800","done":false}︡{"stdout":"\n1001900","done":false}︡{"stdout":"\n1002000","done":false}︡{"stdout":"\n1002100","done":false}︡{"stdout":"\n1002200","done":false}︡{"stdout":"\n1002300","done":false}︡{"stdout":"\n1002400","done":false}︡{"stdout":"\n1002500","done":false}︡{"stdout":"\n1002600","done":false}︡{"stdout":"\n1002700","done":false}︡{"stdout":"\n1002800","done":false}︡{"stdout":"\n1002900","done":false}︡{"stdout":"\n1003000","done":false}︡{"stdout":"\n1003100","done":false}︡{"stdout":"\n1003200","done":false}︡{"stdout":"\n1003300","done":false}︡{"stdout":"\n1003400","done":false}︡{"stdout":"\n1003500","done":false}︡{"stdout":"\n1003600","done":false}︡{"stdout":"\n1003700","done":false}︡{"stdout":"\n1003800","done":false}︡{"stdout":"\n1003900","done":false}︡{"stdout":"\n1004000","done":false}︡{"stdout":"\n1004100","done":false}︡{"stdout":"\n1004200","done":false}︡{"stdout":"\n1004300","done":false}︡{"stdout":"\n1004400","done":false}︡{"stdout":"\n1004500","done":false}︡{"stdout":"\n1004600","done":false}︡{"stdout":"\n1004700","done":false}︡{"stdout":"\n1004800","done":false}︡{"stdout":"\n1004900","done":false}︡{"stdout":"\n","done":false}︡{"stdout":"4515432351156203105\n","done":false}︡{"done":true}
︠4136c8ea-c350-4734-aef4-52c245e84063︠
︡7392c6ea-f0ba-4453-b0e5-7910794ef5a4︡{"done":true}︡
︠a8751b8d-565a-464f-8955-d243c6067ce6︠
︡be612fe6-f49b-4a7f-a92e-ae9200d5d49c︡{"done":true}︡
︠361b12b7-e8c7-4594-b697-ead4c11289ce︠










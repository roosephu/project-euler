from collections import defaultdict

def get_num(info):
    card = info[0]
    if card == 'T':
        num = 10
    elif card == 'J':
        num = 11
    elif card == 'Q':
        num = 12
    elif card == 'K':
        num = 13
    elif card == 'A':
        num = 14
    else:
        num = int(card)
    return [num, info[1]]

def get_type(raw_cards):
    cards = list(reversed(sorted(map(get_num, raw_cards))))
    times = defaultdict(int)
    suits = {}
    for num, suit in cards:
        times[num] += 1
        suits[suit] = 1

    same_suit = len(suits) == 1
    times_cards = list(reversed(sorted(map(lambda s: [times[s[0]], s[0]], cards))))
    if same_suit and cards[0][0] == 10 and times_cards[0][0] == 1:
        ret = [-1]
    elif same_suit and cards[0][0] - cards[4][0] == 4 and times_cards[0][0] == 1:
        ret = [-2]
    elif times_cards[0][0] == 4:
        ret = [-3]
    elif times_cards[0][0] == 3 and times_cards[3][0] == 2:
        ret = [-4]
    elif same_suit:
        ret = [-5]
    elif cards[0][0] - cards[4][0] == 4 and times_cards[0][0] == 1:
        ret = [-6]
    elif times_cards[0][0] == 3:
        ret = [-7]
    elif times_cards[0][0] == 2 and times_cards[2][0] == 2:
        ret = [-8]
    elif times_cards[0][0] == 2:
        ret = [-9]
    else:
        ret = [-10]

    ret += times_cards
    if ret[0] == -9 or True:
        print raw_cards, ret
    return ret

ans = 0
with open('p054_poker.txt') as f:
    for line in f:
        cards = line[:-1].split(' ')
        L, R = cards[:5], cards[5:]
        L = get_type(L)
        R = get_type(R)

        if L > R:
            ans += 1
print ans

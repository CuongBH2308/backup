# let user guess a number between 1~100, users will have 60% chance to
# get it right

# Notes:
# 1. when select 6 from 10, the probability is 53%
# 2. when select 60 from 100, the probability is 59%, why???

import random

def win_or_loss(num):
    targets = random.sample(xrange(1, 101), 60)
    if num in targets:
        return True
    else:
        return False
    

def measure_probability(times):
    wins, losses = 0, 0
    while times > 0:
        num = int(random.random() * 100)
        if win_or_loss(num):
            wins += 1
        else:
            losses += 1
        times -= 1
    return float(wins)/(wins + losses)


print "The probability of this gambling is: %s" % measure_probability(1000)

def play_game(num, bet):
    if win_or_loss(num):
        return bet * 2
    else:
        return 0

# Bet 100 dollars every time
def simulate_even_bet(num, bet, init):
    count = 100
    money = init
    while count > 0 and money > bet:
        money -= bet
        money += play_game(num, bet)
        count -= 1
    return money

print simulate_even_bet(89, 10, 1000)
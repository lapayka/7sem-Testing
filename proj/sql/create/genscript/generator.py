from faker import Faker
from random import randint
from random import uniform
from random import choice


faker = Faker()

names = []
passports = []


passports = [faker.unique.pyint(4500000000, 4599999999) for i in range(1000)]
names = [faker.unique.company() for i in range(1000)]


banks = open("../data/banks.csv", "w")    
for i in range(1000):
    line = "{0}:{1}:{2}:{3}:{4}\n".format(names[i], faker.street_address(), randint(30000, 100000), randint(0, 100000000), names[randint(0, i)])
    banks.write(line)
    
banks.close()


users = open("../data/users.csv", "w")    
for i in range(1000):
    line = "{0}:{1}:{2}:{3}\n".format(passports[i], faker.name(), faker.date(),randint(0, 10))
    users.write(line)
    
users.close()


types = ["buy", "sell", "transaction"]
transactions = open("../data/transactions.csv", "w")    
for i in range(1000):
    line = "{0}:{1}:{2}:{3}:{4}:{5}\n".format(i, choice(names), choice(passports), faker.date(), choice(types), randint(1, 100000))
    transactions.write(line)
    
transactions.close()


ctypes = ["credit", "debit"]
psystem = ["MIR", "VISA", "MASTERCARD"]

cards = open("../data/cards.csv", "w")    
for i in range(1000):
    line = "{0}:{1}:{2}:{3}:{4}:{5}:{6}\n".format(i, choice(names), choice(passports), choice(ctypes), choice(psystem) , randint(1, 100000), faker.date())
    cards.write(line)
    
cards.close()

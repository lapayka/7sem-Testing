from faker import Faker
from random import randint
from random import uniform
from random import choice


mus_size = 10000

faker = Faker()

emails = [faker.unique.email() for i in range(1750)]


users = open("../data/users.csv", "w")    
for i in range(1000):
    line = "{0};{1}\n".format(emails[i], faker.pystr()[:5])
    users.write(line)
    
users.close()


aemails = emails[750:]

artists = open("../data/artists.csv", "w")    
for i in range(1000):
    name = [faker.word() for i in range(randint(1, 2))]
    name = " ".join(name)
    line = "{0};{1};{2}\n".format(aemails[i], faker.pystr()[:5], name)
    artists.write(line)
    
artists.close()

albums = open("../data/albums.csv", "w")    
for i in range(5000):
    name = [faker.word() for i in range(randint(1, 2))]
    name = " ".join(name)
    line = "{0};{1}\n".format(choice(aemails), name)
    albums.write(line)
    
albums.close()


muscomps = open("../data/muscomps.csv", "w")  
for i in range(mus_size):
    name = [faker.word() for i in range(randint(1, 2))]
    name = " ".join(name)
    duration = str(randint(0, 10)) + ':' + str(randint(0, 59))
    line = "{0};{1};{2};{3}\n".format(name, duration, randint(1000, 1000000000), randint(1, 1000))
    muscomps.write(line)
    
muscomps.close()

playlists = open("../data/playlists.csv", "w")    
for i in range(5000):
    name = [faker.word() for i in range(randint(1, 2))]
    name = " ".join(name)
    line = "{0}\n".format(name)
    playlists.write(line)
    
playlists.close()

emails = emails[:1000]
up = open("../data/up.csv", "w")    
for i in range(5000):
    line = "{0};{1}\n".format(choice(emails), i + 1)
    up.write(line)
    
up.close()

pairs = []
size = 100000
uc = open("../data/uc.csv", "w")    
for i in range(30000):
    while True:
        pair = [choice(emails), randint(1, mus_size)]
        if pair not in pairs:
            break
        
    #print(pair)
    pairs.append(pair)
    if (len(pairs) > size):
        print(size)
        size += 10000
    line = "{0};{1};{2}\n".format(pair[0], pair[1], randint(1, 200))
    uc.write(line)
    
uc.close()

pm = open("../data/pm.csv", "w")

for i in range(35000):    
    line = "{0};{1}\n".format(randint(1, 5000), randint(1, mus_size))
    pm.write(line)
    
pm.close()

emails = emails[:750]
requests = open("../data/requests.csv", "w")    
for i in range(10):
    name = [faker.word() for i in range(randint(1, 2))]
    name = " ".join(name)
    line = "{0};{1};{2}\n".format(choice(emails), name, 'active')
    requests.write(line)
    
requests.close()

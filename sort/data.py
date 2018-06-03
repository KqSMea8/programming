import random
import pickle

Max = 10000
a = range(-987, Max)
b = range(-9, Max / 2)
a.extend(b)
file = open("data.pkl", "wb")
pickle.dump(a, file)
file.close()

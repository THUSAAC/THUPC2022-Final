import random
print(" ".join(random.sample(["{}{}".format(s, p) for s in "SHCD" for p in range(1, 14)], 26)))
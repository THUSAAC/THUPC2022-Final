import random
import os
import datetime
import numpy as np

TASK_NUM = 1

R_LIMIT = 1000000000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def genEmpty():
	return

def genRandLR():
	assert 0

def genTestcase(filename, gen, a, b, **extra_param):
	log("Generating input for case {}, params: {} {} {} {}".format(filename, gen.__name__, a, b, extra_param))
	# assert ..., "Parameters invalid!"
	if not extra_param:
		l = random.randint(1, R_LIMIT)
		r = random.randint(1, R_LIMIT)
		if l > r:
			l, r = r, l
	else:
		l = extra_param["l"]
		r = extra_param["r"]
	
	with open("{}.in".format(filename), "w") as f:
		# f.write("{} {} {}\n{}\n".format(n, l, r, " ".join(list(map(str, s)))))
		f.write("{} {} {} {}\n".format(l, r, a, b))
	log("Generating output for case {}".format(filename))
	os.system('(time ../ShinyRacers/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, gen, a, b, **extra_param):
		self.cnt += 1
		genTestcase("{}{}".format(self.prefix, self.cnt), gen, a, b, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
# sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	
	testcase.gen(genEmpty, 6, 14, l = 1, r = 1)
	testcase.gen(genEmpty, 6, 15, l = 999999999, r = 1000000000)
	testcase.gen(genEmpty, 6, 14, l = (1 << 29) - 1, r = 973078527)
	testcase.gen(genEmpty, 6, 15, l = 1 << 29, r = 973078527)
	testcase.gen(genEmpty, 6, 14, l = 333333333, r = 333333333)
	testcase.gen(genRandLR, 2, 2)
	testcase.gen(genRandLR, 5, 5)
	testcase.gen(genRandLR, 6, 9)
	testcase.gen(genRandLR, 6, 10)
	testcase.gen(genRandLR, 6, 13)
	testcase.gen(genRandLR, 6, 16)
	testcase.gen(genRandLR, 6, 25)
	testcase.gen(genRandLR, 6, 26)
	for cnt in range(5):
		testcase.gen(genRandLR, random.randint(2, 6), random.randint(11, 26))
	for cnt in range(2):
		testcase.gen(genRandLR, random.randint(2, 6), random.randint(2, 10))
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")

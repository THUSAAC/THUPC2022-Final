import random
import os
import datetime
import numpy as np

TASK_NUM = 1

N_LIMIT = 100
W_LIMIT = 1000000000
A_LIMIT = 1000000000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def genLogA(num, segnum, bins = None):
	if bins is None:
		bins = [0] + [num - int(num / (i + 1)) for i in range(1, segnum)] + [num]
	else:
		segnum = len(bins) - 1
	log("num = {}, bins = {}".format(num, bins))
	randrange = np.int32(np.logspace(0, 9, segnum + 1, base = 10))
	randrange[segnum] += 1
	rng = np.random.default_rng()
	return np.concatenate(tuple(np.sort(rng.integers(randrange[i], randrange[i + 1], bins[i + 1] - bins[i])) for i in range(segnum)))

def genUniformA(num):
	rng = np.random.default_rng()
	return sorted(rng.integers(1, A_LIMIT, num))

def genInvalid(n, m):
	color = [0, 1]
	edge_dict = {}
	for i in range(2, n + 1):
		u = random.randint(1, i - 1)
		edge_dict[(u, i)] = random.randrange(2, W_LIMIT + 1, 2)
		color.append(1 - color[u])
	for i in range(n, m + 1):
		while True:
			u = random.randint(1, n)
			v = random.randint(1, n)
			if u != v:
				if u > v:
					u, v = v, u
				if color[u] != color[v] and (u, v) not in edge_dict:
					break
		edge_dict[(u, v)] = random.randrange(1, W_LIMIT + 1, 2)
	return 1, genUniformA(n - 1), [(e[0], e[1], edge_dict[e]) for e in edge_dict]

def genMiddle(n, m):
	edge_dict = {}
	for i in range(2, n + 1):
		u = random.randint(1, i - 1)
		edge_dict[(u, i)] = random.randint(1, W_LIMIT)
	for i in range(n, m + 1):
		while True:
			u = random.randint(1, n)
			v = random.randint(1, n)
			if u != v:
				if u > v:
					u, v = v, u
				if (u, v) not in edge_dict:
					break
		edge_dict[(u, v)] = random.randint(1, W_LIMIT)
	return 1, genLogA(n - 1, 2, [0, 2, n - 1]), [(e[0], e[1], edge_dict[e]) for e in edge_dict]

def genComplete(n, m):
	edge_dict = {}
	edge_list = []
	for i in range(1, n):
		for j in range(i + 1, n + 1):
			edge_list.append((i, j))
	edge_list = random.sample(edge_list, m)
	for edge in edge_list:
		edge_dict[(edge[0], edge[1])] = random.randint(1, W_LIMIT)
	return 1, genLogA(n - 1, random.randint(2, 6)), [(e[0], e[1], edge_dict[e]) for e in edge_dict]

def getUniformBins(num, segnum):
	return np.int32(np.linspace(0, num, segnum + 1))

def genSpine(n, m, spine_ratio = 0.8, genbin = None):
	edge_dict = {}
	spine = int(n * spine_ratio)
	assert 1 <= spine <= n
	node_list = [1] + random.sample(list(range(2, n + 1)), n - 1)
	rank = [0] * (n + 1)
	for i in range(n):
		rank[node_list[i]] = i
	for i in range(1, spine):
		edge_dict[(node_list[i - 1], node_list[i])] = (i + 1) * random.randint(1, W_LIMIT // (i + 1))
	for i in range(spine, n):
		u = random.randint(0, i - 1)
		edge_dict[(node_list[u], node_list[i])] = random.randint(1, W_LIMIT)
	edge_list = []
	for i in range(0, n - 1):
		for j in range(i + 1, n):
			if (node_list[i], node_list[j]) not in edge_dict:
				edge_list.append((node_list[i], node_list[j]))
	remain = m - (n - 1)
	random.shuffle(edge_list)
	for i in range(remain):
		edge_dict[edge_list[i]] = random.randint(1, W_LIMIT)
	segnum = random.randint(2, 10)
	if genbin is None:
		bins = None
	else:
		bins = genbin(n - 1, segnum)
	return 1, genLogA(n - 1, segnum, bins), [(e[0], e[1], edge_dict[e]) for e in edge_dict]

def genTestcase(filename, gen, n, m, shuffle_nodes = True, **extra_param):
	log("Generating input for case {}, params: {} {} {} {}".format(filename, gen.__name__, n, m, extra_param))
	# assert ..., "Parameters invalid!"
	if not extra_param:
		s1, a, edge_list = gen(n, m)
	else:
		s1, a, edge_list = gen(n, m, **extra_param)
	node_id = list(range(1, n + 1))
	if shuffle_nodes:
		random.shuffle(node_id)
	node_id = [0] + node_id
	random.shuffle(edge_list)
	with open("{}.in".format(filename), "w") as f:
		# f.write("{} {} {}\n{}\n".format(n, l, r, " ".join(list(map(str, s)))))
		f.write("{} {} {}\n".format(n, m, node_id[s1]))
		f.write(" ".join(map(str, a)) + "\n")
		for edge in edge_list:
			f.write("{} {} {}\n".format(node_id[edge[0]], node_id[edge[1]], edge[2]))
	log("Generating output for case {}".format(filename))
	os.system('(time ../ShinyRacers/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, gen, n, m, **extra_param):
		self.cnt += 1
		genTestcase("{}{}".format(self.prefix, self.cnt), gen, n, m, **extra_param)
	
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
	
	testcase.gen(genInvalid, 99, 500)
	testcase.gen(genMiddle, 99, 500)
	for cnt in range(3):
		testcase.gen(genComplete, N_LIMIT, N_LIMIT * (N_LIMIT - 1) // 2 - random.randint(0, 3))
	for ratio in (0.6, 0.8, 1):
		for cnt in range(3):
			testcase.gen(genSpine, N_LIMIT, N_LIMIT * (N_LIMIT - 1) // 2 - random.randint(0, 3), spine_ratio = ratio)
		for cnt in range(2):
			testcase.gen(genSpine, N_LIMIT, N_LIMIT * (N_LIMIT - 1) // 2 - random.randint(0, 3), spine_ratio = ratio, genbin = getUniformBins)
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")

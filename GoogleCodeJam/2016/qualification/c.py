
def prime_test(num):
	for i in range(3, min(num, 100001)):
		if (num % i == 0):
			return i
	return -1;

length, number = [int(i) for i in input().split(' ')]
count = 0;
for middle in range(0, 2 ** (length - 2)):
	digits = [1]
	tmp = middle
	for k in range(0, length - 2):
		digits.append(tmp % 2)
		tmp = int(tmp / 2)
	digits.append(1);
	digits.reverse()

	div_test = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
	mark = True
	for d in range(2, 10 + 1):
		num = 0
		tmp = 1
		for i in range(0, length):
			num += tmp * digits[i]
			tmp *= d
		div_test[d] = prime_test(num)
		if (div_test[d] == -1):
			mark = False
			break
	if (mark == True):
		count += 1
		print(" ".join([str(num)] + [str(div_test[i]) for i in range(2, 10 + 1)]))
		if (count >= number):
			break


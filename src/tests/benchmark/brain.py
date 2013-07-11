def execute(opcodes):
	opcode_length = len(opcodes)
	memory = {}
	loopstack = []
	sp = 0
	ip = 0

	result = ''

	for i in range(1000):
		memory[i] = 0

	while ip < opcode_length:
		v = opcodes[ip]
		if v == '+':
				memory[sp] += 1
		elif v == '-':
				memory[sp] -= 1
		elif v == '>':
				sp += 1
		elif v == '<':
				sp -= 1
		elif v == '.':
				result += chr(memory[sp])
		elif v == '[':
				if memory[sp] != 0:
					loopstack.append(ip)
				else:
					bracket_matching = 0
					found_index = 0
					for index in range(ip, opcode_length):
						if opcodes[index] == '[':
							bracket_matching += 1
						if opcodes[index] == ']':
							bracket_matching -= 1
						if bracket_matching == 0:
							found_index = index
							break

					if bracket_matching != 0:
						print("error: couldn't find match")
						return result
					else:
						ip = found_index
		elif v == ']':
				ip = loopstack.pop() - 1
		ip += 1

	return result

first = execute('++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.')
print(first)

second = execute('+++++++++++>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]')
print(second)


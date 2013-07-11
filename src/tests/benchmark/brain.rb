def execute opcodes
	opcode_length = opcodes.length
	memory = []
	loopstack = []
	sp = 0
	ip = 0

	result = ''

	for i in 0...1000
		memory[i] = 0
	end

	while ip < opcode_length
		case opcodes[ip]
			when '+'
				memory[sp] += 1
			when '-'
				memory[sp] -= 1
			when '>'
				sp += 1
			when '<'
				sp -= 1
			when '.'
				result += memory[sp].chr
			when '['
				if memory[sp] != 0
					loopstack.push(ip)
				else
					bracket_matching = 0
					found_index = 0
					(ip..opcode_length).each do |index|
						if opcodes[index] == '['
							bracket_matching += 1
						end
						if opcodes[index] == ']'
							bracket_matching -= 1
						end
						if bracket_matching == 0
							found_index = index
							break
						end
					end

					if bracket_matching != 0
						puts "error: couldn't find match"
						return result
					else
						ip = found_index
					end
				end
			when ']'
				ip = loopstack.pop() - 1
		end
		ip += 1
	end

	result
end

first = execute '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.'
puts first

second = execute '+++++++++++>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]'
puts second


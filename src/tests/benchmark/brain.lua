function execute(opcodes)
	opcode_length = string.len(opcodes)
	memory = {}
	loopstack = {}
	loopstack_index = 0
	sp = 0
	ip = 0

	result = ''

	for i = 0,1000 do
		memory[i] = 0
	end

	while ip < opcode_length do
		v = string.sub(opcodes, ip+1, ip+1)

		if v == '+' then
			memory[sp] = memory[sp] + 1
		elseif v == '-' then
			memory[sp] = memory[sp] - 1
		elseif v == '>' then
			sp = sp + 1
		elseif v == '<' then
			sp = sp - 1
		elseif v == '.' then
			result = result .. string.char(memory[sp])
		elseif v == '[' then
				if memory[sp] ~= 0 then
					loopstack[loopstack_index] = ip
					loopstack_index = loopstack_index + 1
				else
					bracket_matching = 0
					found_index = 0
					for index = ip, opcode_length do
						if string.sub(opcodes, index+1, index+1) == '[' then
							bracket_matching = bracket_matching + 1
						end
						if string.sub(opcodes, index+1, index+1) == ']' then
							bracket_matching = bracket_matching - 1
						end
						if bracket_matching == 0 then
							found_index = index
							break
						end
					end

					if bracket_matching ~= 0 then
						print("error: couldn't find match")
						return result
					else
						ip = found_index
					end
				end
		elseif v == ']' then
				loopstack_index = loopstack_index - 1
				ip = loopstack[loopstack_index] - 1
		end
		ip = ip + 1
	end

	return result
end

first = execute("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.")
print(first)

second = execute("+++++++++++>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]")
print(second)

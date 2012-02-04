function execute(opcode_string) {
	opcodes = new String(opcode_string);
	var opcode_length = opcodes.length;
	var memory = [];
	var loopstack = [];
	var sp = 0;
	var ip = 0;

	for (var i=0; i<1000; ++i) {
		memory[i] = 0;
	}

	while (ip < opcode_length) {
		switch(opcodes.charAt(ip)) {
			case '+':
				memory[sp]++;
				break;
			case '-':
				memory[sp]--;
				break;
			case '>':
				sp++;
				break;
			case '<':
				sp--;
				break;
			case '.':
				print(String.fromCharCode(memory[sp]));
				break;
			case '[':
				if (memory[sp]) {
					loopstack.push(ip);
				} else {
					for (var index = ip, bracket_matching = 0; index < opcode_length; index++) {
						opcodes.charAt(index) == '[' && bracket_matching++;
						opcodes.charAt(index) == ']' && bracket_matching--;
						if (bracket_matching == 0) {
							break;
						}
					}
					if (bracket_matching != 0) {
						print("error: couldn't find match");
						return false;
					} else {
						ip = index;
					}
				}
				break;
			case ']':
				ip = loopstack.pop() - 1;
				break;
			default:
				break;
		}
		ip++;
	}
	return true;
}

execute("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");

execute("+++++++++++
>+>>>>++++++++++++++++++++++++++++++++++++++++++++
>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>
+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-
<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<
-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]
>[<<+>>[-]]<<<<<<<]>>>>>[+++++++++++++++++++++++++
+++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++
++++++++++++++++++++++++++++++++++++++++++++.[-]<<
<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<
[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]");

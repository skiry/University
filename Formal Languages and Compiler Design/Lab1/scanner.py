from config import *

last_line = 1
last_position = 0
last_char = ""
tokens = []
symbol_table = {}
next_symbol = {}
program_internal_form = []

def read_tokens(tokens_file):
	global tokens
	with open(tokens_file, "r") as f:
	    r = f.readline()
	    while r:
	        tokens.append(r[:-1])
	        r = f.readline()

def get_char(file):
	global last_line, last_position
	ch = file.read(1)
	add = 1 if ch == '\n' else 0
	last_position = 0 if add else last_position + 1
	last_line += add
	return ch

def is_identifier_helper(word, idx):
	if idx == len(word) and idx:
		return True
	letter = word[idx]
	val = letter.isdigit() or letter.isalpha() or letter == "_"
	return val and is_identifier_helper(word, idx + 1)

def is_identifier(word):
	if len(word) and not word[0].isalpha():
		return False
	if len(word) > 8:
		raise MaxLimitExceeded("Maximum length exceeded for an identifier")
	return is_identifier_helper(word, 0)

def is_boolean(word):
	return word in ["true", "false"]

def is_string(word):
	return word[0] == word[-1] == '"' and len(word) > 1

def is_char(word):
	return len(word) == 3 and word[0] == word[2] and word[0] in ["'", '"'] and word[0] != word[1]

def is_numeric(word):
	if len(word) and word[0] in ["+", "-"]:
		word = word[1:]
	if not word.isnumeric():
		return False
	if len(word) > 1 and word[0] == "0":
		return False
	return True

def is_constant(word):
	return is_boolean(word) or is_string(word) or is_char(word) or is_numeric(word)

def look_forward(prev, curr):
	if curr == "=":
		if prev in [">", "<", "=", "!"]:
			return True
	if curr == prev == "*":
		return True
	return False

def get_word(file):
	global last_char
	word = ""
	current_letter = get_char(file)
	if look_forward(last_char, current_letter):
		to_add = last_char + current_letter
		program_internal_form.append((tokens.index(to_add), -1))
	elif last_char and last_char in OPERATORS:
		if not program_internal_form[-1][0] in range(START_TWO_SIGNS, END_TWO_SIGNS + 1):
			program_internal_form.append((tokens.index(last_char), -1))
	while current_letter not in DELIMITERS:
		word += current_letter
		current_letter = get_char(file)
	if is_numeric(word) and last_char in ["+", "-"]:
		program_internal_form.pop()
		word = last_char + word
	last_char = current_letter
	return word

def check_valid(word):
	if word[0].isdigit() and not word.isnumeric():
		nr = "".join(l for l in word if l.isdigit())
		idtf = "".join(l for l in word if not l.isdigit())
		raise Exception("You wanted to use the number " + str(nr) + \
			" or the identifier " + idtf + " instead of " + word + "?")

def compute_next(word):
	m = "z" * 90
	for k, v in symbol_table.items():
		if word < k:
			m = min(m, k)
	if m == "z" * 90:
		to_replace = -1
	else:
		to_replace = symbol_table[m]
	for k, v in next_symbol.items():
		if v == to_replace:
			next_symbol[k] = len(symbol_table)
	return to_replace

def stringify(nr):
	if nr > 9 or nr < 0:
		return str(nr)
	return " " + str(nr)

def print_st():
	print("-" * 40)
	print("SYMBOL TABLE POSITION | Symbol | Next")
	for k, v in symbol_table.items():
		print(" " * 10 + stringify(v) + " " * 10 + "| " + k + " | " + stringify(next_symbol[k]))

def print_pif():
	print("-" * 40)
	print("TOKEN CODE | ST_POSITION")
	for tpl in program_internal_form:
		print(" " * 3 + stringify(tpl[0]) + " " * 5 + " | " + " " * 3 + stringify(tpl[1]))
	print(" ".join(str(x[0]) for x in program_internal_form))

with open(SOURCE_FILE, "r") as source_code:
	try:
		read_tokens(TOKENS_FILE)
		word = get_word(source_code)
		if word != START:
			raise Exception("Program is not starting properly")
		while word != FINISH:
			if word != EMPTY_STRING:
				if word in tokens:
					program_internal_form.append((tokens.index(word), -1))
				elif is_constant(word) or is_identifier(word):
					if word not in symbol_table:
						next_symbol[word] = compute_next(word)
						symbol_table[word] = len(symbol_table)
					program_internal_form.append((is_constant(word) - 0, symbol_table[word]))
				else:
					raise Exception(word)
			word = get_word(source_code)
		program_internal_form.append((tokens.index(word), -1))
		print_st()
		print_pif()
		print(next_symbol)
	except EOFError as exc:
		print("Program is not ending properly")
	except MaxLimitExceeded as exc:
		print(f"You have a lexical error at line {last_line} position {last_position}")
		print(exc)
	except Exception as exc:
		print(f"You have a lexical error at line {last_line} position {last_position}")
		print("You may want to correct this word: " + str(exc))
		

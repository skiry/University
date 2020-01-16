from collections import defaultdict

def get_set(grammar):
	save_set = 0
	my_set = ""
	for i, letter in enumerate(grammar):
		if save_set and letter != "}":
			my_set += letter
		if letter == "{":
			save_set = 1
		elif letter == "}":
			return my_set, grammar[i + 1:]

def get_production_function(grammar):
	save_function = 0
	my_func = ""
	for i, letter in enumerate(grammar):
		if letter == "[": save_function += 1
		if letter == "]": save_function -= 1

		if save_function:
			my_func += letter
		elif not save_function and my_func:
			return my_func + "]", grammar[i + 1:]

def string_to_set(string):
	return set([x.strip(" ") for x in string.split(",")])

def string_to_map(string):
	productions = {}
	for x in string:
		non_terminal = x.split("->")[0].strip()
		values = [y.strip() for y in x.split("->")[1].split("|") ]
		productions[non_terminal] = values
	return productions

def read_grammar():
	with open("grammar.txt", "r") as f:
		G = f.readline()

		N, G = get_set(G)
		N = string_to_set(N)

		E, G = get_set(G)
		E = string_to_set(E)

		P, G = get_set(G)
		P = [x.strip() for x in P.split(";")]
		S = G.strip(", )")

	return N, E, P, S

def read_finite_automaton():
	with open("finite_automaton.txt", "r") as f:
		FA = f.readline()

		N, FA = get_set(FA)
		N = N.split(", ")

		E, FA = get_set(FA)
		E = E.split(", ")

		RO, FA = get_production_function(FA)
		Q0 = FA.split(",")[1].strip()

		F, FA = get_set(FA)
		F = string_to_set(F)

	return N, E, RO, Q0, F

def print_grammar_menu():
	print("0. Exit")
	print("1. Set of non-terminals")
	print("2. Set of terminals")
	print("3. Set of productions")
	print("4. Productions of a given non-terminal")
	print("5. Verify if the grammar is regular")
	print("6. Construct corresponding finite automaton")

def print_fa_menu():
	print("0. Exit")
	print("1. Set of states")
	print("2. The alphabet")
	print("3. Set of transitions")
	print("4. Set of final states")
	print("5. Construct corresponding regular grammar")

def is_regular_grammar(productions, non_terminals, alphabet, starting_symbol):
	is_right_rg = False
	is_left_rg = False

	have_epsilon = []
	for nt, values in productions.items():
		for rhs in values:
			if rhs == "epsilon":
				have_epsilon.append(nt)
			if rhs.count("+") > 1:
				# S-> 0S1
				return False
			elif rhs.count("+") == 1:
				t1, t2 = rhs.split("+")
				if t1 in alphabet and t2 in non_terminals:
					is_right_rg = True
				elif t2 in alphabet and t1 in non_terminals:
					is_left_rg = True
				else:
					# S->AA or S->11
					return False
			else:
				if rhs in non_terminals:
					# S->A
					return False

	if is_right_rg and is_left_rg:
		# S->aA and B->Ac
		return False

	if not len(have_epsilon):
		return True

	if len(have_epsilon) > 1:
		# S-> Epsilon and A->Epsilon
		return False 


	if have_epsilon[0] != starting_symbol:
		# A->Epsilon
		return False

	for nt, values in productions.items():
		for y in values:
			if starting_symbol in y.split("+"):
				# print(x, y)
				# S->Epsilon and A->S
				return False

	return True


def grammar_to_fa(non_terminals, alphabet, productions, starting_symbol):
	# M - states, E - alphabet, ro - transitions, 	q0 - starting state, F - final_states
	final_states = set()
	if "epsilon" in productions[starting_symbol]:
		final_states.add(starting_symbol)	
	final_states.add("new_final_state")
	productions["new_final_state"] = []
	states = set(productions.keys())
	transitions = [["" for x in alphabet] for x in states]
	trans = -1
	transition_indexes = []
	for non_terminal, production in productions.items():
		trans += 1
		for term in production:
			terminal = term.split("+")
			non_terminal_index = -1
			for index, letter in enumerate(alphabet):
				if letter == terminal[0]:
					non_terminal_index = index
					break
			if len(terminal) == 1:
				if non_terminal_index == -1:
					break
				if transitions[trans][non_terminal_index] == "":
					transitions[trans][non_terminal_index] = "new_final_state"
				else:
					transitions[trans][non_terminal_index] += "+new_final_state"
			else:
				if transitions[trans][non_terminal_index] == "":
					transitions[trans][non_terminal_index] = terminal[1]
				else:
					transitions[trans][non_terminal_index] += "+" + terminal[1]

	print(" \nFA = (Q, E, ro, q0, F)\
			\nM = set of states\
			\nE = alphabet\
			\nro = set of transitions\
			\nq0 = starting state\
			\nF = set of final states\n")
	print("Q = ", states)
	print("E = ", alphabet)
	trans = -1
	for non_terminal, _ in productions.items():
		trans += 1
		print(non_terminal + " : ", transitions[trans])
	print("q0 = ", starting_symbol)
	print("F = ", final_states)
	print()


def fa_to_grammar(states, alphabet, transitions, starting_state, final_states):
	# N - non_terminals, E - alphabet, P - productions, S - starting_symbol
	transitions = [(lambda x: [(lambda y: y.strip(" []"))(y) for y in x.split(",")])(x) for x in transitions.split(";")]
	productions = defaultdict(list)
	for index, state in enumerate(states):
		for idx, prods in enumerate(transitions[index]):
			for term in prods.split("+"):
				productions[state].append(alphabet[idx] + "+" + term)
				if term in final_states:
					if starting_state == state and "epsilon" not in productions[state]:
						productions[state].append("epsilon")
					
					productions[state].append(alphabet[idx])
	print(" \nRG = (N, E, P, S)\
			\nN = set of non-terminals\
			\nE = set of terminals\
			\nP = set of productions\
			\nS = starting symbol\n")
	print("N = ", set(states))
	print("E = ", set(alphabet))
	for non_term in states:
		print(non_term + " -> " + " | ".join(productions[non_term]))
	print("S = ", starting_state)
	print()


def main():
	N, E, P, S = read_grammar()
	Q, E, RO, Q0, F = read_finite_automaton()
	productions = string_to_map(P)
	while True:
		# break
		print_grammar_menu()
		try:
			text = int(input())
			if text == 1: print(N)
			elif text == 2: print(E)
			elif text == 3: print(P) 
			elif text == 4:
				nt = input()
				for production in P:
					if production.split()[0] == nt:
						print(production)
			elif text == 5: print(is_regular_grammar(productions, N, E, S))
			elif text == 6: grammar_to_fa(N, E, productions, S)
			elif not text: break
		except Exception as e:
			print(e)
			print("Please give a number from 0 to 6")

	while True:
		break
		print_fa_menu()
		try:
			text = int(input())
			if text == 1: print(set(Q))
			elif text == 2: print(set(E))
			elif text == 3: print(RO) 
			elif text == 4: print(F)
			elif text == 5: fa_to_grammar(Q, E, RO, Q0, F)
			elif not text: break
		except Exception as e:
			print(e)
			print("Please give a number from 0 to 5")

main()


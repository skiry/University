from collections import defaultdict
from copy import deepcopy

class Element:

    def __init__(self, productions):
        self.productions = productions
        self.first = set()
        self.follow = []
        self.computed_first = False

    def __str__(self):
        return "Productions: " + str(self.productions) + '\n' + \
               "First: " + str(self.first) + '\n' +  \
               "Follow: " + str(self.follow) + '\n' + \
               "Computed first yet - " + str(self.computed_first) + '\n'

def productions_string_to_element_class(productions):
    new_productions = {}
    for non_terminal in productions:
        prods = productions[non_terminal]
        productions_list = []
        for production in prods:
            if production == "epsilon":
                productions_list.append([])
            else:
                productions_list.append(production.split("plus"))
        new_productions[non_terminal] = Element(productions_list)
    return new_productions

def eliminate_left_recursion(productions):
    pass

def first(non_terminal, elements):
    '''
    eliminate left recursions beforehand
    '''
    for production in elements[non_terminal].productions:
        if not production:
            elements[non_terminal].first.add("epsilon")
        else:
            counter = 0
            for term in production:
                if not elements[term].computed_first:
                    first(term, elements)
                if "epsilon" not in elements[term].first:
                    elements[non_terminal].first = elements[non_terminal].first.union(elements[term].first)
                    break
                counter += 1
                elements[non_terminal].first = elements[non_terminal].first.union(elements[term].first.difference({"epsilon"}))
            if counter == len(production):
                elements[non_terminal].first.add("epsilon")
    elements[non_terminal].computed_first = True

def compute_first(elements):
    last = {}
    current = {}

    for non_terminal in elements:
        if not elements[non_terminal].computed_first:
            for prod in elements[non_terminal].productions:
                if not prod:
                    elements[non_terminal].first.add("epsilon")
                else:
                    if elements[prod[0]].computed_first:
                        elements[non_terminal].first = elements[non_terminal].first.union(elements[prod[0]].first)
        last[non_terminal] = deepcopy(elements[non_terminal].first)
        current[non_terminal] = deepcopy(elements[non_terminal].first)
    different = True
    while different:
        different = False
        for non_terminal in last:
            if not elements[non_terminal].computed_first:
                before = len(last[non_terminal])
                for prod in elements[non_terminal].productions:
                    if not prod:
                        current[non_terminal].add("epsilon")
                    else:
                        index = 0
                        '''
                        check if some first from the RHS from the previous step is null. if yes, break
                        '''
                        for p in prod:
                            if not last[p]:
                                index = -1
                        if index == -1:
                            continue
                        while index < len(prod):
                            '''
                            as long as epsilon belongs to some set, add that set excluding epsilon and go to the next 
                            element in the production
                            '''
                            if "epsilon" not in last[prod[index]]:
                                current[non_terminal] = current[non_terminal].union(last[prod[index]])
                                index = len(prod)
                            else:
                                current[non_terminal] = current[non_terminal].union(last[prod[index]].difference({"epsilon"}))
                            index += 1
                        if index == len(prod):
                            '''
                            all the elements from the RHS have epsilon in their FIRST set from the previous step
                            '''
                            current[non_terminal].add("epsilon")
                after = len(current[non_terminal])
                if before != after:
                    different = True
            last[non_terminal] = deepcopy(current[non_terminal])
    for non_terminal in elements:
        if not elements[non_terminal].computed_first:
            elements[non_terminal].first = deepcopy(last[non_terminal])
            elements[non_terminal].computed_first = True


def compute_follow(elements, non_terminals, starting_symbol):
    last = {}
    current = {}
    for non_terminal in non_terminals:
        last[non_terminal] = set()
        current[non_terminal] = set()
    last[starting_symbol] = {"epsilon"}
    current[starting_symbol] = {"epsilon"}

    different = True
    while different:
        different = False
        for non_terminal in non_terminals:
            before = len(last[non_terminal])
            for prod_nt in non_terminals:
                for prod in elements[prod_nt].productions:
                    start = 0
                    if non_terminal in prod:
                        nt_indexes = []
                        for position, element in enumerate(prod):
                            if element == non_terminal:
                                nt_indexes.append(position)
                        for nt_index in nt_indexes:
                            if nt_index == len(prod) - 1:
                                if non_terminal == prod_nt:
                                    '''
                                    C -> *DC
                                    '''
                                    continue

                                '''
                                B -> DC
                                '''
                                current[non_terminal] = current[non_terminal].union(last[prod_nt])
                            else:
                                if "epsilon" in elements[prod[nt_index + 1]].first:
                                    current[non_terminal] = current[non_terminal].union(last[prod_nt])
                                    current[non_terminal] = current[non_terminal].union(elements[prod[nt_index + 1]].first.difference({"epsilon"}))

                                else:
                                    current[non_terminal] = current[non_terminal].union(elements[prod[nt_index + 1]].first)
            after = len(current[non_terminal])
            if before != after:
                different = True
        for non_terminal in non_terminals:
            last[non_terminal] = deepcopy(current[non_terminal])
    for non_terminal in non_terminals:
        elements[non_terminal].follow = deepcopy(last[non_terminal])

def first_of_alpha(prod, elements):
    index = 0
    result = set()
    while index < len(prod):
        '''
        as long as epsilon belongs to some set, add that set excluding epsilon and go to the next 
        element in the production
        '''
        if "epsilon" not in elements[prod[index]].first:
            result = result.union(elements[prod[index]].first)
            index = len(prod)
        else:
            result = result.union(elements[prod[index]].first.difference({"epsilon"}))
        index += 1
    if index == len(prod):
        '''
        all the elements from the RHS have epsilon in their FIRST set from the previous step
        '''
        result.add("epsilon")
    return result

def compute_parsing_table(elements, non_terminals):
    table = defaultdict(dict)
    index = 0
    for non_terminal in non_terminals:
        print(non_terminal)
        for production in elements[non_terminal].productions:
            index += 1
            alpha_result = first_of_alpha(production, elements)
            print(non_terminal, production, alpha_result, table[non_terminal])
            if "epsilon" in alpha_result:
                for follow in elements[non_terminal].follow:
                    if follow == "epsilon":
                        to_add = "$"
                    else:
                        to_add = follow
                    if to_add in table[non_terminal] and table[non_terminal][to_add]:
                        print(to_add)
                        print("ERROR when adding production " + str(production) + " for the non terminal " + str(non_terminal))
                    table[non_terminal][to_add] = [production, index]
            else:
                for first in alpha_result:
                    if first in table[non_terminal] and table[non_terminal][first]:
                        print(first)
                        print("ERROR when adding production " + str(production) + " for the non terminal " + str(non_terminal))
                    table[non_terminal][first] = [production, index]
    for non_terminal in non_terminals:
        print(non_terminal)
        print(table[non_terminal])
    return table

def syntactic_analysis(parsing_table, input_sequence, starting_symbol):
    print(input_sequence)
    input_stack = input_sequence
    work_stack = [starting_symbol]
    output = []
    while True:
        print(input_stack)
        print(work_stack, output)
        print()
        if not work_stack:
            if not input_stack:
                print("Sequence accepted!")
            else:
                print("Sequence not accepted!")
            return output

        if not input_stack:
            '''
            check if the remaining non terminals go into epsilon
            '''
            while work_stack:
                non_terminal = work_stack.pop(0)
                for terminal in parsing_table[non_terminal]:
                    if not parsing_table[non_terminal][terminal][0]:
                        output.append(parsing_table[non_terminal][terminal][1])
                        break
                else:
                    # if I got here it means that some non terminal has no epsilon as a result
                    print("Sequence not accepted!")
                    return output
            print("Sequence accepted!")
            return output

        if input_stack[0] == work_stack[0]:
            # print("POP " + input_stack[0])
            input_stack.pop(0)
            work_stack.pop(0)
        else:
            current_symbol = work_stack.pop(0)
            to_expand = parsing_table[current_symbol][input_stack[0]]
            intermediate_list = work_stack[:]
            work_stack = to_expand[0][:]
            work_stack.extend(intermediate_list)
            output.append(to_expand[1])

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

        S = G.strip(' ,)\n')

        w = f.readline().strip('\n').split()

    return N, E, P, S, w

def print_grammar_menu():
    print("0. Exit")
    print("1. Set of non-terminals")
    print("2. Set of terminals")
    print("3. Set of productions")
    print("4. Productions of a given non-terminal")
    print("5. All info")
    print("6. Compute first")
    print("7. Compute follow")
    print("8. Compute parsing table")
    print("9. Syntactic analysis of an input sequence")
    print("10. Print parsing tree as productions string")


def main():
    N, E, P, S, w = read_grammar()
    productions = string_to_map(P)
    elements = productions_string_to_element_class(productions)
    for terminal in E:
        elements[terminal] = Element([])
        elements[terminal].first = {terminal}
        elements[terminal].computed_first = True
    while True:
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
            elif text == 5:             
                for el in elements:
                    print(el + " : " + str(elements[el]))
            elif text == 6:
                compute_first(elements)
            elif text == 7:
                compute_follow(elements, N, S)
            elif text == 8:
                parsing_table = compute_parsing_table(elements, N)
            elif text == 9:
                output = syntactic_analysis(parsing_table, w, S)
            elif text == 10:
                productions_result = []
                for action in output:
                    added = False
                    for non_terminal in N:
                        if added: break
                        for terminal in parsing_table[non_terminal]:
                            if added: break
                            interm = parsing_table[non_terminal][terminal]
                            if interm[1] == action:
                                productions_result.append([non_terminal, interm[0]])
                                added = True
                    if not added:
                        productions_result.append([non_terminal, 0])
                for production in productions_result:
                    if not production[1]:
                        print(str(production[0]) + " -> ε")
                    else:
                        print(str(production[0]) + " -> " + str(production[1]))
                        for terminal in production[1]:
                            if terminal in E:
                                print("POP " + terminal)
                            else:
                                break
            elif not text: break
        except Exception as e:
            print(e)
            print("Please give a number from 0 to 10")

main()


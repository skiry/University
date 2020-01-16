SOURCE_FILE = "sc-lab4.txt"
#SOURCE_FILE = "lala.txt"
TOKENS_FILE = "words.txt"
DELIMITERS = "{}[]():, =+-*/" + '\n' + '\t'
OPERATORS = "{}[]():,><*=/+-"
EMPTY_STRING = ""
START = "startprogram"
FINISH = "endprogram"
START_TWO_SIGNS = 7
END_TWO_SIGNS = 11

class MaxLimitExceeded(Exception):
	pass

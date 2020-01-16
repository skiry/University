with open("words.txt", "r") as f:
    r = f.readline()
    arr = []
    while r:
        arr.append((r[:-1], len(arr)))
        r = f.readline()
maxx = max((lambda x: len(x[0]))(x) for x in arr)
def stringify(x):
    return str(x) if x > 9 else " " + str(x)
with open("tokens.txt", "w") as f:
    for x in arr:
        f.write("-" * (maxx + 9))
        f.write("\n")
        f.write("| " + x[0] + " " * (maxx - len(x[0])) + " | " + stringify(x[1]) + " |")
        f.write("\n")
    f.write("-" * (maxx + 9))

with open("tokens2.txt", "w") as f:
    for x in arr:
        f.write("\"")
        f.write(x[0])
        f.write("\"\t")
        f.write("{printf( \"Reserved word: %s\\n\", yytext );  return " + str(x[1]) +";}")
        f.write("\n")

with open("tokens3.txt", "w") as f:
    for x in arr:
        f.write("%token " + str(x[1]) + '\n')

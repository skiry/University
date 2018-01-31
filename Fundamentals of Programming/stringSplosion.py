def stringSplosion(word):
    result=""
    for i in range(1,len(word)+1):
        result+=word[:i]
    return result

yword=input("Enter the word you want to stringSplode: ")
print("The stringSplosion of ", yword, " is ", stringSplosion(yword))

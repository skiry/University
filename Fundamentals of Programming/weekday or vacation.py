def sleepIn(weekday, vacation):
    if not weekday or vacation:
        return True
    else:
        return False
weekday = input("Is it a weekday? ")
weekday = (weekday == 'yes')
vacation = input("Are we on vacation? ")
vacation = (vacation == 'yes')
print("Do we sleep in? ", sleepIn(weekday, vacation))

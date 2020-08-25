str = input()


def findss(str):
    last_char = ""
    for i in range(len(str)):
        if(str[i].lower() == "s" and last_char.lower() == "s"):
            return "hiss"
        last_char = str[i]
    return "no hiss"

print(findss(str))



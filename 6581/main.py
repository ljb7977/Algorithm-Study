# with open("input.txt", "r") as f:
import sys

sys.stdin = open("input.txt", "r")

words = []
while True:
    line = sys.stdin.readline()
    if not line:
        break
    words.extend(line.split())

# print(words)
lines=[]
line=""
count = 0
for word in words:
    if word == "<br>":
        lines.append(line)
        # lines.append("")
        line = ""
        count = 0
    elif word == "<hr>":
        if line != "":
            lines.append(line)
        lines.append("-"*80)
        line=""
        count = 0
    else:
        if line == "":
            line += word
            count = len(word)
        else:
            if count+len(word)+1 <= 80:
                count += len(word)+1
                line += " "+word
            else:
                lines.append(line)
                count = len(word)
                line = word+""
lines.append(line)
for line in lines:
    print(line)
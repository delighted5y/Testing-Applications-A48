import random
Commands = ["penup", "pendown", "right", "left", "forward", "backward", "colour", "loop"]
length = int(input("Please enter the number of commands you want to generate:\n"))
loop_depth = int(input("Please enter the maximum number of iterations of a loop:\n"))
loop_size = int(input("Please enter the maxinum number of commands in a loop\n"))
file = open("test-pro.txt", 'w')
for i in range(length):
    choice = random.randint(0,7)
    val = 0
    if Commands[choice] == "colour":
        val = random.randint(0,255)
        file.write(Commands[choice] + ' ' + str(val) + '\n')
    elif Commands[choice] == "forward" or Commands[choice] == "backward":
        val = random.randint(-512, 512)
        file.write(Commands[choice] + ' ' + str(val) + '\n')
    elif Commands[choice] == "loop":
        val = random.randint(0, loop_depth)
        file.write(Commands[choice] + ' ' + str(val) + '\n')
        for j in range(loop_size):
            sub_choice = random.randint(0,6)
            sub_val = 0
            if Commands[sub_choice] == "colour":
                sub_val = random.randint(0,255)
                file.write('  ' + Commands[sub_choice] + ' ' + str(sub_val) + '\n')
            elif Commands[sub_choice] == "forward" or Commands[sub_choice] == "backward":
                sub_val = random.randint(-512, 512)
                file.write('  ' + Commands[sub_choice] + ' ' + str(sub_val) + '\n')
            else:
                file.write('  ' + Commands[sub_choice] + '\n')
    else:
        file.write(Commands[choice] + '\n')
file.close()
print("Commands generated!\n")
    
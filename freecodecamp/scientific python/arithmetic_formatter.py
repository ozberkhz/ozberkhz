import math

def arithmetic_arranger(problems, display = False):

  if len(problems) > 5:
    return "Error: Too many problems."

  arranged_problems = ""

  first_numbers = []
  operators = []
  second_numbers = []
  writing_length_1 = []
  writing_length_2 = []
  longest = []

  for i in problems:

    i = i.split()

    try:
      i[0] = int(i[0])
      i[2] = int(i[2])
    except:
      return "Error: Numbers must only contain digits."

    first_numbers.append(i[0])
    second_numbers.append(i[2])
    
    if i[1] != '+' and i[1] != '-':
      return "Error: Operator must be '+' or '-'."

    operators.append(i[1])

    if i[0] >= 10000 or i[2] >= 10000:
      return "Error: Numbers cannot be more than four digits."

    if i[0] > 1:
        writing_length_1.append(math.ceil(math.log(i[0],9.99)))
    else:
        writing_length_1.append(1)
    if i[2] > 1:    
        writing_length_2.append(math.ceil(math.log(i[2],9.99))) 
    else: 
        writing_length_2.append(1) 

    if writing_length_1[len(writing_length_1) - 1] > writing_length_2[len(writing_length_2) - 1]:
      longest.append(writing_length_1[len(writing_length_1) - 1])
    else:
      longest.append(writing_length_2[len(writing_length_2) - 1])
    
  for i in range(0, len(problems)):
    arranged_problems += (" " * (longest[i] + 2 - writing_length_1[i] )) 
    arranged_problems += str(first_numbers[i])
    if i < len(problems) - 1: 
      arranged_problems += " " * 4
    
  arranged_problems += "\n"

  for i in range(0, len(problems)):
    arranged_problems += operators[i] + (" " * (longest[i] + 1 - writing_length_2[i])) 
    arranged_problems += str(second_numbers[i])
    if i < len(problems) - 1:
      arranged_problems += " " * 4

  arranged_problems += "\n"

  for i in range(0, len(problems)):
    arranged_problems += "-" * (longest[i] + 2)
    if i < len(problems) - 1:
      arranged_problems += " " * 4
    

  if display == True:

    arranged_problems += "\n"

    for i in range(0, len(problems)):
      if operators[i] == '+':
        arranged_problems += " " * (longest[i] + 2 - (math.ceil(math.log(abs(first_numbers[i] + second_numbers[i]), 9.99))))
        arranged_problems += str(first_numbers[i] + second_numbers[i])
        if i < len(problems) - 1:
          arranged_problems += " " * 4
      else:
        if first_numbers[i] - second_numbers[i] < -1:
            arranged_problems += " " * (longest[i] + 1 - (math.ceil(math.log(abs(first_numbers[i] - second_numbers[i]), 9.99))))
        elif first_numbers[i] - second_numbers[i] < 2:
            arranged_problems += " " * (longest[i] + 1)
        else:
            arranged_problems += " " * (longest[i] + 2 - (math.ceil(math.log(abs(first_numbers[i] - second_numbers[i]), 9.99))))
        arranged_problems += str(first_numbers[i] - second_numbers[i])
        if i < len(problems) - 1:
          arranged_problems += " " * 4

    print(arranged_problems)

  return arranged_problems


arithmetic_arranger(["11 + 4", "3801 - 299", "1 + 2", "123 - 123", "1 - 930"], True)














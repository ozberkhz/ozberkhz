import copy
import random

class Hat:
    def __init__(self, **kwargs):
        self.contents = []
        for i in kwargs.items():
            for j in range(0, i[1]):
                self.contents.append(str(i[0])) 
    def draw(self, number_of_removals):
        drawed_balls = []
        if number_of_removals > len(self.contents):
            return self.contents
        else:
            for i in range(0, number_of_removals):
                x = random.randrange(0, len(self.contents))
                drawed_balls.append(self.contents[x])
                self.contents.pop(x)
            return drawed_balls
        
def experiment(hat, expected_balls, num_balls_drawn, num_experiments):
    N = num_experiments
    M = 0
    
    for i in range(0, num_experiments):
        duplicate = copy.deepcopy(hat)
        temp = hat.draw(num_balls_drawn)
        result_of_experiment = dict()
        equal = True
        
        for j in range(0, len(temp)):
            result_of_experiment[str(temp[j])] = 0

        for j in range(0, len(temp)):
            result_of_experiment[str(temp[j])] += 1
        
        for j in expected_balls:
            try:
                if result_of_experiment[j] < expected_balls[j]:
                    equal = False
            except:
                equal = False
        
        if equal:
            M += 1
                        
        hat = copy.deepcopy(duplicate)
    return M/N

hat = Hat(blue=4, red=2, green=6)
print(experiment(hat, {"blue": 2, "red": 1}, 4, 200))

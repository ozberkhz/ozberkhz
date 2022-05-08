import math

class Category:

    def __init__(self, category):
        self.category = category
        self.ledger = []
  
    def get_balance(self):
        money = 0
        for i in self.ledger:
            money += i["amount"]
        return money

    def deposit(self, amount, description = ""):
        if description == None:
            return ""
        else:
            to_append = {"amount": amount, "description": description}
            self.ledger.append(to_append)
            return True

    def withdraw(self, amount, description = ""):
        if amount > self.get_balance():
            return False
        else:
            to_append = {"amount": -amount, "description": description}
            self.ledger.append(to_append)
            return True

    def transfer(self, amount, which_category):
        if self.get_balance() >= amount:
            self.ledger.append({"amount": -amount, "description": "Transfer to {}".format(which_category.category)})
            which_category.ledger.append({"amount": amount, "description": "Transfer from {}".format(self.category)})
            return True  
        else:
            return False

    def check_funds(self, amount):
        if amount > self.get_balance():
            return True
        else:
            return False
  
    def __str__(self):
        display = ""
        length = 30 - len(self.category)
        if length % 2 == 0:
            display += (length // 2) * "*" + self.category + (length // 2) * "*" + "\n"
        else:
            display += ((length // 2) + 1) * "*"  + self.category + (length // 2) * "*" + "\n"
            
        for i in self.ledger:
            if len(i["description"]) <= 23:
                display += i["description"]
                display += (30 - len(i["description"]) - len("{:.2f}".format(float(i["amount"])))) * " "
            else:
                display += i["description"][:23] 
                display += (7 - len(str("{:.2f}".format(float(i["amount"]))))) * " "
            display += "{:.2f}".format(float(i["amount"])) + "\n"
        
        display += "Total: " + str(self.get_balance())
            
        return display
      

def create_spend_chart(categories):
    percentage = [0,0,0,0]
    total_spending = 0
    
    for i in range(0, len(categories)):
        for j in range(0, len(categories[i].ledger)):
            if categories[i].ledger[j]["amount"] < 0:
                percentage[i] -= categories[i].ledger[j]["amount"]  
                total_spending -= categories[i].ledger[j]["amount"]   
    
    for i in range(0, len(categories)):
        percentage[i] = math.floor(percentage[i] / (total_spending) * 10) * 10
        
    
    chart = "Percentage spent by category\n"
    chart += "100|" + " " * 10
    chart += "\n"        
    x = range(90, 0, -10)
    for i in x:
        chart += " " + str(i) + "|"
        
        for j in range(0, len(categories)):
            
            
            if (percentage[j] >= i):
                chart +=  " o "
            else:
                chart += " " * 3    
                    
        chart += " \n"
    chart += "  0| o  o  o  \n"
    chart += " " * 4 + "---" * len(categories) + "-\n"
    
    max_length = max(len(x) for x in [categories[i].category for i in range(0, len(categories))])
    
    chart += " " * 5 
    
    for i in range(0, max_length):
    
        try:
            chart += categories[0].category[i]
        except:
            chart += " "
        if (len(categories) > 1):
            try:
                chart += " " * 2 + categories[1].category[i]
            except:
                chart += " " * 3
        if (len(categories) > 2):
            try:
                chart += " " * 2 + categories[2].category[i]
            except:
                chart += " " * 3
        if (len(categories) > 3):
            try:
                chart += " " * 2 + categories[3].category[i]
            except:
                chart += " " * 3
        if i < max_length - 1:
            chart += "  \n" + " " * 5
    chart += "  "
    return chart


food = Category("Food")
food.deposit(1000, "initial deposit")
food.withdraw(10.15, "groceries")
food.withdraw(15.89, "restaurant and more food for dessert")
print(food.get_balance())
clothing = Category("Clothing")
food.transfer(50, clothing)
clothing.withdraw(25.55)
clothing.withdraw(100)
auto = Category("Auto")
auto.deposit(1000, "initial deposit")
auto.withdraw(15)

print(food)
print(clothing)

print(create_spend_chart([food, clothing, auto]))


























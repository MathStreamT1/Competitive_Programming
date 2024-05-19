import math
from decimal import Decimal, getcontext

# Thiết lập precision cho Decimal
getcontext().prec = 30

def calculate(expression):
    try:
        # Xử lý biểu thức để tính toán giai thừa
        if "factorial" in expression:
            n = int(expression.split("factorial(")[1].split(")")[0])
            result = factorial(n)
        else:
            # Thực hiện các phép tính thông thường
            result = eval(expression)
        return result
    except Exception as e:
        return "Error: " + str(e)

def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

def main():
    while True:
        expression = input("Nhập biểu thức (hoặc 'exit' để thoát): ")
        if expression.lower() == 'exit':
            break
        # Thay thế "sqrt" bằng "math.sqrt" trong biểu thức
        expression = expression.replace("sqrt", "math.sqrt")
        result = calculate(expression)
        print("Kết quả:", result)

if __name__ == "__main__":
    main()

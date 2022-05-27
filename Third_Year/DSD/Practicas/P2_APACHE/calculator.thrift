service Calculator {
	void ping()
	double add(1:double num1, 2:double num2)
	double Subtract(1:double num1, 2:double num2)
	double Multiply(1:double num1, 2:double num2)
	double Divide(1:double num1, 2:double num2)
	
	list<i32> listAdd(1:list<i32> v1, 2:list<i32> v2)
	list<i32> listSubtract(1:list<i32> num1, 2:list<i32> num2)
	list<i32> listMultiply(1:list<i32> num1, 2:list<i32> num2)
	list<i32> listDivide(1:list<i32> num1, 2:list<i32> num2)
}

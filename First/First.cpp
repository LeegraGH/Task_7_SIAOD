#include <iostream>

using namespace std;

// Преобразовать из инфиксной записи в префиксную, реализация через однонаправленный список

void turnOver(string& text, int& first, int& last) // переворот строки
{
	if (size(text) == 1 || size(text) == 0) return;
	swap(text[first], text[last]);
	first += 1;
	last -= 1;
	if ((first == last) || (first > last)) return;
	else turnOver(text, first, last);
}

struct Node // узел
{
	char element;
	Node* next;
	Node(char _element) : element(_element), next(nullptr) {};
};

struct StackList // стек на основе однонаправленного списка
{
	Node* first; // указатель на первый узел списка
	Node* last; // указатель на последний узел списка
	StackList() : first(nullptr), last(nullptr) {};

	void addNode(int element) // добавление узла в список
	{
		Node* p = new Node(element);
		if (first == nullptr)
		{
			first = p;
			last = p;
		}
		else
		{
			Node* temp = first;
			first = p;
			first->next = temp;
		}
	}

	void delNode() // удаление узла
	{
		Node* temp = first;
		first = first->next;
		delete temp;
	}

	char outputNode()
	{
		char el = first->element;
		delNode();
		return el;
	}
};

void convert(string& expression)
{
	StackList symbols;
	string temp = "";
	string sign = "(-+*/)";
	for (int i = 0; i < size(expression); i++)
	{
		if (sign.find(expression[i])==string::npos) temp += expression[i];
		else if (expression[i]=='(') symbols.addNode(expression[i]);
		else if (expression[i] == ')')
		{
			char sym = symbols.outputNode();
			while (sym != '(')
			{
				temp += sym;
				sym = symbols.outputNode();
			}
		}
		else if (expression[i] == '-' || expression[i] == '+')
		{
			if (symbols.first == nullptr || symbols.first->element == '(') symbols.addNode(expression[i]);
			else
			{
				while (symbols.first != nullptr && symbols.first->element != '(') temp += symbols.outputNode();
				symbols.addNode(expression[i]);
			}
		}
		else if (expression[i] == '*' || expression[i] == '/')
		{
			if (symbols.first == nullptr || symbols.first->element == '(') symbols.addNode(expression[i]);
			else if (symbols.first->element == '+' || symbols.first->element == '-') symbols.addNode(expression[i]);
			else
			{
				while (symbols.first != nullptr && sign.substr(0, 3).find(expression[i]) == string::npos)
					temp += symbols.outputNode();
				symbols.addNode(expression[i]);
			}
		}
	}
	while (symbols.first != nullptr) temp += symbols.outputNode();
	int first = 0, last = size(temp) - 1;
	turnOver(temp,first,last);
	expression = temp;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	string expression;
	cout << "Инфиксная запись выражения: ";
	cin >> expression;
	if (expression.find('(')!=string::npos)
	{
		for (int i = 0; i < size(expression); i++)
		{
			if (expression[i] == '(') expression[i] = ')';
			else if (expression[i] == ')') expression[i] = '(';
		}
	}
	int first = 0, last = size(expression) - 1;
	turnOver(expression, first, last);
	convert(expression);
	cout << "Префиксная запись выражения: " << expression;
    return 0;
}
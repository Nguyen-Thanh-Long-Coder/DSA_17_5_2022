#include <iostream>
#include <string>
#include <map>
using namespace std;

struct stack
{
	int *e = new int;
	int capacity;
	int story;

	stack()
	{
		capacity = 1;
		story = -1;
	}

	void push(int val)
	{
		if(story + 1 == capacity)
			doubling();
		e[++story] = val;
	}

	bool pop()
	{
		if(story == -1)
			return false;

		if(capacity / (story + 1) == 2)
		{
			int *tmp = e;
			e = new int[capacity >> 1];
			for(int i=0; i<story; i++)
				e[i] = tmp[i];
			delete []tmp;
			capacity /= 2;
		}

		story--;
		return true;
	}

	int size()
	{
		return story + 1;
	}

	bool isEmpty()
	{
		if(story == -1)
			return true;
		return false;
	}

	int top()
	{
		if(story == -1)
			return -1;
		return e[story];
	}

	void doubling()
	{
		int *tmp = e;
		e = new int[capacity << 1];
		for(int i=0; i<=story; i++)
			e[i] = tmp[i];
		delete []tmp;
		capacity *= 2;
	}
};
typedef struct stack stack;

int caculate(int a, int b, char ope)
{
	if(ope == '*')
		return b * a;
	else if(ope == '/')
		return b / a;
	else if(ope == '+')
		return b + a;
	else
		return b - a;
}

int caculateInfix(string s)
{
	map<char, int > mp;
	mp['+'] = mp['-'] = 1;
	mp['*'] = mp['/'] = 2;
	mp['('] = mp[')'] = 0;

	stack st1, st2;
	for(int i=0; i<s.length(); i++)
	{
		if(s[i] >= '0' && s[i] <= '9')
			st1.push(s[i] - '0');
		else if(s[i] == ')')
		{
			int result;
			while(st2.top() != '(')
			{
				int a = st1.top();
				st1.pop();
				int b = st1.top();
				st1.pop();
				result = caculate(a, b, st2.top());
				st2.pop();
				st1.push(result);
			}
			st2.pop();
		}
		else if(mp[st2.top()] < mp[s[i]] || s[i] == '(' || st2.size() == 0)
		{
			st2.push(s[i]);
		}
		else
		{
			int result;
			while(st2.size() != 0 && mp[st2.top()] >= mp[s[i]])
			{
				int a = st1.top();
				st1.pop();
				int b = st1.top();
				st1.pop();
				result = caculate(a, b, st2.top());
				st2.pop();
				st1.push(result);
			}
			st2.push(s[i]);
		}
		// cout << st1.top() << " " << (char)st2.top() << " " << st2.size() << endl;
	}

	while(st2.size() != 0)
	{
		int result;
		int a = st1.top();
		st1.pop();
		int b = st1.top();
		st1.pop();
		result = caculate(a, b, st2.top());
		st2.pop();
		st1.push(result);
	}

	return st1.top();
}

int main()
{
	string a;
	getline(cin, a);
	cout << caculateInfix(a) << endl;

	return 0;
}
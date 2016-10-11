//前序非递归遍历
	void PreorderPrintNorR()
	{
		if (_root == NULL)	//判断是否为空树
		{
			return;
		}
		else
		{
			stack<Node *> s;
			Node *cur = _root;
			while ((cur != NULL)||(!s.empty()))	
			{
				while (cur)
				{
					cout << cur->_value<<" ";
					s.push(cur);
					cur = cur->_left;
				}
		
				Node *top = s.top();
				s.pop();
				cur = top->_right;
			}
		}
		cout << endl;
	}
	//中序非递归遍历
	void InfixPrintNorR()
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			stack<Node *> s;
			Node *cur = _root;
			while ((cur != NULL) || (!s.empty()))
			{
				while(cur)
				{
					s.push(cur);
					cur = cur->_left;
				}		
				Node *top = s.top();
				s.pop();
				cout << top->_value << " ";

			}
		}
		cout << endl;
	}
	//后序非递归遍历
	void PostPrintNorR()
	{
		if (_root==NULL)
		{
			return;
		}
		else
		{
			stack<Node * > s;
			Node *cur = _root;
			Node *prev = NULL;	//记录上一个访问到的节点。
			while (cur||!s.empty())
			{
				while (cur)		//while循环到最左边的节点
				{
					s.push(cur);
					cur = cur->_left;
				}
				Node *top = s.top();	//取得最左边的节点
				if (top->_right == NULL || prev == top->_right)//如果这个top的右边是访问过的或者是NULL，就不进行访问；
				{
					cout << top->_value << " ";
					s.pop();
					prev = top;
				}
				else
				{
					cur = top->_right;	//访问右边
				}
			}
		}
		cout << endl;
	}
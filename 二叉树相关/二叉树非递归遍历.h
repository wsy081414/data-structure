//ǰ��ǵݹ����
	void PreorderPrintNorR()
	{
		if (_root == NULL)	//�ж��Ƿ�Ϊ����
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
	//����ǵݹ����
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
	//����ǵݹ����
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
			Node *prev = NULL;	//��¼��һ�����ʵ��Ľڵ㡣
			while (cur||!s.empty())
			{
				while (cur)		//whileѭ��������ߵĽڵ�
				{
					s.push(cur);
					cur = cur->_left;
				}
				Node *top = s.top();	//ȡ������ߵĽڵ�
				if (top->_right == NULL || prev == top->_right)//������top���ұ��Ƿ��ʹ��Ļ�����NULL���Ͳ����з��ʣ�
				{
					cout << top->_value << " ";
					s.pop();
					prev = top;
				}
				else
				{
					cur = top->_right;	//�����ұ�
				}
			}
		}
		cout << endl;
	}
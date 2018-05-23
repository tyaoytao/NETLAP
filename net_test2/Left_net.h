#pragma once
#include <vector>
#include <string.h>
#define M 1000
using namespace std;
class CLeft_net
{
public:
	CLeft_net(void);
	~CLeft_net(void);
	typedef struct node
	{
		int name;
		int min_leave,max_leave;
		vector <int> parent;
		vector <int> children;
		bool used;
		bool toleave;//µÖ´ïÊ÷Ò¶
	};
	
	typedef struct occurrence
	{
		vector <int > position;
	};
	vector <occurrence> store;
	typedef struct sub_ptn_struct
	{
		char start,end;		//
		int min,max;		//
	};
	sub_ptn_struct sub_ptn[M];  //pattern p[i]
	int ptn_len;
	int maxgap;
	void convert_p_to_ruler(char *p);
	void dealrange(char *p,int len) ;
	void createnettree_length(vector <node> * nettree);
	void updatenettree(vector <node> * nettree);
	void updatenettree_length_pc(vector <node> *nettree,occurrence &occin);
	void nonoverlength(int minlen,int maxlen);
	CString displayocc();
};

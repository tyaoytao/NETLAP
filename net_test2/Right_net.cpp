#include "StdAfx.h"
#include "Right_net.h"
extern CString str;
CRight_net::CRight_net(void)
: ptn_len(0)
, maxgap(-1)
{
}

CRight_net::~CRight_net(void)
{
}
void CRight_net::createnettree_length(vector <node> * nettree)
{
	//CDealPattern dp;
	for (int i=0;i<ptn_len+1;i++)
		nettree[i].resize (0);//�������ʼ��
	int *start;
	start=new int[ptn_len+1];
	for (int i=0;i<ptn_len+1;i++)
		start[i]=0;
	for (int i=0;i<str.GetLength();i++)
	{
		//��ÿ���ַ���һ���
		//�Խ����г�ʼ����
		//if (i==382)
		//	int tmp=5;
		node anode;
		anode.name =i;
		anode.parent.resize (0);
		anode.children .resize (0);
		anode.used =false;//û��ʹ��Ϊ�٣�ʹ��Ϊ��
		if (sub_ptn[0].start ==str[i])
		{
				//��������ֱ�Ӵ洢�ý��
			int len=nettree[0].size ();
			nettree[0].resize (len+1);
			anode.toroot =true;
			anode.min_root =anode.max_root =anode.name ;
			nettree[0][len]=anode;			
		}
		for (int j=0;j<ptn_len;j++)
		{
			if (sub_ptn[j].end==str[i])
			{
				//��һ������˫��
				int prev_len=nettree[j].size ();
				if (prev_len==0)
				{
					//˵�����޽�㣬�����˳�
					break;
				}
				//�������  ������
				for (int k=start[j];k<prev_len;k++)
				{
					int name=nettree[j][k].name;
					if (i-nettree[j][k].name -1>sub_ptn[j].max )
					{
						//��������Ͻ죬�α����
						start[j]++;
					}
				}
				//�жϼ�϶Լ��
				if (i-nettree[j][prev_len-1].name -1>sub_ptn[j].max)
				{
					//����������϶Լ��
					continue;
				}
				if (i-nettree[j][start[j]].name -1<sub_ptn[j].min)
				{
					continue;
				}
	
				int len=nettree[j+1].size ();
				nettree[j+1].resize (len+1);
				anode.min_root =nettree[j][start[j]].min_root ;
				anode.max_root =nettree[j][start[j]].max_root ;
				anode.toroot =true;
				nettree[j+1][len]=anode;
				for (int k=start[j];k<prev_len;k++)
				{
					if (i-nettree[j][k].name -1<sub_ptn[j].min )
					{
						//��������½磬�˳�
						break;
					}
					//�ڼ�϶Լ��֮��
					//�������ӹ�ϵ
					int nc=nettree[j][k].children .size ();
					nettree[j][k].children.resize (nc+1);
					nettree[j][k].children [nc]=len;//�洢λ��
					int np=nettree[j+1][len].parent .size ();
					nettree[j+1][len].parent.resize (np+1);
					nettree[j+1][len].parent [np]=k;
					if (nettree[j+1][len].min_root >nettree[j][k].min_root )//�������϶�������
					{
						nettree[j+1][len].min_root =nettree[j][k].min_root;
					}
					if (nettree[j+1][len].max_root  <nettree[j][k].max_root )//�������϶�������
					{
						nettree[j+1][len].max_root  =nettree[j][k].max_root;
					}
				}

			}
		}
	}
	delete []start;
	
}


void CRight_net::updatenettree(vector <node> * nettree)
{
	for (int i=ptn_len-1;i>=0;i--)
	{
		for(int j=nettree[i].size ()-1;j>=0;j--)
		{
			bool flag=true;
			int size=nettree[i][j].children.size ();
			for (int k=0;k<size;k++)
			{
				int child=nettree[i][j].children[k];
				if (nettree[i+1][child].used ==false)
				{
					flag=false;					
					break;
				}
			}
			//���ڲ��ִܵ�Ҷ�ӽ��Ľ�㣬��ʶΪ���ã�
			nettree[i][j].used =flag;
		}
	}
}
void CRight_net::updatenettree_length_pc(vector <node> *nettree,occurrence &occin)
{
	//���㷨�����ƣ�����ȫ�����������������з�ʽ����Ӱ��Ľڵ��������
	//���и��׺��ӵĶ�����
	for (int level=0;level<ptn_len;level++)
	{
		int kk;
		int position=occin.position [level];		
		for (;position>=0;position--)
		{
			//��ǰ�ҵ�һ��û��ʹ�õĽ�����
			if (nettree[level][position].used ==false)
				break;
			//���Ӹ���
			int len=nettree[level][position].children .size ();
			//��ǰ���
			//int name=nettree[level][position].name ;
			for (int i=len-1;i>=0;i--)
			{
				//ÿ������
				int child=nettree[level][position].children [i];
				int ps=nettree[level+1][child].parent .size ();
				//int cn=nettree[level+1][child].name ;
				//�Ѿ�������߲��ɵִ�Ҷ��
				if (nettree[level+1][child].used ==true)
					continue;
				if (ps==1)//��һ��˫�ף�
				{
					//��һ��˫�׾�Ӧ�����������Ӳ�������
					//if (nettree[level+1][child].used ==false)
					//{
						nettree[level+1][child].used =true;
						nettree[level+1][child].toroot =false;
					//}
				}
				else
				{
					//���˫��
					for (kk=ps-1;kk>=0;kk--)
					{
						int parent=nettree[level+1][child].parent [kk];
						int pn=nettree[level][parent].name ;
						if(nettree[level][parent].used ==false)
							break;
					}
					if (kk==-1)
					{
						nettree[level+1][child].used =true;
						nettree[level+1][child].toroot =false;
					}
				}	
			}
		}
	}	
	
}
void CRight_net::nonoverlength(int minlen,int maxlen)
{
	int t,j,position;
	vector <node> *nettree;
	nettree=new vector <node> [ptn_len+1];
	createnettree_length(nettree);
	//displaynettree(nettree);
	updatenettree(nettree);
	//cout <<"-------------------\n";
	//displaynettree(nettree);
	//displaychild(nettree);

	store.resize (0);
	for (position=nettree[ptn_len].size ()-1;position>=0;position--)
	{
		
		if (nettree[ptn_len][position].toroot ==false)
		{
			//Ϊ�ٱ�ʾ���ִܵ����
			continue;
		}
		int leaf=nettree[ptn_len][position].name;

		int a=leaf -nettree[ptn_len][position].max_root+1;
		int b=leaf -nettree[ptn_len][position].min_root+1;
		if (!( (minlen<=a&&a<=maxlen)||(minlen<=b&&b<=maxlen)))
		{
			nettree[ptn_len][position].used =true;
			nettree[ptn_len][position].toroot =false;
			//�����㳤��Լ��
			continue;
		}
		//��������
		occurrence occ;
		occurrence occin;//�������е�λ�ã�
		occ.position.resize (ptn_len+1);
		occin.position .resize (ptn_len+1);
		occin.position [ptn_len]=position;
		occ.position [ptn_len]=nettree[ptn_len][position].name ;
		nettree[ptn_len][position].used =true;
		nettree[ptn_len][position].toroot =false;
		//������������
		for (j=ptn_len-1;j>=0;j--)
		{
			
			//���ݺ���������˫��
			int child=occin.position [j+1];//�����������е�λ��
			int ps=nettree[j+1][child].parent .size ();//��ǰ����˫����
			//if (ps<1)
			//	cout <<"imposible error\n";
			for (t=ps-1;t>=0;t--)
			{
				int parent=nettree[j+1][child].parent[t];//����˫�׵�λ��
				int a1=leaf -nettree[j][parent].max_root+1;
				int b1=leaf -nettree[j][parent].min_root+1;	
				//int val=nettree[j][parent].name;
				//int st=nettree[j][parent].used;
				if (nettree[j][parent].used ==false&&
					((a1<=maxlen&&a1>=minlen)||(b1>=minlen&&b1<=maxlen)))
				{
					occin.position [j]=parent;			//
					int value=nettree[j][parent].name;
					occ.position [j]=value ;
					nettree[j][parent].used=true;
					nettree[j][parent].toroot =false;
					break;
				}
			}
			if (t==-1)
			{
				//�����г���Լ����Ե�ʲ�������ȫ�������ɲ������ֵ�����
				//�ָ�����
				for (int kk=j;kk<ptn_len;kk++)
				{
					int pos=occin.position [kk];
					nettree[kk][pos].used=false;
					nettree[kk][pos].toroot =true;
				}
				break;
			}
		}
		if (j==-1)
		{
			int len=store.size ();
			store.resize (len+1);
			store[len]=occ;
			//updatenettree_length4(nettree,occin);
			updatenettree_length_pc(nettree,occin);
			//displaynettree(nettree);
		}
	}
	
}
CString CRight_net::displayocc()
{
	CString printOcc,printposition;
	int i,j;
	for (i=store.size ()-1;i>=0;i--)
	{
		printOcc.Append(_T("<"));
		for (j=0;j<ptn_len;j++)
		{
			printposition.Format(_T("%d"),store[i].position [j]);
			printOcc.Append(printposition);
			printOcc.Append(_T(","));
		}
		printposition.Format(_T("%d"),store[i].position [j]);
		printOcc.Append(printposition);
		printOcc.Append(_T(">\r\n"));
	}
	return printOcc;
}
void CRight_net::dealrange(char *p,int len)      
//put sub-pattern "a[1,3]b" into sub_ptn and sub_ptn.start=a��sub_ptn.end=b, sub_ptn.min=1��sub_ptn.max=3
{
	sub_ptn[ptn_len].start =p[0];
	sub_ptn[ptn_len].end =p[len];
	if (len==1)
	{
		sub_ptn[ptn_len].max =sub_ptn[ptn_len].min=0;
	}
	else
	{
		int value=0;
		int i;
		for ( i=2;p[i]!=',';i++)
			value=value*10+p[i]-48;
		sub_ptn[ptn_len].min=value;		
		value=0;
		for (int j=i+1;p[j]!=']';j++)
			value=value*10+p[j]-48;
		sub_ptn[ptn_len].max=value;
	}
	if (sub_ptn[ptn_len].max-sub_ptn[ptn_len].min+1>maxgap)
		maxgap=sub_ptn[ptn_len].max-sub_ptn[ptn_len].min+1;
	ptn_len++;
}

void CRight_net::convert_p_to_ruler(char *p)     //transform p into sub_ptn
{
	char st,en;
	int l,r ;
	int len=strlen(p);
	st=p[0];
	en=p[len-1];
	if (isalpha(st) && isalpha(en))
	{
		l=0;
		for (int i=1;i<len;i++)
		{
			if (isalpha(p[i]))
			{
				r=i;
				dealrange(p+l,r-l);
				l=i;
			}
		}
	}
	else
	{
		MessageBox(NULL,TEXT("ģʽ���ĸ�ʽ����ȷ!"),TEXT("������ʾ"),MB_OK);
		return;
	}
}

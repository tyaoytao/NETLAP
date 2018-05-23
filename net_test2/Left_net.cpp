#include "StdAfx.h"
#include "Left_net.h"
extern CString str;
CLeft_net::CLeft_net(void)
: ptn_len(0)
, maxgap(-1)

{
}

CLeft_net::~CLeft_net(void)
{
}



void CLeft_net::createnettree_length(vector <node> * nettree)
{
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
		anode.toleave =true;
		anode.max_leave = anode.name;
		anode.min_leave = anode.name ;
		if (sub_ptn[0].start ==str[i])
		{
				//��������ֱ�Ӵ洢�ý��
			int len=nettree[0].size ();
			nettree[0].resize (len+1);
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
					if (i-name -1>sub_ptn[j].max )
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
				}

			}
		}
	}
	delete []start;
}


void CLeft_net::updatenettree(vector <node> * nettree)
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
				if(k==0)
				{
					nettree[i][j].min_leave=nettree[i+1][child].min_leave;
				}
				if(k==size-1)
				{
					nettree[i][j].max_leave=nettree[i+1][child].max_leave;
				}
				if (nettree[i+1][child].used ==false)
				{
					flag=false;										
				}
			}
			//���ڲ��ִܵ�Ҷ�ӽ��Ľ�㣬��ʶΪ���ã�
			nettree[i][j].used =flag;
			if(flag==true)
			{
				nettree[i][j].max_leave=nettree[i][j].name;
				nettree[i][j].min_leave=nettree[i][j].name;
				nettree[i][j].toleave = false;
			}
		}
	}
	
}
void CLeft_net::updatenettree_length_pc(vector <node> *nettree,occurrence &occin)
{
	//���㷨�����ƣ�����ȫ�����������������з�ʽ����Ӱ��Ľڵ��������
	int kk;
	for (int level=ptn_len;level>0;level--)
	{
		int position=occin.position [level];
		int num = nettree[level].size();
		for (;position<num;position++)
		{
			//����ҵ�һ��û��ʹ�õĽ�����
			if (nettree[level][position].used ==false)
				break;
			//��ĸ����
			int len=nettree[level][position].parent .size ();
			//��ǰ���
			//int name=nettree[level][position].name ;
			for (int i=0;i<len;i++)
			{
				//ÿ����ĸ
				int parent=nettree[level][position].parent [i];
				int cs=nettree[level-1][parent].children .size ();
				//int cn=nettree[level+1][child].name ;
				//�Ѿ�������߲��ɵִ�Ҷ��
				if (nettree[level-1][parent].used ==true)
					continue;
				if (cs==1)//��һ�����ӣ�
				{
					//��һ��˫�׾�Ӧ�����������Ӳ�������
					//if (nettree[level+1][child].used ==false)
					//{
						nettree[level-1][parent].used =true;
						nettree[level-1][parent].toleave =false;
					//}
				}
				else
				{
					//�������
					for (kk=0;kk<cs;kk++)
					{
						int child=nettree[level-1][parent].children [kk];
						if(nettree[level][child].used ==false)
							break;
					}
					if (kk==cs)
					{
						nettree[level-1][parent].used =true;
						nettree[level-1][parent].toleave =false;
					}
				}	
			}
		}
	}	
}
void CLeft_net::nonoverlength(int minlen,int maxlen)
{
	int t,j,position;
	vector <node> *nettree;
	nettree=new vector <node> [ptn_len+1];
	createnettree_length(nettree);
	updatenettree(nettree);
	store.resize (0);
	for (position=0;position<nettree[0].size();position++)
	{
		
		if (nettree[0][position].toleave ==false)
		{
			//Ϊ�ٱ�ʾ���ִܵ�Ҷ�ӣ�
			continue;
		}
		int root=nettree[0][position].name;

		int a=nettree[0][position].max_leave-root+1;
		int b=nettree[0][position].min_leave- root+1;
		if (!( (minlen<=a&&a<=maxlen)||(minlen<=b&&b<=maxlen)))
		{
			nettree[0][position].used =true;
			nettree[0][position].toleave =false;
			//�����㳤��Լ��
			continue;
		}
		//��������
		occurrence occ;
		occurrence occin;//�������е�λ�ã�
		occ.position .resize (ptn_len+1);
		occin.position .resize (ptn_len+1);
		occin.position [0]=position;
		occ.position [0]=nettree[0][position].name ;
		nettree[0][position].used =true;
		nettree[0][position].toleave =false;
		//����������
		for (j=1;j<ptn_len+1;j++)
		{
			
			int parent=occin.position [j-1];//˫���������е�λ��
			int cs=nettree[j-1][parent].children.size ();//��ǰ���ĺ�����
			for (t=0;t<cs;t++)
			{
			    int child=nettree[j-1][parent].children[t];//�����ӵ�λ��
				int a1=nettree[j][child].max_leave - root+1;
				int b1=nettree[j][child].min_leave - root+1;	
				if (nettree[j][child].used ==false&&
					((a1<=maxlen&&a1>=minlen)||(b1>=minlen&&b1<=maxlen)))
				{
					occin.position [j]=child;			//
					int value=nettree[j][child].name;
					occ.position [j]=value ;
					nettree[j][child].used=true;
					nettree[j][child].toleave =false;
					break;
				}
			}
			if (t==cs)
				{
					//�����г���Լ����Ե�ʲ�������ȫ�������ɲ������ֵ�����
					//�ָ�����
					for (int kk=0;kk<j;kk++)
					{
						int pos=occin.position [kk];
						nettree[kk][pos].used=false;
						nettree[kk][pos].toleave =true;
					}
					break;
				}
		}
		if (j==ptn_len+1)
		{
			int len=store.size ();
			store.resize (len+1);
			store[len]=occ;
			updatenettree_length_pc(nettree,occin);
		}
	}
}
CString CLeft_net::displayocc()
{
	CString printOcc,printposition;
	int i,j;
	for (i=0;i<store.size ();i++)
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
void CLeft_net::dealrange(char *p,int len)      
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

void CLeft_net::convert_p_to_ruler(char *p)     //transform p into sub_ptn
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

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
		nettree[i].resize (0);//网树层初始化
	int *start;
	start=new int[ptn_len+1];
	for (int i=0;i<ptn_len+1;i++)
		start[i]=0;
	for (int i=0;i<str.GetLength();i++)
	{
		//对每个字符逐一检查
		//对结点进行初始化；
		//if (i==382)
		//	int tmp=5;
		node anode;
		anode.name =i;
		anode.parent.resize (0);
		anode.children .resize (0);
		anode.used =false;//没有使用为假，使用为真
		if (sub_ptn[0].start ==str[i])
		{
				//是树根层直接存储该结点
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
				//上一层中找双亲
				int prev_len=nettree[j].size ();
				if (prev_len==0)
				{
					//说明尚无结点，可以退出
					break;
				}
				//更新起点  。。。
				for (int k=start[j];k<prev_len;k++)
				{
					int name=nettree[j][k].name;
					if (i-nettree[j][k].name -1>sub_ptn[j].max )
					{
						//超过最大上届，游标后移
						start[j]++;
					}
				}
				//判断间隙约束
				if (i-nettree[j][prev_len-1].name -1>sub_ptn[j].max)
				{
					//超过了最大间隙约束
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
						//超过最大下界，退出
						break;
					}
					//在间隙约束之间
					//建立父子关系
					int nc=nettree[j][k].children .size ();
					nettree[j][k].children.resize (nc+1);
					nettree[j][k].children [nc]=len;//存储位置
					int np=nettree[j+1][len].parent .size ();
					nettree[j+1][len].parent.resize (np+1);
					nettree[j+1][len].parent [np]=k;
					if (nettree[j+1][len].min_root >nettree[j][k].min_root )//如果副间隙或许可能
					{
						nettree[j+1][len].min_root =nettree[j][k].min_root;
					}
					if (nettree[j+1][len].max_root  <nettree[j][k].max_root )//如果副间隙或许可能
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
			//对于不能抵达叶子结点的结点，标识为已用；
			nettree[i][j].used =flag;
		}
	}
}
void CRight_net::updatenettree_length_pc(vector <node> *nettree,occurrence &occin)
{
	//本算法的优势，不用全部遍历网树，按照行方式对受影响的节点进行设置
	//所有父亲孩子的都不是
	for (int level=0;level<ptn_len;level++)
	{
		int kk;
		int position=occin.position [level];		
		for (;position>=0;position--)
		{
			//向前找到一个没有使用的结点结束
			if (nettree[level][position].used ==false)
				break;
			//孩子个数
			int len=nettree[level][position].children .size ();
			//当前结点
			//int name=nettree[level][position].name ;
			for (int i=len-1;i>=0;i--)
			{
				//每个孩子
				int child=nettree[level][position].children [i];
				int ps=nettree[level+1][child].parent .size ();
				//int cn=nettree[level+1][child].name ;
				//已经处理或者不可抵达叶子
				if (nettree[level+1][child].used ==true)
					continue;
				if (ps==1)//就一个双亲，
				{
					//仅一个双亲就应该无条件孩子不可以用
					//if (nettree[level+1][child].used ==false)
					//{
						nettree[level+1][child].used =true;
						nettree[level+1][child].toroot =false;
					//}
				}
				else
				{
					//多个双亲
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
			//为假表示不能抵达根；
			continue;
		}
		int leaf=nettree[ptn_len][position].name;

		int a=leaf -nettree[ptn_len][position].max_root+1;
		int b=leaf -nettree[ptn_len][position].min_root+1;
		if (!( (minlen<=a&&a<=maxlen)||(minlen<=b&&b<=maxlen)))
		{
			nettree[ptn_len][position].used =true;
			nettree[ptn_len][position].toroot =false;
			//不满足长度约束
			continue;
		}
		//产生出现
		occurrence occ;
		occurrence occin;//在网树中的位置；
		occ.position.resize (ptn_len+1);
		occin.position .resize (ptn_len+1);
		occin.position [ptn_len]=position;
		occ.position [ptn_len]=nettree[ptn_len][position].name ;
		nettree[ptn_len][position].used =true;
		nettree[ptn_len][position].toroot =false;
		//向上最右祖先
		for (j=ptn_len-1;j>=0;j--)
		{
			
			//依据孩子找最右双亲
			int child=occin.position [j+1];//孩子在网树中的位置
			int ps=nettree[j+1][child].parent .size ();//当前结点的双亲数
			//if (ps<1)
			//	cout <<"imposible error\n";
			for (t=ps-1;t>=0;t--)
			{
				int parent=nettree[j+1][child].parent[t];//最右双亲的位置
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
				//由于有长度约束的缘故并不能完全消除不可产生出现的现象。
				//恢复可用
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
//put sub-pattern "a[1,3]b" into sub_ptn and sub_ptn.start=a，sub_ptn.end=b, sub_ptn.min=1，sub_ptn.max=3
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
		MessageBox(NULL,TEXT("模式串的格式不正确!"),TEXT("错误提示"),MB_OK);
		return;
	}
}

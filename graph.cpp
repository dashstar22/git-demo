#include<iostream>
#include<string>
#define MaxVertexNum 10
typedef int EdgeType;
typedef struct mgraph
{
    int VertexType[MaxVertexNum]; //���㼶
    EdgeType edges[MaxVertexNum][MaxVertexNum]; //�߼�
    int n,e; //�������ͱ���
}MGragh;
typedef struct node
{
    int adjvex;
    struct node *next;
}edgeNode;
typedef struct vnode
{
    int vertex;
    edgeNode *firstedge;
}Vnode;
typedef struct
{
    Vnode adjlist[MaxVertexNum];
    int n,e;
    int visit[MaxVertexNum];
}ALGraph;
typedef struct
{
    int rear = 0;
    int front = 0;
    int data[MaxVertexNum];
}point;
void CreatMGragh(MGragh *G)
{
    int i,j,k;
    std::cout << "�����붥�����ͱ���:" << std::endl; 
    std::cin >> G->n >> G->e ;
    std::cout << "�����붥����Ϣ" << std::endl;
    for(i = 0;i < G->n;i++)
    {
        std::cin >> G->VertexType[i]; 
    }
    for(i = 0;i < G->n;i++)
    {
        for(j=0;j<G->n;j++)
        {
            G->edges[i][j] = 0;
        }
    }
    std::cout << "��������ߵ���Ϣ" << std::endl;
    for(k = 0;k < G->e;k++)
    {
        std::cin >> i >> j;
        G->edges[i][j] = 1;            
    }
}
void CreatALGraph(ALGraph *G)
{
    int i,j,k;
    std::cout << "�����붥�����ͱ���:" << std::endl; 
    std::cin >> G->n >> G->e ;
    std::cout << "�����붥����Ϣ" << std::endl;
    for(i = 0;i < G->n;i++)
    {
        std::cin >> G->adjlist[i].vertex; 
        G->adjlist[i].firstedge = nullptr;
    }
    std::cout << "��������ߵ���Ϣ" << std::endl;
    for(k = 0;k < G->e;k++)
    {
        std::cin >> i >> j;
        edgeNode *m = new edgeNode;
        m->adjvex = j;
        m->next = G->adjlist[i].firstedge;
        G->adjlist[i].firstedge = m;
    }
}
void DFSAL(ALGraph *G,int i)
{
    edgeNode *p;
    std::cout << G->adjlist[i].vertex << " ";
    G->visit[i] = true;
    p = G->adjlist[i].firstedge;
    while(p)
    {
        if(!G->visit[p->adjvex])
        {
            DFSAL(G,p->adjvex);
            p = p->next;
        }
        else
            p = p->next;
    }
}
void ruline(point *L,int k)
{
    L->data[L->rear] = k;
    L->rear = (L->rear++)%MaxVertexNum;
}
int outline(point *L)
{
    int i;
    i = L->data[L->front];
    L->front = (L->front++)%MaxVertexNum;
    return i;
}
int firstnode(ALGraph *G,int i)
{
    edgeNode *p;
    if(G->adjlist[i].firstedge != NULL)
    {
        p = G->adjlist[i].firstedge;
        return p->adjvex;
    }
    else
        return -1;
}
int Nextnode(ALGraph *G,int i,int j)
{
    edgeNode *p;
    p = G->adjlist[i].firstedge;
    while(p->adjvex != j)
    {
        p=p->next;
    }
    p=p->next;
    if(p != NULL)
    {
        return -1;
    }
    else
    {
        return p->adjvex;
    }
}
void BFSM(ALGraph *G,int i)
{
    point L;
    int j,k;
    std::cout << G->adjlist[i].vertex << " ";
    G->visit[i] = true;
    ruline(&L,i);
    while(L.rear != L.front)
    {
        i =outline(&L);
        for(j = firstnode(G,i);j>=0;j = Nextnode(G,i,j))
        {
            if(!G->visit[j])
            {
                std::cout << G->adjlist[j].vertex << " ";
                G->visit[j] = true;
                ruline(&L,j);
            }
        }
    }

}
void DFSTraverseAL(ALGraph *G)
{
    int i;
    for(i = 0;i < G->n;i++)
    {
        G->visit[i] = false;
    }
    for(i = 0;i < G->n;i++)
    {
        if(G->visit[i] == false)
        {
            DFSAL(G,i);
        }
    }
}
void BFSTraverseAL(ALGraph *G)
{
    int i;
    for(i = 0;i < G->n;i++)
    {
        G->visit[i] = false;
    }
    for(i = 0;i < G->n;i++)
    {
        if(G->visit[i] == false)
        {
            BFSM(G,i);
        }
    }
}
int Menu() {
	int n;
	char c;
	printf("\n\n==ͼ��������ʵ��=======\n");
	printf("----------------------------------");
	printf("\n1.�����ڽӾ������");
	printf("\n2.�����ڽӱ�");
	printf("\n3.���ڽӱ�������ȱ��������");
	printf("\n4.���ڽӱ������ȱ��������");
	printf("\n0.�˳�");
	do {
		fflush(stdin);
		printf("\n\n����������0-4ѡ����:");
		c = getchar();
		n = c - 48;
		if (n < 0 || n > 4) {
			printf("\t\t\t����ѡ�����!����������ѡ��");
		}
	} while (n < 0 || n > 4);

	return n;
}

int main()
{
    int select, return_value,lab = 0;
	do {
		system("cls");
		select = Menu();
		switch (select) {
			case 1:
				MGragh G1;
                int i,j;
                CreatMGragh(&G1);
				printf("\n�ڽӾ��󴴽��ɹ�!\n\n");
                for(i = 0;i < G1.n;i++)
                {
                    for(j = 0;j <G1.n;j++)
                    {
                        printf("%d ",G1.edges[i][j]);
                    }
                    printf("\n");
                }
				break;
			case 2:
				ALGraph G;
                CreatALGraph(&G);
                printf("\n�ڽӱ����ɹ�!\n\n");
                lab = 1;
                break;
			case 3:
				if(lab == 0)
                {
                    printf("�ڽӱ�δ����");
                }
                else
                {
                    DFSTraverseAL(&G);
                    printf("\n���ڽӱ�������ȱ����ɹ�");
                }
                break;
			case 4:
				if(lab == 0)
                {
                    printf("�ڽӱ�δ����");
                }
                else
                {
                    BFSTraverseAL(&G);
                    printf("\n���ڽӱ������ȱ����ɹ�");
                }
                break;
			case 0:
				printf("\nллʹ��,�ټ�!");
		}
		printf("\n\n");
		system("pause");
	} while (select != 0);
}
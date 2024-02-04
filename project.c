#include <stdio.h>

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
    int visas; // Number of visas required to enter this node
};

int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        p[i].visas = 0; // Initialize visas to 0 for now
        ncount++;
    }
    return ncount;
}

void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int visas, int count)
{
    int i = 0, index;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].visas = visas; // Set the number of visas required for this node
            p[i].adjcount = c + 1;

            break;
        }
    }
}

int added(int *list, int lcount, int nid)
{
    int i = 0;
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}

void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int visas)
{
    int index = 0, i = 0;

    // Check if list contains the end node and if you have enough visas
    if (list[lcount - 1] == end && visas >= 0)
    {
        int tcost = 0;
        printf("\n");
        for (i = 0; i < lcount; i++)
        {
            printf(" %d ", list[i]);
            tcost += clist[i];
        }
        printf(" cost = %d", tcost);
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    for (i = 0; i < p[index].adjcount; i++)
    {
        int a = added(list, lcount, p[index].adjs[i]);
        int new_visas = visas - p[index].visas; // Deduct the visas required for this node
        if (a == 0 && new_visas >= 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, new_visas);
            lcount--;
        }
    }
}

int main()
{
    // Write C code here
    // printf("Hello world");

    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0, visas = 0;

    while (1)
    {
        printf("n1, n2, cost, visas? ");
        scanf("%d %d %d %d", &n1, &n2, &c, &visas);
        if (n1 == -9 || n2 == -9 || c == -9 || visas == -9)
        {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, visas, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, visas, nodecount);
    }

    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    findpath(nodes, nodecount, start, end, list, clist, lcount, 0); // Start with 0 visas

    return 0;
}

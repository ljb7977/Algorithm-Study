#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

char tree[100000];

void postorder(int i)
{
    if(tree[i]=='.')
        return;
    postorder(i*2);
    postorder(i*2+1);
    printf("%c", tree[i]);
}

void preorder(int i)
{
    if(tree[i]=='.')
        return;
    printf("%c", tree[i]);
    preorder(i*2);
    preorder(i*2+1);
}

void inorder(int i)
{
    if(tree[i]=='.')
        return;
    inorder(i*2);
    printf("%c", tree[i]);
    inorder(i*2+1);
}

int main()
{
    int n, i, index=1;
    scanf("%d\n", &n);
    char parent, left, right;
    //input tree
    for(i=0; i<n; i++){
        scanf("%c %c %c\n", &parent, &left, &right);
        if(i==0)
            index=1;
        else{
            for(int j=0; j<(int)pow(2.0,(double)(i+1)); j++){
                if (tree[j]==parent){
                    index = j;
                    break;
                }
            }
        }
        tree[index]=parent;
        tree[index*2]=left;
        tree[index*2+1]=right;
    }

    preorder(1);
    printf("\n");
    inorder(1);
    printf("\n");
    postorder(1);

    return 0;
}

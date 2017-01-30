#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <climits>
using namespace std;

int current, previous;
int counter;
int n, q;
int values[100002];
vector<int> segment_tree;
int l, r;

void init_tree(int N){
	//Formulazo del tam maximo del segment_tree
	int length = (int)(2 * pow(2.0, floor((log((double)N) / log(2.0)) + 1)));
	segment_tree.resize(length, 0);
}

int adjust(int index, int pos){
	return min(index - pos + 1, values[pos]);
}

bool compare(int idxA, int idxB, int pos){
	return adjust(idxA, pos) >= adjust(idxB, pos);
}

void build_tree(int node, int a, int b){
	if(a == b){
		segment_tree[node] = a;
	} else {
		int leftIndex = 2*node;
		int rightIndex = leftIndex + 1;

		build_tree(leftIndex, a, (a+b)/2);
		build_tree(rightIndex,(a+b)/2 + 1, b);

		int lContent = segment_tree[leftIndex];
		int rContent = segment_tree[rightIndex];

		segment_tree[node] = compare(rContent, lContent, 0);
	}
}

bool is_valid(int index, int i){
	return values[index] <= index - i + 1;
}

int query_tree(int node, int a, int b, int i, int j){
	if(i > b || j < a) return -1;
	if(a == b) return segment_tree[node];
	if(a >= i && b <= j && is_valid(segment_tree[node], i)) return segment_tree[node];

	int p1 = query_tree(2* node, a, (a+b)/2, i, j);
	int p2 = query_tree(2 * node + 1, 1 + (a+b)/2, b, i, j);

	if(p1 == -1) return p2;
	if(p2 == -1) return p1;

	return compare(p1, p2, i) ? p1 : p2;
}

int main(){
	scanf("%d", &n);
	while(n){
		init_tree(n);
		previous = INT_MIN;
		counter = 1;
		scanf("%d", &q);
		for(int i = 1; i <=n; i++){
			scanf("%d", &current);
			if(current != previous){
				counter = 1;
			}
			previous = current;
			values[i] = counter++;
			
		}

		build_tree(1, 1, n);
		//cout << "Arbol Terminado" << endl;
		while(q--){
			scanf("%d %d", &l, &r);
			int val = query_tree(1, 1, n, l, r);
			int adj = adjust(val, l);
			printf("%d\n", adj);
		}
		scanf("%d", &n);
	}
	return 0;
}
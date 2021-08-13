#include<iostream>
#include<queue>
using namespace std;

class Segment_tree{
    public:
        int helper(const int * arr , int * seg_tree , int st , int ed , int i , int x){

            if(st == ed){
                seg_tree[i] = arr[st];
                return seg_tree[i];
            }

            int md = (st + ed)>>1;

            seg_tree[i] =   helper(arr , seg_tree , st , md , 2*i + 1 , x) + 
                            helper(arr , seg_tree , md + 1, ed , 2*i + 2 , x);

            return seg_tree[i];

        }

        pair<int * , int> build_tree(const int * arr , int n){
            int x = 1;

            // find x such that pow(2,x) >= n;
            while(x < n){
                x = x<<1;
            }

            x = 2*x - 1;
            int * seg_tree = new int [x];

            for(int i = 0 ; i < x ; ++i){
                seg_tree[i] = 0;
            }

            helper(arr , seg_tree , 0 , n - 1 , 0 , x);

            return {seg_tree,x};
        }

        void show(int * seg_tree  ,  int sz){
            queue<int> q;
        
            q.push(0);

            while(!q.empty()){

                int size = q.size();

                for(int i = 0 ; i < size ; ++i){
                    int temp = q.front();
                    q.pop();
                    cout<<seg_tree[temp]<<" ";

                    if(2*temp + 1 < sz){
                        q.push(2*temp + 1);
                    }

                    if(2*temp + 2 < sz){
                        q.push(2*temp + 2);
                    }

                }
                cout<<endl;

            }
            return ;
        }

        // quering a segement tree
        int query(int * seg_tree , int l , int r , int st , int ed  , int i ){
                
                if(l > ed || r < st){
                    return 0;
                }

                if(st >= l && ed <= r){
                    return seg_tree[i];
                }

                int md = (st + ed)>>1;

                return query(seg_tree , l , r , st , md , 2*i + 1) + query(seg_tree , l , r , md + 1 , ed , 2*i + 2);

        }

};

int main(){

    int n;
    cin>>n;
    int * arr = new int [n];

    for(int i = 0 ; i < n ; ++i){
        cin>>arr[i];
    }
    Segment_tree stree;
    pair<int * ,int> r = stree.build_tree(arr , n);

    int * seg_tree = r.first;
    int sz = r.second;

    stree.show(seg_tree , sz);

    int k;
    cin>>k;

    for(int i = 0 ; i < k ; ++i){
        int l,r;
        cin>>l>>r;
        cout<<stree.query(seg_tree , l , r , 0 , n - 1 , 0)<<endl;
    }

    delete []seg_tree;
    delete []arr;
    return 0;

}
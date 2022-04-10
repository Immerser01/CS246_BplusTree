#include<bits/stdc++.h>
using namespace std;
int d,t;
int leaf_count=0,index_count=0;
struct block{
    bool leaf;
    block *parent;
    vector<int> data;
    vector<block*> children;
    explicit block(bool if_leaf){
        parent= nullptr;
        if(!if_leaf){
            leaf= false;
        }else{
            leaf= true;
        }
    }
};
int main() {
    cin>>d>>t;
    block * root= nullptr;
    while (true){
        int op;cin>>op;
        if(op==1){
            if(root== nullptr){
                root=new block (true);
                leaf_count++;
            }
            int val;cin>>val;
            block* now=root;
            while (now->leaf==0){
                if(now->data[0]>val){
                    now=now->children[0];
                }else if(val>=now->data.back()){
                    now=now->children.back();
                }else{
                    for(int i=0;i<now->data.size()-1;i++){
                        if(now->data[i]<=val && now->data[i+1]>val){
                            now=now->children[i+1];
                            break;
                        }
                    }
                }
            }
            deque<int> buff;
            while (!now->data.empty() && now->data.back()>val){
                buff.push_back(now->data.back());
                now->data.pop_back();
            }
            now->data.push_back(val);
            while (buff.size()>0){
                now->data.push_back(buff.back());
                buff.pop_back();
            }
            if(now->data.size()<=2*d){
                continue;
            }else{
                block * sibling =new block(1);//
                leaf_count++;
                while (now->data.size()>d){
                    sibling->data.push_back(now->data.back());
                    now->data.pop_back();
                }
                reverse(sibling->data.begin(),sibling->data.end());
                sibling->parent=now->parent;
                int transfer=sibling->data[0];
                bool flg= false;
                while (now->parent != nullptr){
                    deque<block*> buff;
                    deque<int> buff2;
                    block * curr=now->parent;
                    while (curr->children.back()!=now){
                        buff.push_back(curr->children.back());
                        buff2.push_back(curr->data.back());
                        curr->children.pop_back();
                        curr->data.pop_back();
                    }
                    curr->children.push_back(sibling);
                    curr->data.push_back(transfer);
                    while (buff.size()>0){
                        curr->children.push_back(buff.back());
                        curr->data.push_back(buff2.back());
                        buff.pop_back();
                        buff2.pop_back();
                    }
                    if(curr->children.size()>2*t+2){
                        index_count++;
                        sibling = new block(0);
                        sibling->parent=curr->parent;
                        
                        for(int i=0;i<t+1;i++){
                            sibling->data.push_back(curr->data.back());
                            curr->data.pop_back();
                        }
                        transfer=curr->data.back();
                        curr->data.pop_back();
                        for(int i=0;i<t+2;i++){
                            sibling->children.push_back(curr->children.back());
                            curr->children.back()->parent=sibling;
                            curr->children.pop_back();
                        }
                        reverse(sibling->children.begin(),sibling->children.end());
                        reverse(sibling->data.begin(),sibling->data.end());
                        now=curr;
                    }else{
                        flg= true;
                        break;
                    }
                }
                if(!flg){
                    block * newrt =new block(0);
                    index_count++;
                    newrt->children.push_back(now);
                    newrt->children.push_back(sibling);
                    newrt->data.push_back(transfer);
                    now->parent=newrt;
                    sibling->parent=newrt;
                    root=newrt;
                }
            }
        }else if(op==2){
            cout<<index_count<<" "<<leaf_count<<endl;
            for(int i=0;i<root->data.size();i++){
                cout<<root->data[i]<<" ";
            }
            cout<<endl;
        }else{
            break;
        }
    }
    return 0;
}

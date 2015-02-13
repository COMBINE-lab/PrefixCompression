#include "linearmatching.h"
namespace prefixMatching{
linearMatching::linearMatching(suffixTrie* t,vector<int>& m):_trie(t),_match(m),_totalMatched(0)
{
    this->init();
}
/*
void linearMatching::buildPriority(Node* root){
    // if the trie is not empty
    if(root){
        for(size_t i = 0; i <= 3; i++){
            if(root->child(i) && root->child(i)->isBranch()){
                Node* tmp = this->_priority[root->child(i)->depth()];
                this->_priority[root->child(i)->depth()] = root->child(i);
                root->child(i)->setNext(tmp);
            }
            this->buildPriority(root->child(i));
        }
    }

}*/
void linearMatching::init(){
    //int tstring = this->_trie->size();
    this->_match = this->_trie->initMatching();
    //check if there is any duplicate matching in the initial match
   /*
   size_t total = 0; 
    size_t i = 0;
   while(i < this->_match.size()-1){
	if(this->_match[i] != i && this->_match[i+1] != i+1){
		std::cout<<i<<std::endl;
		total++;
	}
	i += 2;
	
    }
	std::cout<<total<<std::endl;
   */
}
/**
  * main procedure for the prefix matching
*/
void  linearMatching::constructSolution(){
    const vector<Node*>& a = this->_trie->priority();
    // start from the deepest node, traverse the priority queue
    if(a.empty())
        return ;
    Node* head = NULL;
    int depth = a.size()-1;
    // traverse the priority queue from the bottom
    while(depth >= 0){
        head = a[depth];
        while(head){
             this->match(head);
             head = head->next();
        }
        depth--;
    }

}


void linearMatching::match(Node* head){
    // find the first pair of string
    vector<int> unmatched;
    int indx(0);
    for(; indx < 4; indx++){
        if(head->child(indx) && !this->isMatched(head->child(indx)->id())){
            unmatched.push_back(indx);
        }
    }
    // there is only one valid pair
    if(unmatched.empty()){
        head->setID(-2);
    }
    else if(unmatched.size() == 2){
	    Node* res =  this->matchPair(head->child(unmatched[0]),head->child(unmatched[1]));
            if(res)
	    	this->collapse_node(head,res->id());
	    else
		this->collapse_node(head,-2);

    }else if(unmatched.size() == 1){ // need to progogate the
        this->collapse_node(head,head->child(unmatched[0])->id());

    }else if(unmatched.size() == 3){ // need to propagate
	Node* unode = this->matchPair(head->child(unmatched[0]),head->child(unmatched[1]));	
        if(!unode){
	    int id = -2;
            if(!this->isReverseComplement(head->child(unmatched[0])->id(),head->child(unmatched[2])->id())
                && !this->isReverseComplement(head->child(unmatched[1])->id(),head->child(unmatched[2])->id()))
                id = head->child(unmatched[2])->id();
            this->collapse_node(head,id);
        }else{
            // 0,1 are reverse complement
	    unode = this->matchPair(unode,head->child(unmatched[2]));
            assert(unode==NULL);
            this->collapse_node(head,-2);
            //head->setID(-2);
        }
    }else{
        // two complete pair
	Node* unode = this->matchPair(head->child(unmatched[0]),head->child(unmatched[1]));
        // 0,1 are not reverse complement
        if(!unode){
		 // if node 2 is reverse complement of node 0 or 1
		 if(this->isReverseComplement(head->child(unmatched[0])->id(),head->child(unmatched[2])->id())
                    || this->isReverseComplement(head->child(unmatched[1])->id(),head->child(unmatched[2])->id())){
			// node 3 is also the reverse complement of node 0 or 1
			if(this->isReverseComplement(head->child(unmatched[0])->id(),head->child(unmatched[3])->id())
                    || this->isReverseComplement(head->child(unmatched[1])->id(),head->child(unmatched[3])->id())){
				this->collapse_node(head,-2);
			}
			else
				this->collapse_node(head,head->child(unmatched[3])->id());
		}
	        else{//node 2 is not reverse complement of node 0 or 1
			// if node 3 is reverse complement of node 0 or 1
			if(this->isReverseComplement(head->child(unmatched[0])->id(),head->child(unmatched[3])->id())
                    || this->isReverseComplement(head->child(unmatched[1])->id(),head->child(unmatched[3])->id())){
				this->collapse_node(head,unmatched[2]);
			}
			else{
				unode = this->matchPair(head->child(unmatched[2]),head->child(unmatched[3]));
				if(unode)
					this->collapse_node(head,unode->id());
				else
					this->collapse_node(head,-2);
			}

		}
		
	}
	else{
	    // unmatched node must be matched with node 2 
            assert(NULL == this->matchPair(unode,head->child(unmatched[2])));
	    if(this->isReverseComplement(head->child(unmatched[2])->id(),head->child(unmatched[3])->id()))
		this->collapse_node(head,-2);
	    else
		this->collapse_node(head,head->child(unmatched[3])->id());
		
        }
      }
}
}

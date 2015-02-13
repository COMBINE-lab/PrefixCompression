#ifndef REORDERDRIVE_H
#define REORDERDRIVE_H
#include <memory>
#include <fstream>
//#include "kmers_initparam.h"
#include "filesplittor.h"
#include "kmers_reads.h"
#include "linearmatching.h"
using std::fstream;
using std::shared_ptr;
using std::unique_ptr;
namespace prefixMatching{
class reorderDrive
{
public:
    reorderDrive(std::shared_ptr<kmers_InitParam>& params);
    void drive(){
        while(!this->_readsLoader->isDone()){
            this->_readsLoader->load(5000,this->_pool);
        }


        this->_trie.reset(new suffixTrie());
        for(const shared_ptr<Read>& r : this->_pool){
            this->_trie->insert(r->patFw);
            this->_trie->insert(r->patRc);
        }
        //std::cout<<this->_pool.size()<<trie->initMatching().size()<<endl;

        std::unique_ptr<linearMatching> alg(new linearMatching(this->_trie.get(),this->_match));

        alg->solution();

        output();

    }
    ~reorderDrive(){
        std::cout<<"There are totally "<< _unmatched <<" unmatched reads"<<endl;
    }
private:
    void init(){
        kmers_Reads* tmp = new kmers_Reads(this->_params->_readsFiles,this->_params->readFormat());
        this->_readsLoader.reset(tmp);
    }
    size_t output(){

        string outprefix(this->_params->outputPrefix());

        string original_prefix = outprefix + "_original";
        std::unique_ptr<fileSplittor> original(new fileSplittor(this->_params->_format,original_prefix));
        original->split(this->_pool);

        string processed_prefix = outprefix + "_ordered";
        std::unique_ptr<fileSplittor> processed(new fileSplittor(this->_params->_format,processed_prefix));
        processed->orderSplit(this->_pool,this->_match);


    }
private:
    std::shared_ptr<kmers_InitParam>            _params;
    std::unique_ptr<kmers_Reads>                _readsLoader;
    vector<std::shared_ptr<Read>>               _pool;
    vector<int>                                 _match;
    std::shared_ptr<suffixTrie>                 _trie;
    int                                         _unmatched;

};
}

#endif // REORDERDRIVE_H

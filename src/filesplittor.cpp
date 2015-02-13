#include "filesplittor.h"


namespace prefixMatching{
fileSplittor::fileSplittor(file_format s,string& outprefix):_format(s),_outprefix(outprefix)
{
    this->init();
}
void fileSplittor::init(){
    this->_bufseq.reset(new OutFileBuf(this->_outprefix + "_seq"));
    this->_bufid.reset(new OutFileBuf(this->_outprefix + "_id"));
    if(this->_format == FASTQ)
        this->_bufqual.reset(new OutFileBuf(this->_outprefix + "_qual"));

}
/**
  * split the reads into several parts and output them
*/
void fileSplittor::split(vector<std::shared_ptr<Read> >& reads) {

    for(const std::shared_ptr<Read>& r: reads){
        this->writeRead(r);
    }
}

/**
  * given a list of array and a match list
  * output the reads into splited files according to the match list
*/
size_t fileSplittor::orderSplit(vector<std::shared_ptr<Read> >& reads,vector<int>& match){

    size_t unmatched = 0;
    size_t i = 0;
    while(i < match.size()-1){
        int revCom = i+1;
        int target = i;
        if(match[i] != i && match[revCom] == revCom){
            target = i;
        }else if(match[i] == i && match[revCom] != revCom){
            target = revCom;
        }else if(match[i] != i && match[revCom] != revCom){
            std::cerr<<" duplicate mathcing for "<<i<<'\t'<<match[i] <<endl;
	     std::cerr<<reads[i/2]->patFw<<'\t'<<reads[match[i]/2]->patFw<<endl;
            std::cerr<<" duplicate mathcing for "<<revCom<<'\t'<<match[revCom]<<endl;
	
        }else{
            // not matched
            unmatched++;
            target = -1;
         }
        // matched
        if(target >= 0){
            if( target < match[target]){

                size_t idx = target/2;
                bool rev = target%2;
                this->writeRead(reads[idx],rev);
                // output
                idx = match[target]/2;
                rev = match[target] %2;
                this->writeRead(reads[idx],rev);
            }
        }else{
            size_t idx = i/2;
            bool rev = i%2;
            this->writeRead(reads[idx],rev);
        }
        i += 2;
    }
    return unmatched;
  }
}

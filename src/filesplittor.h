#ifndef FILESPLITTOR_H
#define FILESPLITTOR_H

#include <string>
#include <vector>
#include <memory>
#include "formats.h"
#include "read.h"
using std::string;
using std::vector;
using std::shared_ptr;


namespace prefixMatching{

/**
  * Given a outprefix and outfile format
  * this class could write given reads into corresponding outfiles
  * in specified order or default order
  *
  * Currently, it supports two different file format
  * One is fasta, which only contains read id and sequence
  * The other is fastq, which contains read id, sequence and quality
*/
class fileSplittor
{
public:
    explicit fileSplittor(file_format s,string& outprefix);
    void split(vector<std::shared_ptr<Read> >&) ;
    size_t orderSplit(vector<std::shared_ptr<Read> >& ,vector<int>&);
    ~fileSplittor(){

    }
private:

    void init();

    template<typename T>
    void write(std::shared_ptr<OutFileBuf>& handler, T& t){
        if(handler.get()){
            handler->writeString(t);
            handler->write('\n');
        }
    }
    void writeRead(const std::shared_ptr<Read>& r,bool rc=false){
        this->_bufid->write('@');
        this->write(this->_bufid,r->name);
        // reverse complement
        if(rc){
            this->write(this->_bufseq,r->patRc);
            r->qual.reverse();
            this->write(this->_bufqual,r->qual);
        }
        else{ // original read
            this->write(this->_bufseq,r->patFw);
            this->write(this->_bufqual,r->qual);
        }
    }
private:

    file_format                                 _format;
    string                                      _outprefix;
    std::shared_ptr<OutFileBuf>                 _bufid;
    std::shared_ptr<OutFileBuf>                 _bufseq;
    std::shared_ptr<OutFileBuf>                 _bufqual;
};
}
#endif // FILESPLITTOR_H

#ifndef ALM_READS_H
#define ALM_READS_H

#include <memory>
#include "suffix_commons.h"
#include "pat.h"
#include "formats.h"
#include "kmers_initparam.h"
#include "read.h"
using std::shared_ptr;
namespace prefixMatching{

/**
   * alm_Reads is a basic class that deal with reads
   * it is the parent of kmers_ReadsPack and kmers_ReadsScan
*/
class kmers_Reads
{
    public:
        kmers_Reads(){}
        /**
            *constructor called by the task manager
            *given a list of readsfile and the pattern parameter

        */
        kmers_Reads(const vector< vector<string> >& readFiles,int format);

        virtual ~kmers_Reads(){
            this->clear();
            cerr<<"This reads processor totally processed :: " << this->_totalReads - 1 <<" reads"<<endl;
            if(!_isDone)
                cerr<<"have not finished the given reads files!"<<endl;
            cerr.flush();
        }
        bool isReady(){
            return !(this->_pPatt == NULL);
        }

        void reset(){
            if(this->_pPatt)
                this->_pPatt->reset();
        }
        bool isDone() {return this->_isDone;}
        virtual string classname(){return std::string("kmers_Reads");}
        /**
            load a given number of reads from file
          */
        void load( size_t num,vector<std::shared_ptr<Read> >& reads){
            this->loadBlock(num,reads);
        }
private:

        /**
            check if the input format is valid
          */
        bool InputFileCheck(const vector< vector<string> >& readFiles,int format);

        /**
            once this batch of reads is done and the next batch is comming
            need to delete the pattensource and create a new one
        */
        void clear(){
            if(this->_pPatt != NULL)
                delete this->_pPatt;
            this->_pPatt = NULL;
            if(this->_pPatParams != NULL)
                delete this->_pPatParams;
            this->_pPatParams = NULL;
            this->_qualities.clear();
            this->_queries.clear();
        }


         void loadBlock(size_t& count,vector<std::shared_ptr<Read> >& reads){


            this->_isDone = _pPatt->loadReads(reads,count);
            _totalReads += count;

        }
protected:

        //engine that read  reads from the file one by one
        PairedPatternSource      *_pPatt;
        //the options of loading reads
        PatternParams            *_pPatParams;

        //total reads loaded
        UINT64                   _totalReads;
        bool                     _isDone;

        //reads sequence and quality files
        EList<string>            _queries;
        EList<string>            _qualities;
};


}//namespace
#endif // ALM_READS_H

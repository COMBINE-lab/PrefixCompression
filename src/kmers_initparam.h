#ifndef KMERS_INITPARAM_H
#define KMERS_INITPARAM_H
#include "suffix_commons.h"
#include "kmers_delimitor.h"
#include "formats.h"
namespace prefixMatching{

/**
  * this class holds all initial options for this program
  * @param[in]:_kmerslen => the number of bp to be set as kmer
  * @param[in]:_nThreads => # of threads enabled
  * @param[in]:_coded    => whether take coded bitwise format
*/

class kmers_InitParam
{
public:

    public:
        kmers_InitParam();
        kmers_InitParam(const char* coded){
            _pDeli = kmers_Delimitor::getInstance();
            this->decode(coded);
        }
        kmers_InitParam(size_t kmerslen, //the length of kmers
                        size_t nThreads, //number of threads enabled
                        bool coded);     //if code the bp into bitwise format,
                                         //true=>coded
        kmers_InitParam(const kmers_InitParam& p);

        virtual string classname();
        virtual char* encode();
        virtual void decode(const char*);
        void reset(){
            _kmersLen               = 23;
            _isCodedBit             = true;
            _nThreads               = 1;
            _format                 = FASTQ;
            _strategyToNs           = NTOA;
            _maxNumOfN              = 3;
            _outPutPrefix           = "";
            _inPutPrefix            = "";
            _tmpFileDir             = "";
            _noHeader               = false;
            _minOccurence           = 1;
            _maxOccurence           = 255;
            _sampleWidth            = 1;    //default, we support two samples comparison
            _posWidth               = 5;    //default, we support reads length less than 128
            _maxNumOfReads          = 1000;   //default, each thread only hold kmers from 1000 reads
            _subjectWidth           = 10;
            _maxNumOfBatch          = 200; //default, the number of records extract from the generated kmers shared queue
            _bufferSz               = 15;    //default, the buffer size for each thread
            _maxSzOfSharedQue       = 500000000;  //default, the size of the generated kmers shared  queue;
            _readsBlockSz           = 500;      //default, the size of reads in each block which processed by sigle thread each batch
            _maxNumOfReadsQue       = 10;         //default, the size of input reads shared queue
            _NumOfTMgrThreads       = 1;     //default, the number of threads at TMgr end
            _approximateNumOfReads  = 0;
            _NumOfDMgrThreads       = 1;    //default, the number of threads that write kmer into files
            _NumOfkmerBytes         = 8;    //default, the number of kmer bytes in file is 8
            _memThreashold          = 500000000;
            _numOfFiles             = 1;    //not coded yet. default, the number of files for each sub range of kmer
            _checkingcycle          = 5000; //default, checking cycle
            _t                      = count; //default, traditional counting
        }
        /**
          * given the read length, calculate the maximum
          * number of Ns allowed in the
        */
        inline void calMaxOfNs(size_t& readLen){

            _maxNumOfN = readLen / _kmersLen;
        }
        /**
         * given a coded string, extract the first params start at the postion (pos)
         * the character start with a delimitor(in or out)
         */
       inline void getCodedParam(const char*p,size_t &pos,string& tmp){
           if(NULL == p){
               cerr<<"invalid coded format of pattern source parameter!"<<endl;
               cerr.flush();
               throw 1;
           }
           size_t len = strlen(p);
           assert( (p[pos]==_pDeli->insideDeli()) || (p[pos]==_pDeli->outsideDeli()) );
           pos++;
           tmp.clear();
           while(p[pos] != _pDeli->insideDeli() && p[pos] != _pDeli->outsideDeli() && pos < len ){
               tmp += p[pos];
               pos++;
           }
           assert(  (p[pos]==_pDeli->insideDeli()) | (p[pos]==_pDeli->outsideDeli()) | (pos == len) );
       }
       inline void getParams(const char *p,size_t& param){

           if(NULL == p){
               cerr<<"invalid coded format of pattern source parameter!"<<endl;
               cerr.flush();
               throw 1;
           }

           param = atoi(p);
       }
       void setInputPrefix(string& str){
           this->_inPutPrefix.assign(str.c_str());
       }
       void setOutputPrefix(string& str){
           this->_outPutPrefix.assign(str.c_str());
       }
       void setKmersLen(size_t len){
           if(len*2u > 64u-this->PositionWidth()){
               cerr<<"can not process such long kmers!"<< len<<endl;
               cerr.flush();
               exit(-1);
           }else if(!(len%2) && _t == count){
               cerr<<"kmers(::"<<len<<") length can not be even!"<<endl;
               cerr.flush();
               exit(-1);
           }
           _kmersLen = len;
       }
       void setFormat(file_format form) { _format = form;}
       void setStrategyToN(NStrategy stra) { this->_strategyToNs = stra;}
       void setMinOccurence(size_t min) { this->_minOccurence = min;}
       void setMaxOccurence(size_t max) { this->_maxOccurence = max;}
       void setThreads(size_t num)  { this->_nThreads = num;}
       void setMaxNumOfNs(size_t num) { this->_maxNumOfN = num;}
       size_t kmers_length() {return _kmersLen;}
       bool   isCodedBit() { return _isCodedBit;}
       size_t NumOfThreads() { return _nThreads;}
       int    strategy_toN() { return _strategyToNs;}
       bool   nohead() {return _noHeader;}
       size_t maximumOfNs() {return _maxNumOfN;}
       int    readFormat()  {return _format;}
       string inputPrefix() { return _inPutPrefix;}
       string outputPrefix() {return _outPutPrefix;}
       int    SampleWidth() {return _sampleWidth;}
       int    PositionWidth() {return _posWidth;}
       int    SubjectWidth() {
           return _subjectWidth;
       }
       void   setSampleWidth(int width){

           if(width > 3 || width < 0){
               cerr<<"This program only support sample number less or equal 8"<<endl;
               cerr.flush();
               exit(-1);
           }
           _sampleWidth = width;
        }
       void   setPositionWidth(int width){
           if(width > 10 || width < 0){
               cerr<<"This program only support reads whose length less than 10"<<endl;
               cerr.flush();
               exit(-1);
           }
           _posWidth = width;
       }
       void   setSubjectWidth(int width){
           if(width > 12 || width < 0){
               cerr<<"This program only support sample number less or equal 8"<<endl;
               cerr.flush();
               exit(-1);
           }
           _subjectWidth = width;
       }
       void setTask(Task o){
            this->_t = o;
       }
    public:
        size_t                   _kmersLen;          // the length of kmers
        bool                     _isCodedBit;        // is the reads and kmers coded into bitwise
        size_t                   _nThreads;          // # of threads enabled
        string                   _outPutPrefix;      // prefix of outfile
        string                   _inPutPrefix;       // prefix of inputfile
        string                   _tmpFileDir;
        file_format              _format;            //reads file format. two basic format: FQ,FA
        NStrategy                _strategyToNs;      //how to deal with Ns in reads
        bool                     _noHeader;          //if output the header in the outfile or not
        size_t                   _minOccurence;     //threshold that a kmers appear in the reads samples
        size_t                   _maxOccurence;     //the upperbound of frequency of any kmer
        bool                     _skip;             //whether skip those kmers appearance smaller than _minOccurence
        size_t                   _maxNumOfN;        //the maximum number of Ns in read
        size_t                   _approximateNumOfReads;  //the rough number of reads totally
        kmers_Delimitor          *_pDeli;
        int                       _sampleWidth;          //the bit wise length for sample ID info
        int                       _posWidth;            //the bitwise length for position info
        int                       _maxNumOfReads;       //the maximum number of reads that one thread can hold for each batch
        int                       _subjectWidth;       //the bitwise width of subject
        size_t                    _maxNumOfBatch;      //the maximum number of
        size_t                    _bufferSz;             //the buffer size in each thread
        size_t                    _maxSzOfSharedQue;    //the size of buffered shared queue;
        size_t                    _readsBlockSz;       //the size of each block size in the shared queue which feed the generater thread
        size_t                    _maxNumOfReadsQue;   //the maximum number of reads block in the input shared que
        size_t                    _NumOfTMgrThreads;   //the maximum number of threads enabled at the TMgr end
        size_t                    _NumOfDMgrThreads;   //the num of threads enabled at dmanager end
        size_t                    _NumOfkmerBytes;     //the number of byte that kmer written into the file
        UINT64                    _memThreashold;      //the upbound of memory usage for each data manager
        int                       _numOfFiles;         //the number of files for each sub range of datamanager
        size_t                    _checkingcycle;      //the checking cycle of memory
        Task                      _t;                   // traditional counting or differential
        vector<vector<string> >   _readsFiles;          //the reads file
};
} //namespace prefixMatching
#endif // KMERS_INITPARAM_H

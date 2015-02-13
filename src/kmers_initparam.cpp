#include "kmers_initparam.h"
using namespace prefixMatching;
namespace prefixMatching{
    kmers_InitParam::kmers_InitParam()
    {
        this->reset();
        this->_pDeli = kmers_Delimitor::getInstance();
    }
    kmers_InitParam::kmers_InitParam(size_t kmerslen, //the length of kmers
                                     size_t nThreads,
                                     bool coded){
        assert_geq(kmerslen,1);
        assert_geq(nThreads,1);
        this->_kmersLen = kmerslen;
        this->_nThreads = nThreads;
        this->_isCodedBit = coded;
        this->_pDeli = kmers_Delimitor::getInstance();
    }
    kmers_InitParam::kmers_InitParam(const kmers_InitParam& p){

        this->_approximateNumOfReads = p._approximateNumOfReads;
        this->_format                = p._format;
        this->_inPutPrefix           = p._inPutPrefix;
        this->_isCodedBit            = p._isCodedBit;
        this->_kmersLen              = p._kmersLen;
        this->_maxNumOfN             = p._maxNumOfN;
        this->_minOccurence          = p._minOccurence;
        this->_noHeader              = p._noHeader;
        this->_nThreads              = p._nThreads;
        this->_outPutPrefix          = p._outPutPrefix;
        this->_tmpFileDir            = p._tmpFileDir;
        this->_skip                  = p._skip;
        this->_strategyToNs          = p._strategyToNs;
        this->_pDeli                 = kmers_Delimitor::getInstance();
        this->_sampleWidth           = p._sampleWidth;
        this->_subjectWidth          = p._subjectWidth;
        this->_posWidth              = p._posWidth;
        this->_maxNumOfReads         = p._maxNumOfReads;
        this->_maxNumOfBatch         = p._maxNumOfBatch;      //the maximum number of
        this->_bufferSz              = p._bufferSz;
        this->_maxSzOfSharedQue      = p._maxSzOfSharedQue;
        this->_readsBlockSz          = p._readsBlockSz;
        this->_maxNumOfReadsQue      = p._maxNumOfReadsQue;
        this->_NumOfTMgrThreads      = p._NumOfTMgrThreads;
        this->_NumOfkmerBytes        = p._NumOfkmerBytes;
        this->_memThreashold         = p._memThreashold;
        this->_maxOccurence          = p._maxOccurence;
        this->_checkingcycle         = p._checkingcycle;
        this->_t                     = p._t;
    }
    string kmers_InitParam::classname(){
        return std::string("class::kmers_InitParam");
    }
    char* kmers_InitParam::encode(){

        char* buf = new char[BUFSIZE];

        sprintf(buf,"%c%lu%c%u%c%s%c%s%c%u%c%u%c%u%c%u%c%u%c%u%c%u%c%u%c%u%c%"\
                    "u%c%u%c%u%c%u%c%u%c%u%c%u%c%u%c%u%c%llu%c%u%c%s%c%u%c%u%c%d%c",
                        _pDeli->outsideDeli(),_kmersLen,
                        _pDeli->insideDeli(), _format,
                        _pDeli->insideDeli(),_inPutPrefix.c_str(),
                        _pDeli->insideDeli(),_outPutPrefix.c_str(),
                        _pDeli->insideDeli(),_maxNumOfN,
                        _pDeli->insideDeli(),_minOccurence,
                        _pDeli->insideDeli(),_nThreads,
                        _pDeli->insideDeli(),_skip,
                        _pDeli->insideDeli(),_strategyToNs,
                        _pDeli->insideDeli(),_isCodedBit,
                        _pDeli->insideDeli(),_approximateNumOfReads,
                        _pDeli->insideDeli(),_sampleWidth,
                        _pDeli->insideDeli(),_posWidth,
                        _pDeli->insideDeli(),_subjectWidth,
                        _pDeli->insideDeli(),_maxNumOfReads,
                        _pDeli->insideDeli(),_maxNumOfBatch,      //the maximum number of
                        _pDeli->insideDeli(),_bufferSz,
                        _pDeli->insideDeli(),_maxSzOfSharedQue,
                        _pDeli->insideDeli(),_readsBlockSz,
                        _pDeli->insideDeli(),_maxNumOfReadsQue,
                        _pDeli->insideDeli(),_NumOfTMgrThreads,
                        _pDeli->insideDeli(),_NumOfkmerBytes,
                        _pDeli->insideDeli(),_memThreashold,
                        _pDeli->insideDeli(),_NumOfDMgrThreads,
                        _pDeli->insideDeli(),_tmpFileDir.c_str(),
                        _pDeli->insideDeli(),_maxOccurence,
                        _pDeli->insideDeli(),_checkingcycle,
                        _pDeli->insideDeli(),_t,
                        _pDeli->outsideDeli());
        return buf;
    }
    void kmers_InitParam::decode(const char* src){

        if(!src){
            reset();
            return;
        }
        size_t pos = 0;
        string tmp;


        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_kmersLen);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_format);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        _inPutPrefix = tmp;
        tmp.clear();

        getCodedParam(src,pos,tmp);
        _outPutPrefix = tmp;
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_maxNumOfN);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_minOccurence);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_nThreads);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_skip);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_strategyToNs);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_isCodedBit);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_approximateNumOfReads);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_sampleWidth);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_posWidth);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_subjectWidth);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_maxNumOfReads);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_maxNumOfBatch);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_bufferSz);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),(size_t&)_maxSzOfSharedQue);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_readsBlockSz);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_maxNumOfReadsQue);
        tmp.clear();
        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_NumOfTMgrThreads);

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_NumOfkmerBytes);

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_memThreashold);

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_NumOfDMgrThreads);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        _tmpFileDir = tmp;
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_maxOccurence);
        tmp.clear();

        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),_checkingcycle);

        size_t s = 0;
        getCodedParam(src,pos,tmp);
        getParams(tmp.c_str(),s);
        this->_t = static_cast<Task>(s);
    }

} //namespace prefixMatching

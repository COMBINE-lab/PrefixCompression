#include "kmers_reads.h"

namespace prefixMatching{


/**
  * constructor for taskmanager use
*/

 kmers_Reads::kmers_Reads(const vector< vector<string> >& readFiles,int format){
     //check the format and the input files
    if(!this->InputFileCheck(readFiles,format)){
        throw 1;
    }
    this->_totalReads = 1;
    try{
        this->_pPatParams = new PatternParams(format,false,0,true,false,false,false,false,0,0,0,false);

    }catch(const exception& e){
        cerr<<e.what()<<endl;
        cerr.flush();
        exit(-1);
    }

    EList<string> mates1;
    EList<string> mates2;
    EList<string> mates12;
    EList<string> qualities1;
    EList<string> qualities2;
    //initialize the read sequence files
    for(size_t i = 0; i < readFiles[0].size(); i++){
        _queries.push_back(readFiles[0][i]);
    }
    if(format == FASTA && readFiles.size() > 1){
        for(size_t i = 0; i < readFiles[1].size(); i++){
            _qualities.push_back(readFiles[1][i]);
        }
    }
    this->_pPatt = PairedPatternSource::setupPatternSources(_queries,
                                                            mates1,
                                                            mates2,
                                                            mates12,
                                                            _qualities,
                                                            qualities1,
                                                            qualities2,
                                                            *(this->_pPatParams),true);

    if(NULL == this->_pPatt){
        cerr<<"invalid read source handler!"<<endl;
        throw 1;
    }
    _isDone = false;
}

 bool kmers_Reads::InputFileCheck(const vector< vector<string> >& readFiles,int format){

      if(readFiles.empty())
          return false;
      switch(format){
      case FASTA:

          if(readFiles.size() > 2){
              cerr<<"the input format is fasta, extra files are supplied! ";
              cerr.flush();
              return false;
          }
          else if(readFiles.size() == 2){
              if(readFiles[1].size() != readFiles[0].size()){
                  cerr<<"the quality files does not match the sequence files"<<endl;
                  cerr.flush();
                  return false;
              }
          }
          return true;
          break;

      case FASTQ:
          if(readFiles.size() != 1){
              cerr<<"the format of input reads file is fq, but the input files is not valid!"<<endl;
              cerr.flush();
              return false;
          }
          return true;
          break;

      default:{
          cerr<<"ppseq-kemrs does not support this kind of format!"<<endl;
          cerr.flush();
          return false;
      }
      }
  }

}//namespace prefixMatching

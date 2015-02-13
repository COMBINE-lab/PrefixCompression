#include <iostream>

#include "reorderdrive.h"

using namespace std;
using namespace prefixMatching;
/**
  * main process
*/
void drive(string readsfile,file_format format,string outprefix){

    vector<string> fq;

    fq.push_back(readsfile);

    std::shared_ptr<kmers_InitParam> param(new kmers_InitParam());
    param->_format = format;
    param->_readsFiles.push_back(fq);
    param->_outPutPrefix = outprefix;
    std::unique_ptr<reorderDrive> order(new reorderDrive(param));

    order->drive();
}

/**
*/
int main(int argc,char* argv[])
{

    assert(argc == 4);
    string readsfile(argv[1]);
    file_format format(static_cast<file_format>(atoi(argv[2])));

    string outprefix(argv[3]);
    drive(readsfile,format,outprefix);

    return 0;
}


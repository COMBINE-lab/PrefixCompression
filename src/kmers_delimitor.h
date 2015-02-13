#ifndef KMERS_DELIMITOR_H
#define KMERS_DELIMITOR_H
#include "suffix_commons.h"
#include "memory"
namespace prefixMatching{
/**
 * signleton class that holds the delimitor
 * for encoding and decoding
 * the first element in the inside deli
 * the second element is the outside delim
 *
*/

    class kmers_Delimitor
    {
        public:
            static kmers_Delimitor* getInstance();
            char  insideDeli();
            char  outsideDeli();
            virtual string classname();
        protected:
            kmers_Delimitor();
            kmers_Delimitor(kmers_Delimitor const&){}
            void init();
        private:
            char _delimitor[2];
            static kmers_Delimitor *_ins;

    };
} //namespace prefixMatching
#endif // KMERS_DELIMITOR_H

#include "reorderdrive.h"

namespace prefixMatching{
reorderDrive::reorderDrive(std::shared_ptr<kmers_InitParam>& params):_params(params)
{
    this->init();
}
}

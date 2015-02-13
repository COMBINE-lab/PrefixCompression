#include "node.h"
namespace prefixMatching{
Node::Node(int id):_id(id),_depth(0),
                    _parent(0)
                    ,_next(0),
                    _isBranch(0)
{
    memset(this->_child,0,4*sizeof(Node*));
    _next = 0;
    _isBranch = 0;
}
}

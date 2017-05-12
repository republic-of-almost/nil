#ifndef LOGIC_INCLUDED_AC052605_9926_4B8E_BFAC_06B52EA74A5C
#define LOGIC_INCLUDED_AC052605_9926_4B8E_BFAC_06B52EA74A5C


#include <nil/fwd.hpp>
#include <stdint.h>


namespace Nil {
namespace Data {



struct Logic
{
  uint32_t      type;
  uint32_t      logic_id;
  
  uintptr_t     aux_01;
  uintptr_t     aux_02;
};


void
get(const Node &node, Logic &out);


void
set(Node &node, const Logic &in);


bool
has_logic(const Node &node);


uint64_t
get_type_id(const Logic &in);


} // ns
} // ns


#endif // inc guard

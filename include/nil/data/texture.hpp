#ifndef TEXTURE_INCLUDED_3AAFC685_6398_4FDE_97FA_B986DAE84797
#define TEXTURE_INCLUDED_3AAFC685_6398_4FDE_97FA_B986DAE84797


#include <nil/fwd.hpp>
#include <stdint.h>


namespace Nil {
namespace Data {


struct Texture {

  uint32_t texture_id;

};


void
get(const Node &node, Texture &out);


void
set(Node &node, const Texture &in);


bool
has_texture(const Node &node);


uint64_t
get_type_id(const Texture &in);


} // ns
} // ns


#endif // inc guard

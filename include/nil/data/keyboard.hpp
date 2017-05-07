#ifndef KEYBOARD_INCLUDED_7F779786_CB96_43BB_97F1_188BF322F487
#define KEYBOARD_INCLUDED_7F779786_CB96_43BB_97F1_188BF322F487


#include <nil/fwd.hpp>
#include <stdint.h>


namespace Nil {
namespace Data {


struct Keyboard
{
  uint32_t id;
  
  uintptr_t key_state; // Unsure atm
};


void
get(const Node &node, Keyboard &out);


void
set(Node &node, const Keyboard &in);


bool
has_keyboard(const Node &node);


uint64_t
get_type_id(const Keyboard &in);


} // n
} // ns


#endif // inc guard

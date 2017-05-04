#ifndef NIL_INCLUDED_AF3E5C57_06A2_419B_A843_2745F0D6F2D0
#define NIL_INCLUDED_AF3E5C57_06A2_419B_A843_2745F0D6F2D0


#include <nil/fwd.hpp>
#include <stdint.h>
#include <stddef.h>


namespace Nil {


constexpr uint32_t version = 0;


class Engine final
{
public:

  explicit
  Engine();
  
  
  ~Engine();
  
  
  void
  add_aspect(Nil::Aspect *aspect);
  
  
  void
  remove_aspect(Nil::Aspect *aspect);
  
  
  size_t
  aspect_count() const;
  
  
  bool
  run();
  

private:


  struct Impl;
  Impl *m_impl;

};


} // ns


#endif // inc guard

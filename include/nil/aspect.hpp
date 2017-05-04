#ifndef ASPECT_INCLUDED_CAAB0E57_5E24_4643_9C26_95880895F3B4
#define ASPECT_INCLUDED_CAAB0E57_5E24_4643_9C26_95880895F3B4


#include <nil/fwd.hpp>
#include <stddef.h>
#include <stdint.h>


namespace Nil {


class Aspect
{
public:

  explicit Aspect();
  virtual ~Aspect();
  
  
  // ---------------------------------------------------------- [ Interface ] --
  
  
  virtual void startup() {}
  virtual void node_events(const Node_event node_events[], const size_t count) {}
  virtual void early_think(const float dt) {}
  virtual void think(const float dt) {}
  virtual void late_think(const float dt) {}
  virtual void shutdown() {}
  
  
  // ----------------------------------------------- [ Public State Getters ] --
  
  
  bool
  get_quit_signal() const;
  
  const uint32_t*
  get_registered_types() const;
  
  size_t
  get_registered_type_count() const;
  
  
protected:


  // ------------------------------------ [ Private State Getters / Setters ] --


  void
  register_data_type(const uint32_t data_type);
  
  void
  unregister_data_type(const uint32_t data_type);
  
  Node&
  get_root_node();
  
  const Node&
  get_root_node() const;
  
  void
  set_quit_signal();
  
private:

  struct Impl;
  Impl *m_impl;

};


} // ns


#endif // inc guard

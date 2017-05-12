#ifndef ASPECT_INCLUDED_CAAB0E57_5E24_4643_9C26_95880895F3B4
#define ASPECT_INCLUDED_CAAB0E57_5E24_4643_9C26_95880895F3B4


#include <nil/fwd.hpp>
#include <stddef.h>
#include <stdint.h>
#include <utilities/array.hpp>
#include <vector>


namespace Nil {


/*
  Callback prototypes.
*/
using aspect_startup_fn     = void(*)(Engine &engine, Aspect &aspect);
using aspect_node_events_fn = void(*)(Engine &engine, Aspect &aspect, Event_list &event_list);
using aspect_early_think_fn = void(*)(Engine &engine, Aspect &aspect);
using aspect_think_fn       = void(*)(Engine &engine, Aspect &aspect);
using aspect_late_think_fn  = void(*)(Engine &engine, Aspect &aspect);
using aspect_shutdown_fn    = void(*)(Engine &engine, Aspect &aspect);
using aspect_ui_window      = void(*)(Engine &engine, Aspect &aspect);
using aspect_ui_menu        = void(*)(Engine &engine, Aspect &aspect);

// --

struct Aspect
{
  aspect_startup_fn         start_up_fn;
  aspect_node_events_fn     events_fn;
  aspect_early_think_fn     early_think_fn;
  aspect_think_fn           think_fn;
  aspect_late_think_fn      late_think_fn;
  aspect_shutdown_fn        shutdown_fn;
  aspect_ui_window          ui_window_fn;
  aspect_ui_menu            ui_menu_fn;
  
  bool                      want_to_quit;
  
//  lib::array<uint64_t, 16>  data_types;
  std::vector<uint64_t>      data_types;
  
  uintptr_t                 user_data;
};



//
//
//
//namespace Aspect {
//
//
///*
//  Controller.
//*/
//struct Controller
//{
//  aspect_startup_fn     startup_fn;
//  aspect_node_events_fn node_events_fn;
//  aspect_early_think_fn early_think_fn;
//  aspect_think_fn       think_fn;
//  aspect_late_think_fn  late_think_fn;
//  aspect_shutdown_fn    shutdown_fn;
//
//  uintptr_t user_data;
//};
//
//
//
//void
//set(Nil::Engine &engine, Aspect::Controller &controller);
//
//
//void
//register_data_type(Nil::Engine &engine, Aspect::Controller &controller, const uint32_t data_id);
//
//
//} // ns


//class Aspect
//{
//public:
//
//  explicit Aspect();
//  virtual ~Aspect();
//  
//  
//  // ---------------------------------------------------------- [ Interface ] --
//  
//  
//  virtual void startup() {}
//  virtual void node_events(const Node_event node_events[], const size_t count) {}
//  virtual void early_think(const float dt) {}
//  virtual void think(const float dt) {}
//  virtual void late_think(const float dt) {}
//  virtual void shutdown() {}
//  
//  
//  // ----------------------------------------------- [ Public State Getters ] --
//  
//  
//  bool
//  get_quit_signal() const;
//  
//  const uint32_t*
//  get_registered_types() const;
//  
//  size_t
//  get_registered_type_count() const;
//  
//  
//protected:
//
//
//  // ------------------------------------ [ Private State Getters / Setters ] --
//
//  friend class Nil::Engine;
//
//  void
//  register_data_type(const uint32_t data_type);
//  
//  void
//  unregister_data_type(const uint32_t data_type);
//  
//  Node&
//  get_root_node();
//  
//  const Node&
//  get_root_node() const;
//  
//  void
//  set_quit_signal();
//  
//  Nil::Engine*
//  get_engine() const;
//  
//  void
//  set_engine(Nil::Engine *engine);
//  
//private:
//
//  struct Impl;
//  Impl *m_impl;
//
//};


} // ns


#endif // inc guard

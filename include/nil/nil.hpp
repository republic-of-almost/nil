#ifndef NIL_INCLUDED_AF3E5C57_06A2_419B_A843_2745F0D6F2D0
#define NIL_INCLUDED_AF3E5C57_06A2_419B_A843_2745F0D6F2D0


#include <nil/fwd.hpp>
#include <stdint.h>
#include <stddef.h>


namespace Nil {


constexpr uint32_t version = 0;


struct Engine_settings
{
  bool pause_node_events;
  bool disable_tasks;
};


struct Engine_state
{
  // Events
  Node_event*   node_events;
  size_t        node_event_count;
  
  // Data Count
  size_t        node_count;
  size_t        bounding_box_count;
  size_t        camera_count;
  size_t        collider_count;
  size_t        developer_count;
  size_t        gamepad_count;
  size_t        keyboard_count;
  size_t        light_count;
  size_t        material_count;
  size_t        mesh_count;
  size_t        mouse_count;
  size_t        resouce_count;
  size_t        rigidbody_count;
  size_t        texture_count;
  size_t        transform_count;
  size_t        window_count;
};


class Engine final
{
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

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
  
  
  void
  set_settings(const Engine_settings &in);
  
  
  void
  get_settings(Engine_settings &out);
  
  
  void
  get_state(Engine_state &out);
  

private:


  struct Impl;
  Impl *m_impl;

};


} // ns


#endif // inc guard

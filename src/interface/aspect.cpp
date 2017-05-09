#include <nil/aspect.hpp>
#include <nil/nil.hpp>
#include <data/data.hpp>
#include <utilities/array.hpp>
#include <utilities/logging.hpp>


//namespace Nil {
//namespace Aspect {
//
//
//void
//set(Nil::Engine &engine, Aspect::Controller &controller)
//{
//  engine.add_aspect(&controller);
//}
//
//
//void
//register_data_type(Nil::Engine &engine, Aspect::Controller &controller, const uint32_t data_id)
//{
//  
//}
//
//
//} // ns
//} // ns




namespace Nil {


struct Aspect::Impl
{
  bool wants_to_quit;
  lib::array<uint32_t, 8> registered_type_ids;
};


Aspect::Aspect()
: m_impl(new Impl)
{
  m_impl->wants_to_quit = false;
}


Aspect::~Aspect()
{
  delete m_impl;
  m_impl = nullptr;
}


// ------------------------------------------------- [ Public State Getters ] --


bool
Aspect::get_quit_signal() const
{
  return m_impl->wants_to_quit;
}


const uint32_t*
Aspect::get_registered_types() const
{
  return m_impl->registered_type_ids.data();
}


size_t
Aspect::get_registered_type_count() const
{
  return m_impl->registered_type_ids.size();
}


// -------------------------------------- [ Private State Getters / Setters ] --


void
Aspect::register_data_type(const uint32_t data_type)
{
  // Check if its already been added.
  for(uint32_t &id : m_impl->registered_type_ids)
  {
    if(id == data_type)
    {
      LOG_WARNING("Type already registered");
      return;
    }
  }
  
  m_impl->registered_type_ids.emplace_back(data_type);
}


void
Aspect::unregister_data_type(const uint32_t data_type)
{
  for(size_t i = 0; i < m_impl->registered_type_ids.size(); ++i)
  {
    if(m_impl->registered_type_ids[i] == data_type)
    {
      m_impl->registered_type_ids.erase(i);
      return;
    }
  }
  
  LOG_WARNING("Type not registered");
}


Node&
Aspect::get_root_node()
{
  return Data::get_root_node();
}


const Node&
Aspect::get_root_node() const
{
  return Data::get_root_node();
}


void
Aspect::set_quit_signal()
{
  m_impl->wants_to_quit = true;
}


} // ns

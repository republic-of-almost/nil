#include <nil/nil.hpp>
#include <nil/node.hpp>
#include <nil/node_event.hpp>
#include <nil/aspect.hpp>
#include <data/data.hpp>
#include <graph/graph.hpp>
#include <graph/graph_data.hpp>
#include <utilities/array.hpp>
#include <utilities/assert.hpp>


namespace Nil {


struct Engine::Impl
{
  lib::array<Aspect*, 16> aspects;
};


Engine::Engine()
: m_impl(new Impl)
{
  LIB_ASSERT(m_impl);
  
  if(!m_impl)
  {
    LOG_ERROR_ONCE("Engine is in corrupted state.");
    return;
  }
}


Engine::~Engine()
{
  delete m_impl;
  m_impl = nullptr;
}


void
Engine::add_aspect(Nil::Aspect *aspect)
{
  LIB_ASSERT(aspect);
  LIB_ASSERT(m_impl);
  
  if(!m_impl)
  {
    LOG_ERROR_ONCE("Engine is in corrupted state.");
    return;
  }
  
  // Search to see if its in already
  for(Aspect *asp : m_impl->aspects)
  {
    if(asp == aspect)
    {
      LOG_WARNING("Already added this aspect");
      return;
    }
  }
  
  // Add to list.
  m_impl->aspects.emplace_back(aspect);
}


void
Engine::remove_aspect(Nil::Aspect *aspect)
{
  LIB_ASSERT(aspect);
  LIB_ASSERT(m_impl);
  
  if(!m_impl)
  {
    LOG_ERROR_ONCE("Engine is in corrupted state.");
    return;
  }

  // Search to see if its in already
  for(size_t i = 0; i < m_impl->aspects.size(); ++i)
  {
    if(m_impl->aspects[i] == aspect)
    {
      m_impl->aspects.erase(i);
      return;
    }
  }
  
  LOG_WARNING("Can't find aspect to remove.")
}


size_t
Engine::aspect_count() const
{
  LIB_ASSERT(m_impl);
  
  if(!m_impl)
  {
    LOG_ERROR_ONCE("Engine is in corrupted state.");
    return false;
  }

  return m_impl->aspects.size();
}


bool
Engine::run()
{
  LIB_ASSERT(m_impl);
  
  if(!m_impl)
  {
    LOG_ERROR_ONCE("Engine is in corrupted state.");
    return false;
  }
  
 
  // Distro Events
  {
    std::vector<Node_event> nodes;
  
    for(Aspect *asp : m_impl->aspects)
    {
      const size_t count = asp->get_registered_type_count();
      const uint32_t *reged_ids = asp->get_registered_types();
      
      nodes.clear();
      
      for(size_t i = 0; i < count; ++i)
      {
        uint32_t data_id = reged_ids[i];
        
        for(size_t j = 0; j < Data::get_graph_data()->node_events.size(); ++j)
        {
          const Node event_node(Data::get_graph_data()->node_events[j].node_id, false);
        
          if(data_id & event_node.get_data_type_id())
          {
            const uint32_t actions = Data::get_graph_data()->node_events[j].event_action;
          
            nodes.emplace_back(Node_event{actions, event_node});
          }
        }
      }
      
      asp->node_events(nodes.data(), nodes.size());
      
      // Get list of registered type ids
      // Build list of changes.
      // send to aspect event handler.
    }
    
    Graph::think(Data::get_graph_data());
    
//    Data::get_graph_data()->node_events.clear();
  }
  
  
  
  // Thinking
  {
    for(Aspect *asp : m_impl->aspects)
    {
      asp->early_think(0.16);
    }
    
    // Think
    for(Aspect *asp : m_impl->aspects)
    {
      asp->think(0.16);
    }
    
    // Late Think
    for(Aspect *asp : m_impl->aspects)
    {
      asp->late_think(0.16);
    }
  }
  
  /*
    Check to see if any aspects are ready to quit.
  */
  {
    bool should_quit = false;
    
    for(Aspect *asp : m_impl->aspects)
    {
      should_quit |= asp->get_quit_signal();
    }

    return !should_quit;
  }
}


void
Engine::set_settings(const Engine_settings &in)
{
}


void
Engine::get_settings(Engine_settings &out)
{
}


void
Engine::get_state(Engine_state &out)
{
}


} // ns

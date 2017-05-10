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
  Engine_settings settings;
  std::vector<Node_event> pending_events;
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
  
  m_impl->settings.pause_node_events = false;
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
  aspect->set_engine(this);
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
 
  /*
    Create list of events
  */
  {
    m_impl->pending_events.clear();
    
    Graph::Data *graph = Data::get_graph_data();
    LIB_ASSERT(graph);
  
    for(size_t j = 0; j < graph->node_events.size(); ++j)
    {
      m_impl->pending_events.emplace_back(
        Node_event{
          Node(graph->node_events[j].node_id, false),
          graph->node_events[j].event_action
        }
      );
    }
  }
 
  // Distro Events
  if(!m_impl->settings.pause_node_events)
  {
    std::vector<Node_event> nodes;
  
    for(Aspect *asp : m_impl->aspects)
    {
      for(size_t j = 0; j < Data::get_graph_data()->node_events.size(); ++j)
      {
        const Node event_node(Data::get_graph_data()->node_events[j].node_id, false);
       
        const size_t count = asp->get_registered_type_count();
        const uint32_t *reged_ids = asp->get_registered_types();
        
        for(size_t i = 0; i < count; ++i)
        {
          const uint32_t data_id = reged_ids[i];
          
          if(data_id & event_node.get_data_type_id())
          {
            const uint32_t actions = Data::get_graph_data()->node_events[j].event_action;
          
            nodes.emplace_back(Node_event{event_node, actions});
            break;
          }
        }
      }

      
//      const size_t count = asp->get_registered_type_count();
//      const uint32_t *reged_ids = asp->get_registered_types();
//      
//      nodes.clear();
//      
//      for(size_t i = 0; i < count; ++i)
//      {
//        uint32_t data_id = reged_ids[i];
//        
//        for(size_t j = 0; j < Data::get_graph_data()->node_events.size(); ++j)
//        {
//          const Node event_node(Data::get_graph_data()->node_events[j].node_id, false);
//        
//          if(data_id & event_node.get_data_type_id())
//          {
//            const uint32_t actions = Data::get_graph_data()->node_events[j].event_action;
//          
//            nodes.emplace_back(Node_event{event_node, actions});
//            break;
//          }
//        }
//      }
    
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
  m_impl->settings = in;
}


void
Engine::get_settings(Engine_settings &out)
{
  out = m_impl->settings;
}


void
Engine::get_state(Engine_state &out)
{
  const Graph::Data *graph = Data::get_graph_data();
  const Graph::Component_data *data = &graph->component_data;
  
  /*
    Events
  */
  out.node_events = m_impl->pending_events.data();
  out.node_event_count  = m_impl->pending_events.size();
  
  /*
    Set the count of things.
  */
  out.node_count              = Graph::node_descendants_count(graph, 0);
  out.bounding_box_count      = out.node_count;
  out.camera_count            = data->camera_node_id.size();
  out.collider_count          = data->collider_node_id.size();
  out.developer_count         = data->developer_node_id.size();
  out.gamepad_count           = data->gamepad_node_id.size();
  out.graphics_count          = data->graphics_node_id.size();
  out.keyboard_count          = data->keyboard_node_id.size();
  out.light_count             = data->light_node_id.size();
  out.logic_count             = data->logic_node_id.size();
  out.material_count          = data->material_node_id.size();
  out.mesh_count              = data->mesh_node_id.size();
  out.mesh_resource_count     = data->mesh_resource_node_id.size();
  out.mouse_count             = data->mouse_node_id.size();
  out.resouce_count           = data->resource_node_id.size();
  out.rigidbody_count         = data->rigidbody_node_id.size();
  out.texture_count           = data->texture_node_id.size();
  out.texture_resource_count  = data->texture_resource_node_id.size();
  out.transform_count         = out.node_count;
  out.window_count            = data->window_node_id.size();
}


} // ns
